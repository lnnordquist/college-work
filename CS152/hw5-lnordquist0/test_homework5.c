/*
 * CS 152, Spring 2022
 * Homework #5 Automated Tests 
 *
 * Run make test_homework5 to compile these tests and ./test_homework5
 * to run these tests. See the homework write-up for instructions
 * on how to run a subset of the tests.
 * 
 * Do not modify this file.
 */

#include <stdbool.h>
#include <string.h>
#include <criterion/criterion.h>
#include "homework5.h"

// Check that two books are the same
void book_eq(book_t *b1, char *title, char *author, int year, int ISBN) {
    cr_assert_eq(strcmp(b1->title, title), 0);
    cr_assert_eq(strcmp(b1->author, author), 0);
    cr_assert_eq(b1->year, year);
    cr_assert_eq(b1->ISBN, ISBN);
}

Test(add_book, test0) {
    library_t *l = make_library();
    char *titles[] = {"T1"}; // add one book
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1"};
    char *expected_authors[] = {"A1"};
    int expected_years[] = {2000};
    int expected_ISBNs[] = {1000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test1) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"}; // add to end
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 2001};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2"};
    char *expected_authors[] = {"A1", "A2"};
    int expected_years[] = {2000, 2001};
    int expected_ISBNs[] = {1000, 2000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test2) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"}; // add to beginning
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 1999};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T2", "T1"};
    char *expected_authors[] = {"A2", "A1"};
    int expected_years[] = {1999, 2000};
    int expected_ISBNs[] = {2000, 1000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        b = b->next;
    }
    cr_assert_eq(l->books, b);

    free_library(l);
}

Test(add_book, test3) {
    library_t *l = make_library();
    char *titles[] = {"T2", "T1"}; // add to beginning, same year
    char *authors[] = {"A2", "A1"};
    int years[] = {2000, 2000};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2"};
    char *expected_authors[] = {"A1", "A2"};
    int expected_years[] = {2000, 2000};
    int expected_ISBNs[] = {2000, 1000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test4) {
    library_t *l = make_library();
    char *titles[] = {"T2", "T1"}; // add to beginning, same year, same author
    char *authors[] = {"A1", "A1"};
    int years[] = {2000, 2000};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2"};
    char *expected_authors[] = {"A1", "A1"};
    int expected_years[] = {2000, 2000};
    int expected_ISBNs[] = {2000, 1000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test6) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"}; // add to end
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 2002};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2", "T3"};
    char *expected_authors[] = {"A1", "A2", "A3"};
    int expected_years[] = {2000, 2001, 2002};
    int expected_ISBNs[] = {1000, 2000, 3000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test7) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"}; // add in middle
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2002, 2001};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T3", "T2"};
    char *expected_authors[] = {"A1", "A3", "A2"};
    int expected_years[] = {2000, 2001, 2002};
    int expected_ISBNs[] = {1000, 3000, 2000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test8) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"}; // add in middle
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2001, 2002, 2000};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T3", "T1", "T2"};
    char *expected_authors[] = {"A3", "A1", "A2"};
    int expected_years[] = {2000, 2001, 2002};
    int expected_ISBNs[] = {3000, 1000, 2000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test9) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2001, 2002, 2003, 2004};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *expected_authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int expected_years[] = {2000, 2001, 2002, 2003, 2004};
    int expected_ISBNs[] = {1000, 2000, 3000, 4000, 5000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test10) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2004, 2003, 2002, 2001, 2000};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T5", "T4", "T3", "T2", "T1"};
    char *expected_authors[] = {"A5", "A4", "A3", "A2", "A1"};
    int expected_years[] = {2000, 2001, 2002, 2003, 2004};
    int expected_ISBNs[] = {5000, 4000, 3000, 2000, 1000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test11) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2000, 2000, 2000, 2000};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *expected_authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int expected_years[] = {2000, 2000, 2000, 2000, 2000};
    int expected_ISBNs[] = {1000, 2000, 3000, 4000, 5000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test12) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2002, 2003, 1999, 2004};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T4", "T1", "T2", "T3", "T5"};
    char *expected_authors[] = {"A4", "A1", "A2", "A3", "A5"};
    int expected_years[] = {1999, 2000, 2002, 2003, 2004};
    int expected_ISBNs[] = {4000, 1000, 2000, 3000, 5000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test13) {
    library_t *l = make_library();
    char *titles[] = {"T2", "T5", "T1", "T3", "T4"};
    char *authors[] = {"A1", "A1", "A1", "A1", "A1"};
    int years[] = {2000, 2000, 2000, 2000, 2000};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *expected_authors[] = {"A1", "A1", "A1", "A1", "A1"};
    int expected_years[] = {2000, 2000, 2000, 2000, 2000};
    int expected_ISBNs[] = {3000, 1000, 4000, 5000, 2000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(add_book, test14) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2003, 2004, 2002, 2005, 2001};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T5", "T3", "T1", "T2", "T4"};
    char *expected_authors[] = {"A5", "A3", "A1", "A2", "A4"};
    int expected_years[] = {2001, 2002, 2003, 2004, 2005};
    int expected_ISBNs[] = {5000, 3000, 1000, 2000, 4000};

    cr_assert_eq(l->num_books, num_books);

    book_t *b = l->books;
    book_t *e;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(empty_library, test0) {
    library_t *l = make_library();
    cr_assert_eq(empty_library(l), true);
    free_library(l);
}

Test(empty_library, test1) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    cr_assert_eq(empty_library(l), false);
    free_library(l);
}

