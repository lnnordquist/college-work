#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum face {
    JACK, QUEEN, KING
};

enum suit {
    HEARTS, DIAMONDS, SPADES, CLUBS
};

enum card_tag {
    FACE, NUMBERED, JOKER
};

struct face_card {
    enum face rank;
    enum suit suit;
};

struct numbered_card {
    int rank;
    enum suit suit;
};

union card_type {
    struct face_card f;
    struct numbered_card n;
};

struct card {
    union card_type type; // empty for JOKER
    enum card_tag tag;
};

/*
 * valid_card: Determine whether or not a card is a valid card
 *
 * card: the card
 *
 * Returns: true if card is valid, false otherwise
 */
bool valid_card(struct card card);

/*
 * cut: "Cut" a deck of cards in-place
 *
 * deck: an array of cards (the deck)
 * num_cards: the length of the array
 *
 * Returns: Nothing, modifies deck in-place
 */
void cut(struct card *deck, int num_cards);

/*
 * flush: Determine whether or not a hand contains a flush
 *
 * hand: an array of cards (the hand)
 * num_cards: the length of the array
 *
 * Returns: the enum suit of the suit that created the flush,
 *   or -1 if the hand does not contain a flush
 */
enum suit flush(struct card *hand, int num_cards);

/*
 * four_of_a_kind: Determine whether or not a hand contains 
 *   four-of-a-kind
 *
 * hand: an array of cards (the hand)
 * num_cards: the length of the array
 *
 * Returns: true if the hand contains four-of-a-kind, false otherwise
 */
bool four_of_a_kind(struct card *hand, int num_cards);

/*
 * bust: Determine whether or not a player "busts"
 *
 * hand: an array of cards (the hand)
 * num_cards: the length of the array
 *
 * Returns: true if the hand busts, false otherwise
 */
bool bust(struct card *hand, int num_cards);

/*
 * winner: Determine whether Player 1 or Player 2 is the winner
 *
 * hand1: an array of cards (the hand of Player 1)
 * num_cards1: the length of hand1
 * hand2: an array of cards (the hand of Player 2)
 * num_cards2: the length of hand2
 *
 * Returns: A negative number of Player 1 wins, a positive number if
 *   Player 2 wins, or zero for a tie
 */
int winner(struct card *hand1, int num_cards1, 
           struct card *hand2, int num_cards2);