#ifndef CARDDECK_H
#define CARDDECK_H

#include "Card.h"

typedef struct {
    Card* cards;
    int size;
    int capacity;
} CardDeck;

void CardDeck_init(CardDeck* deck);
void CardDeck_initWithPacks(CardDeck* deck, int numPacks);
void CardDeck_copy(const CardDeck* src, CardDeck* dest);
void CardDeck_cleanup(CardDeck* deck);

int CardDeck_getSize(const CardDeck* deck);
int CardDeck_isEmpty(const CardDeck* deck);
void CardDeck_addCardToTop(CardDeck* deck, Card card);
Card CardDeck_removeCardFromTop(CardDeck* deck);
Card CardDeck_removeCardAtIndex(CardDeck* deck, int index);
Card CardDeck_getCardAtIndex(const CardDeck* deck, int index);

void CardDeck_shuffle(CardDeck* deck);
void CardDeck_sort(CardDeck* deck);
void CardDeck_addStandardPack(CardDeck* deck);

int compareCards(const Card* a, const Card* b);
const char* cardToString(Card card);
const char* suitToString(Suit suit);
const char* rankToString(Rank rank);

#endif