Test(empty_library, test2) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"};
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 2001};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    cr_assert_eq(empty_library(l), false);
    free_library(l);
}

Test(empty_library, test3) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 1999};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    cr_assert_eq(empty_library(l), false);
    free_library(l);
}

Test(empty_library, test4) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    cr_assert_eq(empty_library(l), false);
    free_library(l);
}

Test(verify_num_books, test0) {
    library_t *l = make_library();
    l->num_books = 0;
    cr_assert_eq(verify_num_books(l), true);
    free_library(l);
}

Test(verify_num_books, test1) {
    library_t *l = make_library();
    l->num_books = 2;
    cr_assert_eq(verify_num_books(l), false);
    free_library(l);
}

Test(verify_num_books, test2) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    l->num_books = 1;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test3) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    l->num_books = 0;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test4) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    l->num_books = 2;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test5) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 1999};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    l->num_books = 3;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test6) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 1999};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    l->num_books = 4;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test7) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 1999};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    l->num_books = 2;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test8) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2001, 1999, 2000, 2001};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    l->num_books = 5;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test9) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2001, 1999, 2000, 2001};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    l->num_books = 4;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(verify_num_books, test10) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2001, 1999, 2000, 2001};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    l->num_books = 6;
    cr_assert_eq(verify_num_books(l), num_books == l->num_books);
    free_library(l);
}

Test(remove_book, test0) {
    library_t *l = make_library();
    bool actual = remove_book(l, 1000); // empty library
    cr_assert_eq(actual, false);
    cr_assert_eq(l->books, NULL);
    free_library(l);
}

Test(remove_book, test1) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    int expected_num_books = 0;

    bool actual = remove_book(l, 1000); // remove only book
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, expected_num_books);
    cr_assert_eq(l->books, NULL);
    free_library(l);
}

