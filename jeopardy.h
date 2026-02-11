/*
 * Tutorial 4 Jeopardy Project 
 * Group 5
 * Alexy Pichette (100822470)
 * Rida Siddiqi (100825212)
 * Muhammad Mujtaba Madad (100790195)
 * Ishmeet Kaur (100809450)
 */
#ifndef JEOPARDY_H_
#define JEOPARDY_H_

#define MAX_LEN 256

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
extern void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
extern void show_results(player *players, int num_players);

#endif /* JEOPARDY_H_ */
