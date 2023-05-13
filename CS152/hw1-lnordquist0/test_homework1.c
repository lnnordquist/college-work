/*
 * CS 152, Spring 2022
 * Homework #1 Automated Tests 
 *
 * Run make test_homework1 to compile these tests and ./test_homework1
 * to run these tests.  See the homework write-up for instructions
 * on how to run a subset of the tests.
 * 
 * Do not modify this file.
 */

#include <stdbool.h>
#include <criterion/criterion.h>
#include "homework1.h"

#define EPSILON (0.01)

/* Tests for Exercise 1 */
Test(are_friendly, test0) {
    bool actual = are_friendly(1, 1, 1);
    cr_assert(actual);
}

Test(are_friendly, test1) {
    bool actual = are_friendly(4, 4, 1);
    cr_assert(actual);
}

Test(are_friendly, test2) {
    bool actual = are_friendly(4, 4, 4);
    cr_assert(actual);
}

Test(are_friendly, test3) {
    bool actual = are_friendly(2, 4, 2);
    cr_assert(actual);
}

Test(are_friendly, test4) {
    bool actual = are_friendly(4, 2, 2);
    cr_assert(actual);
}

Test(are_friendly, test5) {
    bool actual = are_friendly(2, 4, 4);
    cr_assert(!actual);
}

Test(are_friendly, test6) {
    bool actual = are_friendly(4, 2, 4);
    cr_assert(!actual);
}

Test(are_friendly, test7) {
    bool actual = are_friendly(12, 15, 1);
    cr_assert(actual);
}

Test(are_friendly, test8) {
    bool actual = are_friendly(12, 15, 2);
    cr_assert(!actual);
}

Test(are_friendly, test9) {
    bool actual = are_friendly(12, 15, 3);
    cr_assert(actual);
}

Test(are_friendly, test10) {
    bool actual = are_friendly(12, 15, 3);
    cr_assert(actual);
}

Test(are_friendly, test11) {
    bool actual = are_friendly(12, 15, 4);
    cr_assert(!actual);
}

Test(are_friendly, test12) {
    bool actual = are_friendly(12, 15, 5);
    cr_assert(!actual);
}

/* Tests for Exercise 2 */
Test(degree_of_friendship, test0) {
    int actual = degree_of_friendship(1, 1);
    cr_assert(actual == 1);
}

Test(degree_of_friendship, test1) {
    int actual = degree_of_friendship(1, 2);
    cr_assert(actual == 1);
}

Test(degree_of_friendship, test2) {
    int actual = degree_of_friendship(2, 1);
    cr_assert(actual == 1);
}

Test(degree_of_friendship, test3) {
    int actual = degree_of_friendship(2, 4);
    cr_assert(actual == 2);
}

Test(degree_of_friendship, test4) {
    int actual = degree_of_friendship(4, 2);
    cr_assert(actual == 2);
}

Test(degree_of_friendship, test5) {
    int actual = degree_of_friendship(3, 5);
    cr_assert(actual == 1);
}

Test(degree_of_friendship, test6) {
    int actual = degree_of_friendship(5, 3);
    cr_assert(actual == 1);
}

Test(degree_of_friendship, test7) {
    int actual = degree_of_friendship(12, 15);
    cr_assert(actual == 2);
}

Test(degree_of_friendship, test8) {
    int actual = degree_of_friendship(15, 12);
    cr_assert(actual == 2);
}

Test(degree_of_friendship, test9) {
    int actual = degree_of_friendship(12, 36);
    cr_assert(actual == 6);
}

Test(degree_of_friendship, test10) {
    int actual = degree_of_friendship(36, 12);
    cr_assert(actual == 6);
}

/* Tests for Exercise 3 */
Test(has_even_parity, test0) {
    bool actual = has_even_parity(1);
    cr_assert(!actual);
}

Test(has_even_parity, test1) {
    bool actual = has_even_parity(2);
    cr_assert(actual);
}

Test(has_even_parity, test2) {
    bool actual = has_even_parity(3);
    cr_assert(!actual);
}

Test(has_even_parity, test3) {
    bool actual = has_even_parity(4);
    cr_assert(actual);
}

Test(has_even_parity, test4) {
    bool actual = has_even_parity(100);
    cr_assert(actual);
}

Test(has_even_parity, test5) {
    bool actual = has_even_parity(101);
    cr_assert(!actual);
}

