/*
 * CS 152, Spring 2022
 * Book Data Structure Implementation
 * 
 * You will modify this file.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "order.h"
#include "book.h"
#include "util.h"
 
/* These types are not visible outside this file.
 * Do NOT move them.
 */
typedef struct order_list order_list_t;


struct order_list {
  struct order *order;
  order_list_t *next;
};

struct book {
    enum book_type type;     // BUY_BOOK or SELL_BOOK
    order_list_t *pending;   // orders still in play.
};

/* mk_book: allocates space for a book, sets the appropriate book type, and sets
*           the pending field to NULL.
*
*   type: enum, book type
*
*   Returns a pointer to the book.
*/
book_t *mk_book(enum book_type type){
    book_t *new_book = (book_t *)ck_malloc(sizeof(book_t), "mk_book");
    new_book->type = type;
    new_book->pending = NULL;
    return new_book;
}

/* mk_order_list: makes an order list from an order, a pointer to the previous
* order, and a pointer to the next order
*
*   order: pointer to order
*   prev: pointer to previous
*   next: pointer to next
*
*   Returns: pointer to new order list (node)
*/

order_list_t *mk_order_list(struct order *order, order_list_t *next){
    order_list_t *order_list = (order_list_t *)ck_malloc(sizeof(order_list_t), 
                                                              "mk_order_list");
    order_list->order = order;
    order_list->next = next;

    return order_list;

}

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
                                                          enum book_type type){
  switch(type){
    case BUY_BOOK:
        if(order1->price != order2->price){
          return order2->price < order1->price;
        }
        break;
    case SELL_BOOK:
        if(order1->price != order2->price){
            return order2->price > order1->price;
        }
  }
  return order1->time < order2->time;
}


/* add_order_to_book: takes an order and adds it to a book
*
*   book: pointer to book to be added to
*   order: pointer to order to be added
*
*   Returns: nothing
*/

void add_order_to_book(struct book *book, struct order *order){
    
    order_list_t *added_order = mk_order_list(order, NULL);
    if(book->pending == NULL){
        book->pending = added_order;
        return;
    }
    order_list_t *pos = book->pending;
    order_list_t *pos_prev = NULL;
    enum book_type type = book->type;

    while(pos != NULL){
        if(order_compare(order, pos->order, type)){  
            if(pos == book->pending){
                book->pending = added_order;
            }else{
                pos_prev->next = added_order;
            }   
            added_order->next = pos;  
            return;
        }
        pos_prev = pos;
        pos = pos->next;
    }
    pos_prev->next = added_order;
    return;
}

/* remove_front: takes a book, relinks it around its front, and free the order
*       using the free_order function. NOTE: because of how the exchange
*       works, will only free from beginning or if only element.
*
*   book: pointer to book which contains order
*
*
*   Returns: nothing
*/

void remove_front(struct book *book){

    if(book->pending == NULL){
        return;
    }

    order_list_t *front = book->pending;
    book->pending = book->pending->next;

    free_order(front->order);
    free(front);
    return;
}

/* free_book: takes a book and frees all of its elements, then frees the book
*       struct itself.
*
*   book: pointer to book to free
*
*   Returns: nothing
*/

void free_book(struct book *book){
    if(book == NULL){
        return;
    }
    while(book->pending != NULL){
        remove_front(book);
    }
    free(book);
    return;
}

/* print_book: prints the contents of an entire book.
*
*   book: pointer to book to print
*
* Returns: nothing
*/

void print_book(struct book *book){
    order_list_t *pos = book->pending;
    printf("Book type: %s\n", (book->type)? "sell": "buy");
    while(pos != NULL){
        print_order(pos->order);
        pos = pos->next;
    }
    return;
}


/* return_front: given a book, returns a pointer to the first order, if it
                exists. Removes the front and tries again if it has 0 shares.
*
*   book: pointer to book to be matched to
*
* Returns: either pointer to order at front of book, or NULL if none exists.
*/
struct order *return_front(book_t *book){
    if(book->pending == NULL){
        return NULL;
    }
    return book->pending->order;
}

