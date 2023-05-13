/*
 * CS 152, Spring 2022
 * Homework #1 Student Test Code
 *
 * Add your tests to this file.  
 * Run make student_test_homework1 to compile your tests 
 * and ./student_test_homework1 to run your tests.
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "homework1.h"

/** Add your test functions (if any) here **/

int main(int argc, char **argv) {
    // Sample test for Exercise #1
    if (are_friendly(12, 15, 3)) {
        printf("Passed are_friendly test #1\n");
    } else {
        printf("Failed are_friendly test #1\n");
    }

    // Sample test for Exercise #2
    if (degree_of_friendship(12, 15) == 2) {
        printf("Passed degree_of_friendship test #1\n");
    } else {
        printf("Failed degree_of_friendship test #1\n");
    }

    if (degree_of_friendship(12, 36) == 6) {
        printf("Passed degree_of_friendship test #1\n");
    } else {
        printf("Failed degree_of_friendship test #1\n");
    }    

    // Sample test for Exercise #3
    if (has_even_parity(4)) {
        printf("Passed has_even_parity test #1\n");
    } else {
        printf("Failed has_even_parity test #1\n");
    }
    if (has_even_parity(5)) {
        printf("Failed has_even_parity test #2\n");
    } else {
        printf("Passed has_even_parity test #2\n");
    }

    if (has_even_parity(0)) {
        printf("Passed has_even_parity test #2\n");
    } else {
        printf("Failed has_even_parity test #2\n");
    }

    // Sample test for Exercise #4
    if (fabs(goldschmidt(4, 0.5, 10, 0.001) - 2) < 0.01) {
        printf("Passed goldschmidt test #1\n");
    } else {
        printf("Failed goldschmidt test #1\n");
    }

    // Sample test for Exercise #5
    if (index_of_highest_1(12) == 3) {
        printf("Passed index_of_highest_1 test #1\n");
    } else {
        printf("Failed index_of_highest_1 test #1\n");
    }

    // Sample test for Exercise #6
    if (is_narcissistic(153)) {
        printf("Passed is_narcissistic test #1\n");
    } else {
        printf("Failed is_narcissistic test #1\n");
    }

    // Add your tests here
}
