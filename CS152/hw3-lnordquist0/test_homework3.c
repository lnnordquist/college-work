/*
 * CS 152, Spring 2022
 * Homework #3 Automated Tests 
 *
 * Run make test_homework3 to compile these tests and ./test_homework3
 * to run these tests.  See the homework write-up for instructions
 * on how to run a subset of the tests.
 * 
 * Do not modify this file.
 */

#include <stdbool.h>
#include <string.h>
#include <criterion/criterion.h>
#include "homework3.h"

#define EPSILON (0.0000001)

void test_new_color(uint8_t red, uint8_t green, uint8_t blue, char *name) {
    color_t *actual = new_color(red, green, blue, name);

    cr_assert_eq(actual->red, red);
    cr_assert_eq(actual->green, green);
    cr_assert_eq(actual->blue, blue);
    cr_assert_eq(strcmp(actual->name, name), 0);
    
    free_color(actual);
}

Test(new_color, test0) {
    test_new_color(0, 0, 0, "black");
}

Test(new_color, test1) {
    test_new_color(255, 255, 255, "white");
}

Test(new_color, test2) {
    test_new_color(255, 0, 0, "red");
}

Test(new_color, test3) {
    test_new_color(0, 255, 0, "green");
}

Test(new_color, test4) {
    test_new_color(0, 0, 255, "blue");
}

Test(new_color, test5) {
    test_new_color(105, 107, 105, "gray");
}

Test(new_color, test6) {
    test_new_color(252, 244, 3, "yellow");
}

Test(new_color, test7) {
    test_new_color(48, 138, 47, "forest green");
}

Test(new_color, test8) {
    test_new_color(159, 255, 191, "sea foam green");
}

Test(new_color, test9) {
    test_new_color(130, 217, 178, "mint");
}

void test_copy_color(uint8_t red, uint8_t green, uint8_t blue, char *name) {
    color_t *expected = new_color(red, green, blue, name);
    color_t *actual = copy_color(expected);

    cr_assert_eq(expected->red, actual->red);
    cr_assert_eq(expected->green, actual->green);
    cr_assert_eq(expected->blue, actual->blue);
    cr_assert_eq(strcmp(expected->name, actual->name), 0);

    free_color(expected);
    free_color(actual);
}

Test(copy_color, test0) {
    test_copy_color(0, 0, 0, "black");
}

Test(copy_color, test1) {
    test_copy_color(255, 255, 255, "white");
}

Test(copy_color, test2) {
    test_copy_color(255, 0, 0, "red");
}

Test(copy_color, test3) {
    test_copy_color(0, 255, 0, "green");
}

Test(copy_color, test4) {
    test_copy_color(0, 0, 255, "blue");
}

Test(copy_color, test5) {
    test_copy_color(105, 107, 105, "gray");
}

Test(copy_color, test6) {
    test_copy_color(252, 244, 3, "yellow");
}

Test(copy_color, test7) {
    test_copy_color(48, 138, 47, "forest green");
}

Test(copy_color, test8) {
    test_copy_color(159, 255, 191, "sea foam green");
}

Test(copy_color, test9) {
    test_copy_color(130, 217, 178, "mint");
}

void test_luminance(uint8_t red, uint8_t green, uint8_t blue, char *name) {
    color_t *color = new_color(red, green, blue, name);
    double actual = luminance(color);
    double expected = 0.2126*red + 0.7152*green + 0.0722*blue;

    cr_assert_float_eq(actual, expected, EPSILON);

    free_color(color);
}

Test(luminance, test0) {
    test_luminance(0, 0, 0, "black");
}

Test(luminance, test1) {
    test_luminance(255, 255, 255, "white");
}

Test(luminance, test2) {
    test_luminance(255, 0, 0, "red");
}

Test(luminance, test3) {
    test_luminance(0, 255, 0, "green");
}

Test(luminance, test4) {
    test_luminance(0, 0, 255, "blue");
}

Test(luminance, test5) {
    test_luminance(105, 107, 105, "gray");
}

Test(luminance, test6) {
    test_luminance(252, 244, 3, "yellow");
}

Test(luminance, test7) {
    test_luminance(48, 138, 47, "forest green");
}

Test(luminance, test8) {
    test_luminance(159, 255, 191, "sea foam green");
}

Test(luminance, test9) {
    test_luminance(130, 217, 178, "mint");
}

