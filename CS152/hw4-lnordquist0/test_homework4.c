/*
 * CS 152, Spring 2022
 * Homework #4 Automated Tests 
 *
 * Run make test_homework4 to compile these tests and ./test_homework4
 * to run these tests.  See the homework write-up for instructions
 * on how to run a subset of the tests.
 * 
 * Do not modify this file.
 */

#include <stdbool.h>
#include <criterion/criterion.h>
#include "homework4.h"

/**************** Helper functions ****************/
struct card make_face_card(enum face face, enum suit suit) {
    struct card card;
    card.tag = FACE;
    card.type.f.rank = face;
    card.type.f.suit = suit;

    return card;
}

struct card make_numbered_card(int rank, enum suit suit) {
    struct card card;
    card.tag = NUMBERED;
    card.type.n.rank = rank;
    card.type.n.suit = suit;

    return card;
}

struct card make_joker() {
    struct card card;
    card.tag = JOKER;
    return card;
}

/**************** Exercise 1 ****************/
Test(valid_card, test0) {
    struct card c = make_face_card(QUEEN, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test1) {
    struct card c = make_face_card(QUEEN, DIAMONDS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test2) {
    struct card c = make_face_card(QUEEN, SPADES);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test3) {
    struct card c = make_face_card(QUEEN, CLUBS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test4) {
    struct card c = make_face_card(JACK, CLUBS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test5) {
    struct card c = make_face_card(KING, CLUBS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test6) {
    struct card c = make_face_card(-1, CLUBS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test7) {
    struct card c = make_face_card(3, CLUBS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test8) {
    struct card c = make_face_card(4, CLUBS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test9) {
    struct card c = make_face_card(JACK, -1);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test10) {
    struct card c = make_face_card(JACK, 5);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test11) {
    struct card c = make_joker();
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test12) {
    struct card c;
    c.tag = -1;
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test13) {
    struct card c;
    c.tag = 4;
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test14) {
    struct card c = make_numbered_card(1, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test15) {
    struct card c = make_numbered_card(2, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test16) {
    struct card c = make_numbered_card(5, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test17) {
    struct card c = make_numbered_card(10, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, true);
}

Test(valid_card, test18) {
    struct card c = make_numbered_card(-1, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test19) {
    struct card c = make_numbered_card(11, HEARTS);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test20) {
    struct card c = make_numbered_card(1, -1);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

Test(valid_card, test21) {
    struct card c = make_numbered_card(1, 4);
    bool actual = valid_card(c);
    cr_assert_eq(actual, false);
}

/**************** Exercise 2 ****************/
void test_cards_equal(struct card c1, struct card c2) {
    cr_assert_eq(c1.tag, c2.tag);
    switch (c1.tag) {
        case JOKER:
            return;
        case FACE:
            cr_assert_eq(c1.type.f.rank, c2.type.f.rank);
            cr_assert_eq(c1.type.f.suit, c2.type.f.suit);
        case NUMBERED:
            cr_assert_eq(c1.type.n.rank, c2.type.n.rank);
            cr_assert_eq(c1.type.n.suit, c2.type.n.suit);
    }
} 

Test(cut, test0) {
    struct card c1 = make_face_card(QUEEN, HEARTS);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card actual[] = {c1, c2};
    struct card expected[] = {c2, c1};
    int num_cards = 2;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test1) {
    struct card c1 = make_numbered_card(9, DIAMONDS);
    struct card c2 = make_face_card(QUEEN, HEARTS);
    struct card actual[] = {c1, c2};
    struct card expected[] = {c2, c1};
    int num_cards = 2;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test2) {
    struct card c1 = make_numbered_card(9, DIAMONDS);
    struct card c2 = make_joker();
    struct card actual[] = {c1, c2};
    struct card expected[] = {c2, c1};
    int num_cards = 2;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test3) {
    struct card c1 = make_joker();
    struct card c2 = make_face_card(QUEEN, HEARTS);
    struct card actual[] = {c1, c2};
    struct card expected[] = {c2, c1};
    int num_cards = 2;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test4) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card actual[] = {c1, c2, c3, c4};
    struct card expected[] = {c3, c4, c1, c2};
    int num_cards = 4;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test5) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card c3 = make_joker();
    struct card c4 = make_face_card(JACK, SPADES);
    struct card actual[] = {c1, c2, c3, c4};
    struct card expected[] = {c3, c4, c1, c2};
    int num_cards = 4;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test6) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card c5 = make_face_card(QUEEN, HEARTS);
    struct card c6 = make_numbered_card(1, CLUBS);
    struct card actual[] = {c1, c2, c3, c4, c5, c6};
    struct card expected[] = {c4, c5, c6, c1, c2, c3};
    int num_cards = 6;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

Test(cut, test8) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card c5 = make_face_card(QUEEN, HEARTS);
    struct card c6 = make_numbered_card(1, CLUBS);
    struct card c7 = make_numbered_card(2, CLUBS);
    struct card c8 = make_face_card(JACK, HEARTS);
    struct card actual[] = {c1, c2, c3, c4, c5, c6, c7, c8};
    struct card expected[] = {c5, c6, c7, c8, c1, c2, c3, c4};
    int num_cards = 8;

    cut(actual, num_cards);
    for (int i = 0; i < num_cards; i++) {
        test_cards_equal(actual[i], expected[i]);
    }
}

/**************** Exercise 3 ****************/
Test(flush, test0) {
    struct card c1 = make_face_card(QUEEN, HEARTS);
    struct card hand[] = {c1};
    int num_cards = 1;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, HEARTS);
}

Test(flush, test1) {
    struct card c1 = make_numbered_card(3, SPADES);
    struct card hand[] = {c1};
    int num_cards = 1;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, SPADES);
}

Test(flush, test2) {
    struct card c1 = make_face_card(QUEEN, HEARTS);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card hand[] = {c1, c2};
    int num_cards = 2;

    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, -1);
}

Test(flush, test3) {
    struct card c1 = make_face_card(QUEEN, HEARTS);
    struct card c2 = make_numbered_card(9, HEARTS);
    struct card hand[] = {c1, c2};
    int num_cards = 2;

    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, HEARTS);
}

Test(flush, test4) {
    struct card c1 = make_face_card(KING, CLUBS);
    struct card c2 = make_numbered_card(9, CLUBS);
    struct card c3 = make_numbered_card(3, CLUBS);
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, CLUBS);
}

Test(flush, test5) {
    struct card c1 = make_face_card(KING, CLUBS);
    struct card c2 = make_numbered_card(9, CLUBS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, -1);
}

Test(flush, test6) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, SPADES);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, SPADES);
}

Test(flush, test7) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, -1);
}

