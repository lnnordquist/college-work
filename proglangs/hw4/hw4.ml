module SS = Set.Make(String)

open List
open Char
open Format

exception Not_implemented
exception Parse_exn
exception NotAbs of string
exception NotFound of string
exception DuplicateVar of string

(* Data Definitions *)

type token
= LParen
| RParen
| TokLam
| TokDot
| TokVar of string
| TokIf 
| TokThen
| TokElse
| TokZero
| TokSucc
| TokPred
| TokIsZero
| TokColon
| TokBool
| TokNat
| TokArrow
| TokTrue
| TokFalse

type typ 
= TBool
| TNat 
| TFun of typ * typ

type term
= TmVar of string
| TmAbs of string * typ * term
| TmApp of term * term
| TmTrue 
| TmFalse 
| TmZero
| TmIf of term * term * term
| TmSucc of term
| TmPred of term
| TmIsZero of term

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
   - skip whitespace characters (except inside strings)
   - throw an exception if the characters cannot be tokenized *)

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
                  (match acc with
                  | [] -> 
                    if ((c>=(int_of_char 'A'))&&(c<=(int_of_char 'Z')))
                      || ((c>=(int_of_char 'a'))&&(c<=(int_of_char 'z')))
                    then string_detect rest (acc @ [c1])
                    else raise Parse_exn
                  | _ -> string_detect rest (acc @ [c1]))
                else raise Parse_exn;;

let rec nextToken (cs: char list) : (token * char list) option = 
  match cs with
  | [] -> None
  | ' '::rest -> nextToken(rest)
  | '('::rest -> Some (LParen,rest)
  | ')'::rest -> Some (RParen,rest)
  | '&'::rest -> Some (TokLam,rest)
  | '.'::rest -> Some (TokDot,rest)
  | 'I'::'f'::rest -> Some(TokIf,rest)
  | 'T'::'h'::'e'::'n'::rest-> Some(TokThen,rest)
  | 'E'::'l'::'s'::'e'::rest-> Some(TokElse,rest)
  | '0'::rest-> Some(TokZero,rest)
  | 'S'::'u'::'c'::'c'::rest -> Some(TokSucc,rest)
  | 'P'::'r'::'e'::'d'::rest -> Some(TokPred,rest)
  | 'I'::'s'::'Z'::'e'::'r'::'o'::rest -> Some(TokIsZero,rest)
  | ':'::rest -> Some(TokColon,rest)
  | 'B'::'o'::'o'::'l'::rest -> Some(TokBool,rest)
  | 'N'::'a'::'t'::rest -> Some(TokNat,rest)
  | '-'::'>'::rest -> Some(TokArrow,rest)
  | 'T'::'r'::'u'::'e'::rest -> Some(TokTrue,rest)
  | 'F'::'a'::'l'::'s'::'e'::rest -> Some(TokFalse,rest)
  | _ -> string_detect cs [];;

