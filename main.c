#include <stdio.h>
#include "CardDeck.h"
#include "carddeck_sort.h"
#include "game_logic.h"

int main() {
    int numPacks;

    printf("=== Card Game ===\n");
    printf("Enter number of card packs to use: ");
    scanf("%d", &numPacks);

    if (numPacks < 1) {
        printf("Invalid number of packs. Using 1 pack.\n");
        numPacks = 1;
    }

    /* Initialize decks */
    CardDeck hiddenDeck, player1, player2, playedDeck;
    CardDeck_init(&hiddenDeck);
    CardDeck_init(&player1);
    CardDeck_init(&player2);
    CardDeck_init(&playedDeck);

    /* Create and shuffle hidden deck */
    CardDeck_initWithPacks(&hiddenDeck, numPacks);
    CardDeck_shuffle(&hiddenDeck);
    printf("Created and shuffled hidden deck with %d cards\n", CardDeck_getSize(&hiddenDeck));

    /* Deal cards and play game */
    dealCards(&hiddenDeck, &player1, &player2);
    playGame(&hiddenDeck, &playedDeck, &player1, &player2);

    /* Cleanup */
    CardDeck_cleanup(&hiddenDeck);
    CardDeck_cleanup(&player1);
    CardDeck_cleanup(&player2);
    CardDeck_cleanup(&playedDeck);

    printf("Game finished. Press Enter to exit...");
    getchar(); getchar(); /* Wait for user input */

    return 0;
}