Test(flush, test8) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, SPADES);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, DIAMONDS);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, -1);
}

Test(flush, test9) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, SPADES);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card c5 = make_face_card(QUEEN, SPADES);
    struct card c6 = make_numbered_card(1, CLUBS);
    struct card c7 = make_numbered_card(2, SPADES);
    struct card c8 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7, c8};
    int num_cards = 8;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, -1);
}

Test(flush, test10) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, SPADES);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card c5 = make_face_card(QUEEN, SPADES);
    struct card c6 = make_numbered_card(1, SPADES);
    struct card c7 = make_numbered_card(2, SPADES);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7};
    int num_cards = 7;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, SPADES);
}

Test(flush, test11) {
    struct card c1 = make_face_card(QUEEN, HEARTS);
    struct card c2 = make_joker();
    struct card hand[] = {c1, c2};
    int num_cards = 2;

    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, HEARTS);
}

Test(flush, test12) {
    struct card c1 = make_joker();
    struct card c2 = make_numbered_card(9, CLUBS);
    struct card c3 = make_numbered_card(3, CLUBS);
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, CLUBS);
}

Test(flush, test13) {
    struct card c1 = make_face_card(KING, CLUBS);
    struct card c2 = make_joker();
    struct card c3 = make_joker();
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, CLUBS);
}

Test(flush, test14) {
    struct card c1 = make_face_card(KING, DIAMONDS);
    struct card c2 = make_joker();
    struct card c3 = make_numbered_card(3, DIAMONDS);
    struct card c4 = make_face_card(JACK, DIAMONDS);
    struct card c5 = make_face_card(QUEEN, DIAMONDS);
    struct card c6 = make_joker();
    struct card c7 = make_numbered_card(2, DIAMONDS);
    struct card c8 = make_numbered_card(9, DIAMONDS);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7, c8};
    int num_cards = 8;
    
    enum suit actual = flush(hand, num_cards);
    cr_assert_eq(actual, DIAMONDS);
}

