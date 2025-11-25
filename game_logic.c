/**
 * @file game_logic.c
 * @brief Implementation of game logic functions for the card game
 * @author David Bradshaw
 * @date 2025
 */

#include "game_logic.h"
#include <stdio.h>

 /**
  * @brief Clears the input buffer to prevent input issues
  */
static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void dealCards(CardDeck* hiddenDeck, CardDeck* player1, CardDeck* player2) {
    if (hiddenDeck == NULL || player1 == NULL || player2 == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to dealCards\n");
        return;
    }

    printf("Dealing 8 cards to each player...\n");

    /* Deal 8 cards to each player alternately */
    for (int i = 0; i < 8; i++) {
        /* Deal to player 1 */
        if (!CardDeck_isEmpty(hiddenDeck)) {
            Card card = CardDeck_removeCardFromTop(hiddenDeck);
            CardDeck_addCardToTop(player1, card);
        }

        /* Deal to player 2 */
        if (!CardDeck_isEmpty(hiddenDeck)) {
            Card card = CardDeck_removeCardFromTop(hiddenDeck);
            CardDeck_addCardToTop(player2, card);
        }
    }

    /* Sort both players' hands */
    deck_sort(player1);
    deck_sort(player2);

    printf("Player 1 hand after dealing:\n");
    printPlayerHand(player1, 1);
    printf("Player 2 hand after dealing:\n");
    printPlayerHand(player2, 2);
}

void handleEmptyHiddenDeck(CardDeck* hiddenDeck, CardDeck* playedDeck) {
    if (hiddenDeck == NULL || playedDeck == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to handleEmptyHiddenDeck\n");
        return;
    }

    printf("Hidden deck is empty! Reshuffling played cards...\n");

    /* Keep the last played card in the played deck */
    if (CardDeck_getSize(playedDeck) > 1) {
        Card lastCard = CardDeck_removeCardFromTop(playedDeck);

        /* Transfer all remaining played cards to hidden deck */
        while (!CardDeck_isEmpty(playedDeck)) {
            Card card = CardDeck_removeCardFromTop(playedDeck);
            CardDeck_addCardToTop(hiddenDeck, card);
        }

        /* Put the last card back to played deck */
        CardDeck_addCardToTop(playedDeck, lastCard);

        /* Shuffle the new hidden deck */
        CardDeck_shuffle(hiddenDeck);

        printf("Reshuffled hidden deck now has %d cards\n", CardDeck_getSize(hiddenDeck));
    }
}

int executePlayerTurn(CardDeck* player, CardDeck* hiddenDeck, CardDeck* playedDeck, Card topCard, int playerNum) {
    if (player == NULL || hiddenDeck == NULL || playedDeck == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to executePlayerTurn\n");
        return 0;
    }

    printf("\n--- Player %d's Turn ---\n", playerNum);
    printf("Top card: %s\n", cardToString(topCard));

    /* Find a playable card in player's hand */
    int playableIndex = find_matching_card(player, topCard);

    if (playableIndex != -1) {
        /* Player has a playable card - play it */
        Card playedCard = CardDeck_removeCardAtIndex(player, playableIndex);
        CardDeck_addCardToTop(playedDeck, playedCard);

        printf("Player %d played: %s\n", playerNum, cardToString(playedCard));
        printf("Player %d's hand after playing:\n", playerNum);
        printPlayerHand(player, playerNum);

        return 1; /* Player played a card */
    }
    else {
        /* Player has no playable card - draw from hidden deck */
        if (!CardDeck_isEmpty(hiddenDeck)) {
            Card drawnCard = CardDeck_removeCardFromTop(hiddenDeck);
            CardDeck_addCardToTop(player, drawnCard);
            deck_sort(player); /* Sort hand after drawing */

            printf("Player %d has no playable card. Draws: %s\n", playerNum, cardToString(drawnCard));
            printf("Player %d's hand after drawing:\n", playerNum);
            printPlayerHand(player, playerNum);
        }
        else {
            printf("Player %d has no playable card, but hidden deck is also empty. Skipping turn.\n", playerNum);
        }

        return 0; /* Player drew a card or skipped */
    }
}

void printPlayerHand(const CardDeck* player, int playerNum) {
    if (player == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to printPlayerHand\n");
        return;
    }

    if (CardDeck_isEmpty(player)) {
        printf("  Player %d has no cards\n", playerNum);
        return;
    }

    for (int i = 0; i < CardDeck_getSize(player); i++) {
        Card card = CardDeck_getCardAtIndex(player, i);
        printf("  %d: %s\n", i + 1, cardToString(card));
    }
    printf("  Total cards: %d\n", CardDeck_getSize(player));
}

void playGame(CardDeck* hiddenDeck, CardDeck* playedDeck, CardDeck* player1, CardDeck* player2) {
    if (hiddenDeck == NULL || playedDeck == NULL || player1 == NULL || player2 == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to playGame\n");
        return;
    }

    printf("\n=== Starting Game ===\n");

    /* Start the game by moving first card from hidden to played deck */
    if (!CardDeck_isEmpty(hiddenDeck)) {
        Card firstCard = CardDeck_removeCardFromTop(hiddenDeck);
        CardDeck_addCardToTop(playedDeck, firstCard);
        printf("First card on table: %s\n", cardToString(firstCard));
    }
    else {
        printf("Error: Hidden deck is empty at game start!\n");
        return;
    }

    int turnCount = 0;
    int currentPlayer = 1; /* Start with player 1 */

    /* Main game loop */
    while (!CardDeck_isEmpty(player1) && !CardDeck_isEmpty(player2)) {
        turnCount++;

        /* Check if hidden deck needs reshuffling */
        if (CardDeck_isEmpty(hiddenDeck)) {
            handleEmptyHiddenDeck(hiddenDeck, playedDeck);
        }

        /* Get current top card from played deck */
        Card topCard = CardDeck_getCardAtIndex(playedDeck, 0);

        /* Execute current player's turn */
        if (currentPlayer == 1) {
            executePlayerTurn(player1, hiddenDeck, playedDeck, topCard, 1);
        }
        else {
            executePlayerTurn(player2, hiddenDeck, playedDeck, topCard, 2);
        }

        printf("\nPress Enter to continue to next turn...");
        fflush(stdout); // Force output to display
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // Wait for Enter key

        /* Switch to other player */
        currentPlayer = (currentPlayer == 1) ? 2 : 1;

        /* Safety check to prevent infinite loop */
        if (turnCount > 500) {
            printf("Game terminated after 500 turns - possible infinite loop\n");
            break;
        }
    }

    /* Determine winner */
    printf("\n=== Game Over ===\n");
    if (CardDeck_isEmpty(player1)) {
        printf("Player 1 wins! No cards left.\n");
    }
    else if (CardDeck_isEmpty(player2)) {
        printf("Player 2 wins! No cards left.\n");
    }
    else {
        printf("Game ended without a clear winner.\n");
    }
    printf("Total turns played: %d\n", turnCount);
}