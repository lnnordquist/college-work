/*
 * CS 152, Spring 2022
 * Homework #1 Deliverables
 *
 * Name: Lars Nordquist
 *
 * Sources used:
 *   None
 *                                                                                                                                          
 * People consulted:
 *   None
 *
 */

 /*******************************************************************
  * IMPORTANT NOTE.  Some tasks in this homework require you to use a
  * restricted subset of C.  You will not get full credit for these
  * question if your code does not meet these restrictions.
  *******************************************************************/


#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "homework1.h"

/*
 * Exercise 1
 *
 * are_friendly: Determine whether two integers are friendly
 * with respect to a divisor.
 *
 * num1: the first integer
 * num2: the second integer
 * divisor: the divisor
 *
 * Returns: true if num1 and num2 are friendly, false otherwise. 
 */
bool are_friendly(int num1, int num2, int divisor) {

    bool common_div = ((num1 % divisor == 0) && (num2 % divisor == 0));
    //printf("%d and %d are friendly with %d: %d\n", num1, num2, divisor, common_div);
    return common_div;
}


/* Exercise 2
 *
 * degree_of_friendship: Find the number of common divisors
 * for two integers.
 *
 * num1: the first integer
 * num2: the second integer
 *
 * Returns: The number of common divisors.
 */
int degree_of_friendship(int num1, int num2) {
    int num = (num1 < num2)? num1 : num2;
    int degree_acc = 0;
    for(int i = 1; i <= num; i++) {
        if (are_friendly(num1, num2, i)) {
            degree_acc += 1;
        } else {
            continue;
        }
    }

    //printf("%d and %d have a degree of %d\n", num1, num2, degree_acc);
    return degree_acc;
}


/* Exercise 3 
 *
 * has_even_parity: Determine whether an integer has even parity
 * (i.e., whether it's even).
 *
 * Restriction: May NOT use the modulus operator (%) for this exercise.
 *
 * num: the integer
 *
 * Returns: true if num is even, false otherwise.
 */
bool has_even_parity(int num) {

    bool parity = !(num & 1);
    if (parity) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
    // Replace false with an appropriate return value
    return parity;
}


/* Exercise 4
 *
 * goldschmidt: Compute the square root of a number using Goldschmidt's
 * algorithm.
 * 
 * N: the number to find the square root of
 * est: an estimate for 1/sqrt(N)
 * max_iters: the maximum number of iteration to perform
 * tol: the convergence tolerance
 *
 * Returns: An approximation of the square root of N.
 */

double goldschmidt(double N, double est, int max_iters, double tol) {
    double b_n = N;
    double y_n = est;
    double x_n = b_n * y_n;
    int i = 1;
    while((fabs(b_n - 1) > tol) && i <= max_iters) {
        b_n *= (y_n * y_n);
        y_n = (3.0-b_n)/2.0;
        x_n *= y_n;
        i++;
    }
    //printf("sqrt %f, %d times: b_n is %f, y_n is %f, x_n is %f\n", N, i, b_n, y_n, x_n);
    return x_n;
}


/* Exercise 5
 *
 * index_of_highest_1: Find the index of the highest-order 1 bit
 * in the binary representation of an integer.
 *
 * Restrictions: You may only use bitwise operations (&, |, ~, >>, and
 * <<) for this task.  You may not use the arithmetic operators (*, /, %).
 *
 * num: the integer
 *
 * Returns: The index of the highest-order 1, or -1 if the integer does
 * not have a 1 in its binary representation.
 */
int index_of_highest_1(unsigned int num) {
    int index = 0;
    if(num != 0) {
        while(num != 1) {
            num = num >> 1;   
            index++;
        }
    } else {
        index -= 1;
        }
    //printf("Index of %d is %d\n", num, index);
    return index;
}

/* Exercise 6
 *
 * is_narcissistic: Determine whether or not an integer is narcissistic.
 *
 * num: the integer
 *
 * Returns: true if num is narcissistic, false otherwise.
 */
bool is_narcissistic(int num) {
    assert(num > 0);
    int digts = 0;
    int num_d = num;
    while(num_d != 0) {
        num_d /= 10;
        digts++;
    }
    int num_n = num;
    int acc = 0;
    while (num_n !=0) {
        acc += pow((num_n % 10), digts);
        num_n /= 10;
    }
    //printf("num is %d, acc is %d\n", num, acc);
    return (num == acc);
}