void test_grayscale(uint8_t red, uint8_t green, uint8_t blue, char *name) {
    color_t *color = new_color(red, green, blue, name);
    color_t *actual = grayscale(color);
    uint8_t expected = (77*red + 150*green + 29*blue)/256.0;

    cr_assert_eq(actual->red, expected);
    cr_assert_eq(actual->green, expected);
    cr_assert_eq(actual->blue, expected);
    cr_assert_eq(strcmp(actual->name, "gray"), 0);

    free_color(color);
    free_color(actual);
}

Test(grayscale, test0) {
    test_grayscale(0, 0, 0, "black");
}

Test(grayscale, test1) {
    test_grayscale(255, 255, 255, "white");
}

Test(grayscale, test2) {
    test_grayscale(255, 0, 0, "red");
}

Test(grayscale, test3) {
    test_grayscale(0, 255, 0, "green");
}

Test(grayscale, test4) {
    test_grayscale(0, 0, 255, "blue");
}

Test(grayscale, test5) {
    test_grayscale(105, 107, 105, "gray");
}

Test(grayscale, test6) {
    test_grayscale(252, 244, 3, "yellow");
}

Test(grayscale, test7) {
    test_grayscale(48, 138, 47, "forest green");
}

Test(grayscale, test8) {
    test_grayscale(159, 255, 191, "sea foam green");
}

Test(grayscale, test9) {
    test_grayscale(130, 217, 178, "mint");
}

void test_stripe(uint8_t red, uint8_t green, uint8_t blue, char *name, int len) {
    color_t *color = new_color(red, green, blue, name);
    color_t **actual = make_stripe(color, len);

    for (int i = 0; i < len; i++) {
        cr_assert_eq(actual[0]->red, red);
        cr_assert_eq(actual[0]->green, green);
        cr_assert_eq(actual[0]->blue, blue);
        cr_assert_eq(strcmp(actual[0]->name, name), 0);
    }

    free_color(color);
    free_stripe(actual, len);
}

Test(make_stripe, test0) {
    test_stripe(0, 0, 0, "black", 1);
}

Test(make_stripe, test1) {
    test_stripe(0, 0, 0, "black", 2);
}

Test(make_stripe, test2) {
    test_stripe(0, 0, 0, "black", 3);
}

Test(make_stripe, test3) {
    test_stripe(0, 0, 0, "black", 10);
}

Test(make_stripe, test4) {
    test_stripe(250, 250, 250, "white", 4);
}

Test(make_stripe, test5) {
    test_stripe(48, 138, 47, "forest green", 5);
}

Test(make_stripe, test6) {
    test_stripe(255, 0, 0, "red", 6);
}

Test(make_stripe, test7) {
    test_stripe(252, 244, 3, "yellow", 12);
}

void test_pack_color(uint8_t red, uint8_t green, uint8_t blue, char *name, uint32_t expected) {
    color_t *color = new_color(red, green, blue, name);
    uint32_t actual = pack_color(color);

    cr_assert_eq(actual, expected);

    free_color(color);
}


Test(pack_color, test0) {
    test_pack_color(0, 0, 0, "black", 0x00000000);
}

Test(pack_color, test1) {
    test_pack_color(255, 255, 255, "white", 0x00FFFFFF);
}

Test(pack_color, test2) {
    test_pack_color(255, 0, 0, "red", 0x00FF0000);
}

Test(pack_color, test3) {
    test_pack_color(0, 255, 0, "green", 0x0000FF00);
}

Test(pack_color, test4) {
    test_pack_color(0, 0, 255, "blue", 0x000000FF);
}

Test(pack_color, test5) {
    test_pack_color(105, 107, 105, "gray", 0x00696B69);
}

Test(pack_color, test6) {
    test_pack_color(252, 244, 3, "yellow", 0x00FCF403);
}

Test(pack_color, test7) {
    test_pack_color(48, 138, 47, "forest green", 0x00308A2F);
}

Test(pack_color, test8) {
    test_pack_color(159, 255, 191, "sea foam green", 0x009FFFBF);
}

Test(pack_color, test9) {
    test_pack_color(130, 217, 178, "mint", 0x0082D9B2);
}

