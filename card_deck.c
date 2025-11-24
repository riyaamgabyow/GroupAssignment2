

#include <stdlib.h>
#include "card_deck.h"

 
static int carddeck_reserve(CardDeck* deck, int new_capacity)
{
	Card* new_cards;
	if (new_capacity <= deck->capacity) {
		return 0;
	}

	new_cards = (Card*)realloc(deck->cards, (size_t)new_capacity * sizeof(Card));
	if (new_cards == NULL) {
		return -1;
	}

	deck->cards = new_cards;
	deck->capacity = new_capacity;
	return 0;
}

void carddeck_init(CardDeck* deck)
{
	deck->cards = NULL;
	deck->size = 0;
	deck->capacity = 0;
}

void carddeck_free(CardDeck* deck)
{
	if (deck->cards != NULL) {
		free(deck->cards);
		deck->cards = NULL;
	}
	deck->size = 0;
	deck->capacity = 0;
}












int carddeck_add_top(CardDeck* deck, Card card)
{
	int new_capacity;
	if (deck->size >= deck->capacity) {
		if (deck->capacity == 0) {
			new_capacity = 4;
		} else {
			new_capacity = deck->capacity * 2;
		}

		if (carddeck_reserve(deck, new_capacity) != 0) {
			return -1;
		}
	}
	deck->cards[deck->size] = card;
	deck->size++;
	return 0;
}

int carddeck_add(CardDeck* deck, int index, Card card)
{
	int i;
	int new_capacity;

	if (index < 0 || index > deck->size) {
		return -1;
	}

	if (deck->size >= deck->capacity) {
		if (deck->capacity == 0) {
			new_capacity = 4;
		} else {
			new_capacity = deck->capacity * 2;
		}
		if (carddeck_reserve(deck, new_capacity) != 0) {
			return -1;
		}
	}
	/* Shifts elements up to make room for the new card */
	for (i = deck->size; i > index; i--) {
		deck->cards[i] = deck->cards[i - 1];
	}
	deck->cards[index] = card;
	deck->size++;
	return 0;
}










int carddeck_remove_top(CardDeck* deck, Card* out_card)
{
	if (deck->size == 0) {
		return -1;
	}

	if (out_card != NULL) {
		*out_card = deck->cards[deck->size - 1];
	}

	deck->size--;
	return 0;
}

int carddeck_remove(CardDeck* deck, int index, Card* out_card)
{
	int i;

	if (index < 0 || index >= deck->size) {
		return -1;
	}

	if (out_card != NULL) {
		*out_card = deck->cards[index];
	}

	/* Shift elements down to fill gap */
	for (i = index; i < deck->size - 1; i++) {
		deck->cards[i] = deck->cards[i + 1];
	}

	deck->size--;
	return 0;
}














int carddeck_get(const CardDeck* deck, int index, Card* out_card)
{
	if (index < 0 || index >= deck->size || out_card == NULL) {
		return -1;
	}
	*out_card = deck->cards[index];
	return 0;
}

int carddeck_set(CardDeck* deck, int index, Card card)
{
	if (index < 0 || index >= deck->size) {
		return -1;
	}
	deck->cards[index] = card;
	return 0;
}