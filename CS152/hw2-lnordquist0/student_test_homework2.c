/*
 * CS 152, Spring 2022
 * Homework #2 Student Test Code
 *
 * Add your tests to this file.  
 * Run make student_test_homework2 to compile your tests 
 * and ./student_test_homework2 to run your tests.
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "homework2.h"

/** Add your test functions (if any) here **/

/* 
 * int_arrays_are_identical: Check if two arrays have
 *     the same elements
 * 
 * a: the first array
 * b: the second array
 * len: the length of the array
 *
 * Returns: true if a and b are identical, false otherwise
 */
bool int_arrays_are_identical(int *a, int *b, int len) {
    assert(a != NULL);
    assert(b != NULL);
    assert(len > 0);

    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

/* 
 * char_arrays_are_identical: Check if two arrays have
 *     the same elements
 * 
 * a: the first array
 * b: the second array
 * len: the length of the array
 *
 * Returns: true if a and b are identical, false otherwise
 */
bool char_arrays_are_identical(char *a, char *b, int len) {
    assert(a != NULL);
    assert(b != NULL);
    assert(len > 0);

    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    // Sample test for Exercise #1
    int input1[] = {1, 2, 3, 4};
    int expected1[] = {4, 3, 2, 1};
    flip(input1, 4);
    if (int_arrays_are_identical(input1, expected1, 4)) {
        printf("Passed flip test #1\n");
    } else {
        printf("Failed flip test #1\n");
    }

    // Sample test for Exercise #2
    int input2[] = {1, 2, 3, 4};
    int expected2[] = {4, 1, 2, 3};
    shift(input2, 4);
    if (int_arrays_are_identical(input2, expected2, 4)) {
        printf("Passed shift test #1\n");
    } else {
        printf("Failed shift test #1\n");
    }

    // Sample test for Exercise #3
    char sentence[] = "Hello, my name is Joe.";
    int num_words;
    char *output3 = first_letter(sentence, &num_words);
    char expected3[] = {'H', 'm', 'n', 'i', 'J'};
    if (num_words == 5) {
        printf("Passed first_letter test #1\n");
    } else {
        printf("Failed first_letter test #1\n");
    }
    if (char_arrays_are_identical(output3, expected3, num_words)) {
        printf("Passed first_letter test #2\n");
    } else {
        printf("Failed first_letter test #2\n");
    }

    // Add your tests here
}
