/*
 * CS 152, Spring 2022
 * Homework #2 Automated Tests 
 *
 * Run make test_homework2 to compile these tests and ./test_homework2
 * to run these tests.  See the homework write-up for instructions
 * on how to run a subset of the tests.
 * 
 * Do not modify this file.
 */

#include <stdbool.h>
#include <criterion/criterion.h>
#include "homework2.h"

Test(flip, test0) {
    int input[] = {1};
    int expected[] = {1};
    int input_len = 1;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test1) {
    int input[] = {0};
    int expected[] = {0};
    int input_len = 1;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test2) {
    int input[] = {1, 2};
    int expected[] = {2, 1};
    int input_len = 2;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test3) {
    int input[] = {0, 0};
    int expected[] = {0, 0};
    int input_len = 2;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test4) {
    int input[] = {1, 2, 3};
    int expected[] = {3, 2, 1};
    int input_len = 3;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test5) {
    int input[] = {-1, -1, -1};
    int expected[] = {-1, -1, -1};
    int input_len = 3;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test6) {
    int input[] = {1, 0, 1};
    int expected[] = {1, 0, 1};
    int input_len = 3;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test7) {
    int input[] = {1, 2, 3, 4};
    int expected[] = {4, 3, 2, 1};
    int input_len = 4;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test8) {
    int input[] = {-1, -2, -3 , -4, -5};
    int expected[] = {-5, -4, -3, -2, -1};
    int input_len = 5;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test9) {
    int input[] = {-5, -4, -3, -2, -1};
    int expected[] = {-1, -2, -3 , -4, -5};
    int input_len = 5;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test10) {
    int input[] = {1, 2, 1, 3, 4, 1, 3, 2, 0, 5};
    int expected[] = {5, 0, 2, 3, 1, 4, 3, 1, 2, 1};
    int input_len = 10;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(flip, test11) {
    int input[] = {1, 2, 1, 3, 4, 1, 3, 2, 0, 5, 2};
    int expected[] = {2, 5, 0, 2, 3, 1, 4, 3, 1, 2, 1};
    int input_len = 11;

    flip(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test0) {
    int input[] = {1};
    int expected[] = {1};
    int input_len = 1;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test1) {
    int input[] = {0};
    int expected[] = {0};
    int input_len = 1;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test2) {
    int input[] = {1, 2};
    int expected[] = {2, 1};
    int input_len = 2;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test3) {
    int input[] = {0, 0};
    int expected[] = {0, 0};
    int input_len = 2;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test4) {
    int input[] = {1, 2, 3};
    int expected[] = {3, 1, 2};
    int input_len = 3;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test5) {
    int input[] = {-1, -1, -1};
    int expected[] = {-1, -1, -1};
    int input_len = 3;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test6) {
    int input[] = {1, 0, 1};
    int expected[] = {1, 1, 0};
    int input_len = 3;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test7) {
    int input[] = {1, 2, 3, 4};
    int expected[] = {4, 1, 2, 3};
    int input_len = 4;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test8) {
    int input[] = {-1, -2, -3 , -4, -5};
    int expected[] = {-5, -1, -2, -3 , -4};
    int input_len = 5;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test9) {
    int input[] = {-5, -4, -3, -2, -1};
    int expected[] = {-1, -5, -4, -3, -2};
    int input_len = 5;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test10) {
    int input[] = {1, 2, 1, 3, 4, 1, 3, 2, 0, 5};
    int expected[] = {5, 1, 2, 1, 3, 4, 1, 3, 2, 0};
    int input_len = 10;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(shift, test11) {
    int input[] = {1, 2, 1, 3, 4, 1, 3, 2, 0, 5, 2};
    int expected[] = {2, 1, 2, 1, 3, 4, 1, 3, 2, 0, 5};
    int input_len = 11;

    shift(input, input_len);
    for (int i = 0; i < input_len; i++) {
        cr_assert_eq(input[i], expected[i]);
    }
}

Test(first_letter, test0) {
    char *input = "Hello";
    char expected[] = {'H'};
    int expected_len = 1;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test1) {
    char *input = "hi";
    char expected[] = {'h'};
    int expected_len = 1;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test2) {
    char *input = "bye!";
    char expected[] = {'b'};
    int expected_len = 1;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test3) {
    char *input = "bye hi";
    char expected[] = {'b', 'h'};
    int expected_len = 2;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test4) {
    char *input = "Hello, Goodbye!";
    char expected[] = {'H', 'G'};
    int expected_len = 2;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test5) {
    char *input = "hello hello hello";
    char expected[] = {'h', 'h', 'h'};
    int expected_len = 3;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test7) {
    char *input = "yes No maybe";
    char expected[] = {'y', 'N', 'm'};
    int expected_len = 3;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test8) {
    char *input = "yes, No MAYBE?";
    char expected[] = {'y', 'N', 'M'};
    int expected_len = 3;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test9) {
    char *input = "Hello, my name is Joe.";
    char expected[] = {'H', 'm', 'n', 'i', 'J'};
    int expected_len = 5;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test10) {
    char *input = "I AM LEARNING HOW TO PROGRAM IN C THIS QUARTER";
    char expected[] = {'I', 'A', 'L', 'H', 'T', 'P', 'I', 'C', 'T', 'Q'};
    int expected_len = 10;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(first_letter, test11) {
    char *input = "Hello, my name is Joe and my favorite color is blue";
    char expected[] = {'H', 'm', 'n', 'i', 'J', 'a', 'm', 'f', 'c', 'i', 'b'};
    int expected_len = 11;

    int actual_len;
    char *actual = first_letter(input, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(count_zeros_and_runs, test0) {
    int input[] = {0};
    int input_len = 1;
    int expected_zeros = 1;
    int expected_runs = 1;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test1) {
    int input[] = {1};
    int input_len = 1;
    int expected_zeros = 0;
    int expected_runs = 0;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test2) {
    int input[] = {0, 0};
    int input_len = 2;
    int expected_zeros = 2;
    int expected_runs = 1;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test3) {
    int input[] = {1, 1};
    int input_len = 2;
    int expected_zeros = 0;
    int expected_runs = 0;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test4) {
    int input[] = {0, 0, 0, 0};
    int input_len = 4;
    int expected_zeros = 4;
    int expected_runs = 1;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test5) {
    int input[] = {2, 1, 1, 3};
    int input_len = 4;
    int expected_zeros = 0;
    int expected_runs = 0;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test6) {
    int input[] = {0, 0, 1};
    int input_len = 3;
    int expected_zeros = 2;
    int expected_runs = 1;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test7) {
    int input[] = {1, 0, 0};
    int input_len = 3;
    int expected_zeros = 2;
    int expected_runs = 1;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test8) {
    int input[] = {1, 0, 1};
    int input_len = 3;
    int expected_zeros = 1;
    int expected_runs = 1;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test9) {
    int input[] = {0, 1, 0};
    int input_len = 3;
    int expected_zeros = 2;
    int expected_runs = 2;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test10) {
    int input[] = {0, 1, 0, 0, 1};
    int input_len = 5;
    int expected_zeros = 3;
    int expected_runs = 2;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test11) {
    int input[] = {0, 0, 1, 0, 1};
    int input_len = 5;
    int expected_zeros = 3;
    int expected_runs = 2;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test12) {
    int input[] = {1, 0, 0, 2, 0, 0, 0};
    int input_len = 7;
    int expected_zeros = 5;
    int expected_runs = 2;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test13) {
    int input[] = {0, 0, 2, 0, 0, 0, 1};
    int input_len = 7;
    int expected_zeros = 5;
    int expected_runs = 2;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test14) {
    int input[] = {2, 1, 0, 0, 0, 3, 2, 0, 0, 4, 0, 0, 0, 0, 5};
    int input_len = 15;
    int expected_zeros = 9;
    int expected_runs = 3;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(count_zeros_and_runs, test15) {
    int input[] = {0, 2, 1, 0, 0, 0, 3, 2, 0, 0, 4, 0, 0, 0, 0, 5, 0, 0};
    int input_len = 18;
    int expected_zeros = 12;
    int expected_runs = 5;

    int actual_zeros;
    int actual_runs;
    count_zeros_and_runs(input, input_len, &actual_zeros, &actual_runs);
    cr_assert_eq(expected_zeros, actual_zeros);
    cr_assert_eq(expected_runs, actual_runs);
}

Test(saves_space, test0) {
    int input[] = {0};
    int input_len = 1;
    bool expected = false;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test1) {
    int input[] = {0, 1};
    int input_len = 2;
    bool expected = false;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test2) {
    int input[] = {0, 0, 1};
    int input_len = 3;
    bool expected = false;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test3) {
    int input[] = {2, 0, 0, 0}; // 2, 0, 3
    int input_len = 4;
    bool expected = true;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test4) {
    int input[] = {2, 0, 0, 0, 1, 3, 0, 0}; // 2 0 3 1 3 0 2
    int input_len = 8;
    bool expected = true;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test5) {
    int input[] = {2, 0, 0, 1, 3, 0}; // 2 0 2 1 3 0 1
    int input_len = 6;
    bool expected = false;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test6) {
    int input[] = {2, 0, 1, 3, 0, 0, 0, 3, 4, 5, 0, 6}; // 2 0 1 1 3 0 3 3 4 5 0 1 6
    int input_len = 12;
    bool expected = false;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(saves_space, test7) {
    int input[] = {1, 0, 0, 2, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1}; // 1 0 2 2 0 3 5 3 2 0 4 1
    int input_len = 15;
    bool expected = true;

    bool actual = saves_space(input, input_len);
    cr_assert_eq(expected, actual);
}

Test(encode, test0) {
    int input[] = {1};
    int input_len = 1;
    int expected[] = {1};
    int expected_len = 1;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test1) {
    int input[] = {1, 2};
    int input_len = 2;
    int expected[] = {1, 2};
    int expected_len = 2;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test3) {
    int input[] = {0};
    int input_len = 1;
    int expected[] = {0, 1};
    int expected_len = 2;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test4) {
    int input[] = {0, 0};
    int input_len = 2;
    int expected[] = {0, 2};
    int expected_len = 2;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test5) {
    int input[] = {0, 0, 0};
    int input_len = 3;
    int expected[] = {0, 3};
    int expected_len = 2;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test6) {
    int input[] = {0, 0, 1};
    int input_len = 3;
    int expected[] = {0, 2, 1};
    int expected_len = 3;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test7) {
    int input[] = {1, 0, 0};
    int input_len = 3;
    int expected[] = {1, 0, 2};
    int expected_len = 3;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test8) {
    int input[] = {0, 1, 0, 0, 0};
    int input_len = 5;
    int expected[] = {0, 1, 1, 0, 3};
    int expected_len = 5;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test9) {
    int input[] = {0, 0, 2, 0, 0, 0};
    int input_len = 6;
    int expected[] = {0, 2, 2, 0, 3};
    int expected_len = 5;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test10) {
    int input[] = {1, 0, 0, 2, 0, 0, 0};
    int input_len = 7;
    int expected[] = {1, 0, 2, 2, 0, 3};
    int expected_len = 6;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test11) {
    int input[] = {1, 0, 0, 2, 0, 0, 0, 4, 3, 0, 0};
    int input_len = 11;
    int expected[] = {1, 0, 2, 2, 0, 3, 4, 3, 0, 2};
    int expected_len = 10;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test12) {
    int input[] = {0, 0, 2, 0, 0, 0, 0, 0, 4, 3, 0, 5, 5};
    int input_len = 13;
    int expected[] = {0, 2, 2, 0, 5, 4, 3, 0, 1, 5, 5};
    int expected_len = 11;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test13) {
    int input[] = {0, 0, 2, 0, 0, 0, 0, 0, 4, 3, 1, 1, 0, 0, 0, 5};
    int input_len = 16;
    int expected[] = {0, 2, 2, 0, 5, 4, 3, 1, 1, 0, 3, 5};
    int expected_len = 12;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(encode, test14) {
    int input[] = {3, 1, 1, 0, 5, 0, 1, 0, 0, 0, 2, 0, 5, 0, 0, 4};
    int input_len = 16;
    int expected[] = {3, 1, 1, 0, 1, 5, 0, 1, 1, 0, 3, 2, 0, 1, 5, 0, 2, 4};
    int expected_len = 18;

    int actual_len;
    int *actual = encode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test0) {
    int input[] = {1};
    int input_len = 1;
    int expected[] = {1};
    int expected_len = 1;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test1) {
    int input[] = {1, 2};
    int input_len = 2;
    int expected[] = {1, 2};
    int expected_len = 2;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test3) {
    int input[] = {0, 1};
    int input_len = 2;
    int expected[] = {0};
    int expected_len = 1;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test4) {
    int input[] = {0, 2};
    int input_len = 2;
    int expected[] = {0, 0};
    int expected_len = 2;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test5) {
    int input[] = {0, 3};
    int input_len = 2;
    int expected[] = {0, 0, 0};
    int expected_len = 3;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test6) {
    int input[] = {0, 2, 1};
    int input_len = 3;
    int expected[] = {0, 0, 1};
    int expected_len = 3;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test7) {
    int input[] = {1, 0, 2};
    int input_len = 3;
    int expected[] = {1, 0, 0};
    int expected_len = 3;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test8) {
    int input[] = {0, 1, 1, 0, 3};
    int input_len = 5;
    int expected[] = {0, 1, 0, 0, 0};
    int expected_len = 5;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test9) {
    int input[] = {0, 2, 2, 0, 3};
    int input_len = 5;
    int expected[] = {0, 0, 2, 0, 0, 0};
    int expected_len = 6;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test10) {
    int input[] = {1, 0, 2, 2, 0, 3};
    int input_len = 6;
    int expected[] = {1, 0, 0, 2, 0, 0, 0};
    int expected_len = 7;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test11) {
    int input[] = {1, 0, 2, 2, 0, 3, 4, 3, 0, 2};
    int input_len = 10;
    int expected[] = {1, 0, 0, 2, 0, 0, 0, 4, 3, 0, 0};
    int expected_len = 11;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test12) {
    int input[] = {0, 2, 2, 0, 5, 4, 3, 0, 1, 5, 5};
    int input_len = 11;
    int expected[] = {0, 0, 2, 0, 0, 0, 0, 0, 4, 3, 0, 5, 5};
    int expected_len = 13;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test13) {
    int input[] = {0, 2, 2, 0, 5, 4, 3, 1, 1, 0, 3, 5};
    int input_len = 12;
    int expected[] = {0, 0, 2, 0, 0, 0, 0, 0, 4, 3, 1, 1, 0, 0, 0, 5};
    int expected_len = 16;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}

Test(decode, test14) {
    int input[] = {3, 1, 1, 0, 1, 5, 0, 1, 1, 0, 3, 2, 0, 1, 5, 0, 2, 4};
    int input_len = 18;
    int expected[] = {3, 1, 1, 0, 5, 0, 1, 0, 0, 0, 2, 0, 5, 0, 0, 4};
    int expected_len = 16;

    int actual_len;
    int *actual = decode(input, input_len, &actual_len);
    cr_assert_eq(expected_len, actual_len);
    for (int i = 0; i < expected_len; i++) {
        cr_assert_eq(expected[i], actual[i]);
    }
    free(actual);
}