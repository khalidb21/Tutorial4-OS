/*
 * Tutorial 4 Jeopardy Project 
 * Group 7
 * Alexy Pichette (100822470)
 * Khalid Badri (100917156)
 * Ihsan Ismail (100915143)
 * Nathan Tenn (100795860)
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// ---------------- COLORS ----------------
#define COLOR_RESET  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_WHITE  "\033[37m"

// ---------------- CONSTANTS ----------------
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// ---------------- QUESTION STATES ----------------
typedef enum {
    Q_AVAILABLE,
    Q_CORRECT,
    Q_WRONG
} QuestionState;

// <<< ADAPT TO YOUR GAME SIZE >>>
// Example: 5 categories x 5 values
#define NUM_CATEGORIES 5
#define NUM_VALUES 5

QuestionState question_states[NUM_CATEGORIES][NUM_VALUES];

// ---------------- TOKENIZER ----------------
char *tokens[MAX_LEN];
int tokencount = 0;

void tokenizer(char *answer){
    int i = 0;
    char *p = strtok(answer, " ");

    while (p != NULL){
        tokens[i++] = p;
        p = strtok(NULL, " ");
    }
    tokencount = i;
}

// ---------------- STRING CONCAT ----------------
char* concat(const char *a, const char *b){
    char *res = malloc(strlen(a) + strlen(b) + 1);
    strcpy(res, a);
    strcat(res, b);
    return res;
}

// ---------------- INIT QUESTION STATES ----------------
void init_question_states() {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            question_states[i][j] = Q_AVAILABLE;
        }
    }
}

// <<< YOU NEED A WAY TO MAP category+price -> indices >>>
int category_to_index(const char *category) {
    // Example mapping — ADAPT this to your categories
    if (strcasecmp(category, "History") == 0) return 0;
    if (strcasecmp(category, "Science") == 0) return 1;
    if (strcasecmp(category, "Sports") == 0) return 2;
    if (strcasecmp(category, "Music") == 0) return 3;
    if (strcasecmp(category, "Movies") == 0) return 4;
    return -1;
}

int price_to_index(int price) {
    // Example: 100,200,300,400,500 -> 0..4
    return (price / 100) - 1;
}

// ---------------- MARK QUESTION ----------------
void mark_question(const char *category, int price, QuestionState state) {
    int c = category_to_index(category);
    int v = price_to_index(price);

    if (c >= 0 && v >= 0 && c < NUM_CATEGORIES && v < NUM_VALUES) {
        question_states[c][v] = state;
    }
}

// ---------------- COLORED DISPLAY ----------------
void display_categories_colored() {
    // <<< ADAPT: Replace this with your real category/value layout >>>

    const char *categories[NUM_CATEGORIES] = {
        "History", "Science", "Sports", "Music", "Movies"
    };

    int values[NUM_VALUES] = {100, 200, 300, 400, 500};

    printf("\n");

    // Print header
    for (int c = 0; c < NUM_CATEGORIES; c++) {
        printf("%12s", categories[c]);
    }
    printf("\n");

    // Print grid
    for (int v = 0; v < NUM_VALUES; v++) {
        for (int c = 0; c < NUM_CATEGORIES; c++) {
            if (question_states[c][v] == Q_AVAILABLE) {
                printf(COLOR_WHITE "%12d" COLOR_RESET, values[v]);
            }
            else if (question_states[c][v] == Q_CORRECT) {
                printf(COLOR_GREEN "%12d" COLOR_RESET, values[v]);
            }
            else if (question_states[c][v] == Q_WRONG) {
                printf(COLOR_RED "%12d" COLOR_RESET, values[v]);
            }
        }
        printf("\n");
    }

    printf("\n");
}

// ---------------- MAIN ----------------
int main(int argc, char *argv[]){
    printf("                 WELCOME TO JEOPARDY!\n\n");

    // Init question states
    init_question_states();

    // Players
    player players[NUM_PLAYERS] = {{"empty", 0}, {"empty", 0}, {"empty", 0}, {"empty", 0}};
    char buffer[BUFFER_LEN] = { 0 };

    // Get player names
    for (int i = 0; i < NUM_PLAYERS; i++){
        printf("Enter Player %i Name: ", i+1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }

    while (fgets(buffer, BUFFER_LEN, stdin) != NULL){
        system("clear");

        char selected_player[MAX_LEN];
        char selected_category[MAX_LEN];
        int selected_price;
        char answer[MAX_LEN];

        // DISPLAY BOARD (COLORED)
        display_categories_colored();

        for(int i = 0; i < NUM_PLAYERS; i++){
            printf("\t\t       %s - $%d \n", players[i].name, players[i].score);
        }

        printf("\n-------------------------------------------------------\n");

        // Select player
        do{
            printf("Select a Player for this Round: ");
            scanf("%s", selected_player);

            if(player_exists(players, NUM_PLAYERS, selected_player) == false){
                printf("Error! Player Does not Exist!\n\n");
            }
        }
        while (player_exists(players, NUM_PLAYERS, selected_player) == false);

        // Select category & price
        do{
            printf("Please Select a Category: ");
            scanf("%s", selected_category);

            printf("And Please Select a Price: ");
            scanf("%d", &selected_price);

            if(already_answered(selected_category, selected_price) == true){
                printf("Error! Already answered!\n\n");
            }
        }
        while (already_answered(selected_category, selected_price) == true);

        system("clear");

        display_question(selected_category, selected_price); 
        printf("*********************************************");

        printf("\nWho/What is [your answer]? ");
        printf("\nEnter your Answer: ");
        getchar();
        scanf("%[^\n]s", answer);

        tokenizer(answer);

        char* path = "";
        for (int i = 2; i < tokencount; i++) {
            if(i != 2){   
                path = concat(path, " ");
            }
            path = concat(path, tokens[i]);
        }

        // Check answer
        if(strcasecmp(tokens[0], "Who") == 0 || strcasecmp(tokens[0], "What") == 0){
            if(valid_answer(selected_category, selected_price, path) == true){
                printf("\n\nYou are Correct!\nGood Job, You have been awarded $%d", selected_price);
                update_score(players, NUM_PLAYERS, selected_player, selected_price);
                mark_question(selected_category, selected_price, Q_CORRECT);
                remove_question(selected_category, selected_price);
            }
            else{
                printf("\n\nYou are Incorrect!\nNo points have been awarded");
                mark_question(selected_category, selected_price, Q_WRONG);
                remove_question(selected_category, selected_price); 
            }
        }
        else{
            printf("\n\nIncorrect Format!\nNo points have been awarded");
            mark_question(selected_category, selected_price, Q_WRONG);
            remove_question(selected_category, selected_price); 
        }

        printf("\n\n\nPress Enter to Continue ...");
        getchar();

        if (check_if_finished() == true){
            break;
        }
    }

    system("clear");
    printf("The Game Has Ended!\nHere are the Final Scores ... \n\n");

    for(int i = 0; i < NUM_PLAYERS; i++){
        printf("%s - $%d \n", players[i].name, players[i].score);
    }

    highest_score(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}
