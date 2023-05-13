exception No_solution 

(* Problem 1: The Collatz Sequence *)

(* Let f(n) = n/2     if n is even
              3n+1    otherwise     *)

(* The Collatz conjecture states that every n > 0, 
   repeated application of f to n terminates in 1. 
   Compute the Collatz sequence [n, f(n), ..., 1] for arbitrary n. 
   Throw an Invalid_argument exception if a number less than 1 is provided. *)

let rec coll_helper n acc =
   match n with
   | 1 -> acc @ [1]
   | _ -> if n < 1 then raise (Invalid_argument "n<1") 
   else if (n mod 2) == 0 
      then coll_helper (n/2) (acc @ [n])
      else coll_helper (3*n+1) (acc @ [n]);;

let rec collatz_list (n : int) = 
   coll_helper n [];;

(* Now compute the length of the Collatz sequence. *)

let rec length_calc n acc =
   match n with
   | [] -> acc
   | x :: xs -> length_calc xs (acc+1);; 

let rec collatz_length (n : int) : int = 
   length_calc (collatz_list n) 0;;

(* Problem 2: Binary search trees *)

(* Consider the following tree type *)
type 'a tree = Nil | Node of 'a tree * 'a * 'a tree 

(* Write a function that tests whether a tree is a valid binary search tree using the built-in '<' operation *)

