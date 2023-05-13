/*
 * CS 152, Spring 2022
 * Homework #3 Student Test Code
 *
 * Add your tests to this file.  
 * Run make student_test_homework3 to compile your tests 
 * and ./student_test_homework3 to run your tests.
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "homework3.h"

/** Add your test functions (if any) here **/

int main(int argc, char **argv) {

    // Testing luminance of black
    color_t *black = new_color(0, 0, 0, "black");
    printf("Luminance of black (expecting 0): %f\n", luminance(black));
    free_color(black);

    // Add your tests here
}
