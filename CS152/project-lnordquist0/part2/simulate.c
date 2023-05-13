/*
 * CS 152, Spring 2022
 * Simulation -- main file
 * 
 * You will modify this file
 *
 * Name: Lars Nordquist
 *
 * Sources used: None
 *
 * People consulted: Liam Lee Kitt
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "action_report.h"
#include "exchange.h"

#define MAX_ORDER_LEN 1000
#define MAX_TEST_FILENAME 30

void pull_and_process_order(exchange_t *exchange, int *time, FILE *read_from, FILE *write_to){
    char ord_str[MAX_ORDER_LEN];
    while(fgets(ord_str, MAX_ORDER_LEN, read_from) != NULL){
        action_report_t *ar = process_order(exchange, ord_str, *time);
        write_action_report_to_file(ar, write_to, *time);
        *time += 1;
        free_action_report(ar);
    }
    return;
}

int main(int argc, char **argv) {

    char *test_num = argv[2];
    char *ticker = argv[1];
    int time = 0;

    if(argc != 3){
        fprintf(stderr, "usage: simulate %s %s\n", ticker, test_num);
        return 0;
    }

    exchange_t *exchange = mk_exchange(ticker);

    char in[MAX_TEST_FILENAME];
    char out[MAX_TEST_FILENAME];
    sprintf(in, "tests/test%s_orders.csv", test_num);
    sprintf(out, "tests/test%s_actions.csv", test_num);
    
    FILE *read_from = fopen(in, "r");
    if(read_from == NULL){
        fprintf(stderr, "simulate.c, main: no test with given number\n");
        exit(1);
    }
    FILE *write_to = fopen(out, "w");
    if(write_to == NULL){
        fprintf(stderr, "simulate.c, main: no test with given number\n");
        exit(1);
    }
    
    
    pull_and_process_order(exchange, &time, read_from, write_to);

    fclose(read_from);
    fclose(write_to);
    free_exchange(exchange);
    return 0;
}


