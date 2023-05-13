module SS = Set.Make(String)
module SMap = Map.Make(String)
module IMap = Map.Make(Int)

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

type label = string

type typ 
= TUnit
| TBool
| TNat
| TFun of typ * typ
| TVariant of (label * typ) list 
| TRef of typ

type term
= TmVar of string
| TmAbs of string * typ * term
| TmApp of term * term
| TmUnit
| TmTrue 
| TmFalse 
| TmIf of term * term * term
| TmZero
| TmSucc of term
| TmPred of term
| TmIsZero of term
| TmVariant of label * term * typ (* eg. red = 6 as [red:Nat; blue:Nat] *)
| TmCase of term * (label * string * term) list (* eg. case red 2 of [red x => 5 | blue y => 9] *)
| TmRef of term 
| TmLoc of int 
| TmBang of term (* !t *)
| TmAssn of term * term 
| TmRaise of term
| TmTry of term * term
| TmNull
| TmIsNull of typ * term

(* Utilities *) 

let string_to_char_list (s: string) : char list =
  s |> String.to_seq |> List.of_seq
  
let char_list_to_string (cl: char list) : string =
  cl |> List.to_seq |> String.of_seq
  
(* The tokenizer, lexer and parser are provided for you. *)

let rec nextToken (cs: char list) : (token * char list) option = 
  raise Not_implemented

let rec scan (ls : char list) : token list = raise Not_implemented

let rec nextTerm (ts: token list) : (term * token list) option = raise Not_implemented

let parse (tokens : token list) : term = raise Not_implemented


(* Variants *)

(* Implement an option type, some and none as variants *)

let tp_opt (tp : typ) : typ = TVariant[("some",tp);("none",TUnit)]

let tm_some (t : term) (tp : typ) : term = TmVariant("some",t,tp)

let tm_none (tp : typ) : term = TmVariant("none",TmUnit,tp)

(* Implement an exception type as a variant. 
   There are at least three possible exceptions that you should be able to handle. 
   (These should become clear as you progress through the homework, but feel free to start
    with some obvious candidates.) *)

let tp_exn : typ = TVariant[
                ("null_pointer_exception", TUnit); 
                  ("location_not_found", TUnit);
                    ("no_matching_case", TUnit)]

