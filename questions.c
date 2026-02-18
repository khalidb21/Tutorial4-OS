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
#include <stdbool.h>
#include <strings.h>   
#include "questions.h"

// 0 = not answered, 1 = answered
static int answered[NUM_CATEGORIES][NUM_VALUES] = {0};

// Categories
static const char *categories[NUM_CATEGORIES] = {
    "History", "Science", "Sports", "Geography", "Movies"
};

// Values
static const int values[NUM_VALUES] = {100, 200, 300, 400, 500};

// Questions
static const char *questions[NUM_CATEGORIES][NUM_VALUES] = {
    // History
    {
        "This ancient civilization built the pyramids.",
        "He was the first President of the United States.",
        "This wall fell in 1989, symbolizing the end of the Cold War division in Germany.",
        "This ship famously sank in 1912 after hitting an iceberg.",
        "This empire was ruled by Julius Caesar and later Augustus."
    },
    // Science
    {
        "This particle has a negative electric charge.",
        "This planet is known as the Red Planet.",
        "This gas do plants absorb from the atmosphere for photosynthesis?",
        "This is the process by which water turns into vapor.",
        "This force keeps planets in orbit around the sun."
    },
    // Sports
    {
        "This sport uses a bat, a ball, and bases.",
        "This country won the FIFA World Cup in 2018.",
        "In basketball, this shot is worth three points.",
        "This athlete is known as the fastest man in the world (last name only).",
        "This event is held every four years and features many sports."
    },
    // Geography
    {
        "This is the capital of France.",
        "This is the largest ocean on Earth.",
        "This continent is also a country.",
        "This river is the longest in the world (commonly taught answer).",
        "This mountain is the tallest in the world above sea level."
    },
    // Movies
    {
        "This movie features a shark named Bruce (answer is the movie title).",
        "This movie features the quote: 'I'll be back.'",
        "This movie is about a box of chocolates and life (main character's story).",
        "This movie features dinosaurs brought back to life.",
        "This movie features the characters Neo and Morpheus."
    }
};

// Answers 
static const char *answers[NUM_CATEGORIES][NUM_VALUES] = {
    // History
    {
        "egyptians",
        "george washington",
        "berlin wall",
        "titanic",
        "roman empire"
    },
    // Science
    {
        "electron",
        "mars",
        "carbon dioxide",
        "evaporation",
        "gravity"
    },
    // Sports
    {
        "baseball",
        "france",
        "three pointer",
        "bolt",
        "olympics"
    },
    // Geography
    {
        "paris",
        "pacific",
        "australia",
        "nile",
        "mount everest"
    },
    // Movies
    {
        "jaws",
        "terminator",
        "forrest gump",
        "jurassic park",
        "the matrix"
    }
};

static int category_to_index(const char *category) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (strcasecmp(category, categories[i]) == 0) {
            return i;
        }
    }
    return -1;
}

static int price_to_index(int price) {
    return (price / 100) - 1; // 100->0, 200->1, ...
}

void display_categories(void) {
    printf("\n");

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%12s", categories[i]);
    }
    printf("\n");

    for (int v = 0; v < NUM_VALUES; v++) {
        for (int c = 0; c < NUM_CATEGORIES; c++) {
            if (answered[c][v]) {
                printf("%12s", "----");
            } else {
                printf("%12d", values[v]);
            }
        }
        printf("\n");
    }

    printf("\n");
}

void display_question(const char *category, int price) {
    int c = category_to_index(category);
    int v = price_to_index(price);

    if (c < 0 || v < 0 || c >= NUM_CATEGORIES || v >= NUM_VALUES) {
        printf("Invalid category or price.\n");
        return;
    }

    printf("\nCategory: %s for $%d\n", categories[c], values[v]);
    printf("Question: %s\n", questions[c][v]);
}

bool valid_answer(const char *category, int price, const char *answer) {
    int c = category_to_index(category);
    int v = price_to_index(price);

    if (c < 0 || v < 0 || c >= NUM_CATEGORIES || v >= NUM_VALUES) {
        return false;
    }

    // Case-insensitive compare
    if (strcasecmp(answer, answers[c][v]) == 0) {
        return true;
    }
    return false;
}

bool already_answered(const char *category, int price) {
    int c = category_to_index(category);
    int v = price_to_index(price);

    if (c < 0 || v < 0 || c >= NUM_CATEGORIES || v >= NUM_VALUES) {
        return true;
    }

    return answered[c][v] == 1;
}

void remove_question(const char *category, int price) {
    int c = category_to_index(category);
    int v = price_to_index(price);

    if (c >= 0 && v >= 0 && c < NUM_CATEGORIES && v < NUM_VALUES) {
        answered[c][v] = 1;
    }
}

bool check_if_finished(void) {
    for (int c = 0; c < NUM_CATEGORIES; c++) {
        for (int v = 0; v < NUM_VALUES; v++) {
            if (answered[c][v] == 0) {
                return false;
            }
        }
    }
    return true;
}

