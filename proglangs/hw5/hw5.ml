module SS = Set.Make(String)
module CTX = Map.Make(String)

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
| LCurly
| RCurly
| LSquare
| RSquare
| TokLam
| TokDot
| TokVar of string
| TokIf 
| TokThen
| TokFst
| TokSnd
| TokElse
| TokZero
| TokSucc
| TokPred
| TokIsZero
| TokColon
| TokBool
| TokTrue
| TokFalse
| TokOf
| TokNat
| TokArrow
| TokFatArrow
| TokCross
| TokPlus
| TokWith
| TokNil
| TokCons
| TokIsNil
| TokHead
| TokUnit
| TokTail
| TokBar
| TokCase
| TokComma
| TokInl
| TokInr

type typ 
= TUnit
| TBool
| TNat 
| TFun of typ * typ
| TProd of typ * typ 
| TSum of typ * typ
| TList of typ

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
| TmUnit
| TmPair of term * term
| TmFst of term
| TmSnd of term
| TmInl of typ * term
| TmInr of typ * term
| TmCase of term * string * term * string * term (* case term1 of inl string1 => term2 | inr string2 => term3 *)
| TmNil of typ
| TmCons of typ * term * term 
| TmIsNil of typ * term 
| TmHead of typ * term 
| TmTail of typ * term 



(* Utilities *) 

let string_to_char_list (s: string) : char list =
  s |> String.to_seq |> List.of_seq
  
let char_list_to_string (cl: char list) : string =
  cl |> List.to_seq |> String.of_seq
  
(* The tokenizer, lexer and parser are provided for you. *)

let varStart (c : char) : bool = 
  match c with
  | 'a'..'z' -> true
  | _ -> false

let validVar (c: char) : bool = 
  match c with
  | 'a'..'z' -> true
  | 'A'..'Z' -> true
  | '0'..'9' -> true
  | _ -> false

let rec nextVar (cs: char list) : (char list * char list) =
  match cs with
  | [] -> ([], [])
  | c::tl -> 
    if validVar c 
    then (match nextVar tl with
      | (var, rem) -> (c::var, rem))
    else ([], c::tl)

let rec nextToken (cs: char list) : (token * char list) option = 
  match cs with
  | '0'::tl -> Some (TokZero, tl)
  | 'X'::tl -> Some(TokCross, tl)
  | '+'::tl -> Some(TokPlus, tl)
  | 'o'::'f'::tl -> Some(TokOf, tl)
  | 'u'::'n'::'i'::'t'::tl -> Some (TokUnit, tl)
  | 'c'::'a'::'s'::'e'::tl -> Some(TokCase, tl)
  | 'S'::'u'::'c'::'c'::tl -> Some (TokSucc, tl)
  | 'P'::'r'::'e'::'d'::tl -> Some (TokPred, tl)
  | 'T'::'r'::'u'::'e'::tl -> Some (TokTrue, tl)
  | 'F'::'a'::'l'::'s'::'e'::tl -> Some (TokFalse, tl)
  | 'I'::'f'::tl -> Some (TokIf, tl)
  | 'T'::'h'::'e'::'n'::tl -> Some (TokThen, tl)
  | 'E'::'l'::'s'::'e'::tl -> Some (TokElse, tl)
  | 'I'::'s'::'Z'::'e'::'r'::'o'::tl -> Some (TokIsZero, tl)
  | 'B'::'o'::'o'::'l'::tl -> Some (TokBool, tl)
  | 'N'::'a'::'t'::tl -> Some (TokNat, tl)
  | 'n'::'i'::'l'::tl -> Some (TokNil, tl)
  | 'c'::'o'::'n'::'s'::tl -> Some(TokCons, tl)
  | 'w'::'i'::'t'::'h'::tl -> Some(TokWith, tl)
  | 'i'::'s'::'n'::'i'::'l':: tl -> Some(TokIsNil, tl)
  | 'h'::'e'::'a'::'d'::tl -> Some (TokHead, tl)
  | 't'::'a'::'i'::'l'::tl -> Some(TokTail, tl)
  | 'f'::'s'::'t'::tl -> Some(TokFst, tl)
  | 's'::'n'::'d'::tl -> Some(TokSnd, tl)
  | 'i'::'n'::'l'::tl -> Some (TokInl, tl)
  | 'i'::'n'::'r'::tl -> Some (TokInr, tl)
  | '-'::'>'::tl -> Some (TokArrow, tl)
  | '='::'>'::tl -> Some (TokFatArrow, tl)
  | ':'::tl -> Some(TokColon, tl)
  | '('::tl -> Some(LParen, tl)
  | '{'::tl -> Some(LCurly, tl)
  | '['::tl -> Some(LSquare, tl)
  | ']'::tl -> Some(RSquare, tl)
  | '}'::tl -> Some(RCurly, tl)
  | ')'::tl -> Some(RParen, tl)
  | '|'::tl -> Some(TokBar, tl)
  | '&'::tl -> Some(TokLam, tl)
  | '.'::tl -> Some(TokDot, tl)
  | ','::tl -> Some(TokComma, tl)
  | ' '::tl -> nextToken tl
  | c::tl -> 
    (if (varStart c)
      then (match nextVar (c::tl) with
            | (var, rem) -> Some (TokVar (char_list_to_string var), rem))
      else (raise Parse_exn))
  | [] -> None