(* This should print an error message for each possible exception and return raise unit. *)
(* Think of this as throwing an error message to the console. *)
(* not req'd for hmwk *)
(* let print_exn : term = raise Not_implemented *)



(* Small-step evaluation *)

(* Implement the small-step evaluation relations from class. 
   Note the presence of a store and the possibility of encountering 
   raise and null. *)

type store = term IMap.t

(* need to know if something is a val *)
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
  | TmLoc n -> true
  | TmVariant (lab,tm,ty) -> true
  | TmNull -> true
  | _ -> false;;

(* needed for abstractions *)
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

(* need a way to add a new term to a store *)

let rec add_to_mu t n mu =
  match (IMap.mem n mu) with
  | true -> add_to_mu t (n+1) mu
  | false -> Some(n, IMap.add n t mu);;

let rec cbv (t : term) (mu : store) : (term*store) option = 
  match t with
  | TmApp(t1, t2) ->
    (match t1,t2 with 
    | (TmRaise t11),_ -> 
      (match (cbv t11 mu) with
      | Some (t12,mu1) -> Some(TmApp((TmRaise t12),t2),mu1)
      | _ -> Some(TmRaise t11,mu))
    | _, (TmRaise t21) -> 
      (match (cbv t21 mu) with
      | Some (t22,mu1) -> Some(TmApp(t1,(TmRaise t22)),mu1)
      | _ -> Some(TmRaise t21,mu))
    | (TmApp(t11, t21)),_ -> 
      (match (cbv t1 mu) with
      | Some (t3,mu1) -> Some(TmApp(t3,t2),mu1)
      | None -> None)
    | (TmAbs(y, t_y, x)),_ -> 
     (match t2 with 
      | (TmApp(t3, t4)) ->
        (match (cbv t2 mu) with
        | Some (t,mu1) -> Some(TmApp((TmAbs(y, t_y, x)),t),mu1)
        | None -> None)
      | (TmAbs(t3, t_3, t4)) -> Some((subst y (TmAbs(t3, t_3, t4)) x),mu)
      | TmNull -> Some(x,mu)
      | _ -> None))
  | TmIf (t1,t2,t3) -> 
    (match t1 with
    | TmTrue -> Some(t2,mu)
    | TmFalse -> Some(t3,mu)
    | _ -> 
      (match (cbv t1 mu) with
      | Some (t,mu1) -> Some(TmIf(t,t2,t3),mu1)
      | _ -> None))
  | TmPred t ->
    (match t with
    | TmSucc t1 -> Some(t1,mu)
    | TmZero -> Some(TmZero,mu)
    | _ -> None)
  | TmIsZero t ->
    (match t with
    | TmZero -> Some(TmTrue,mu)
    | TmSucc t1 -> Some(TmFalse,mu)
    | _ -> None)
  | TmUnit -> None
  | TmVariant (lab,t,ty) -> 
    (match (cbv t mu) with
    | Some (t1,mu1) -> Some (TmVariant (lab,t1,ty),mu1)
    | _ -> None)
  | TmCase(t, vs) ->
    (match (cbv t mu) with
    | Some (t1,mu1) -> Some(TmCase(t1,vs),mu1)
    | _ ->
      (match t with
      | TmVariant (lab,tm,ty) -> 
        (match (List.find_opt (fun (l_i,_,_)->l_i=lab) vs) with
        | Some(l_i,t_i,ty_i) -> Some((subst t_i tm ty_i),mu)
        | _ -> None)
      | _ -> None))
  | TmRef t -> 
    if (is_val t) then
      (match (add_to_mu t 0 mu) with
      | Some(n,mu1) -> Some(TmLoc n, mu1) )
    else 
      (match (cbv t mu) with
      | Some (t1,mu1) -> Some ((TmRef t1),mu1)
      | _ -> None)
  | TmLoc n -> None
  | TmBang t -> 
    (match (cbv t mu) with
      | Some (t1,mu1)-> Some((TmBang t1),mu1)
      | _ -> 
        (match t with
        | TmLoc n -> 
          (match (IMap.find_opt n mu) with
          | Some t1 -> Some (t1,mu)
          | _ -> None)
        | _ -> None))
  | TmAssn (t1,t2) -> 
    (match t1 with
    | TmLoc n -> if(is_val t2) 
      then Some(TmUnit,(IMap.add n t2 mu))
      else( match (cbv t2 mu) with
      | Some(t2_1,mu1) -> Some(TmAssn(t1,t2_1),mu1)
      | _ -> None)
    | _ -> None)
    (* | _ ->
      (match (cbv t1) with
      | Some(t1_1,mu1)->Some(TmAssn(t1_1,mu1))
      | _ -> None)) *)
  | TmRaise t -> 
    (match t with
    | TmRaise t1 -> Some((TmRaise t1),mu)
    | _ ->
      (match (cbv t mu) with
      | Some(t1,mu1) -> Some((TmRaise t1),mu1)
      | _ -> None))
  | TmTry (t1,t2) -> 
    (match (cbv t1 mu) with
    | Some (t11,mu1) -> Some(TmTry(t11,t2),mu1)
    | _ ->
      (match t1 with
      | TmRaise t11 -> Some(TmApp(t2,t11),mu)
      | _ -> Some(t1,mu)))
  | TmIsNull (ty,t1) ->
    (match t1 with
    | TmNull -> Some(TmTrue,mu)
    | _ -> 
      match (cbv t1 mu) with
      | Some (t1_1,mu1) -> Some(TmIsNull(ty,t1_1),mu1)
      | _ -> Some(TmFalse,mu))
  | _ -> None;;

(* needed context to be preserved between iterations *)
let rec multistep_helper t mu =
  match cbv t mu with
  | Some (t1,mu1) -> multistep_helper t1 mu1
  | _ -> t;;

let rec multistep (t : term) : term = 
  multistep_helper t IMap.empty;;


(* Typechecking utilities *)

type ctx = typ SMap.t
type typ_store = typ IMap.t 

let empty_ctx : ctx = SMap.empty

let empty_store : typ_store = IMap.empty

