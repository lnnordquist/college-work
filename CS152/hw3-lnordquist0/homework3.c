/*
 * Homework #3 Deliverables
 *
 * Name: Lars Nordqusit
 *
 * Sources used: None
 *
 * People consulted: Liam Lee Kitt
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "homework3.h"
extern char* strdup(const char*);

/* Part 1: Colors */

/*
 * new_color: Create a new heap-allocated color
 *
 * red: red value
 * green: green value
 * blue: blue value
 * name: name of color
 *
 * Returns: Heap-allocated color struct with heap-allocated name
 */
color_t *new_color(uint8_t red, uint8_t green, uint8_t blue, char *name) {
    assert(name != NULL);
    color_t *color = (color_t *) malloc(sizeof(color_t));
    if (color == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }
    char *c_name = (char *) malloc(sizeof(name));
    if (c_name == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }
    c_name = strdup(name);
    uint8_t nred = red, ngreen = green, nblue = blue;
    color->red = nred;
    color->green = ngreen;
    color->blue = nblue;
    color->name = c_name;

    return color;
} 

/*
 * copy_color: Create a new heap-allocated copy of a color
 *
 * c: color to copy
 *
 * Returns: Heap-allocated color struct with heap-allocated name
 */
color_t *copy_color(color_t *c) {
    assert(c != NULL);
    color_t *c_color = new_color(c->red, c->green, c->blue, c->name);
    return c_color;
}

/*
 * free_color: Free a heap-allocated color
 *
 * c: color to free
 *
 * Returns: Nothing, frees c
 */
void free_color(color_t *c) {
    assert(c != NULL);
    
    free(c->name);
    free(c);
    return;
}

/*
 * luminance: Compute the luminance of a color using the
 *     formula: 0.2126*R + 0.7152*G + 0.0722*B
 * 
 * c: color
 * 
 * Returns: the luminance of c
 */
double luminance(color_t *c) {
    assert(c != NULL);
    double lum = 0.2126*(c->red) + 0.7152*(c->green) + 0.0722*(c->blue);
    return lum;
}

/*
 * grayscale: Create a heap-allocated grayscale version of a color
 *    using the forumla: (77*R + 150*G + 29*B)/256
 *
 * c: color
 *
 * Returns: Heap-allocated grayscale version of c with the name "gray"
 */
color_t *grayscale(color_t *c) {
    assert(c != NULL);
    char *gray_name = "gray";
    double gray_av = (77.0*(c->red) + 150.0*(c->green) + 29.0*(c->blue))/256.0;
    color_t *gray = new_color(gray_av, gray_av, gray_av, gray_name);
    return gray;
}

/*
 * make_stripe: Create a strip of a single color
 *
 * c: color
 * stripe_len: length of the strip
 *
 * Returns: An array (stripe) of colors
 */
color_t **make_stripe(color_t *c, int stripe_len) {
    assert(c != NULL);
    assert(stripe_len > 0);
    color_t **stripe = (color_t **) malloc(sizeof(color_t*) * stripe_len);
    if (stripe == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }
    for(int i = 0; i<stripe_len; i++){
        stripe[i] = copy_color(c);
    }
    return stripe;
}

/*
 * free_stripe: Free a stripe of colors
 *
 * stripe: array of colors
 * stripe_len: length of the strip
 *
 * Returns: Nothing, frees stripe
 */
void free_stripe(color_t **stripe, int stripe_len) {
    assert(stripe != NULL);
    assert(stripe_len > 0);
    for(int i = 0; i<stripe_len; i++){
        free_color(stripe[i]);
    }

    return;
}

/*
 * pack_color: Pack the values of a color into 32 bits using: 0RGB
 *
 * c: color
 *
 * Returns: Packed version of c in a 32-bit unsigned integer
 */
uint32_t pack_color(color_t *c) {
    assert(c != NULL);
    uint32_t packed = c->red;
    packed = packed << 8;
    packed += c->green;
    packed = packed << 8;
    packed += c->blue;
    return packed;
}

