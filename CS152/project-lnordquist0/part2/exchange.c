/*
 * CS 152, Spring 2022
 * Exchange Data Structure
 * 
 * You will modify this file
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "order.h"
#include "book.h"
#include "action_report.h"
#include "util.h"
#include "exchange.h"

struct exchange {
  char *ticker;
  book_t *buy;
  book_t *sell;  
};

/* 
 * mk_exchange: make an exchange for the specified ticker symbol
 *
 * ticker: the ticker symbol for the stock
 *
 * Returns: an exchange
 */
exchange_t *mk_exchange(char *ticker) {
    exchange_t *new_exchange = (exchange_t *)ck_malloc(sizeof(exchange_t), 
                                                                "mk_exchange");
    char *tick = ck_strdup(ticker, "mk_exchange");
    new_exchange->ticker = tick;
    new_exchange->buy = mk_book(BUY_BOOK);
    new_exchange->sell = mk_book(SELL_BOOK);
    return new_exchange;
}

/*
 * free_exchange: free the space associated with the
 *   exchange
 *
 * exchange: an exchange
 */
void free_exchange(exchange_t *exchange) {
    if(exchange == NULL){
        return;
    }
    free_book(exchange->buy);
    free_book(exchange->sell);
    free(exchange->ticker);
    free(exchange);
    return;
}


/* 
 * process_order: process an order. Returns a action_report for the
 *   actions completed in the process. 
 *
 * exchange: an exchange
 * ord_str: a string describing the order (in the expected format)
 * time: the time the order was placed.
 */
action_report_t  *process_order(exchange_t *exchange, char *ord_str, int time) {
    assert(exchange != NULL);
    assert(ord_str != NULL);

    struct order *order = mk_order_from_line(ord_str, time);
    struct order *front = NULL;
    struct action_report *report = mk_action_report(exchange->ticker);

    bool buy = is_buy_order(order);
    book_t *other_book = buy? exchange->sell : exchange->buy;
    book_t *same_book = buy? exchange->buy : exchange->sell;
    enum action process_book = buy? BOOKED_BUY : BOOKED_SELL;

    if(order->type == 'C'){
        int index = 0;
        order_t *removed = check_match(same_book, order->oref, &index);
        enum action cancel_book = buy? CANCEL_BUY : CANCEL_SELL;
        if(removed != NULL){
            if(order->shares >= removed->shares){
                add_action(report, cancel_book, order->oref, order->price, removed->shares);
                remove_order(same_book, index);
            }else{
                removed->shares -= order->shares;
                add_action(report, cancel_book, order->oref, order->price, order->shares);
            }
        }
    }else{
        while(order->shares != 0){
        
            front = return_front(other_book);

            if((front == NULL) || (buy? order->price < front->price : order->price > front->price)){
                add_order_to_book(same_book, order);
                add_action(report, process_book, order->oref, order->price, order->shares);
                return(report);
            }
        
            int shares = (order->shares < front->shares)? order->shares : front->shares;
            order->shares -= shares;
            front->shares -= shares;
            add_action(report, EXECUTE, front->oref, front->price, shares);
            if(front->shares == 0){
                remove_front(other_book);
            }
        }
    }
    free_order(order);
    return report;
}


/*
 * print_exchange: print the contents of the exchange
 *
 * exchange: the exchange.
 */
void print_exchange(exchange_t *exchange) {
    printf("Exchange for ticker %s:\n", exchange->ticker);
    print_book(exchange->buy);
    print_book(exchange->sell);
    return;
}
