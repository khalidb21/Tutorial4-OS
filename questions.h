/*
 * Tutorial 4 Jeopardy Project 
 * Group 7
 * Alexy Pichette (100822470)
 * Khalid Badri (100917156)
 * Ihsan Ismail (100915143)
 * Nathan Tenn (100795860)
 */
#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdbool.h>

#define NUM_CATEGORIES 5
#define NUM_VALUES 5

void display_categories(void);
void display_question(const char *category, int price);
bool valid_answer(const char *category, int price, const char *answer);
bool already_answered(const char *category, int price);
void remove_question(const char *category, int price);
bool check_if_finished(void);

#endif