let rec bst_help (t: 'a tree) min max : bool =
  match t with
  | Nil -> true
  | Node (t_l, v, t_r) ->
   match min, max with
   | None, None -> (bst_help t_l min (Some v)) && (bst_help t_r (Some v) max)
   | Some n, None -> n < v && (bst_help t_l (Some n) (Some v)) 
                                          && (bst_help t_r (Some v) max)
   | None, Some x -> v < x && (bst_help t_l min (Some v)) 
                                          && (bst_help t_r (Some v) (Some x))
   | Some n, Some x -> n < v && v < x && (bst_help t_l (Some n) (Some v)) 
                                          && (bst_help t_r (Some v) (Some x));;

let rec valid_bst (t : 'a tree) : bool = 
   (bst_help t None None);;

(* Problem 3: Searching a tree *)

(* We define directions as follows *)

type direction = Left | Right

(* These direction can be used to traverse the trees above. 
   Write a function to return the element at the indicated spot. 
   The end of the input list means to stop. 
   
   Since this will often fail, write versions that 
   1. raise a Not_found exception, and
   2. return a default element,
   3. return an option type.
   *)

let rec search_tree_exn (t : 'a tree) (ds : direction list) : 'a = 
   match ds, t with
   | _, Nil -> raise Not_found
   | [], Node (t_l, v, t_r) -> v
   | d :: ds, Node (t_l, v, t_r) ->
      match d with
      | Left -> search_tree_exn t_l ds
      | Right -> search_tree_exn t_r ds;;

let rec search_tree_def (t : 'a tree) (ds : direction list) (d : 'a) : 'a = 
   match ds, t with
   | _, Nil -> d
   | [], Node (t_l, v, t_r) -> v
   | r :: rs, Node (t_l, v, t_r) ->
      match r with
      | Left -> search_tree_def t_l rs d
      | Right -> search_tree_def t_r rs d;;

let rec search_tree_opt (t : 'a tree) (ds : direction list) : 'a option = 
   match ds, t with
   | _, Nil -> None
   | [], Node (t_l, v, t_r) -> Some v
   | d :: ds, Node (t_l, v, t_r) ->
      match d with
      | Left -> search_tree_opt t_l ds
      | Right -> search_tree_opt t_r ds;;

(* Problem 4: Summing tree values *)
  
(* For each of the methods above, write a function that takes a list of trees of integers and 
   returns the sum of the values at the given directions. *)

(* throw an exception if any of the trees are missing the desired element *)
let rec sum_tree_exn (ts : int tree list) (ds : direction list) : int =
   match ds, ts with 
   | _, [] -> 0
   | _, t :: ts -> (search_tree_exn t ds) + (sum_tree_exn ts ds);;

(* Use 0 as the default here *)
let rec sum_tree_def (ts : int tree list) (ds : direction list) : int = 
   match ds, ts with
   | _, [] -> 0
   | _, t :: ts -> (search_tree_def t ds 0) + (sum_tree_def ts ds);;

(* Return None if any of the trees do. *)
let rec sum_tree_opt (ts : int tree list) (ds : direction list) : 'a option = 
   match ds, ts with
   | _, [] -> Some 0
   | _, t :: ts -> match (search_tree_opt t ds),(sum_tree_opt ts ds) with
                     | None, _ -> None
                     | _, None -> None
                     | Some a, Some b -> Some (a + b);;

(* Problem 5: Reversing Lists *)

(* Here is a simple definition of reverse: *)

let rec reverse (l : 'a list) = 
  match l with
  | [] -> []
  | h::t -> reverse t @ [ h ]

(* though correct, this function reverses a list
   in O(n^2) time, since appending to the end of
   a list is done in O(n). It is possible to write
   an alternate definition which can reverse a list
   in linear time. Write such a definition.

   Hint: It will be necessary to write a helper function.
 *)

let rec rev_helper acc l =
   match l with
   | [] -> acc
   | h::t -> rev_helper (h::acc) t;;

let reverse_fast (l : 'a list) =
   rev_helper [] l;;

(* Problem 6: Binary Numbers *)

(* The following is a representation of a binary digit: *)

type digit = Zero | One

(* We can represent a natural number in binary as a list of
   binary digits. Write digits_of_int which converts a machine integer
   into a list of binary digits, where the least significant
   digit is at the head of the list. Raise Negative if the input
   is negative. *)

exception Negative
let rec digits_of_int (n : int) : digit list =
   if n<0 then raise Negative
   else if n==0 then []
   else match (n mod 2) with
   | 1 -> One :: (digits_of_int ((n-1)/2)) 
   | _ -> Zero :: (digits_of_int (n/2));;

(* int_of_digits converts a list of digits into a machine integer *)
let rec int_of_digits (digits : digit list) : int = 
   match digits with
   | [] -> 0
   | Zero :: ds -> 2*int_of_digits ds
   | One :: ds -> 1+2*int_of_digits ds;;

(* succ computes the successor of the binary number. For example,
   succ [Zero]      = [One]
   succ [Zero; One] = [One; One]
   succ [One; One]  = [Zero; Zero; One]

   Don't use digits_of_int or int_of_digits in the definition of this function! *)
let rec succ (digits : digit list) : digit list =
   match digits with
   | [] -> [One]
   | Zero :: ds -> One :: ds
   | One :: ds -> Zero :: succ ds;; 

(* List.iter (Printf.printf "%d ") (List.map int_of_digit (succ dlist));;
print_string("\n");; *)


(* Problem 7: Tic-Tac-Toe *)

exception Invalid_input

type player = X | O

(* 
  Read the final board of a tic-tac-toe game from a file. Valid input will be of the format:
  `---
   ---
   ---` 
   where each `-` should be `X` or `O`. Raise Invalid_input if input does not match this format.
   Only considering cases where an `X` or an `O` populates every place on the board (so no blank spaces), 
   raise Invalid_input if the board is not a valid end state for a tic-tac-toe game:
    - if there are multiple winners
   Return the winner of this game, if any, as Some winner, where winner : player. 
   If there is no winner, return None.
   You may want to write at least one helper function for this.
 *)

let string_to_players_3 str =
   let char_to_player ch =
      match ch with
      | 'O' -> O
      | 'X' -> X
      | _ -> raise Invalid_input
   in
   [(char_to_player (String.get str 0));
      (char_to_player (String.get str 1));
         (char_to_player (String.get str 2))];;

let win_check_X row1 row2 row3 =
   match row1,row2,row3 with
   |[X;X;X],_,_ -> Some X
   |_,[X;X;X],_ -> Some X
   |_,_,[X;X;X] -> Some X
   |[X;_;_],[X;_;_],[X;_;_] -> Some X
   |[_;X;_],[_;X;_],[_;X;_] -> Some X
   |[_;_;X],[_;_;X],[_;_;X] -> Some X
   |[X;_;_],[_;X;_],[_;_;X] -> Some X
   |[_;_;X],[_;X;_],[X;_;_] -> Some X
   |_ -> None;;

let win_check_O row1 row2 row3 =
   match row1,row2,row3 with
   |[O;O;O],_,_ -> Some O
   |_,[O;O;O],_ -> Some O
   |_,_,[O;O;O] -> Some O
   |[O;_;_],[O;_;_],[O;_;_] -> Some O
   |[_;O;_],[_;O;_],[_;O;_] -> Some O
   |[_;_;O],[_;_;O],[_;_;O] -> Some O
   |[O;_;_],[_;O;_],[_;_;O] -> Some O
   |[_;_;O],[_;O;_],[O;_;_] -> Some O
   |_ -> None;;   

let get_winner (filename : string) : player option = 
   let f = open_in filename in
   let row1 = string_to_players_3 (input_line f) in
   let row2 = string_to_players_3 (input_line f) in
   let row3 = string_to_players_3 (input_line f) in
   close_in f;
   match (win_check_O row1 row2 row3),(win_check_X row1 row2 row3) with
   | None, None -> None
   | Some O, None -> Some O
   | None, Some X -> Some X
   | Some O, Some X -> raise Invalid_input;;