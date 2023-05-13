/*
 * CS 152, Spring 2022
 * Homework #1 Header File
 *
 * Do not modify this file
 */

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
bool are_friendly(int num1, int num2, int divisor);


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
int degree_of_friendship(int num1, int num2);


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
bool has_even_parity(int num);


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
double goldschmidt(double N, double est, int max_iters, double tol);


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
int index_of_highest_1(unsigned int num);

/* Exercise 6
 *
 * is_narcissistic: Determine whether or not an integer is narcissistic.
 *
 * num: the integer
 *
 * Returns: true if num is narcissistic, false otherwise.
 */
bool is_narcissistic(int num);