/* Tests for Exercise 4 */
Test(goldschmidt, test0) {
    double actual = goldschmidt(4, 0.4, 1, 0.001);
    cr_assert_float_eq(actual, 1.88, EPSILON);
}

Test(goldschmidt, test1) {
    double actual = goldschmidt(4, 0.4, 2, 0.001);
    cr_assert_float_eq(actual, 1.99, EPSILON);
}

Test(goldschmidt, test2) {
    double actual = goldschmidt(4, 0.4, 3, 0.001);
    cr_assert_float_eq(actual, 1.99, EPSILON);
}

Test(goldschmidt, test3) {
    double actual = goldschmidt(4, 0.4, 4, 0.001);
    cr_assert_float_eq(actual, 2.0, EPSILON);
}

Test(goldschmidt, test4) {
    double actual = goldschmidt(4, 0.4, 10, 0.001);
    cr_assert_float_eq(actual, 2, EPSILON);
}

Test(goldschmidt, test5) {
    double actual = goldschmidt(4, 0.6, 1, 0.001);
    cr_assert_float_eq(actual, 1.87, EPSILON);
}

Test(goldschmidt, test6) {
    double actual = goldschmidt(4, 0.6, 2, 0.001);
    cr_assert_float_eq(actual, 1.98, EPSILON);
}

Test(goldschmidt, test7) {
    double actual = goldschmidt(4, 0.6, 3, 0.001);
    cr_assert_float_eq(actual, 1.99, EPSILON);
}

Test(goldschmidt, test8) {
    double actual = goldschmidt(4, 0.6, 10, 0.001);
    cr_assert_float_eq(actual, 2, EPSILON);
}

Test(goldschmidt, test9) {
    double actual = goldschmidt(4, 0.6, 10, 0.5);
    cr_assert_float_eq(actual, 1.87, EPSILON);
}

Test(goldschmidt, test10) {
    double actual = goldschmidt(4, 0.6, 10, 0.2);
    cr_assert_float_eq(actual, 1.98, EPSILON);
}

Test(goldschmidt, test11) {
    double actual = goldschmidt(4, 0.6, 10, 0.1);
    cr_assert_float_eq(actual, 1.99, EPSILON);
}

/* Tests for Exercise 5 */
Test(index_of_highest_1, test0) {
    int actual = index_of_highest_1(1);
    cr_assert(actual == 0);
}

Test(index_of_highest_1, test1) {
    int actual = index_of_highest_1(2);
    cr_assert(actual == 1);
}

Test(index_of_highest_1, test2) {
    int actual = index_of_highest_1(3);
    cr_assert(actual == 1);
}

Test(index_of_highest_1, test3) {
    int actual = index_of_highest_1(4);
    cr_assert(actual == 2);
}

Test(index_of_highest_1, test4) {
    int actual = index_of_highest_1(20);
    cr_assert(actual == 4);
}

Test(index_of_highest_1, test5) {
    int actual = index_of_highest_1(100);
    cr_assert(actual == 6);
}

Test(index_of_highest_1, test6) {
    int actual = index_of_highest_1(1000);
    cr_assert(actual == 9);
}

Test(index_of_highest_1, test7) {
    int actual = index_of_highest_1(10000);
    cr_assert(actual == 13);
}

/* Tests for Exercise 6 */
Test(is_narcissistic, test0) {
    bool actual = is_narcissistic(1);
    cr_assert(actual);
}

Test(is_narcissistic, test1) {
    bool actual = is_narcissistic(2);
    cr_assert(actual);
}

Test(is_narcissistic, test2) {
    bool actual = is_narcissistic(5);
    cr_assert(actual);
}

Test(is_narcissistic, test3) {
    bool actual = is_narcissistic(10);
    cr_assert(!actual);
}

Test(is_narcissistic, test4) {
    bool actual = is_narcissistic(100);
    cr_assert(!actual);
}

Test(is_narcissistic, test5) {
    bool actual = is_narcissistic(152);
    cr_assert(!actual);
}

Test(is_narcissistic, test6) {
    bool actual = is_narcissistic(153);
    cr_assert(actual);
}

Test(is_narcissistic, test7) {
    bool actual = is_narcissistic(154);
    cr_assert(!actual);
}

Test(is_narcissistic, test8) {
    bool actual = is_narcissistic(1000);
    cr_assert(!actual);
}

Test(is_narcissistic, test9) {
    bool actual = is_narcissistic(9474);
    cr_assert(actual);
}