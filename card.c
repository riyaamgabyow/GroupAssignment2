/**
 * @file card.c
 * @brief Implements the functions declared in card.h for handling individual cards.
 *
 * This file contains:
 *   - Internal lookup tables for converting enum values to text
 *   - printCard(): prints a readable description of a card
 *   - cardMatches(): checks if two cards match by rank or suit
 */

#include "card.h"
#include <stdio.h>   // Needed for printf()


 /*
    Lookup tables for converting enum values (integers) into readable strings.
    These are used for printing human-friendly card names.
 */

 // suitNames[suit] gives the string name of a suit
static const char* suitNames[] = {
    "Clubs",
    "Spades",
    "Hearts",
    "Diamonds"
};

// rankNames[rank] gives the string name of a rank
static const char* rankNames[] = {
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King",
    "Ace"
};


/**
 * @brief Prints a readable representation of a card such as:
 *        "Five of Hearts"
 *
 * This function accesses rankNames[] and suitNames[] using the enum values
 * stored inside the Card structure. The rank and suit fields are guaranteed
 * to be valid as long as the Card was created correctly.
 *
 * @param c Pointer to the Card to be printed. If NULL, an error message prints.
 */
void printCard(const Card* c)
{
    // Check for invalid pointer to prevent program crashes
    if (c == NULL) {
        printf("Invalid card (NULL pointer)\n");
        return;
    }

    // Print using lookup tables. Example output:
    //  rankNames[FIVE] -> "Five"
    //  suitNames[HEART] -> "Hearts"
    printf("%s of %s\n",
        rankNames[c->rank],   // Convert rank enum to string
        suitNames[c->suit]);  // Convert suit enum to string
}


/**
 * @brief Determines whether two cards match by suit or rank.
 *
 * A card matches another card if:
 *  - They have the same rank (e.g., both are Fives), OR
 *  - They have the same suit (e.g., both are Hearts).
 *
 * This is exactly the rule described in CE4703 Assignment 2.
 *
 * @param c Pointer to the card the player wants to play.
 * @param top Pointer to the card currently at the top of the played pile.
 * @return 1 if the cards match, 0 otherwise.
 */
int cardMatches(const Card* c, const Card* top)
{
    // Defensive check: prevent crashes if someone passes invalid pointers
    if (c == NULL || top == NULL)
        return 0;

    // Check matching rank
    if (c->rank == top->rank)
        return 1;   // Same rank -> valid match

    // Check matching suit
    if (c->suit == top->suit)
        return 1;   // Same suit -> valid match

    // If neither rank nor suit match, then the card cannot be played
    return 0;
}