/**************** Exercise 4 ****************/
Test(four_of_a_kind, test0) {
    struct card c1 = make_face_card(9, SPADES);
    struct card c2 = make_numbered_card(9, CLUBS);
    struct card c3 = make_numbered_card(9, DIAMONDS);
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;

    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test1) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test2) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_numbered_card(3, HEARTS);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test3) {
    struct card c1 = make_numbered_card(3, CLUBS);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_numbered_card(4, HEARTS);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test4) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_face_card(QUEEN, SPADES);
    struct card c3 = make_face_card(KING, CLUBS);
    struct card c4 = make_face_card(KING, DIAMONDS);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;

    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test5) {
    struct card c1 = make_face_card(JACK, CLUBS);
    struct card c2 = make_face_card(JACK, DIAMONDS);
    struct card c3 = make_face_card(JACK, SPADES);
    struct card c4 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test6) {
    struct card c1 = make_face_card(JACK, CLUBS);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_face_card(JACK, DIAMONDS);
    struct card c4 = make_face_card(JACK, SPADES);
    struct card c5 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5};
    int num_cards = 5;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test7) {
    struct card c1 = make_face_card(JACK, CLUBS);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(2, DIAMONDS);
    struct card c4 = make_face_card(JACK, DIAMONDS);
    struct card c5 = make_face_card(JACK, SPADES);
    struct card c6 = make_numbered_card(5, DIAMONDS);
    struct card c7 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7};
    int num_cards = 7;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test8) {
    struct card c1 = make_joker();
    struct card c2 = make_numbered_card(9, CLUBS);
    struct card c3 = make_numbered_card(9, DIAMONDS);
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;

    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test9) {
    struct card c1 = make_joker();
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_joker();
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test10) {
    struct card c1 = make_joker();
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_numbered_card(3, HEARTS);
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test11) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_joker();
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(four_of_a_kind, test12) {
    struct card c1 = make_face_card(JACK, CLUBS);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_face_card(JACK, DIAMONDS);
    struct card c4 = make_joker();
    struct card c5 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5};
    int num_cards = 5;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test13) {
    struct card c1 = make_face_card(JACK, CLUBS);
    struct card c2 = make_numbered_card(3, DIAMONDS);
    struct card c3 = make_joker();
    struct card c4 = make_joker();
    struct card c5 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5};
    int num_cards = 5;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test14) {
    struct card c1 = make_numbered_card(3, DIAMONDS);
    struct card c2 = make_joker();
    struct card c3 = make_numbered_card(1, HEARTS);
    struct card c4 = make_face_card(JACK, DIAMONDS);
    struct card c5 = make_face_card(JACK, SPADES);
    struct card c6 = make_face_card(QUEEN, CLUBS);
    struct card c7 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7};
    int num_cards = 7;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test15) {
    struct card c1 = make_numbered_card(3, DIAMONDS);
    struct card c2 = make_joker();
    struct card c3 = make_numbered_card(1, HEARTS);
    struct card c4 = make_face_card(JACK, DIAMONDS);
    struct card c5 = make_joker();
    struct card c6 = make_face_card(QUEEN, CLUBS);
    struct card c7 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7};
    int num_cards = 7;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(four_of_a_kind, test16) {
    struct card c1 = make_numbered_card(3, DIAMONDS);
    struct card c2 = make_joker();
    struct card c3 = make_numbered_card(1, HEARTS);
    struct card c4 = make_face_card(JACK, DIAMONDS);
    struct card c5 = make_face_card(KING, CLUBS);
    struct card c6 = make_face_card(QUEEN, CLUBS);
    struct card c7 = make_face_card(JACK, HEARTS);
    struct card hand[] = {c1, c2, c3, c4, c5, c6, c7};
    int num_cards = 7;
    
    bool actual = four_of_a_kind(hand, num_cards);
    cr_assert_eq(actual, false);
}

