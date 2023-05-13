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
 
/* These types are not visible outside this file.  Do NOT move them.
 */

struct book {
    enum book_type type;     // BUY_BOOK or SELL_BOOK
    int num_fields;
    int num_filled;
    order_t **pending;
};


/* mk_book : takes a book type (BUY_BOOK or SELL_BOOK) and returns an empty book
* with 5 slots allocated (none filled). Initializes the first value of pending
* to NULL to avoid memory leak issues with return_front.
*
*   type: enum of book type to be made
*
*   RETURNS: pointer to the new book
*/


book_t *mk_book(enum book_type type){
    book_t *book = (book_t *)ck_malloc(sizeof(book_t), "mk_book");
    book->type = type;
    book->num_fields = 5;
    book->num_filled = 0;
    book->pending = (order_t **)ck_malloc(sizeof(order_t*)*5, "mk_book");
    for(int i = 0; i<book->num_fields; i++){
        book->pending[i] = NULL;
    }
    return book;
}

/* order_compare: compares two orders, and returns which one comes first, 
*                 (depending on book type)
*
*   order1: first order to compare
*   order2: second order to compare
* Returns true if order1 comes first, false if order2 does.
* Ties broken by time; earlier orders go first either way.
* Any order precedes NULL.
*
*/

bool order_compare(struct order *order1, struct order *order2, 
                                                          enum book_type type){
  if(order1 == NULL){
      return false;
  }
  if(order2 == NULL){
      return true;
  }

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

/*  swap_order: swaps two orders in a given book by their indices.
*
*   book: book to swap in
*   first: index of first order to swap
*   second: index of second order to swap   
*
*   Returns: nothing (heap changed in-place)
*/

void swap_order(book_t *book, int first, int second){
    order_t *temp = book->pending[first];
    book->pending[first] = book->pending[second];
    book->pending[second] = temp;
    return;
}

/* sift_up: sifts an order from a given index to the top.
*
*   book: pointer to book to be sifted up on
*   index: index to order to be sifted up
*
*   Returns: nothing
*/

void sift_up(book_t *book, int index){
    int i = index;
    while(i > 0){
        int p = (i - 1)/2;
        if(order_compare(book->pending[i], book->pending[p], book->type)){
            swap_order(book, i, p);
        }else{
            return;
        }
        i = p;
    }
    return;
}

/* add_order_to_book: adds an order to a book; if not enough space, reallocs and
                    adds anyway. A sift up function is not implemented because
                    it has no use beyond this function.
*
*       book: pointer to book to be added to
*       order: pointer to order to add
*
*   Returns: nothing
*/

void add_order_to_book(book_t *book, order_t *order){
    assert(order != NULL);
    int filled = book->num_filled;
    if(book->num_fields == book->num_filled){
        //if full, reallocs 50% more space
        int new_num_fields = (int) (book->num_fields*1.5);
        book->pending = (order_t **)ck_realloc(book->pending, 
                                            sizeof(order_t *)*new_num_fields, 
                                            "add_order_to_book");
        for(int i = book->num_fields; i<new_num_fields; i++){
            book->pending[i] = NULL;
        }
        book->num_fields = new_num_fields;
    }
    book->num_filled += 1;
    book->pending[filled] = order;
    int i = book->num_filled -1;
    sift_up(book, i);
    return;
}

/* sift_down: sifts a heap from an index to bottom.
*
*   book: pointer to book
*
*   Returns: nothing
*/

void sift_down(book_t *book, int index){
    
    int size = book->num_filled;
    int i = index;
    
    while(2*i + 1 < size){
        int min_i = i, left = 2*i + 1, right = 2*i + 2;
        if(left < size){
            if(order_compare(book->pending[left], book->pending[min_i], book->type)){
                min_i = left;
            }
        }
        if(right < size){
            if(order_compare(book->pending[right], book->pending[min_i], book->type)){
                min_i = right;
            }
        }
        if(min_i != i){
            swap_order(book, i, min_i);
        }else{
            return;
        }
        i = min_i;
    }
}

/* remove_order: removes an order given by index by swapping it with the last one,
*           freeing it, and sifting the swapped order from the top to the bottom.  
*
*   book: pointer to book to sift down on
*   index: index of order to remove
*
*   Returns: nothing
*/

void remove_order(book_t *book, int index){
    assert(book->pending[index] != NULL);
    int last = book->num_filled - 1;
    swap_order(book, index, last);
    free_order(book->pending[last]);
    book->pending[last] = NULL;
    book->num_filled -= 1;

    sift_down(book, 0);

    return;
}

/* remove_front: removes the first order (root) by swapping it with the last one,
*           freeing it, and sifting the swapped order from the top to the bottom.  
*
*   book: pointer to book to sift down on
*
*   Returns: nothing
*/

void remove_front(book_t *book){
    remove_order(book, 0);
    return;
}

/* free_book: frees a book and all orders within. 
*
*   book: pointer to book to fill
*
*   Returns: nothing
*/

void free_book(book_t *book){
    int filled = book->num_fields;
    for(int i = 0; i<filled; i++){
        if(book->pending[i] != NULL){
            free_order(book->pending[i]);
        }
    }
    free(book->pending);
    free(book);
    return;
}

/* return_front: returns a pointer to the first order in a book.
*
*   book: pointer to book
*
* Returns: pointer to first order in book.
*/

order_t *return_front(book_t *book){
    return book->pending[0];
}


/* print_book: prints a book.
*
*   book: pointer to book to print
*
*   returns: nothing (prints in terminal)
*/

void print_book(book_t *book){
    printf("Book type: %s\n", (book->type)? "sell": "buy");
    printf("Num slots: %d. Num filled: %d\n", book->num_fields, book->num_filled);
    for(int i = 0; i<book->num_filled; i++){
        print_order(book->pending[i]);
    }
    return;
}

/* check_match: given an oref and abook, returns a pointer to (the first) 
*               matching order; returns NULL if not found. Index is given as an
*               out parameter.
*
*   book: pointer to book
*   oref: oref of order to find.
*
*   Returns: number of filled fields in book
*/

order_t *check_match(book_t *book, long long oref, int *index){
    int fields = book->num_fields;
    for(int i = 0; i<fields; i++){
        if(book->pending[i] != NULL && oref == book->pending[i]->oref){
            *index = i;
            return book->pending[i];
        }
    }
    return NULL;
}