(* turn a string of code (like "&x:Bool.x" into a list of tokens (like [TokLam, TokVar("x"), TokColon, TokBool, TokDot, TokVar("x")]) *)
let rec scan (ls : char list) : token list = 
  match nextToken ls with
  | None -> []
  | Some (tok, list) -> tok::(scan list)
  | _ -> raise Parse_exn;;

(* Parser *)

(* nextTerm should return the next term from a list of tokens, along with the tokens thereafter
   - return None if the list of tokens is empty
   - throw an exception if the characters cannot be tokenized *)

let rec typ_getter ts = 
  match ts with
  | [] -> None
  | TokBool::rest -> 
    (match rest with
    | TokArrow::r1 ->
      (match typ_getter r1 with
      | Some (typ,r2) -> Some(TFun(TBool,typ),r2)
      | _ -> raise Parse_exn)
    | _ -> Some(TBool,rest))
  | TokNat::rest -> 
    (match rest with
    | TokArrow::r1 ->
      (match typ_getter r1 with
      | Some (typ,r2) -> Some(TFun(TNat,typ),r2)
      | _ -> raise Parse_exn)
    | _ -> Some(TNat,rest))
  | LParen::rest -> 
    (match typ_getter rest with
    | Some(typ1, RParen::TokArrow::r1) ->
      (match typ_getter r1 with
      | Some (typ2,r2) -> Some(TFun(typ1,typ2),r2)
      | _ -> None)
    | _ -> None)
  | _ -> None;;

let rec nextTerm (ts: token list) : (term * token list) option = 
  match ts with
  | [] -> None
  | TokTrue::rest -> Some(TmTrue,rest) 
  | TokFalse::rest -> Some(TmFalse,rest)
  | TokZero::rest -> Some(TmZero,rest)
  | (TokVar str)::rest -> Some (TmVar str,rest)
  | LParen::rest -> 
    (match nextTerm(rest) with
    | Some (t1, RParen::LParen::r1) -> 
      (match nextTerm(r1) with
      | Some (t2, RParen::r2) -> Some(TmApp(t1, t2),r2)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokLam::(TokVar str)::TokColon::rest ->
    (match typ_getter rest with
    | Some(typ,TokDot::r1) ->
      (match nextTerm r1 with
      | Some(tm,r2) -> Some(TmAbs(str,typ,tm),r2)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokIf::r1 ->
    (match nextTerm r1 with
    | Some(t1, TokThen::r2) -> 
      (match nextTerm r2 with
      | Some(t2,TokElse::r3) ->
        (match nextTerm r3 with
        | Some(t3,rest) -> Some(TmIf(t1,t2,t3),rest)
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokSucc::rest ->
    (match nextTerm rest with
    | Some(tm,rest) -> Some((TmSucc tm),rest)
    | _ -> raise Parse_exn)
  | TokPred::rest ->
    (match nextTerm rest with
    | Some(tm,rest) -> Some((TmPred tm),rest)
    | _ -> raise Parse_exn)
  | TokIsZero::rest -> 
    (match nextTerm rest with
    | Some(tok, r1) -> Some(TmIsZero tok,r1)
    | _ -> raise Parse_exn)
  | _ -> raise Parse_exn;;
  

(* turn a list of tokens (like [TokLam, TokVar of "x", TokDot, TokVar of "x"] into a term (like TmAbs ("x", TmVar("x"))) *)
let parse (tokens : token list) : term = 
  match nextTerm tokens with
  | Some (term, []) -> term
  | _ -> raise Parse_exn;;


(* Alpha Conversion *)

(* takes a list of variable strings and produces a new string not in the set *)

let rec f_var_help vars t =
  if (SS.mem ("a"^(string_of_int t)) vars) 
    then f_var_help vars (t+1) 
    else ("a"^(string_of_int t));;

let fresh_var (vars : SS.t) = 
  f_var_help vars 0;;

(* takes a term of the form &x:T.t1 and turns it into an equivalent &y:T.t1', where
   y is a fresh variable and t1' is t1 with (free) x's replaced with ys. 
   If t is not a lambda abstraction return a NotAbs exception*)

let rec subst_alpha (x: string) (s: string) (t: term) = 
  match t with
  | TmVar y -> 
   ( match y with
    | _ when y = x -> TmVar s
    | _ -> t)
  | TmAbs (y, typ, t1) -> TmAbs(y,typ,(subst_alpha x s t1))
  | TmApp (t1, t2) -> TmApp ((subst_alpha x s t1), (subst_alpha x s t2))
  | TmIf (t1,t2,t3) -> TmIf((subst_alpha x s t1),
                              (subst_alpha x s t2),
                                  (subst_alpha x s t3))
  | TmSucc t1 -> TmSucc (subst_alpha x s t1)
  | TmPred t1 -> TmPred(subst_alpha x s t1)
  | TmIsZero t1 -> (subst_alpha x s t1)
  | _ -> t;;

let alpha_convert  (t : term) (vars : SS.t) : term =
  match t with
  | TmAbs (str, typ, term) ->
    let new_var = fresh_var vars in
    TmAbs(new_var, typ, (subst_alpha str new_var term))
  | _ -> raise (NotAbs "not abs");;


(* Typechecking *)

(* give a reasonable type to context *)
type ctx = (string * typ) list;;

(* define the empty context *)
let empty_ctx : ctx = [];;

(* look up a given variable's typ, throw a NotFound exception if the variable is not found *)

let ctx_exist g x =
  List.exists(fun (v1, t1) -> v1 = x) g;;

let lookup (g : ctx) (x : string) : typ = 
  if (ctx_exist g x) then 
    (match (List.find (fun (v2, t2) -> v2 = x) g) with
    | (a,b) -> b)
  else raise (NotFound "not found");;

(* extend a context with a new variable-typ association *)
(* throw a DuplicateVar exception if the variable already exists in g *)
let extend (g : ctx) (x : string) (t : typ): ctx = 
  if (ctx_exist g x)
    then raise (DuplicateVar "duplicate var")
    else (x,t)::g;;


(* return the type of a term in the given context *)
(* return None if the term is ill-typed *)

let rec typer_h g t =
  match t with
  | TmTrue -> Some(TBool)
  | TmFalse -> Some (TBool)
  | TmZero -> Some (TNat)
  | TmVar str -> 
    (if (ctx_exist g str) 
      then Some (lookup g str)
      else None)
  | TmSucc t1 -> 
    (match (typer_h g t1) with
    | Some TNat -> Some TNat
    | _ -> None)
  | TmPred t1 ->
    (match (typer_h g t1) with
    | Some TNat -> Some TNat
    | _ -> None)
  | TmIsZero t1 ->
    (match (typer_h g t1) with
    | Some TNat -> Some TBool
    | _ -> None)
  | TmIf (t1,t2,t3) ->
    (match (typer_h g t1) with
    | Some TBool -> 
      (match ((typer_h g t2),(typer_h g t3)) with
      | Some TBool, Some TBool -> Some TBool
      | Some TNat, Some TNat -> Some TNat
      | _ -> None)
    | _ -> None)
  | TmAbs (str,typ, t) ->
    (match (typer_h (extend g str typ) t) with
    | Some typ1 -> Some(TFun(typ,typ1))
    | _ -> None)
  | TmApp (t1, t2) ->
    (match (typer_h g t1),(typer_h g t2) with
    | Some t1, Some t2 ->
      (match t1 with
      | TFun(t3,t4) -> Some t4
      | _ -> None)
    | _ -> None);;
  

let type_of (g : ctx) (t : term) : typ option = 
  typer_h g t;;


(* Interpreter *)

(* This is for you to debug your code. *)
(* The current interpret function will parse a term and return its
  type in the empty context. *)
(* You're encouraged to add additional tests. *)

let rec typ_to_string (t : typ) : string = match t with
| TBool -> "Bool"
| TNat -> "Nat"
| TFun(t1,t2) -> "(" ^ typ_to_string t1 ^ "->" ^ typ_to_string t2 ^ ")"

let rec term_to_string (t : term) : string = match t with
| TmVar(str) -> str
| TmAbs(var, tp, body) -> "&" ^ var ^ ":" ^ typ_to_string tp ^ "." ^ term_to_string body
| TmApp(t1, t2) -> "(" ^ term_to_string t1 ^ ") (" ^ term_to_string t2 ^ ")"
| TmTrue -> "True"
| TmFalse -> "False"
| TmZero -> "0"
| TmIf (t1, t2, t3) -> "If " ^ term_to_string t1 ^ " Then " ^ term_to_string t2 ^ " Else " ^ term_to_string t3
| TmSucc (t1) -> "Succ " ^ term_to_string t1
| TmPred (t1) -> "Pred " ^ term_to_string t1
| TmIsZero (t1) -> "IsZero " ^ term_to_string t1

let opt_typ_to_string (o : typ option) : string = 
  match o with
  | None -> " "
  | Some t -> typ_to_string t 

  let interpret (str : string) : unit =
    let chars = string_to_char_list str in
    let tokens = scan chars in
    let ast = parse tokens in
    let term_str = term_to_string ast in
    let _ = print_endline ("----- Type Checking -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline (": " ^ (opt_typ_to_string (type_of empty_ctx ast))) in
    print_endline "";;


interpret Sys.argv.(1)
