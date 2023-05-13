/*
 * CS 152, Spring 2022
 * Homework #4 Student Test Code
 *
 * Add your tests to this file.  
 * Run make student_test_homework4 to compile your tests 
 * and ./student_test_homework4 to run your tests.
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "homework4.h"

/** Add your test functions (if any) here **/

/*
 * make_face_card: Create a card struct that represents a 
 *   face card
 *
 * face: the rank of the card
 * suit: the suit of the card
 *
 * Returns: A card with rank face, suit suit, and 
 *   tag FACE
 */
struct card make_face_card(enum face face, enum suit suit) {
    struct card card;
    card.tag = FACE;
    card.type.f.rank = face;
    card.type.f.suit = suit;

    return card;
}

/*
 * make_numbered_card: Create a card struct that represents a 
 *   numbered card
 *
 * rank: the rank of the card
 * suit: the suit of the card
 *
 * Returns: A card with rank rank, suit suit, and 
 *   tag NUMBERED
 */
struct card make_numbered_card(int rank, enum suit suit) {
    struct card card;
    card.tag = NUMBERED;
    card.type.n.rank = rank;
    card.type.n.suit = suit;

    return card;
}

/*
 * make_joker: Create a card struct that represents a 
 *   joker
 *
 * Returns: A card with tag JOKER
 */
struct card make_joker() {
    struct card card;
    card.tag = JOKER;
    return card;
}

int main(int argc, char **argv) {

    struct card queen = make_face_card(QUEEN, HEARTS);
    struct card ace = make_numbered_card(1, SPADES);

    struct card hand[] = {queen, ace};
    int num_cards = 2;

    printf("Testing: bust\n");
    bool busted = bust(hand, num_cards); // Should score 21
    if (busted) {
        printf("    Test #1 failed\n");
    } else {
        printf("    Test #1 passed\n");
    }

    // Add your tests here
}