/*
 * unpack_colors: Unpack an array of 32-bit packed colors
 *
 * packed_colors: array of 32-bit packed colors
 * names: array of names of packed colors
 * num_colors: number of colors in the array
 *
 * Returns: Array of pointers to color structs, unpacked
 */
color_t **unpack_colors(uint32_t *packed_colors, char **names, int num_colors) {
    assert(packed_colors != NULL);
    assert(names != NULL);
    assert(num_colors > 0);
    color_t **unpacked_colors = (color_t **) malloc(sizeof(color_t*) * num_colors);
    if (unpacked_colors == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }
    
    for(int i = 0; i<num_colors; i++){
        uint8_t unp_blue = packed_colors[i];
        uint8_t unp_green = packed_colors[i] >> 8;
        uint8_t unp_red = packed_colors[i] >> 16;
        unpacked_colors[i] = new_color(unp_red, unp_green, unp_blue, names[i]);
    }
    return unpacked_colors;
}

/* Part 2: Ingredients */

/*
 * shopping_list_amounts: Determine the amount of each ingredient that is 
 *     needed to make a recipe given a list of ingredients in a pantry 
 *     and a list of ingredients in a recipe.
 *
 * pantry: array of ingredients
 * pantry_len: number of ingredients in the pantry
 * recipe: array of ingredients
 * recipe_len: number of ingredients in the recipe
 *
 * Returns: An array of ingredient amounts where element i is the number of units
 *     of ingredient i that are needed
 */
double *shopping_list_amounts(ingredient_t *pantry, int pantry_len, 
                              ingredient_t *recipe, int recipe_len) {
    assert(pantry != NULL);
    assert(recipe != NULL);
    assert(recipe_len > 0);

    double *shopping_list = (double *) malloc(sizeof(recipe));
    if (shopping_list == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }

    for(int i = 0; i<recipe_len; i++){
        shopping_list[i] = recipe[i].amount;
        for(int j = 0; j<pantry_len; j++){
            if(strcmp(recipe[i].food_name, pantry[j].food_name)==0){
                if(recipe[i].amount > pantry[j].amount){
                    shopping_list[i] = recipe[i].amount - pantry[j].amount;
                }else {
                    shopping_list[i] = 0;
                }
            }
        }
    }
    return shopping_list;
}

/*
 * new_ingredient: Create a new stack-allocated ingredient
 *
 * food_name: name of ingredient
 * amount: amount of ingredient
 *
 * Returns: Ingredient struct
 */
ingredient_t new_ingredient(char *food_name, double amount) {
    assert(food_name != NULL);
    assert(amount > 0);

    ingredient_t new;
    new.food_name = food_name;
    new.amount = amount;
    return new;
}

/*
 * shopping_list: Create a shopping list containing the ingredients that are 
 *     needed to make a recipe given a list of ingredients in a pantry 
 *     and a list of ingredients in a recipe.
 *
 * pantry: array of ingredients
 * pantry_len: number of ingredients in the pantry
 * recipe: array of ingredients
 * recipe_len: number of ingredients in the recipe
 * shopping_list_len: length of the shopping list (out parameter)
 *
 * Returns: An array of ingredients
 */
ingredient_t *shopping_list(ingredient_t *pantry, int pantry_len, 
                            ingredient_t *recipe, int recipe_len,
                            int *shopping_list_len) {
    assert(pantry != NULL);
    assert(recipe != NULL);
    assert(recipe_len > 0);
    assert(shopping_list_len != NULL);

    ingredient_t *shopping_list = (ingredient_t *) malloc(sizeof(recipe));
    //unsure the max length of an ingredient so I assumed about 20 chars
    if (shopping_list == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }

    *shopping_list_len = 0;
    double *unfiltered_list = shopping_list_amounts(pantry, pantry_len, recipe, recipe_len);
    int j = 0;
    for(int i = 0; i< recipe_len ;i++){
        if(unfiltered_list[i] != 0){
            shopping_list[j].amount = unfiltered_list[i];
            shopping_list[j].food_name = recipe[i].food_name;
            j++;
            *shopping_list_len += 1;
        }
    }
    return shopping_list;
}