/**************** Exercise 5 ****************/
Test(bust, test0) {
    struct card c1 = make_numbered_card(3, DIAMONDS);
    struct card c2 = make_numbered_card(9, DIAMONDS); // 12
    struct card hand[] = {c1, c2};
    int num_cards = 2;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test1) {
    struct card c1 = make_face_card(KING, SPADES);
    struct card c2 = make_numbered_card(9, DIAMONDS); // 19
    struct card hand[] = {c1, c2};
    int num_cards = 2;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test2) {
    struct card c1 = make_face_card(KING, CLUBS);
    struct card c2 = make_numbered_card(3, CLUBS);
    struct card c3 = make_numbered_card(7, DIAMONDS); // 20
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test3) {
    struct card c1 = make_numbered_card(4, CLUBS);
    struct card c2 = make_numbered_card(7, DIAMONDS);
    struct card c3 = make_face_card(JACK, SPADES); // 21
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test4) {
    struct card c1 = make_numbered_card(2, CLUBS);
    struct card c2 = make_face_card(JACK, SPADES);
    struct card c3 = make_face_card(QUEEN, DIAMONDS); // 22
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(bust, test5) {
    struct card c1 = make_numbered_card(1, DIAMONDS); // 11
    struct card hand[] = {c1};
    int num_cards = 1;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test6) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(5, CLUBS); // 16
    struct card hand[] = {c1, c2};
    int num_cards = 2;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test7) {
    struct card c1 = make_numbered_card(10, HEARTS);
    struct card c2 = make_numbered_card(1, DIAMONDS); // 21 (Ace 11)
    struct card hand[] = {c1, c2};
    int num_cards = 2;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test8) {
    struct card c1 = make_face_card(JACK, SPADES);
    struct card c2 = make_numbered_card(1, DIAMONDS);
    struct card c3 = make_numbered_card(3, HEARTS); // 14 (Ace 1)
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test9) {
    struct card c1 = make_face_card(JACK, SPADES);
    struct card c2 = make_numbered_card(1, DIAMONDS);
    struct card c3 = make_numbered_card(10, HEARTS);
    struct card c4 = make_numbered_card(2, HEARTS); // 23 (Ace 1)
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(bust, test10) {
    struct card c1 = make_numbered_card(4, SPADES);
    struct card c2 = make_numbered_card(1, DIAMONDS);
    struct card c3 = make_numbered_card(3, HEARTS);
    struct card c4 = make_numbered_card(1, HEARTS); // 19 (Ace 11, 1)
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test11) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(4, SPADES);
    struct card c3 = make_numbered_card(1, HEARTS);
    struct card c4 = make_face_card(QUEEN, SPADES); // 16 (Ace 1, 1)
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test12) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(1, SPADES);
    struct card c3 = make_numbered_card(1, HEARTS); // 13 (Ace 11, 1, 1)
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test13) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(4, SPADES);
    struct card c3 = make_numbered_card(1, SPADES);
    struct card c4 = make_numbered_card(1, HEARTS); // 17 (Ace 11, 1, 1)
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test14) {
    struct card c1 = make_face_card(JACK, SPADES);
    struct card c2 = make_numbered_card(1, DIAMONDS);
    struct card c3 = make_numbered_card(2, HEARTS); // 13 (Ace 1)
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test15) {
    struct card c1 = make_numbered_card(5, CLUBS);
    struct card c2 = make_numbered_card(7, DIAMONDS);
    struct card c3 = make_face_card(JACK, SPADES); // 22
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(bust, test16) {
    struct card c1 = make_numbered_card(1, CLUBS);
    struct card c2 = make_numbered_card(7, DIAMONDS);
    struct card c3 = make_numbered_card(4, DIAMONDS);
    struct card c4 = make_face_card(JACK, SPADES); // 22 (Ace 1)
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(bust, test17) {
    struct card c1 = make_numbered_card(1, CLUBS);
    struct card c2 = make_numbered_card(10, DIAMONDS);
    struct card c3 = make_numbered_card(1, DIAMONDS);
    struct card c4 = make_face_card(JACK, SPADES); // 22 (Ace 1, 1)
    struct card hand[] = {c1, c2, c3, c4};
    int num_cards = 4;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, true);
}

Test(bust, test18) {
    struct card c1 = make_numbered_card(4, CLUBS);
    struct card c2 = make_numbered_card(7, DIAMONDS);
    struct card c3 = make_face_card(JACK, SPADES); // 21
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test19) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_joker();
    struct card c3 = make_numbered_card(5, CLUBS); // 16
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test20) {
    struct card c1 = make_numbered_card(10, HEARTS);
    struct card c2 = make_numbered_card(1, DIAMONDS); // 21
    struct card c3 = make_joker();
    struct card hand[] = {c1, c2, c3};
    int num_cards = 3;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, false);
}

Test(bust, test21) {
    struct card c1 = make_joker();
    struct card c2 = make_numbered_card(1, CLUBS);
    struct card c3 = make_numbered_card(7, DIAMONDS);
    struct card c4 = make_joker();
    struct card c5 = make_numbered_card(4, DIAMONDS);
    struct card c6 = make_face_card(JACK, SPADES); // 22 (Ace 1)
    struct card hand[] = {c1, c2, c3, c4, c5, c6};
    int num_cards = 6;
    
    bool actual = bust(hand, num_cards);
    cr_assert_eq(actual, true);
}

