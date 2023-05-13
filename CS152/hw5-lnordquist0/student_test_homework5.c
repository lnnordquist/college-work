/*
 * CS 152, Spring 2022
 * Homework #5 Student Test Code
 *
 * Add your tests to this file.  
 * Run make student_test_homework5 to compile your tests 
 * and ./student_test_homework5 to run your tests.
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "homework5.h"

/** Add your test functions (if any) here **/

int main(int argc, char **argv) {

    library_t *lib = make_library();
    
    // Testing empty_library
    if (empty_library(lib)) {
        printf("empty_library Test #1 passed\n");
    } else {
        printf("empty_library Test #1 failed\n");
    }

    // Testing book_cmp
    book_t *frankenstein = make_book("Frankenstein", "Shelley", 1918, 1000);
    book_t *contact = make_book("Contact", "Sagan", 1985, 1024);
    if (book_cmp(frankenstein, contact) < 0) {
        printf("\"Frankenstein\" was written before \"Contact\"\n");
    } else {
        printf("\"Contact\" was written before \"Frankenstein\"\n");
    }

    // Add your tests here

    free_book(frankenstein);
    free_book(contact);
    free_library(lib);
}