Test(remove_book, test2) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int ISBNs[] = {1000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1"};
    char *expected_authors[] = {"A1"};
    int expected_years[] = {2000};
    int expected_ISBNs[] = {1000};
    int expected_num_books = 1;

    bool actual = remove_book(l, 2000); // not in library
    cr_assert_eq(actual, false);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test3) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"};
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 2001};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T2"};
    char *expected_authors[] = {"A2"};
    int expected_years[] = {2001};
    int expected_ISBNs[] = {2000};
    int expected_num_books = 1;

    bool actual = remove_book(l, 1000); // remove from front
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test4) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"};
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 2001};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1"};
    char *expected_authors[] = {"A1"};
    int expected_years[] = {2000};
    int expected_ISBNs[] = {1000};
    int expected_num_books = 1;

    bool actual = remove_book(l, 2000); // remove from end
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test5) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"};
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 2001};
    int ISBNs[] = {1000, 2000};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2"};
    char *expected_authors[] = {"A1", "A2"};
    int expected_years[] = {2000, 2001};
    int expected_ISBNs[] = {1000, 2000};
    int expected_num_books = 2;

    bool actual = remove_book(l, 3000); // not in library
    cr_assert_eq(actual, false);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test6) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 2002};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T2", "T3"};
    char *expected_authors[] = {"A2", "A3"};
    int expected_years[] = {2001, 2002};
    int expected_ISBNs[] = {2000, 3000};
    int expected_num_books = 2;

    bool actual = remove_book(l, 1000); // remove from front
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test7) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 2002};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T3"};
    char *expected_authors[] = {"A1", "A3"};
    int expected_years[] = {2000, 2002};
    int expected_ISBNs[] = {1000, 3000};
    int expected_num_books = 2;

    bool actual = remove_book(l, 2000); // remove from middle
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test8) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 2002};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    char *expected_titles[] = {"T1", "T2"};
    char *expected_authors[] = {"A1", "A2"};
    int expected_years[] = {2000, 2001};
    int expected_ISBNs[] = {1000, 2000};
    int expected_num_books = 2;

    bool actual = remove_book(l, 3000); // remove from end
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, expected_num_books);

    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < expected_num_books; i++) {
        book_eq(b, expected_titles[i], expected_authors[i], expected_years[i], expected_ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == expected_num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test9) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 2002};
    int ISBNs[] = {1000, 2000, 3000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    bool actual = remove_book(l, 4000); // not in library
    cr_assert_eq(actual, false);
    cr_assert_eq(l->num_books, num_books);
    
    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, titles[i], authors[i], years[i], ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}


Test(remove_book, test10) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    bool actual = remove_book(l, 4500); // not in library
    cr_assert_eq(actual, false);
    cr_assert_eq(l->num_books, num_books);
    
    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        book_eq(b, titles[i], authors[i], years[i], ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test11) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    bool actual = remove_book(l, 5000);
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, num_books - 1);
    
    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        if (i == 4) {
            continue;
        }
        book_eq(b, titles[i], authors[i], years[i], ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test12) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    bool actual = remove_book(l, 2000);
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, num_books - 1);
    
    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        if (i == 1) {
            continue;
        }
        book_eq(b, titles[i], authors[i], years[i], ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test13) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    bool actual = remove_book(l, 8000);
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, num_books - 1);
    
    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        if (i == 7) {
            continue;
        }
        book_eq(b, titles[i], authors[i], years[i], ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == 6) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(remove_book, test14) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};
    int ISBNs[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], ISBNs[i]);
    }

    bool actual = remove_book(l, 1000);
    cr_assert_eq(actual, true);
    cr_assert_eq(l->num_books, num_books - 1);
    
    book_t *e;
    book_t *b = l->books;
    for (int i = 0; i < num_books; i++) {
        if (i == 0) {
            continue;
        }
        book_eq(b, titles[i], authors[i], years[i], ISBNs[i]);
        cr_assert_eq(b->next->prev, b);
        if (i == num_books - 1) {
            e = b;
        }
        b = b->next;
    }
    cr_assert_eq(l->books, b);
    cr_assert_eq(b->prev, e);

    free_library(l);
}

Test(books_by_year, test0) {
    library_t *l = make_library();

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);
    cr_assert_eq(actual_num_years, 0);
    cr_assert_eq(actual, NULL);

    free_library(l);
}

