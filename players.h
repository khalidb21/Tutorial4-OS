/*
 * Tutorial 4 Jeopardy Project 
 * Group 7
 * Alexy Pichette (100822470)
 * Khalid Badri (100917156)
 * Ihsan Ismail (100915143)
 * Nathan Tenn (100795860)
 */
#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <stdbool.h>

#define MAX_LEN 256

typedef struct {
    char name[MAX_LEN];
    int score;
} player;

bool player_exists(player *players, int num_players, const char *name);
void update_score(player *players, int num_players, const char *name, int points);
void highest_score(player *players, int num_players);

#endif
