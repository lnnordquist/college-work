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


/* add_order_to_book: takes an order and adds it to a book
*
*   book: pointer to book to be added to
*   order: pointer to order to be added
*
*   Returns: nothing
*/

void add_order_to_book(struct book *book, struct order *order);



/* remove_front: takes an order, relinks book around it, and free the order
*       using the free_order function. NOTE: because of how the exchange
*       works, will only free from beginning or if only element.
*
*   book: book which contains order
*
*
*   Returns: nothing
*/

void remove_front(struct book *book);

/* free_book: takes a book and frees all of its elements, then frees the book
*       struct itself.
*
*
*   book: pointer to book to free
*
*   Returns: nothing
*/

void free_book(struct book *book);


/* print_book: prints the contents of an entire book.
*
*   book: pointer to book to print
*
* Returns: nothing
*/

void print_book(struct book *book);

/* return_front: given a book, returns a pointer to the first order, if it
                exists.
*
*   book: pointer to book to be matched to
*
* Returns: either pointer to order at front of book, or NULL if none exists.
*/
struct order *return_front(book_t *book);

/* mk_book: allocates space for a book, sets the appropriate book type, and sets
*           the pending field to NULL.
*
*   type: enum, book type
*
*   Returns a pointer to the book.
*/
book_t *mk_book(enum book_type type);

// Do not remove the next line
#endif
