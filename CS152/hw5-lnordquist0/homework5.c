/*
 * CS 152, Spring 2022
 * Homework #5
 *
 * Name: Lars Nordquist
 *
 * Sources used: None
 *
 * People consulted: Liam Lee Kitt
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "homework5.h"
extern char* strdup(const char*);

/*
 * make_book: Create a book_t
 *
 * title: title of the book
 * author: author of the book
 * year: year the book was published
 * ISBN: ISBN of the book
 *
 * Returns: A pointer to the book
 */
book_t *make_book(char *title, char *author, int year, int ISBN) {
    assert(title != NULL);
    assert(author != NULL);

    book_t *b = (book_t*)malloc(sizeof(book_t));
    if (b == NULL) {
        fprintf(stderr, "make_book: Unable to allocate\n");
        exit(1);
    }

    b->title = strdup(title);
    b->author = strdup(author);
    b->year = year;
    b->ISBN = ISBN;
    b->prev = NULL;
    b->next = NULL;

    return b;
}

/*
 * make_library: Make an empty library
 *
 * Returns: A pointer to a library
 */
library_t *make_library() {

    library_t *l = (library_t*)malloc(sizeof(library_t));
    if (l == NULL) {
        fprintf(stderr, "make_library: Unable to allocate\n");
        exit(1);
    }

    l->num_books = 0;
    l->books = NULL;
    
    return l;
}

/*
 * free_book: Free a book and all associated space
 *
 * b: the book
 *
 * Returns: Nothing, frees heap-allocated space
 */
void free_book(book_t *b) {
    assert(b != NULL);

    free(b->title);
    free(b->author);
    free(b);
}

/*
 * free_library: Free a library and all associated space
 *
 * l: the library
 *
 * Returns: Nothing, frees heap-allocated space
 */
void free_library(library_t *l) {
    assert(l != NULL);

    if (l->books == NULL) {
        free(l);
        return;
    }

    book_t *curr = l->books->next;
    while (curr != l->books) {
        book_t *next = curr->next;
        free_book(curr);
        curr = next;
    }
    free_book(curr);
    free(l);
}

/*
 * book_cmp: Compare two books by year, then author, then title
 *
 * b1: first book
 * b2: second book
 *
 * Returns:
 *   < 0: b1 comes before b2
 *   = 0: b1 is the same as b2
 *   > 0: b2 comes before b1
 */
int book_cmp(book_t *b1, book_t *b2) {
    assert(b1 != NULL);
    assert(b2 != NULL);

    // compare year
    if (b1->year != b2->year) {
        return b1->year - b2->year;
    }

    // compare author, if necessary
    int author_cmp = strcmp(b1->author, b2->author);
    if (author_cmp != 0) {
        return author_cmp;
    }

    // compare title, if necessary
    return strcmp(b1->title, b2->title);
}

/* 
 * empty_library: Determine whether a library is empty
 *
 * l: the library
 *
 * Returns: true if the library is empty, false otherwise
 */
bool empty_library(library_t *l) {
    assert(l != NULL);
    if(l->books == NULL){
        return true;
    }
    return false;
}

/* 
 * verify_num_books: Verify that the library's num_books
 *   is the number of books in the library
 *
 * l: the library
 *
 * Returns: true if num_books is the number of books in the
 *   library, false otherwise
 */
bool verify_num_books(library_t *l) {
    assert(l != NULL);
    
    if(empty_library(l)){
        return l->num_books == 0;
    }
    int real_num = 1;
    book_t *pos = l->books;
    while(pos->next != l->books){
        real_num++;
        pos = pos->next;
    }
    return real_num == l->num_books;
}

/*
 * add_book: Add a book to the library in order:
 *   year, author, title
 *
 * l: the library
 * title: title of the book
 * author: author of the book
 * year: year the book was published
 * ISBN: ISBN of the book
 *
 * Returns: Nothing, modifies the library
 */
