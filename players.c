/*
 * Tutorial 4 Jeopardy Project 
 * Group 7
 * Alexy Pichette (100822470)
 * Khalid Badri (100917156)
 * Ihsan Ismail (100915143)
 * Nathan Tenn (100795860)
 */
#include <stdio.h>
#include <string.h>
#include "players.h"

bool player_exists(player *players, int num_players, const char *name) {
    for (int i = 0; i < num_players; i++) {
        if (strcasecmp(players[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

void update_score(player *players, int num_players, const char *name, int points) {
    for (int i = 0; i < num_players; i++) {
        if (strcasecmp(players[i].name, name) == 0) {
            players[i].score += points;
            return;
        }
    }
}

void highest_score(player *players, int num_players) {
    int best = 0;

    for (int i = 1; i < num_players; i++) {
        if (players[i].score > players[best].score) {
            best = i;
        }
    }

    printf("\nWinner: %s with $%d\n", players[best].name, players[best].score);
}