(* look up a given variable's typ, throw a NotFound exception if the variable is not found *)
let lookup (g : ctx) (x : string) : typ = match SMap.find_opt x g with
| Some t -> t
| None -> raise (NotFound x)

(* extend a context with a new variable-typ association *)
let extend (g : ctx) (x : string) (t : typ): ctx = 
  if SMap.mem x g then raise (DuplicateVar x)
  else SMap.add x t g


(* Typechecking *)


  

(* This should infer the type of a term in the given context *)
(* return None if the term is ill-typed OR the type cannot be inferred *)
(* You may want to use type_check or other helper functions in writing this. *)
let rec type_infer (g : ctx) (s : typ_store) (t : term) : typ option = 
  match t with
  | TmVar str -> Some(lookup g str) 
  | TmAbs (str,ty,t) ->
    (match type_infer (extend g str ty) s t with
    | Some ty1 -> Some(TFun(ty,ty1))
    | _ -> None)
  | TmApp (t1,t2) ->
    (match (type_infer g s t1),(type_infer g s t2) with
    | Some t1, Some t2 ->
      (match t1 with
      | TFun(t3,t4) -> Some t4
      | _ -> None)
    | Some ty1, _ ->
      (match ty1,t2 with
      (* can't tell the type of TmNull in this context *)
      (* assuming it's well-typed *)
      | TFun(t3,t4),TmNull -> Some t4
      | _,_ -> None)
    | _ -> None)
  | TmTrue -> Some TBool
  | TmFalse -> Some TBool
  | TmZero -> Some TNat
  | TmIf(t1,t2,t3) ->
    (match (type_infer g s t1) with
    | Some TBool -> 
      (match ((type_infer g s t2),(type_infer g s t3)) with
      | Some TBool, Some TBool -> Some TBool
      | Some TNat, Some TNat -> Some TNat
      | _ -> None)
    | _ -> None)
  | TmSucc t -> 
    (match (type_infer g s t) with
    | Some TNat -> Some TNat
    | _ -> None)
  | TmPred t ->
    (match (type_infer g s t) with
    | Some TNat -> Some TNat
    | _ -> None)
  | TmIsZero t ->
    (match (type_infer g s t) with
    | Some TNat -> Some TBool
    | _ -> None)
  | TmUnit -> Some TUnit
  | TmVariant (lab,t,TVariant(vs)) ->
    (match (List.find_opt (fun (l_i,ty_i)->l_i=lab) vs) with
    | Some ty_j -> Some(TVariant(vs))
    | _ -> None)
  | TmCase (TmVariant(lab,t,TVariant(vs)),v_s) -> 
    (match (List.find_opt (fun (l_i,ty_i)->l_i=lab) vs) with
    | Some (lab,ty_j) -> 
      match (type_infer g s t) with
      | Some ty_t when ty_j = ty_t -> Some ty_j
      | _ -> None
    | _ -> None)
  | TmRef t -> 
    (match (type_infer g s t) with
    | Some ty_1 -> Some(TRef ty_1)
    | _ -> None)
  | TmLoc n -> 
    if (IMap.mem n s) then
      Some (TRef(IMap.find n s))
      else None
  | TmBang t ->
    (match (type_infer g s t) with
    | Some (TRef ty_1) -> Some ty_1
    | _ -> None)
  | TmAssn (t1,t2) ->
    (match (type_infer g s t1) with
    | Some (TRef t11) -> 
      (match (type_infer g s t2) with
      | Some t21 -> if(t11 == t21) then Some(TUnit) else None
      | _ -> None)
    | _ -> None)
  | TmRaise (TmVariant (lab, t, ty)) -> 
    if (ty = tp_exn) then Some ty else None
  | TmTry(t1,t2) -> 
    (match (type_infer g s t2),(type_infer g s t1) with
    | Some (TFun(ty21,ty22)), Some ty1->
      if (ty21=tp_exn) then Some(ty22) else None
    | _ -> None)
  | TmIsNull(ty,t) -> Some(TBool)
  | _ -> None

(* check if a term has the given type. *)
(* Takes in a context and a store, as well as a term t and type T *)
(* Returns true iff gamma | sigma |- t : T *)

  let type_check (g : ctx) (s : typ_store) (t : term) (tp : typ) = 
    match t with
    | TmNull -> true
    | TmSucc(TmNull) -> true
    | TmPred(TmNull) -> true
    | TmIsZero(TmNull) -> true
    | TmRef(TmNull) -> true
    | TmApp(_,TmNull) -> true
    | TmApp(TmNull,_) -> true
    | _ -> 
      match (type_infer g s t) with
      | Some ty -> (tp = ty)
      | _ -> false;;


(* Checks if the given store is well typed with respect to the given type_store
   and typing context. *)
(* Returns true iff gamma | sigma |- mu *)

  let store_helper key g s v =
    match (IMap.mem key s) with
    | true ->
      (match (IMap.find key s),(type_infer g s v) with
      | ty1,Some(ty2) when ty1=ty2 -> true
      | _,_ -> false)
    | _ -> false

  let store_well_typed (g : ctx) (s : typ_store) (mu : store) = 
    IMap.fold (fun key v t -> t && store_helper key g s v) mu true;;

  


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
    let _ = print_endline ("----- Type Inference -----") in
    let _ = print_endline ("      " ^ term_str) in 
    let _ = print_endline (": " ^ (opt_typ_to_string (type_infer empty_ctx empty_store ast))) in
    print_endline "";;


interpret Sys.argv.(1)