void test_unpack_colors(uint32_t *packed_colors, char **names, 
                        uint8_t *reds, uint8_t *greens, uint8_t *blues, int len) {

    color_t **actual = unpack_colors(packed_colors, names, len);
    for (int i = 0; i < len; i++) {
        cr_assert_eq(actual[i]->red, reds[i]);
        cr_assert_eq(actual[i]->green, greens[i]);
        cr_assert_eq(actual[i]->blue, blues[i]);
        cr_assert_eq(strcmp(actual[i]->name, names[i]), 0);
    }

    free_stripe(actual, len);
}

Test(unpack_colors, test0) {
    uint32_t packed_colors[] = {0};
    char *names[] = {"black"};
    uint8_t reds[] = {0};
    uint8_t greens[] = {0};
    uint8_t blues[] = {0};
    test_unpack_colors(packed_colors, names, reds, greens, blues, 1);
}

Test(unpack_colors, test1) {
    uint32_t packed_colors[] = {0x00000000, 0x00FFFFFF};
    char *names[] = {"black", "white"};
    uint8_t reds[] = {0x00, 0xFF};
    uint8_t greens[] = {0x00, 0xFF};
    uint8_t blues[] = {0x00, 0xFF};
    test_unpack_colors(packed_colors, names, reds, greens, blues, 2);
}

Test(unpack_colors, test2) {
    uint32_t packed_colors[] = {0x00FF0000, 0x0000FF00, 0x000000FF};
    char *names[] = {"red", "green", "blue"};
    uint8_t reds[] = {0xFF, 0x00, 0x00};
    uint8_t greens[] = {0x00, 0xFF, 0x00};
    uint8_t blues[] = {0x00, 0x00, 0xFF};
    test_unpack_colors(packed_colors, names, reds, greens, blues, 3);
}

Test(unpack_colors, test3) {
    uint32_t packed_colors[] = {0x00696B69, 0x00FCF403, 0x00308A2F, 0x009FFFBF, 0x0082D9B2};
    char *names[] = {"gray", "yellow", "forest green", "sea foam green", "mint"};
    uint8_t reds[] = {0x69, 0xFC, 0x30, 0x9F, 0x82};
    uint8_t greens[] = {0x6B, 0xF4, 0x8A, 0xFF, 0xD9};
    uint8_t blues[] = {0x69, 0x03, 0x2F, 0xBF, 0xB2};
    test_unpack_colors(packed_colors, names, reds, greens, blues, 5);
}

void test_shopping_list_amounts(ingredient_t *pantry, int p_len, 
                                ingredient_t *recipe, int r_len, double *expected) {
    double *actual = shopping_list_amounts(pantry, p_len, recipe, r_len);

    for (int i = 0; i < r_len; i++) {
        cr_assert_float_eq(actual[i], expected[i], EPSILON);
    }

    free(actual);
}

Test(shopping_list_amounts, test0) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t recipe[] = {food1};
    ingredient_t pantry[0];
    double expected[] = {100};

    test_shopping_list_amounts(pantry, 0, recipe, 1, expected);
}

Test(shopping_list_amounts, test1) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[0];
    double expected[] = {100, 300};

    test_shopping_list_amounts(pantry, 0, recipe, 2, expected);
}

Test(shopping_list_amounts, test2) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3};
    double expected[] = {100, 300};

    test_shopping_list_amounts(pantry, 1, recipe, 2, expected);
}

Test(shopping_list_amounts, test3) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4};
    double expected[] = {100, 300};

    test_shopping_list_amounts(pantry, 2, recipe, 2, expected);
}

Test(shopping_list_amounts, test4) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 50);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food5, food4};
    double expected[] = {50, 300};

    test_shopping_list_amounts(pantry, 3, recipe, 2, expected);
}

Test(shopping_list_amounts, test5) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 100);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4, food5};
    double expected[] = {0, 300};

    test_shopping_list_amounts(pantry, 3, recipe, 2, expected);
}

Test(shopping_list_amounts, test6) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 125);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4, food5};
    double expected[] = {0, 300};

    test_shopping_list_amounts(pantry, 3, recipe, 2, expected);
}

Test(shopping_list_amounts, test7) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 150);
    ingredient_t food6 = new_ingredient("sugar", 100);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4, food5, food6};
    double expected[] = {0, 200};

    test_shopping_list_amounts(pantry, 4, recipe, 2, expected);
}

