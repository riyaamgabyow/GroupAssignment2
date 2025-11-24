

#ifndef CARD_DECK_H
#define CARD_DECK_H

#include "card.h"

typedef struct {
	Card* cards;
	int size;
	int capacity;
} CardDeck;

void carddeck_init(CardDeck* deck);

void carddeck_free(CardDeck* deck);



int carddeck_add_top(CardDeck* deck, Card card);

int carddeck_add(CardDeck* deck, int index, Card card);



int carddeck_remove_top(CardDeck* deck, Card* out_card);

int carddeck_remove(CardDeck* deck, int index, Card* out_card);



int carddeck_get(const CardDeck* deck, int index, Card* out_card);

int carddeck_set(CardDeck* deck, int index, Card card);



#endif