Test(books_by_year, test1) {
    library_t *l = make_library();
    char *titles[] = {"T1"};
    char *authors[] = {"A1"};
    int years[] = {2000};
    int num_books = 1;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    int expected_num_years = 1;
    int expected[] = {1};

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test2) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2"};
    char *authors[] = {"A1", "A2"};
    int years[] = {2000, 2001};
    int num_books = 2;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    int expected_num_years = 2;
    int expected[] = {1, 1};

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test3) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3"};
    char *authors[] = {"A1", "A2", "A3"};
    int years[] = {2000, 2001, 2000};
    int num_books = 3;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    int expected_num_years = 2;
    int expected[] = {2, 1};

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test4) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2001, 2002, 2003, 2004};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    int expected_num_years = 5;
    int expected[] = {1, 1, 1, 1, 1};

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test5) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2001, 2001, 2000, 2001};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int expected_num_years = 2;
    int expected[] = {2, 3};

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test6) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2004, 2001, 2005, 2001};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int expected_num_years = 6;
    int expected[] = {1, 2, 0, 0, 1, 1};

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test7) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2000, 2000, 2000, 2000, 2000};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int expected_num_years = 1;
    int expected[] = {5};

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test8) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2004, 2002, 2001, 2004, 2003, 2007, 2007, 2001};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int expected_num_years = 7;
    int expected[] = {2, 1, 1, 2, 0, 0, 2};

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(books_by_year, test9) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"};
    int years[] = {2007, 2007, 2007, 2005, 2002, 2002, 2005, 2005};
    int num_books = 8;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    int expected_num_years = 6;
    int expected[] = {2, 0, 0, 3, 0, 3};

    int actual_num_years;
    int *actual = books_by_year(l, &actual_num_years);

    cr_assert_eq(actual_num_years, expected_num_years);
    for (int i = 0; i < expected_num_years; i++) {
        cr_assert_eq(actual[i], expected[i]);
    }

    free(actual);
    free_library(l);
}

Test(flip_through_books, test0) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[0];
    book_t *actual = flip_through_books(l, flips, 0);

    book_eq(actual, "T1", "A1", 2001, 0);

    free_library(l);
}

Test(flip_through_books, test1) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {FORWARDS};
    book_t *actual = flip_through_books(l, flips, 1);

    book_eq(actual, "T2", "A2", 2002, 0);

    free_library(l);
}

Test(flip_through_books, test2) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {BACKWARDS};
    book_t *actual = flip_through_books(l, flips, 1);

    book_eq(actual, "T5", "A5", 2005, 0);

    free_library(l);
}

Test(flip_through_books, test3) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {FORWARDS, BACKWARDS};
    book_t *actual = flip_through_books(l, flips, 2);

    book_eq(actual, "T1", "A1", 2001, 0);

    free_library(l);
}

Test(flip_through_books, test4) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {BACKWARDS, FORWARDS};
    book_t *actual = flip_through_books(l, flips, 2);

    book_eq(actual, "T1", "A1", 2001, 0);

    free_library(l);
}

Test(flip_through_books, test5) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {FORWARDS, FORWARDS, FORWARDS};
    book_t *actual = flip_through_books(l, flips, 3);

    book_eq(actual, "T4", "A4", 2004, 0);

    free_library(l);
}

Test(flip_through_books, test6) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {FORWARDS, FORWARDS, BACKWARDS};
    book_t *actual = flip_through_books(l, flips, 3);

    book_eq(actual, "T2", "A2", 2002, 0);

    free_library(l);
}

Test(flip_through_books, test7) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {FORWARDS, FORWARDS, BACKWARDS, FORWARDS, FORWARDS};
    book_t *actual = flip_through_books(l, flips, 5);

    book_eq(actual, "T4", "A4", 2004, 0);

    free_library(l);
}

Test(flip_through_books, test8) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {FORWARDS, FORWARDS, BACKWARDS, BACKWARDS, FORWARDS};
    book_t *actual = flip_through_books(l, flips, 5);

    book_eq(actual, "T2", "A2", 2002, 0);

    free_library(l);
}

Test(flip_through_books, test9) {
    library_t *l = make_library();
    char *titles[] = {"T1", "T2", "T3", "T4", "T5"};
    char *authors[] = {"A1", "A2", "A3", "A4", "A5"};
    int years[] = {2001, 2002, 2003, 2004, 2005};
    int num_books = 5;
    for (int i = 0; i < num_books; i++) {
        add_book(l, titles[i], authors[i], years[i], 0);
    }

    enum flip flips[] = {BACKWARDS, BACKWARDS, BACKWARDS, FORWARDS, BACKWARDS, BACKWARDS};
    book_t *actual = flip_through_books(l, flips, 6);

    book_eq(actual, "T2", "A2", 2002, 0);

    free_library(l);
}