void add_book(library_t *l, char *title, char *author, int year, int ISBN) {
    assert(l != NULL);
    assert(title != NULL);
    assert(author != NULL);

    book_t *new_book = make_book(title, author, year, ISBN);

    int booknum = l->num_books;
    book_t *pos = l->books;
    l->num_books += 1;

    if(l->books == NULL){
        l->books = new_book;
        new_book->next = new_book;
        new_book->prev = new_book;
        return;       
    }

    for(int i = 0; i<booknum; i++){
        if(book_cmp(new_book, pos) < 0){
            if(i==0){
                l->books = new_book;
                new_book->next = pos;
                new_book->prev = pos->prev;
                pos->prev->next = new_book;
                pos->prev = new_book;                
                return;
            }else{
                new_book->next = pos;
                new_book->prev = pos->prev;
                pos->prev->next = new_book;
                pos->prev = new_book;
                return;
            }
        }

        if(i == (booknum-1)){
            new_book->prev = pos;
            new_book->next = l->books;
            pos->next = new_book;
            l->books->prev = new_book;
            return;
        }

        pos = pos->next;
    }
}

/*
 * remove_book: Remove a book from the library
 *   by ISBN number
 *
 * l: the library
 * b: the book to add
 *
 * Returns: true if the book was successfully removed,
 *   false otherwise
 */
bool remove_book(library_t *l, int ISBN) {
    assert(l != NULL);

    int numbooks = l->num_books;
    book_t *pos = l->books;

    if(numbooks == 1){
        if(l->books->ISBN == ISBN){
            l->books = NULL;
            l->num_books -= 1;
            free(pos);
            return true;
        }
    }
    for(int i = 0; i< numbooks; i++){
        if(pos->ISBN == ISBN){
            if(i==0){
                l->books->next->prev = l->books->prev;
                l->books->prev->next = l->books->next;
                l->books = l->books->next;
                free_book(pos);
                l->num_books -= 1;
                return true;
            }
            
            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;
            free_book(pos);
            l->num_books -= 1;
            return true;
        }
        pos = pos->next;
    }
    return false;
}

/*
 * books_by_year: Create and populate an array so that it contains
 *   the number of books from each year in the library
 *
 * l: the library
 * num_years: the number of years (out parameter)
 *
 * Returns: An array of integers representing the number of books
 *   in the library from each year
 */
int *books_by_year(library_t *l, int *num_years) {
    assert(l != NULL);
    assert(num_years != NULL);

    *num_years = 0;
    if(l->books == NULL){
        return NULL;
    }

    int first_year = l->books->year;
    int numbooks = l->num_books;

    book_t *pos = l->books;
    for(int i = 0; i<numbooks; i++){
        if(pos->year < first_year){
            first_year = pos->year;
        }
        if(pos->year - first_year + 1 > *num_years){
            *num_years = pos->year - first_year + 1;
        }
        pos = pos->next;
    }

    int *l_by_year = (int*)calloc(sizeof(int), *num_years);
    if(l_by_year == NULL){
        fprintf(stderr, "books_by_year: allocation error");
        exit(1);
    }

    pos = l->books;
    for(int j = 0; j<numbooks; j++){
        l_by_year[pos->year - first_year] += 1;
        pos = pos->next;
    }

    return l_by_year;
}

/* 
 * flip_through_books: Flips through the books in a library
 *
 * l: the library
 * flips: directions to flip
 * num_flips: number of flips
 *
 * Returns: A pointer to the book that the flips end on
 */
book_t *flip_through_books(library_t *l, enum flip *flips, int num_flips) {
    assert(l != NULL);
    assert(flips != NULL);

    if(l->books == NULL){
        return NULL;
    }

    book_t *pos = l->books;
    for(int i = 0; i<num_flips; i++){
        switch(flips[i]){
            case FORWARDS:
                pos = pos->next;
                break;
            case BACKWARDS:
                pos = pos->prev;
                break;
        }
    }
    

    return pos;
}