#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
extern char* strdup(const char*);

typedef struct book book_t;
typedef struct library library_t;

struct book {
    char *title;
    char *author;
    int year;
    int ISBN;
    book_t *prev;
    book_t *next;
};

struct library {
    int num_books;
    book_t *books;
};

enum flip {FORWARDS, BACKWARDS};

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
book_t *make_book(char *title, char *author, int year, int ISBN);

/*
 * make_library: Make an empty library
 *
 * Returns: A pointer to a library
 */
library_t *make_library();

/*
 * free_book: Free a book and all associated space
 *
 * b: the book
 *
 * Returns: Nothing, frees heap-allocated space
 */
void free_book(book_t *b);

/*
 * free_library: Free a library and all associated space
 *
 * l: the library
 *
 * Returns: Nothing, frees heap-allocated space
 */
void free_library(library_t *l);

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
int book_cmp(book_t *b1, book_t *b2);

/* 
 * empty_library: Determine whether a library is empty
 *
 * l: the library
 *
 * Returns: true if the library is empty, false otherwise
 */
bool empty_library(library_t *l);

/* 
 * verify_num_books: Verify that the library's num_books
 *   is the number of books in the library
 *
 * l: the library
 *
 * Returns: true if num_books is the number of books in the
 *   library, false otherwise
 */
bool verify_num_books(library_t *l);

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
void add_book(library_t *l, char *title, char *author, int year, int ISBN);

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
bool remove_book(library_t *l, int ISBN);

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
int *books_by_year(library_t *l, int *num_years);

/* 
 * flip_through_books: Flips through the books in a library
 *
 * l: the library
 * flips: directions to flip
 * num_flips: number of flips
 *
 * Returns: A pointer to the book that the flips end on
 */
book_t *flip_through_books(library_t *l, enum flip *flips, int num_flips);