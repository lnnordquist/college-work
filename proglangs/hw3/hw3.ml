module SS = Set.Make(String)

open List
open Char
open Format

exception Not_implemented
exception Parse_exn
exception CaptureException of string

(* Data Definitions *)

type token
= LParen
| RParen
| TokLam
| TokDot
| TokVar of string

type term
= TmVar of string
| TmAbs of string * term
| TmApp of term * term

(* Utilities *) 

(* Strings in ocaml are not represented as lists of characters. For lexing and parsing purposes, it's easier to work
with lists of characters. You shouldn't need to touch these functions that convert between the two, but feel free to use them for debugging. *)
let string_to_char_list (s: string) : char list =
  s |> String.to_seq |> List.of_seq
  
let char_list_to_string (cl: char list) : string =
  cl |> List.to_seq |> String.of_seq
  
(* Lexical Scanner *)

(* nextToken should return the next token from a list of characters, along with the characters thereafter
   - return None if the list of chars is empty
   - skip whitespace characters
   - throw an exception if the characters cannot be tokenized *)

(* I couldn't get the Char module to work, so I had to hard code with ASCII*)

let rec string_detect (cs: char list) (acc: char list) =
  match cs with
  | [] -> Some(TokVar(char_list_to_string acc),[])
  | ' '::rest -> Some(TokVar(char_list_to_string acc),' '::rest)
  | '('::rest -> Some(TokVar(char_list_to_string acc),'('::rest)
  | ')'::rest -> Some(TokVar(char_list_to_string acc),')'::rest)
  | '&'::rest -> Some(TokVar(char_list_to_string acc),'&'::rest)
  | '.'::rest -> Some(TokVar(char_list_to_string acc),'.'::rest)
  | c1::rest -> 
    let c = int_of_char c1 in 
                if ((c>=(int_of_char '0'))&&(c <= (int_of_char '9')))
                || ((c>=(int_of_char 'A'))&&(c<=(int_of_char 'Z')))
                || ((c>=(int_of_char 'a'))&&(c<=(int_of_char 'z')))
                || (c==(int_of_char ' '))
                then 
    string_detect rest (acc @ [c1])
                else raise Parse_exn;;

(* string_detect (nextToken "&") [];; *)

let rec nextToken (cs: char list) : (token * char list) option = 
  match cs with
  | [] -> None
  | ' '::rest -> nextToken(rest)
  | '('::rest -> Some (LParen,rest)
  | ')'::rest -> Some (RParen,rest)
  | '&'::rest -> Some (TokLam,rest)
  | '.'::rest -> Some (TokDot,rest)
  | _ -> string_detect cs [];;

(* turn a string of code (like "&x.x" into a list of tokens (like [TokLam, TokVar("x"), TokDot, TokVar("x")]) *)
let rec scan (ls : char list) : token list = 
  match nextToken ls with
  | None -> []
  | Some (tok, list) -> tok::(scan list)
  | _ -> raise Parse_exn;;

(* Parser *)

(* nextTerm should return the next term from a list of tokens, along with the tokens thereafter
   - return None if the list of tokens is empty
   - throw an exception if the characters cannot be tokenized *)
let rec nextTerm (ts: token list) : (term * token list) option =
  match ts with
  | [] -> None
  | LParen::rest -> 
    (match nextTerm(rest) with
    | Some (t1, RParen::LParen::r1) -> 
      (match nextTerm(r1) with
      | Some (t2, RParen::r2) -> Some(TmApp(t1, t2),r2)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | (TokVar str)::rest -> Some (TmVar str,rest)
  | TokLam::(TokVar str)::TokDot::rest -> 
    (match nextTerm rest with
    | Some (tok,rest) -> Some(TmAbs(str,tok), rest)
    | _ -> raise Parse_exn)
  | _ -> raise Parse_exn;;
  

(* turn a list of tokens (like [TokLam, TokVar of "x", TokDot, TokVar of "x"] into a term (like TmAbs ("x", TmVar("x"))) *)
let parse (tokens : token list) : term = 
  match nextTerm tokens with
  | Some (term, []) -> term
  | _ -> raise Parse_exn;;

(* Substitution *)

(* Implement the substitution function `[x |-> s] t` discussed in class. 
   If substitution would result in variable capture, simply 
   raise a CaptureException (with the message string of your choice). *)

(* Get the free variables of t as a string set . *)

let rec fv (t:term) : SS.t =
  match t with
  | TmVar str -> SS.singleton str
  | TmAbs (y,x) -> SS.diff (fv x) (SS.singleton y)
  | TmApp (t1,t2) -> SS.union (fv t1) (fv t2);;

let rec subst (x : string) (s : term) (t : term) : term = 
  match t with
  | TmVar y -> 
   ( match y with
    | _ when y = x -> s
    | _ -> t)
  | TmAbs (y, t1) -> 
    (match y with
    | _ when y = x -> t
    | _ when (SS.mem y (fv s)) -> raise (CaptureException "error")
    | _ -> TmAbs(y, (subst x s t1)))
  | TmApp (t1, t2) -> TmApp ((subst x s t1), (subst x s t2));;
  

(* Small-step evaluation *)

(* Implement the small-step evaluation relations from class. 
   We will implement both variants from class: call-by-name and
   call-by-value. 
   We will also implement a third approach: Full beta reduction,
   which reduces terms under a lambda. 
   Return none if a term doesn't step. *)
let rec cbn (t : term) : term option = 
  match t with
  | TmApp(t1, t2) ->
    (match t1 with 
    | (TmApp(t11, t21)) -> 
      (match (cbn t1) with
      | Some t3 -> Some(TmApp(t3,t2))
      | None -> None)
    | (TmAbs(y, x)) -> Some(subst y t2 x)
    | _ -> None)
  | _ -> None;;

let rec cbv (t : term) : term option = 
  match t with
  | TmApp(t1, t2) ->
    (match t1 with 
    | (TmApp(t11, t21)) -> 
      (match (cbv (TmApp(t11, t21))) with
      | Some t3 -> Some(TmApp(t3,t2))
      | None -> None)
    | (TmAbs(y, x)) -> 
     (match t2 with 
      | (TmApp(t3, t4)) ->
        (match (cbv t2) with
        | Some t -> Some(TmApp((TmAbs(y, x)),t))
        | None -> None)
      | (TmAbs(t3, t4)) -> Some(subst y (TmAbs(t3, t4)) x)
      | _ -> None)
    | _ -> None)
  | _ -> None;;

let rec beta (t : term) : term option = 
  match t with
  | TmAbs(t1,t2) -> 
    (match beta t2 with
    | Some t3 -> Some(TmAbs(t1,t3))
    | None -> None)
  | TmApp(t1, t2) ->
    (match t1 with 
    | TmAbs(x,y) -> Some(subst x t2 y)
    | _ -> 
      (match beta t1 with
      | Some t3 -> Some(TmApp(t3,t2))
      | None -> 
        match beta t2 with
        | Some t4 -> Some(TmApp(t1,t4))
        | None -> None))
  | _ -> None;;

(* Given an evaluation strategy above and a term t, return t' 
  such that t ->* t' and t' is a normal form for the given evaluation 
  strategy. *)
let rec multistep (strat : term -> term option) (t : term) : term = 
  match (strat t) with
  | Some t1 -> multistep strat t1
  | None -> t;;

(* Define the boolean terms true and false as given in class.
  (We'll use the book's `tru` and `fls` to avoid notation clashes.)
   Define a lambda term that implements an `xor` operation on bools. *)

let rec tru : term = TmAbs("t", TmAbs("f", TmVar("t")));;

let rec fls : term = TmAbs("t", TmAbs("f", TmVar("f")));;

let rec not : term = TmApp(TmVar("x"),TmApp(fls, tru));;

let rec xor : term = TmAbs("a",(TmAbs("b",(TmApp((TmApp(not,TmVar("b"))),TmVar("b"))))));;

(* Interpreter *)

(* You should not need to modify this code -- feel free to add statements for debugging,
   but remember to delete them before submitting. *)

let rec term_to_string (t : term) : string = match t with
| TmVar(str) -> str
| TmAbs(var, body) -> "&" ^ var ^ "." ^ (term_to_string body)
| TmApp(t1, t2) -> "(" ^ (term_to_string t1) ^ ") (" ^ (term_to_string t2) ^ ")"

let opt_term_to_string (o : term option) : string = 
  match o with
  | None -> " "
  | Some t -> term_to_string t 

  let interpret (str : string) : unit =
    let chars = string_to_char_list str in
    let tokens = scan chars in
    let ast = parse tokens in
    let term_str = term_to_string ast in
    let _ = print_endline ("----- Call by Name Evaluation -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline ("->    " ^ (opt_term_to_string (cbn ast))) in
    let _ = print_endline "" in
    let _ = print_endline "-----------------------------------" in
    let _ = print_endline "" in
    let _ = print_endline ("----- Call by Name Multistep Evaluation -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline ("->    " ^ (term_to_string (multistep cbn ast))) in
    let _ = print_endline "" in
    let _ = print_endline "-----------------------------------" in
    let _ = print_endline "" in
    let _ = print_endline ("----- Call by Value Evaluation -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline ("->    " ^ (opt_term_to_string (cbv ast))) in
    let _ = print_endline "" in
    let _ = print_endline "-----------------------------------" in
    let _ = print_endline "" in
    let _ = print_endline ("----- Call by Value Multistep Evaluation -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline ("->    " ^ (term_to_string (multistep cbv ast))) in
    let _ = print_endline "" in
    let _ = print_endline "-----------------------------------" in
    let _ = print_endline "" in
    let _ = print_endline ("----- Full Beta Evaluation -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline ("->    " ^ (opt_term_to_string (beta ast))) in
    let _ = print_endline "" in
    let _ = print_endline "-----------------------------------" in
    let _ = print_endline "" in
    let _ = print_endline ("----- Full Beta Multistep Evaluation -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline ("->    " ^ (term_to_string (multistep beta ast))) in
    print_endline "";;


interpret Sys.argv.(1)
