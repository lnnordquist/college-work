/*
 * CS 152, Spring 2022
 * Book Data Structure Interface.
 * 
 * You will modify this file.
 */

/********* Do not modify this section *********/
#ifndef BOOK_H
#define BOOK_H

enum book_type {BUY_BOOK, SELL_BOOK};

/* The book type is opaque, which means that the client cannot reach
 * into the implementation and make changes directly.  Do NOT move the
 * structure type into this file.
 */
typedef struct book book_t;


/********** Modify below **********************/

// The prototypes for your public book functions
// go here.  Don't forget to include header
// comments that describe the purpose of the
// functions, the arguments, and the return value.


/* mk_book : takes a book type (BUY_BOOK or SELL_BOOK) and returns an empty book
* with 5 slots allocated (none filled).
*
*   type: enum of book type to be made
*
*   RETURNS: pointer to the new book
*/


book_t *mk_book(enum book_type type);

/* order_compare: compares two orders, and returns which one comes first, 
*                 (depending on book type)
*
*   order1: first order to compare
*   order2: second order to compare
* Returns true if order1 comes first, false if order2 does.
* Ties broken by time; earlier orders go first either way.
*
*/

bool order_compare(struct order *order1, struct order *order2, 
                                                          enum book_type type);


/*  swap_order: swaps two orders in a given book by their indices.
*
*   book: book to swap in
*   first: index of first order to swap
*   second: index of second order to swap   
*
*   Returns: nothing (heap changed in-place)
*/

void swap_order(book_t *book, int first, int second);

/* add_order_to_book: adds an order to a book; if not enough space, reallocs and
                    adds anyway.
*
*       book: pointer to book to be added to
*       order: pointer to order to add
*
*   Returns: nothing
*/

void add_order_to_book(book_t *book, order_t *order);

/* remove_front: removes the first order (root) by swapping it with the last one,
*           freeing it, and sifting the swapped order from the top to the bottom.  
*
*   book: pointer to book to sift down on
*
*   Returns: nothing
*/

void remove_front(book_t *book);

/* free_book: frees a book and all orders within. 
*
*   book: pointer to book to fill
*
*   Returns: nothing
*/

void free_book(book_t *book);

/* return_front: returns a pointer to the first order in a book.
*
*   book: pointer to book
*
* Returns: pointer to first order in book.
*/

order_t *return_front(book_t *book);

/* print_book: prints a book.
*
*   book: pointer to book to print
*
*   returns: nothing (prints in terminal)
*/

void print_book(book_t *book);

/* check_match: given an oref and abook, returns a pointer to (the first) 
*               matching order; returns NULL if not found. Index is given as an
*               out parameter.
*
*   book: pointer to book
*   oref: oref of order to find.
*
*   Returns: number of filled fields in book
*/

order_t *check_match(book_t *book, long long oref, int *index);

/* remove_order: removes an order given by index by swapping it with the last one,
*           freeing it, and sifting the swapped order from the top to the bottom.  
*
*   book: pointer to book to sift down on
*   index: index of order to remove
*
*   Returns: nothing
*/

void remove_order(book_t *book, int index);

// Do not remove the next line
#endif
