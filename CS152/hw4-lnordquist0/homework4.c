/*
 * Homework #4 Deliverables
 *
 * Name: Lars Nordquist
 *
 * Sources used: None
 *
 * People consulted: Liam Lee Kitt
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "homework4.h"

/*
 * valid_card: Determine whether or not a card is a valid card
 *
 * card: the card
 *
 * Returns: true if card is valid, false otherwise
 */
bool valid_card(struct card card) {
    
    bool valid_rank = false;
    switch(card.tag){
        case JOKER:
            return true;
        case FACE:
            switch(card.type.f.rank){
                case JACK:
                    valid_rank = true;
                    break;
                case QUEEN:
                    valid_rank = true;
                    break;
                case KING:
                    valid_rank = true;
                    break;
            }
            switch(card.type.f.suit){
                case HEARTS:
                    return valid_rank;
                case DIAMONDS:
                    return valid_rank;
                case SPADES:
                    return valid_rank;
                case CLUBS:
                    return valid_rank;
                default:
                    return false;
            }
            break;
        case NUMBERED:
            valid_rank = ((1 <= card.type.n.rank) && (card.type.n.rank <= 10));
            switch(card.type.n.suit){
                case HEARTS:
                    return valid_rank;
                case DIAMONDS:
                    return valid_rank;
                case SPADES:
                    return valid_rank;
                case CLUBS:
                    return valid_rank;
                default:
                    return false;
            }
            break;
        default: 
            return false;
    }
}

/*
 * cut: "Cut" a deck of cards in-place
 *
 * deck: an array of cards (the deck)
 * num_cards: the length of the array
 *
 * Returns: Nothing, modifies deck in-place
 */
void cut(struct card *deck, int num_cards) {
    assert(deck != NULL);
    assert(num_cards > 0);
    
    for(int i = 0; i<num_cards/2; i++){
        struct card first_card = deck[i];
        deck[i] = deck[i+num_cards/2];
        deck[i+num_cards/2] = first_card;
    }
}

/*
 * flush: Determine whether or not a hand contains a flush
 *
 * hand: an array of cards (the hand)
 * num_cards: the length of the array
 *
 * Returns: the enum suit of the suit that created the flush,
 *   or -1 if the hand does not contain a flush
 */
enum suit flush(struct card *hand, int num_cards) {
    assert(hand != NULL);
    assert(num_cards > 0);
    int h_suit = -1;
    

    for(int i = 0; i<num_cards; i++){
        if(h_suit != -1){
            switch(hand[i].tag){
                case JOKER:
                    continue;
                case NUMBERED:
                    if(h_suit != hand[i].type.n.suit){
                        return -1;
                    }
                    break;
                case FACE:
                    if(h_suit != hand[i].type.f.suit){
                        return -1;
                    }
                    break;
            }
        }else{
            switch(hand[i].tag){
                case JOKER:
                    continue;
                case NUMBERED:
                    h_suit = hand[i].type.n.suit;
                    break;
                case FACE:
                    h_suit = hand[i].type.f.suit;
                    break;
            }
        }
    }
    return h_suit;
}

/*
 * four_of_a_kind: Determine whether or not a hand contains 
 *   four-of-a-kind
 *
 * hand: an array of cards (the hand)
 * num_cards: the length of the array
 *
 * Returns: true if the hand contains four-of-a-kind, false otherwise
 */
bool four_of_a_kind(struct card *hand, int num_cards) {
    assert(hand != NULL);
    assert(num_cards > 0);

    int unique_card_nums[13] = {0};
    //the cards are stored in the position corresponding to their rank
    //ranks: 1-10 as 0-9, then Jack 10, Queen 11, King 13
    int num_jokers = 0;

    //iterating over hand to construct the number of each
    for(int i = 0; i<num_cards; i++){
        switch(hand[i].tag){
            case JOKER:
                num_jokers++;
                break;
            case NUMBERED:
                unique_card_nums[hand[i].type.n.rank - 1]++;
                break;
            case FACE:
                unique_card_nums[hand[i].type.f.rank + 10]++;                  
                break;
            }
    }

    //checking if there are four of any of the cards
    for(int j = 0; j<13; j++){
        if(unique_card_nums[j] + num_jokers == 4){
            return true;
        }
    }
    return false;
}


/* score: HELPER FUNCTION that calculates the score of a particular hand.
*  Deals with Aces by counting as 11 if that does not cause a bust, 1 if it does
*
*  Two loops: one to count normal score, one to deal with aces
*  (since adding two aces may have to be counted as +2, rather than +11 then +1)
*
*  hand: an array of cards (the hand)
*  num_cards: the length of the array
*
* Returns: score as an int
*/

int score(struct card *hand, int num_cards){
    assert(hand != NULL);
    assert(num_cards > 0);

    int score = 0;
    int aces = 0;

    for (int i = 0; i<num_cards; i++){
        switch(hand[i].tag){
            case JOKER:
                break;
            case NUMBERED:
                if(hand[i].type.n.rank == 1) {
                    aces++;
                }else{
                    score += hand[i].type.n.rank;
                }
                break;
            case FACE:
                score += 10;
                break;
        }
    }

    if(aces>0){
        if(score + 11 <= 21){
            score += 11;
            aces--;
        }
        score += aces;
    }

    return score;
}


/*
 * bust: Determine whether or not a player "busts"
 *
 * hand: an array of cards (the hand)
 * num_cards: the length of the array
 *
 * Returns: true if the hand busts, false otherwise
 */
bool bust(struct card *hand, int num_cards) {
    assert(hand != NULL);
    assert(num_cards > 0);
    int hand_score = score(hand, num_cards);
    return hand_score > 21;
}

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
           struct card *hand2, int num_cards2) {
    assert(hand1 != NULL);
    assert(num_cards1 > 0);
    assert(hand2 != NULL);
    assert(num_cards2 > 0);

    int p1_score = score(hand1, num_cards1);
    int p2_score = score(hand2, num_cards2);

    if((p1_score>21) && (p2_score>21)){
        return 0;
    }else if (p2_score>21){
        return -1;
    }else if(p1_score>21){
        return 1;
    }       
    return p2_score - p1_score;
}