#ifndef CARDDECK_SORT_H
#define CARDDECK_SORT_H

/**
 * @file carddeck_sort.h
 * @brief Declarations for sorting and search functions for CardDeck.
 *
 * This module provides functions to sort a CardDeck and to find the
 * first playable card in a player's hand according to the game rules
 * (a card is playable if it matches the suit or rank of the top card).
 */

#include "card.h"      /* must define: Card and compare_cards()      */
#include "carddeck.h"  /* must define: CardDeck with cards/size/etc. */

 /**
  * @brief Sorts the cards in a deck in place.
  *
  * The deck is sorted using a simple bubble sort. The comparison between
  * two cards is delegated to compare_cards(), which is expected to define
  * the ordering (for example, by suit then rank).
  *
  * @param deck Pointer to the deck to sort. If NULL or if deck->size is
  *             less than or equal to 1, the function returns immediately.
  */
void deck_sort(CardDeck* deck);

/**
 * @brief Finds the first playable card in a hand.
 *
 * A card is considered playable if its suit matches the suit of
 * @p top_card or its rank matches the rank of @p top_card.
 *
 * @param hand     Pointer to the player's hand (a CardDeck). May be NULL.
 * @param top_card The card currently on top of the played pile.
 * @return The zero-based index of the first playable card in @p hand,
 *         or -1 if @p hand is NULL or no playable card exists.
 */
int find_matching_card(const CardDeck* hand, Card top_card);

#endif /* CARDDECK_SORT_H */
