/**
 * @file carddeck_sort.c
 * @brief Implements sorting and search functions for CardDeck.
 *
 * This file contains the definitions of deck_sort() and
 * find_matching_card(). A simple bubble sort is used to order the
 * cards in a deck, and a linear scan is used to locate the first
 * playable card in a player's hand.
 */

#include "carddeck_sort.h"

void deck_sort(CardDeck* deck)
{
    int i, j;

    if (deck == NULL || deck->size <= 1) {
        return;
    }

    for (i = 0; i < deck->size - 1; i++) {
        for (j = 0; j < deck->size - 1 - i; j++) {
            Card* a = &deck->cards[j];
            Card* b = &deck->cards[j + 1];

            /* compare_cards(a, b) > 0 means *a should come after *b */
            if (compare_cards(a, b) > 0) {
                Card temp = *a;
                *a = *b;
                *b = temp;
            }
        }
    }
}

/**
 * @brief Finds the first playable card in a hand.
 *
 * A card is considered playable if its suit matches the suit of
 * top_card or its rank matches the rank of top_card.
 *
 * @param hand     Pointer to the player's hand (a CardDeck). May be NULL.
 * @param top_card The card currently on top of the played pile.
 * @return The zero-based index of the first playable card in hand,
 *         or -1 if hand is NULL or no playable card exists.
 */
int find_matching_card(const CardDeck* hand, Card top_card)
{
    int i;

    if (hand == NULL) {
        return -1;
    }

    for (i = 0; i < hand->size; i++) {
        Card c = hand->cards[i];

        /* playable if same suit OR same rank */
        if (c.suit == top_card.suit || c.rank == top_card.rank) {
            return i;   /* first playable card */
        }
    }

    return -1;          /* no playable card found */
}
