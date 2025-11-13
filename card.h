#ifndef CARD_H
#define CARD_H

/**
 * @file card.h
 * @brief Provides data types and function declarations for representing and
 *        working with individual playing cards.
 *
 * This header defines:
 *   - The Suit enumeration (4 possible suits)
 *   - The Rank enumeration (13 possible card values)
 *   - The Card structure (combines suit + rank)
 *   - Functions to print a card and check matching rules
 *
 * These definitions form the foundation of the card game used in the project.
 * All other modules (Deck, Game Logic, etc.) depend on this file.
 */

 /**
  * @enum Suit
  * @brief Represents the four possible suits in a standard 52-card deck.
  *
  * The actual integer values (0–3) are irrelevant but the symbolic names improve
  * readability and prevent errors when dealing with suits.
  */
typedef enum {
    CLUB,      /**< Clubs suit (black clover symbol)  */
    SPADE,     /**< Spades suit (black pointed symbol) */
    HEART,     /**< Hearts suit (red heart symbol)     */
    DIAMOND    /**< Diamonds suit (red diamond symbol) */
} Suit;

/**
 * @enum Rank
 * @brief Represents all possible card ranks from Two through Ace.
 *
 * These values range from 0 to 12. Their ordering supports sorting operations
 * performed later in the assignment by the deck module.
 */
typedef enum {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN,   /**< Number cards 2–7 */
    EIGHT, NINE, TEN,                     /**< Number cards 8–10 */
    JACK, QUEEN, KING, ACE                /**< Face cards + Ace */
} Rank;

/**
 * @struct Card
 * @brief A single playing card consisting of a Rank and Suit.
 *
 * This structure stores the full identity of a card. All card-related logic,
 * matching rules, deck storage, and printing rely on this structure.
 */
typedef struct {
    Suit suit;   /**< The card's suit (e.g., HEART) */
    Rank rank;   /**< The card's rank (e.g., KING)  */
} Card;

/**
 * @brief Prints a human-readable description of a card.
 *
 * Example output:
 * @code
 * Ace of Spades
 * Five of Hearts
 * @endcode
 *
 * @param c Pointer to the Card to be printed. Must not be NULL.
 */
void printCard(const Card* c);

/**
 * @brief Determines whether card @p c can be played on top of @p top based on
 *        the assignment's matching rules.
 *
 * A card is considered a match if:
 *   - It has the same rank as @p top, OR
 *   - It has the same suit as @p top.
 *
 * @param c   The card the player wants to play.
 * @param top The card currently on top of the played deck.
 * @return 1 if the cards match, otherwise 0.
 */
int cardMatches(const Card* c, const Card* top);

#endif