/**************** Exercise 5 ****************/
Test(winner, test0) {
    struct card c1 = make_numbered_card(3, DIAMONDS);
    struct card c2 = make_numbered_card(9, DIAMONDS); // 12
    struct card hand1[] = {c1, c2};
    int num_cards1 = 2;

    struct card c3 = make_numbered_card(1, DIAMONDS); // 11
    struct card hand2[] = {c3};
    int num_cards2 = 1;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_lt(actual, 0);
}

Test(winner, test1) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(5, CLUBS); // 16
    struct card hand1[] = {c1, c2};
    int num_cards1 = 2;

    struct card c3 = make_face_card(KING, CLUBS);
    struct card c4 = make_numbered_card(3, CLUBS);
    struct card c5 = make_numbered_card(7, DIAMONDS); // 20
    struct card hand2[] = {c3, c4, c5};
    int num_cards2 = 3;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_gt(actual, 0);
}

Test(winner, test2) {
    struct card c1 = make_numbered_card(4, CLUBS);
    struct card c2 = make_numbered_card(7, DIAMONDS);
    struct card c3 = make_face_card(JACK, SPADES); // 21
    struct card hand1[] = {c1, c2, c3};
    int num_cards1 = 3;

    struct card c4 = make_numbered_card(10, HEARTS);
    struct card c5 = make_numbered_card(1, DIAMONDS); // 21 (Ace 11)
    struct card hand2[] = {c4, c5};
    int num_cards2 = 2;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_eq(actual, 0);
}

Test(winner, test3) {
    struct card c1 = make_face_card(JACK, SPADES);
    struct card c2 = make_numbered_card(1, DIAMONDS);
    struct card c3 = make_numbered_card(10, HEARTS);
    struct card c4 = make_numbered_card(2, HEARTS); // 23 (Ace 1)
    struct card hand1[] = {c1, c2, c3, c4};
    int num_cards1 = 4;

    struct card c5 = make_face_card(JACK, SPADES);
    struct card c6 = make_numbered_card(1, DIAMONDS);
    struct card c7 = make_numbered_card(3, HEARTS); // 14 (Ace 1)
    struct card hand2[] = {c5, c6, c7};
    int num_cards2 = 3;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_gt(actual, 0);
}

Test(winner, test4) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(5, CLUBS); // 16
    struct card hand1[] = {c1, c2};
    int num_cards1 = 2;

    struct card c3 = make_numbered_card(5, CLUBS);
    struct card c4 = make_numbered_card(7, DIAMONDS);
    struct card c5 = make_face_card(JACK, SPADES); // 22
    struct card hand2[] = {c3, c4, c5};
    int num_cards2 = 3;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_lt(actual, 0);
}

Test(winner, test5) {
    struct card c1 = make_joker();
    struct card c2 = make_numbered_card(1, CLUBS);
    struct card c3 = make_numbered_card(7, DIAMONDS);
    struct card c4 = make_joker();
    struct card c5 = make_numbered_card(4, DIAMONDS);
    struct card c6 = make_face_card(JACK, SPADES); // 22 (Ace 1)
    struct card hand1[] = {c1, c2, c3, c4, c5, c6};
    int num_cards1 = 6;

    struct card c7 = make_numbered_card(1, CLUBS);
    struct card c8 = make_numbered_card(7, DIAMONDS);
    struct card c9 = make_numbered_card(4, DIAMONDS);
    struct card c10 = make_face_card(JACK, SPADES); // 22 (Ace 1)
    struct card hand2[] = {c7, c8, c9, c10};
    int num_cards2 = 4;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_eq(actual, 0);
}

Test(winner, test6) {
    struct card c1 = make_numbered_card(1, DIAMONDS);
    struct card c2 = make_numbered_card(5, CLUBS); // 16
    struct card hand1[] = {c1, c2};
    int num_cards1 = 2;

    struct card c3 = make_numbered_card(6, DIAMONDS);
    struct card c4 = make_face_card(JACK, SPADES); // 16
    struct card hand2[] = {c3, c4};
    int num_cards2 = 2;

    int actual = winner(hand1, num_cards1, hand2, num_cards2);
    cr_assert_eq(actual, 0);
}