open List
open Char
open Format

exception Not_implemented
exception Parse_exn

(* Data Definitions *)

type token
= LParen
| RParen
| TokTrue
| TokFalse
| TokZero
| TokIf
| TokSucc
| TokPred
| TokIsZero
| TokAnd
| TokOr
| TokNot

type term
= True
| False
| Zero
| If of term * term * term
| Succ of term
| Pred of term
| IsZero of term
| And of term * term
| Or of term * term
| Not of term

(* A term in normal form is either a Value or Stuck. *)
type normal_form
= Value of term
| Stuck of term

(* Utilities *) 

(* Strings in ocaml are not represented as lists of characters. For lexing and parsing purposes, it's easier to work
with lists of characters. You shouldn't need to touch these functions that convert between the two, but feel free to use them for debugging. *)
let string_to_char_list (s: string) : char list =
  s |> String.to_seq |> List.of_seq
  
let char_list_to_string (cl: char list) : string =
  cl |> List.to_seq |> String.of_seq
  
(* Value Judgements *)

(* Returns true if the term is a numeric value, false otherwise. *)
let rec is_num_val (t: term) : bool = 
  match t with
  | Zero -> true
  | Succ x -> is_num_val x
  | _ -> false;;

(* Returns true if the term is a value, false otherwise. *)
let is_val (t: term) : bool = 
  if (is_num_val t) then true else
    match t with 
    | True -> true
    | False -> true
    | _ -> false;;

(* Lexical Scanner *)

(* nextToken should return the next token from a list of characters, along with the characters thereafter
   - return None if the list of chars is empty
   - skip whitespace characters
   - throw an exception if the characters cannot be tokenized 
  Some basic cases have been given for you. *)
let rec nextToken (cs: char list) : (token * char list) option = 
  match cs with
  | [] -> None
  | ' '::tl -> nextToken tl
  | '('::tl -> Some (LParen, tl)
  | ')'::tl -> Some (RParen, tl)
  | 't'::'r'::'u'::'e'::tl -> Some (TokTrue, tl)
  | 'f'::'a'::'l'::'s'::'e'::tl -> Some (TokFalse, tl)
  | '0'::tl -> Some (TokZero, tl)
  | 'i'::'f'::tl -> Some (TokIf,tl)
  | 's'::'u'::'c'::'c'::tl -> Some (TokSucc,tl)
  | 'p'::'r'::'e'::'d'::tl-> Some (TokPred,tl)
  | 'i'::'s'::'z'::'e'::'r'::'o'::tl -> Some (TokIsZero,tl)
  | 'a'::'n'::'d'::tl -> Some (TokAnd,tl)
  | 'o'::'r'::tl -> Some (TokOr,tl)
  | 'n'::'o'::'t'::tl-> Some (TokNot,tl)
  | _ -> raise Parse_exn

(* turn a string of code (like "(pred 0)" into a list of tokens (like [LParen, TokPred, TokZero, RParen]) *)
let rec scan (ls : char list) : token list =
  match (nextToken ls) with
  | None -> []
  | Some (tok, tl) -> tok::(scan tl);;

(* Parser *)

(* nextTerm should return the next term from a list of tokens, along with the tokens thereafter
   - return None if the list of tokens is empty
   - throw an exception if the characters cannot be tokenized *)

let rec nextTerm (ts: token list) : (term * token list) option =
  match ts with
  | [] -> None
  | LParen::trs -> nextTerm trs
  | TokTrue::trs -> Some(True, trs)
  | TokFalse::trs -> Some(False, trs)
  | TokZero::trs -> Some (Zero, trs)
  | TokSucc::t1 -> 
    (match (nextTerm t1) with
    | Some(t2,RParen::t3) -> Some(Succ(t2),t3)
    | _ -> raise Parse_exn)
  | TokPred::t1 -> 
    (match (nextTerm t1) with
    | Some(t2,RParen::t3) -> Some(Pred(t2),t3)
    | _ -> raise Parse_exn)
  | TokIsZero::t1 -> 
    (match (nextTerm t1) with
    | Some(t2,RParen::t3) -> Some(IsZero(t2),t3)
    | _ -> raise Parse_exn)
  | TokNot::t1 -> 
    (match (nextTerm t1) with
    | Some(t2,RParen::t3) -> Some(Not(t2),t3)
    | _ -> raise Parse_exn)
  | TokAnd::t1 ->
    (match (nextTerm t1) with
    | Some(t2,t3) -> 
      (match (nextTerm t3) with
      | Some(t4,RParen::t5)->Some(And(t2,t4),t5)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokOr::t1 ->
    (match (nextTerm t1) with
    | Some(t2,t3) -> 
      (match (nextTerm t3) with
      | Some(t4,RParen::t5)->Some(Or(t2,t4),t5)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokIf::t1 ->
    (match (nextTerm t1) with
    | Some(t2,t3) -> 
      (match (nextTerm t3) with
      | Some(t4,t5)->
        (match (nextTerm t5) with
        | Some(t6,RParen::t7)->Some(If(t2,t4,t6),t7)
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | _ -> raise Parse_exn;;
  

(* turn a list of tokens (like [LParen ,TokPred, TokZero, RParen] into a term (like Pred 0) *)
let parse (tokens : token list) : term =
  match nextTerm tokens with
  | Some (t, []) -> t
  | _ -> raise Parse_exn;;


(* Small Step evaluator *)

(* Implement the small-step evaluation relation from class. 
   For And, Or and Not, you should be able to determine 
   appropriate rules by extrapolating from the If rules.
   If a term is not a normal form, take the next possible step
   - i.e., if t -> u, then step(t) should return Some(u)
   if a term is a normal form, return None *)
let rec small_step (t : term) : term option =
  match t with
  | True -> None
  | False -> None
  | Zero -> None
  | Succ t1 -> 
    (match t1 with
    | Zero -> None
    | Pred t2 -> Some t2
    | _ -> 
      match small_step t1 with
      | None -> None
      | Some t2 -> Some (Succ t2))
  | Pred t1 ->
    (match t1 with
    | Zero -> Some Zero
    | Succ t2 -> Some t2
    | _ -> 
      match small_step t1 with
      | None -> None
      | Some t2 -> Some (Pred t2))
  | Not t1 -> 
    (match t1 with
    | True -> Some False
    | False -> Some True
    | _ -> 
      match small_step t1 with
      | None -> None
      | Some t2 -> Some (Not t2))
  | IsZero t1 ->
    (match t1 with
    | Zero -> Some True
    | Succ t2 -> Some False
    | _ -> small_step t1)
  | And (t1,t2) ->
    (match t1 with
    | False -> Some False
    | True -> Some t2
    | _ -> 
      (match small_step t1 with
      | Some t3 -> Some (And(t3,t2))
      | None -> 
        (match small_step t2 with
        | Some t3 -> Some (And (t1,t3))
        | None -> None)))
  | Or (t1,t2) ->
    (match t1 with
    | True -> Some True
    | False -> Some t2
    | _ -> 
      (match small_step t1 with
      | Some t3 -> Some (Or(t3,t2))
      | None -> 
        (match small_step t2 with
        | Some t3 -> Some (Or(t1,t3))
        | None -> None)))
  | If (t1,t2,t3) ->
    (match t1 with
    | True -> Some t2
    | False -> Some t3
    | _ -> 
      (match small_step t1 with
      | Some t4 -> Some (If(t4,t2,t3))
      | None -> 
        (match small_step t2 with
        | Some t4 -> Some (If(t1,t4,t3))
        | None -> 
          match small_step t3 with
          | Some t4 -> Some (If(t1,t2,t4))
          | None -> None)));;

(* Returns true if the term is a normal form, false otherwise. *)
let is_normal (t: term) : bool = 
  match small_step t with
  | None -> true
  | Some _ -> false;;

(* Returns true if the term is stuck, false otherwise. *)
let is_stuck (t: term) : bool =
  if (is_val t) then false 
  else match (small_step t) with
  | None -> true
  | Some _ -> false;;

(* Given t, return t' such that t ->* t' and t' is a normal form. *)
let rec multistep_full (t : term) : term =
  match (small_step t) with
  | None -> t
  | Some t2 -> multistep_full t2;;

(* Returns true if a term steps to a value, and false otherwise. *)
let rec multisteps_to_value (t: term) : bool = 
  match (multistep_full t) with
  | t1 -> if (is_val t1) then true 
          else if (is_stuck t1) then false 
          else multisteps_to_value(t1);;

(* Big Step evaluator *)

(* Now implement the big-step relation from class. 
   Again, return none if the program doesn't (big) step. *)
let rec big_step (t : term) : term option =
  if (is_val t) then Some t else
  match t with
  | Succ t1 -> 
    (match (big_step t1) with
    | Some t2 -> Some (Succ t2)
    | _ -> None)
  | Pred t1 ->
    (match (big_step t1) with
    | Some Zero -> Some Zero
    | Some Succ t2 -> Some t2
    | _ -> None)
  | Not t1 -> 
    (match (big_step t1) with
    | Some True -> Some False
    | Some False -> Some True
    | _ -> None)
  | IsZero t1 ->
    (match (big_step t1) with
    | Some Zero -> Some True
    | Some Succ t2 -> Some False
    | _ -> None)
  | And (t1,t2) ->
    (match (big_step t1) with
    | Some False -> Some False
    | Some True -> Some t2
    | _ -> None)
  | Or (t1,t2) ->
    (match t1 with
    | True -> Some True
    | False -> Some t2
    | _ -> None)
  | If (t1,t2,t3) ->
    (match (big_step t1) with
    | Some True -> big_step t2
    | Some False -> big_step t3
    | _ -> None)
  | _ -> None ;;

(* Interpreter *)

(* You should not need to modify this code -- feel free to add statements for debugging,
   but remember to delete them before submitting. *)

let rec term_to_string (t : term) : string = match t with
| True -> "true"
| False -> "false"
| Zero -> "zero"
| If (t1, t2, t3) -> "(" ^ "if " ^ term_to_string t1 ^ " then " ^ term_to_string t2 ^ " else " ^ term_to_string t3  ^ ")"
| Succ (t1) -> "(" ^ "succ " ^ term_to_string t1 ^ ")"
| Pred (t1) -> "(" ^ "pred " ^ term_to_string t1 ^ ")"
| IsZero (t1) ->  "(" ^ "iszero " ^ term_to_string t1 ^ ")"
| And (t1, t2) -> "(" ^ term_to_string t1 ^ " and " ^ term_to_string t2 ^ ")"
| Or (t1, t2) -> "(" ^ term_to_string t1 ^ " or " ^ term_to_string t2 ^ ")"
| Not (t1) -> "(" ^ "not " ^ term_to_string t1 ^ ")"

let opt_term_to_string (o : term option) : string = 
  match o with
  | None -> " "
  | Some t -> term_to_string t 

let interpret (str : string) : unit =
  let chars = string_to_char_list str in
  let tokens = scan chars in
  let ast = parse tokens in
  let ss_term = small_step ast in
  let bs_term = big_step ast in
  let term_str = term_to_string ast in 
  let ss_term_str = opt_term_to_string ss_term in
  let bs_term_str = opt_term_to_string bs_term in
  let _ = print_endline ("----- Small Step Evaluation -----") in
  let _ = print_endline ("      " ^ term_str) in 
  let _ = print_endline ("->    " ^ ss_term_str) in
  let _ = print_endline "-----" in
  let _ = print_endline "-----" in
  let _ = print_endline "-----" in
  let _ = print_endline ("----- Big Step Evaluation -----") in
  let _ = print_endline ("      " ^ term_str) in 
  print_endline ("||" ^ bs_term_str);;


interpret Sys.argv.(1)
