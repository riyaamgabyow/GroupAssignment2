/**
 * @file game_logic.h
 * @brief Game logic functions for the card game
 * @author David Bradshaw
 * @date 2025
 */

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Correct the paths to the header files
#include "..\..\..\Downloads\GROUP_ASSIGNMENT\CardDeck.h"
#include "..\..\..\Downloads\GROUP_ASSIGNMENT\carddeck_sort.h"

 /**
  * @brief Deals cards from the hidden deck to players
  *
  * Deals 8 cards to each player alternately from the top of the hidden deck.
  * The first card goes to player one, second to player two, third to player one, etc.
  * After dealing, sorts both players' hands.
  *
  * @param hiddenDeck Pointer to the hidden deck to deal from
  * @param player1 Pointer to first player's hand deck
  * @param player2 Pointer to second player's hand deck
  */
void dealCards(CardDeck* hiddenDeck, CardDeck* player1, CardDeck* player2);

/**
 * @brief Handles the situation when the hidden deck becomes empty
 *
 * Transfers all played cards (except the last one) to the hidden deck,
 * then shuffles the hidden deck. The last played card remains in the played deck.
 *
 * @param hiddenDeck Pointer to the hidden deck (will be refilled)
 * @param playedDeck Pointer to the played deck (will be reduced to last card)
 */
void handleEmptyHiddenDeck(CardDeck* hiddenDeck, CardDeck* playedDeck);

/**
 * @brief Executes a single player's turn
 *
 * Checks if the player has a playable card. If yes, plays the first matching card.
 * If no, draws a card from the hidden deck and sorts the player's hand.
 *
 * @param player Pointer to the player's hand deck
 * @param hiddenDeck Pointer to the hidden deck
 * @param playedDeck Pointer to the played deck
 * @param topCard The current top card on the played deck
 * @param playerNum The player number (1 or 2) for display purposes
 * @return int 1 if the player played a card, 0 if they drew a card
 */
int executePlayerTurn(CardDeck* player, CardDeck* hiddenDeck, CardDeck* playedDeck, Card topCard, int playerNum);

/**
 * @brief Prints all cards in a player's hand to the console
 *
 * @param player Pointer to the player's hand deck
 * @param playerNum The player number (1 or 2) for display purposes
 */
void printPlayerHand(const CardDeck* player, int playerNum);

/**
 * @brief Main game loop that runs the complete card game
 *
 * Manages the game flow including initial setup, player turns,
 * deck management, and win condition checking. Continues until
 * one player has no cards left.
 *
 * @param hiddenDeck Pointer to the initialized and shuffled hidden deck
 * @param playedDeck Pointer to the empty played deck
 * @param player1 Pointer to first player's hand deck
 * @param player2 Pointer to second player's hand deck
 */
void playGame(CardDeck* hiddenDeck, CardDeck* playedDeck, CardDeck* player1, CardDeck* player2);

#endif