Test(shopping_list_amounts, test8) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 150);
    ingredient_t food6 = new_ingredient("sugar", 100);
    ingredient_t recipe[] = {food2, food1};
    ingredient_t pantry[] = {food3, food6, food4, food5};
    double expected[] = {200, 0};

    test_shopping_list_amounts(pantry, 4, recipe, 2, expected);
}

Test(shopping_list_amounts, test9) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 150);
    ingredient_t food6 = new_ingredient("sugar", 350);
    ingredient_t recipe[] = {food2, food1};
    ingredient_t pantry[] = {food3, food6, food4, food5};
    double expected[] = {0, 0};

    test_shopping_list_amounts(pantry, 4, recipe, 2, expected);
}

void test_shopping_list(ingredient_t *pantry, int p_len, 
                        ingredient_t *recipe, int r_len, 
                        int expected_len, ingredient_t *expected) {

    int actual_len;
    ingredient_t *actual = shopping_list(pantry, p_len, recipe, r_len, &actual_len);

    cr_assert_eq(actual_len, expected_len);
    for (int i = 0; i < actual_len; i++) {
        cr_assert_eq(strcmp(actual[i].food_name, expected[i].food_name), 0);
        cr_assert_float_eq(actual[i].amount, expected[i].amount, EPSILON);
    }

    free(actual);
}

Test(shopping_list, test0) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t recipe[] = {food1};
    ingredient_t pantry[0];
    int expected_len = 1;
    ingredient_t expected[] = {food1};

    test_shopping_list(pantry, 0, recipe, 1, expected_len, expected);
}

Test(shopping_list, test1) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[0];
    int expected_len = 2;
    ingredient_t expected[] = {food1, food2};

    test_shopping_list(pantry, 0, recipe, 2, expected_len, expected);
}

Test(shopping_list, test2) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3};
    int expected_len = 2;
    ingredient_t expected[] = {food1, food2};

    test_shopping_list(pantry, 1, recipe, 2, expected_len, expected);
}

Test(shopping_list, test3) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4};
    int expected_len = 2;
    ingredient_t expected[] = {food1, food2};

    test_shopping_list(pantry, 2, recipe, 2, expected_len, expected);
}

Test(shopping_list, test4) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 50);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food5, food4};
    int expected_len = 2;
    ingredient_t expected[] = {food5, food2};

    test_shopping_list(pantry, 3, recipe, 2, expected_len, expected);
}

Test(shopping_list, test5) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 100);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4, food5};
    int expected_len = 1;
    ingredient_t expected[] = {food2};

    test_shopping_list(pantry, 3, recipe, 2, expected_len, expected);
}

Test(shopping_list, test6) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 125);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4, food5};
    int expected_len = 1;
    ingredient_t expected[] = {food2};

    test_shopping_list(pantry, 3, recipe, 2, expected_len, expected);
}

Test(shopping_list, test7) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 150);
    ingredient_t food6 = new_ingredient("sugar", 100);
    ingredient_t recipe[] = {food1, food2};
    ingredient_t pantry[] = {food3, food4, food5, food6};
    int expected_len = 1;
    ingredient_t food7 = new_ingredient("sugar", 200);
    ingredient_t expected[] = {food7};

    test_shopping_list(pantry, 4, recipe, 2, expected_len, expected);
}

Test(shopping_list, test8) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 150);
    ingredient_t food6 = new_ingredient("sugar", 100);
    ingredient_t recipe[] = {food2, food1};
    ingredient_t pantry[] = {food3, food6, food4, food5};
    int expected_len = 1;
    ingredient_t food7 = new_ingredient("sugar", 200);
    ingredient_t expected[] = {food7};

    test_shopping_list(pantry, 4, recipe, 2, expected_len, expected);
}

Test(shopping_list, test9) {
    ingredient_t food1 = new_ingredient("peanut butter", 100);
    ingredient_t food2 = new_ingredient("sugar", 300);
    ingredient_t food3 = new_ingredient("honey", 300);
    ingredient_t food4 = new_ingredient("flour", 300);
    ingredient_t food5 = new_ingredient("peanut butter", 150);
    ingredient_t food6 = new_ingredient("sugar", 350);
    ingredient_t recipe[] = {food2, food1};
    ingredient_t pantry[] = {food3, food6, food4, food5};
    int expected_len = 0;
    ingredient_t expected[0];

    test_shopping_list(pantry, 4, recipe, 2, expected_len, expected);
}