let rec scan (ls : char list) : token list =
  match nextToken ls with
    | Some (tok, tl) -> tok :: scan tl
    | None -> []

let rec nextType (ts : token list) : (typ * token list) option =
  match ts with
  | TokNat::tl -> Some(TNat, tl)
  | TokBool::tl -> Some(TBool, tl)
  | TokUnit::tl -> Some(TUnit, tl)
  | LParen::tl -> (match tl with
    | TokCross::tl' -> (match nextType tl' with
      | Some(ty0, tl'') -> (match nextType tl'' with
        | Some(ty1, tl''') -> Some(TProd(ty0, ty1), tl''')
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | TokPlus::tl' -> (match nextType tl' with
      | Some(ty0, tl'') -> (match nextType tl'' with
        | Some(ty1, tl''') -> Some(TSum(ty0, ty1), tl''')
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | TokArrow::tl' -> (match nextType tl' with
      | Some(ty0, tl'') -> (match nextType tl'' with
        | Some(ty1, tl''') -> Some(TFun(ty0, ty1), tl''')
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | LSquare::tl -> (match nextType tl with
    | Some(ty0, RSquare::tl') -> Some(TList(ty0), tl')
    | _ -> raise Parse_exn)
  | _ -> raise Parse_exn    

let rec nextTerm (ts: token list) : (term * token list) option = 
  match ts with
  | TokVar(var)::tks -> Some(TmVar(var), tks)
  | LParen::tks ->(match nextTerm tks with
    | Some (tm0, RParen::LParen::tks') -> (match nextTerm tks' with
      | Some (tm1, RParen::tks'') -> Some(TmApp(tm0, tm1), tks'')
      | _ -> raise Parse_exn)
    | Some (tm1, TokComma::tks'') ->( match nextTerm tks'' with
      | Some(tm2, RParen::tks''') -> Some(TmPair(tm1, tm2), tks''')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokLam::TokVar(var)::TokColon::tl -> (match nextType tl with 
    | Some(ty0, TokDot::tl') -> (match nextTerm tl' with
      | Some(tm0, tl'') -> Some(TmAbs(var, ty0, tm0), tl'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokTrue::tl -> Some (TmTrue, tl)
  | TokFalse::tl -> Some (TmFalse, tl)
  | TokIf::tl -> (match nextTerm tl with
    | Some(tm0, TokThen::tl') -> (match nextTerm tl' with
      | Some(tm1, TokElse::tl'') -> (match nextTerm tl'' with
        | Some(tm2, tl''') -> Some(TmIf(tm0, tm1, tm2), tl''')
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokZero::tl -> Some (TmZero, tl)
  | TokIsZero::tl -> 
    (match nextTerm tl with
    | Some (trm, tl0) -> Some (TmIsZero trm, tl0)
    | _ -> raise Parse_exn)
  | TokPred::tl ->
    (match nextTerm tl with
    | Some (trm, tl0) -> Some (TmPred trm, tl0)
    | _ -> raise Parse_exn)
  | TokSucc::tl ->
    (match nextTerm tl with
    | Some (trm, tl0) -> Some (TmSucc trm, tl0)
    | _ -> raise Parse_exn)
  | LCurly::tks -> (match nextTerm tks with
    | Some (tm0, TokComma::tks') -> (match nextTerm tks' with
      | Some (tm1, RCurly::tks'') -> Some(TmPair(tm0, tm1), tks'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokUnit::tl -> Some(TmUnit, tl)
  | TokFst::tks -> (match nextTerm tks with
    | Some (tm0, tks') -> Some(TmFst(tm0), tks')
    | _ -> raise Parse_exn)
  | TokSnd::tks -> (match nextTerm tks with
    | Some (tm0, tks') -> Some(TmSnd(tm0), tks')
    | _ -> raise Parse_exn)
  | TokHead::tl -> (match nextType tl with
    | Some(TList(ty0), tl') -> (match nextTerm tl' with
      | Some(tm0, tl'') -> Some(TmHead(ty0, tm0), tl'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokTail::tl -> (match nextType tl with
    | Some(TList(ty0), tl') -> (match nextTerm tl' with
      | Some(tm0, tl'') -> Some(TmTail(ty0, tm0), tl'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokNil::tl -> (match nextType tl with
    | Some(TList(ty0), tl') -> Some(TmNil(ty0), tl')
    | _ -> raise Parse_exn)
  | TokCons::tl -> (match nextType tl with
    | Some(TList(ty0), tl') -> (match nextTerm tl' with
      | Some(tm0, tl'') -> (match nextTerm tl'' with
        | Some(tm1, tl''') -> Some(TmCons(ty0, tm0, tm1), tl''')
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokIsNil::tl -> (match nextType tl with
    | Some(TList(ty0), tl') -> (match nextTerm tl' with
      | Some(tm0, tl'') -> Some(TmIsNil(ty0, tm0), tl'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokInl::tl -> (match nextTerm tl with
    | Some(tm0, TokWith::tl') -> (match nextType tl' with
      | Some(ty0, tl'') -> Some(TmInl(ty0, tm0), tl'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokInr::tl -> (match nextTerm tl with
    | Some(tm0, TokWith::tl') -> (match nextType tl' with
      | Some(ty0, tl'') -> Some(TmInr(ty0, tm0), tl'')
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | TokCase::tl -> (match nextTerm tl with
    | Some(tm0, TokOf::TokInl::TokVar(x1)::TokFatArrow::tl') -> (match nextTerm tl' with
      | Some(tm1, TokBar::TokInr::TokVar(x2)::TokFatArrow::tl'') -> (match nextTerm tl'' with
        | Some(tm2, tl''') -> Some(TmCase(tm0, x1, tm1, x2, tm2), tl''')
        | _ -> raise Parse_exn)
      | _ -> raise Parse_exn)
    | _ -> raise Parse_exn)
  | _ -> raise Parse_exn

let parse (tokens : token list) : term = 
  match nextTerm tokens with
  | Some (trm, []) -> trm
  | _ -> raise Parse_exn

(* Derived forms *)

(* Implement the derived forms t;t, let x : T = t in t, option T
   and option case from the book and class. *)
(* In t;t, the first t should have type unit. *)
(* In let, note that x is annotated with a type.  *)
(* option T use a sum type to encode an option type *)
(* option case should case on None and Some t, returning a term for each case *)


(* do I need to make sure the var names don't overlap? *)

(* let rec fv (t:term) : SS.t =
  match t with
  | TmVar str -> SS.singleton str
  | TmAbs (y,x) -> SS.diff (fv x) (SS.singleton y)
  | TmApp (t1,t2) -> SS.union (fv t1) (fv t2);;
  | TmIf (t1,t2,t3) -> SS.union (fv t1) (SS.union (fv t2) (fv t3))
  | TmSucc t -> fv t
  | TmPred t -> fv t
  | TmIsZero t -> fv t
  | TmPair(t1,t2) -> SS.union (fv t1) (fv t2)
  | TmFst t -> fv t
  | TmSnd t -> fv t
  | TmInl (ty,t) -> fv t
  | TmInr (ty,t) -> fv t
  | TmCons (ty,t1,t2)
  | TmIsNil (ty,t) -> fv t
  | TmHead (ty,t) -> fv t 
  | TmTail (ty,t) -> fv t
  | _ -> SS.empty;;

let rec f_var_help vars t =
  if (SS.mem ("a"^(string_of_int t)) vars) 
    then f_var_help vars (t+1) 
    else ("a"^(string_of_int t));;

let fresh_var (vars : SS.t) = 
  f_var_help vars 0;; *)

(* now applied to tm_seq to make sure no accidents *)

let tm_seq (t1 : term) (t2 : term) : term = 
  (* let fvar = fresh_var (SS.union (fv t1) (fv t2)) in *)
  TmApp(TmAbs("fvar",TUnit,t2),t1);;

let tm_let (x : string) (tp : typ) (t1 : term) (t2 : term) : term = 
  TmApp(TmAbs(x,tp,t2),t1);; 

let tp_opt (tp : typ) : typ = TSum(TUnit,tp);;

let tm_some (t : term) : term = TmInr(TUnit,t);;

let tm_none (t : typ) : term = TmInl(t,TmUnit);;

let tm_opt_case (t: term) (t_some : string -> term) (t_none : term) : term = 
  match t with 
  | TmInr(TUnit,tm_1) -> TmCase(t, "x", t_some "x","y",t_some "y")
  | TmInl(ty1,TmUnit) -> t_none
  | _ -> t;;
  
(* case term1 of inl string1 => term2 | inr string2 => term3 *)

(* Small-step evaluation *)

(* Implement the small-step evaluation relations from class. 
   Note that we're only concerned with call-by-value for this homework. 
   Feel free to reuse code from homework 3. 
   (Implementing capture-avoiding substitution is encouraged, but not what we 
   will be grading this on) *)

(* I need substitution for applications and cases *)

let rec is_val t =
  match t with
  | TmVar str -> true
  | TmAbs (str,ty,t) -> true
  | TmApp (t1,t2) -> true
  | TmTrue -> true
  | TmFalse -> true
  | TmZero -> true
  | TmSucc t -> true
  | TmUnit -> true
  | TmNil ty -> true
  | TmCons (ty,t1,t2) -> (is_val t1) && (is_val t2)
  | _ -> false;;


let rec subst (x : string) (s : term) (t : term) : term = 
  match t with
  | TmVar y -> 
   ( match y with
    | _ when y = x -> s
    | _ -> t)
  | TmAbs (y, t_y, t1) -> 
    (match y with
    | _ when y = x -> t
    (* | _ when (SS.mem y (fv s)) -> raise (CaptureException "error") *)
    | _ -> TmAbs(y, t_y,(subst x s t1)))
  | TmApp (t1, t2) -> TmApp ((subst x s t1), (subst x s t2))
  | _ -> raise Parse_exn;;

let rec cbv (t : term) : term option = 
  match t with
  | TmApp(t1, t2) ->
    (match t1 with 
    | (TmApp(t11, t21)) -> 
      (match (cbv (TmApp(t11, t21))) with
      | Some t3 -> Some(TmApp(t3,t2))
      | None -> None)
    | (TmAbs(y, t_y, x)) -> 
     (match t2 with 
      | (TmApp(t3, t4)) ->
        (match (cbv t2) with
        | Some t -> Some(TmApp((TmAbs(y, t_y, x)),t))
        | None -> None)
      | (TmAbs(t3, t_3, t4)) -> Some(subst y (TmAbs(t3, t_3, t4)) x)
      | _ -> None)
    | _ -> None)
  | TmIf (t1,t2,t3) -> 
    (match t1 with
    | TmTrue -> Some(t2)
    | TmFalse -> Some(t3)
    | _ -> 
      (match (cbv t1) with
      | Some t -> Some(TmIf(t,t2,t3))
      | _ -> None))
  | TmPred t ->
    (match t with
    | TmSucc t1 -> Some(t1)
    | TmZero -> Some(TmZero)
    | _ -> None)
  | TmIsZero t ->
    (match t with
    | TmZero -> Some(TmTrue)
    | TmSucc t1 -> Some(TmFalse)
    | _ -> None)
  | TmUnit -> None
  | TmPair (t1,t2) -> 
    (match (cbv t1) with
    | Some t -> Some(TmPair(t,t2))
    | _ -> if (is_val t1) then
      (match (cbv t2) with
      | Some t -> Some(TmPair(t1,t))
      | _ -> None)
    else None)
  | TmFst t ->
    (match t with
    | TmPair(t1,t2) ->
     (match (cbv t) with
      | Some(TmPair(t1,t2)) -> Some(TmFst(TmPair(t1,t2)))
      | _ -> Some(t1))
    | _ -> None)
  | TmSnd t ->
    (match t with
    | TmPair(t1,t2) ->
     (match (cbv t) with
      | Some(TmPair(t1,t2)) -> Some(TmFst(TmPair(t1,t2)))
      | _ -> Some(t2))
    | _ -> None)
  | TmInl (ty,t) -> 
    (match (cbv t) with
    | Some t1 -> Some (TmInl (ty,t1))
    | _ -> None)
  | TmInr (ty,t) -> 
    (match (cbv t) with
    | Some t1 -> Some (TmInr (ty,t1))
    | _ -> None)
  | TmCase (t1,s1,t2,s2,t3) -> 
    (match t1 with
    | TmInr(ty,t) -> 
      if(is_val t) then (Some(subst s1 t t2)) else
        (match (cbv t1) with
        | Some t_1 -> Some(TmCase(t_1,s1,t2,s2,t3))
        | _ -> None)
    | TmInl(ty,t) -> 
      if(is_val t) then (Some(subst s2 t t3)) else 
        (match (cbv t1) with
        | Some t_1 -> Some(TmCase(t_1,s1,t2,s2,t3))
        | _ -> None)
    | _ -> None)
  | TmNil ty -> None
  | TmCons (ty,t1,t2) -> 
    (match (cbv t1) with
    | Some t -> Some(TmCons (ty,t,t2))
    | _ -> 
      (match (cbv t2) with
      | Some t -> Some(TmCons (ty,t1,t2))
      | _ -> None))
  | TmIsNil (ty, t) ->
    (match t with
    | TmNil ty1 -> Some(TmTrue)
    | TmCons (ty1,t1,t2) -> Some(TmFalse)
    | _ -> 
      (match (cbv t) with
      | Some t1 -> Some (TmIsNil (ty,t1))
      | _ -> None))
  | TmHead (ty, t) ->
    (match (cbv t) with
    | Some t1 -> Some (TmHead(ty,t1))
    | _ -> 
      (match t with 
      | TmCons (ty,t1,t2) -> Some (TmInr (TUnit, t1))
      | TmNil ty -> Some (TmInl (ty, TmUnit))
      | _ -> None))
  | TmTail (ty,t)->
    (match (cbv t) with
    | Some t1 -> Some (TmHead(ty,t1))
    | _ -> 
      (match t with 
      | TmCons (ty,t1,t2) -> Some t2
      | TmNil ty -> Some (TmNil ty)
      | _ -> None))
  | _ -> None;;

let rec multistep (t : term) : term option = 
  match (cbv t) with
  | Some t1 -> multistep t1
  | None -> Some t;;

(* Typechecking utilities *)

(* These first few functions can be copied from prior homeworks. 
   We will try to give solutions shortly after the late deadline. *)

(* give a reasonable type to context *)
type ctx = typ CTX.t;;

(* define the empty context *)
let empty_ctx : ctx = CTX.empty;;

(* look up a given variable's typ, throw a NotFound exception if the variable is not found *)
let lookup (g : ctx) (x : string) : typ = 
  match CTX.find_opt x g with
  | Some t -> t
  | None -> raise (NotFound x);;

let in_g g x =
  CTX.find_opt x g;;

(* extend a context with a new variable-typ association *)
let extend (g : ctx) (x : string) (t : typ): ctx = 
  if CTX.mem x g then raise (DuplicateVar x)
  else CTX.add x t g;;


(* Typechecking *)

(* return the type of a term in the given context *)
(* return None if the term is ill-typed *)


let rec typer_h g t = 
  match t with
  | TmVar str -> (in_g g str) 
  | TmAbs (str,ty,t) ->
    (match (typer_h (extend g str ty) t) with
    | Some ty1 -> Some(TFun(ty,ty1))
    | _ -> None)
  | TmApp (t1,t2) ->
    (match (typer_h g t1),(typer_h g t2) with
    | Some t1, Some t2 ->
      (match t1 with
      | TFun(t3,t4) -> Some t4
      | _ -> None)
    | _ -> None)
  | TmTrue -> Some TBool
  | TmFalse -> Some TBool
  | TmZero -> Some TNat
  | TmIf(t1,t2,t3) ->
    (match (typer_h g t1) with
    | Some TBool -> 
      (match ((typer_h g t2),(typer_h g t3)) with
      | Some TBool, Some TBool -> Some TBool
      | Some TNat, Some TNat -> Some TNat
      | _ -> None)
    | _ -> None)
  | TmSucc t -> 
    (match (typer_h g t) with
    | Some TNat -> Some TNat
    | _ -> None)
  | TmPred t ->
    (match (typer_h g t) with
    | Some TNat -> Some TNat
    | _ -> None)
  | TmIsZero t ->
    (match (typer_h g t) with
    | Some TNat -> Some TBool
    | _ -> None)
  | TmUnit -> Some TUnit
  | TmPair(t1,t2) -> 
    (match ((typer_h g t1),(typer_h g t2)) with
    | (Some typ1),(Some typ2) -> Some(TProd(typ1,typ2))
    | _ -> None)
  | TmFst t ->
    (match (typer_h g t) with
    | (Some (TProd (typ1, typ2))) -> Some(typ1)
    | _ -> None)
  | TmSnd t ->
    (match (typer_h g t) with
    | (Some (TProd (typ1, typ2))) -> Some(typ2)
    | _ -> None)
  | TmInl (ty,t) -> 
    (match (typer_h g t) with
    | Some ty1 -> Some(TSum(ty1,ty))
    | _ -> None)
  | TmInr (ty,t) -> 
    (match (typer_h g t) with
    | Some ty1 -> Some(TSum(ty,ty1))
    | _ -> None)
  | TmCase (t1,s1,t2,s2,t3) -> 
    (match (typer_h g t1) with
    | Some (TSum (ty1,ty2)) -> 
      (match (extend g s1 ty1) with
      | g1 -> 
        (match (extend g s2 ty2) with
        | g2 ->
          (match ((typer_h g t2),(typer_h g t3)) with
          | ((Some ty_1),(Some ty_2)) when (ty_1 == ty_2) -> Some ty_1
          | _ -> None)
        | _ -> None))
      | _ -> None
    | _ -> None)
  | TmNil ty -> Some (TList ty)
  | TmCons (ty,t1,t2) -> 
    (match (typer_h g t1) with
    | Some ty1 when (ty1 == ty) -> 
      (match (typer_h g t2) with
      | Some (TList ty2) when (ty2==ty) -> Some(TList ty)
      | _ -> None)
    | _ -> None)
  | TmIsNil(ty,t) ->
    (match (typer_h g t) with
    | Some (TList ty1) when (ty == ty1) -> Some(TBool)
    | _ -> None)
  | TmHead(ty,t) ->
    (match (typer_h g t) with
    | Some (TList ty1) when (ty == ty1) -> Some (TSum (TUnit, ty))
    | _ -> None)
  | TmTail(ty,t) ->
    (match (typer_h g t) with
    | Some (TList ty1) when (ty == ty1) -> Some(TList(ty))
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
| TList(t1) -> "[" ^ typ_to_string t1 ^ "]"
| TProd(t1, t2) -> typ_to_string t1 ^ " X " ^ typ_to_string t2
| TSum(t1, t2) -> typ_to_string t1 ^ " + " ^ typ_to_string t2
| TUnit -> "Unit"

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
| TmCase(t0, x1, t1, x2, t2) -> "case " ^ term_to_string t0 ^ " of inl " ^ x1 ^ " | inr " ^ x2 ^ " => " ^ term_to_string t2
| TmInl(ty, tm) -> "inl " ^ term_to_string tm ^ " with " ^ typ_to_string ty
| TmInr(ty, tm) -> "inr " ^ term_to_string tm ^ " with " ^ typ_to_string ty
| TmNil(ty)-> "nil[" ^ typ_to_string ty ^ "]"
| TmCons(ty, tm1, tm2) -> "cons[" ^ typ_to_string ty ^ "] " ^ term_to_string tm1 ^ " " ^ term_to_string tm2 
| TmIsNil(ty, tm) -> "isnil[" ^ typ_to_string ty ^ "] " ^ term_to_string tm 
| TmHead(ty, tm) -> "head[" ^ typ_to_string ty ^ "] " ^ term_to_string tm
| TmTail(ty, tm) -> "tail[" ^ typ_to_string ty ^ "] " ^ term_to_string tm
| TmFst(tm) -> "fst " ^ term_to_string tm
| TmSnd(tm) -> "snd " ^ term_to_string tm
| TmUnit -> "unit"
| TmPair(tm1, tm2) -> "{ " ^ term_to_string tm1 ^ " , " ^ term_to_string tm2 ^ " }"


 
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