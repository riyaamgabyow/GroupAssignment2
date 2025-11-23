#include "CardDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static int randomInitialized = 0;

static void CardDeck_resize(CardDeck* deck, int newCapacity) {
    Card* newCards = (Card*)malloc(newCapacity * sizeof(Card));
    
    for (int i = 0; i < deck->size; i++) {
        newCards[i] = deck->cards[i];
    }
    
    free(deck->cards);
    deck->cards = newCards;
    deck->capacity = newCapacity;
}

void CardDeck_init(CardDeck* deck) {
    deck->cards = NULL;
    deck->size = 0;
    deck->capacity = 0;
    
    if (!randomInitialized) {
        srand((unsigned int)time(NULL));
        randomInitialized = 1;
    }
}

void CardDeck_initWithPacks(CardDeck* deck, int numPacks) {
    CardDeck_init(deck);
    
    for (int i = 0; i < numPacks; i++) {
        CardDeck_addStandardPack(deck);
    }
}

void CardDeck_copy(const CardDeck* src, CardDeck* dest) {
    dest->size = src->size;
    dest->capacity = src->size;
    dest->cards = (Card*)malloc(dest->capacity * sizeof(Card));
    
    for (int i = 0; i < src->size; i++) {
        dest->cards[i] = src->cards[i];
    }
}

void CardDeck_cleanup(CardDeck* deck) {
    free(deck->cards);
    deck->cards = NULL;
    deck->size = 0;
    deck->capacity = 0;
}

int CardDeck_getSize(const CardDeck* deck) {
    return deck->size;
}

int CardDeck_isEmpty(const CardDeck* deck) {
    return deck->size == 0;
}

void CardDeck_addCardToTop(CardDeck* deck, Card card) {
    if (deck->size >= deck->capacity) {
        int newCapacity = (deck->capacity == 0) ? 4 : deck->capacity * 2;
        CardDeck_resize(deck, newCapacity);
    }
    
    for (int i = deck->size; i > 0; i--) {
        deck->cards[i] = deck->cards[i - 1];
    }
    
    deck->cards[0] = card;
    deck->size++;
}

Card CardDeck_removeCardFromTop(CardDeck* deck) {
    if (CardDeck_isEmpty(deck)) {
        fprintf(stderr, "Cannot remove card from empty deck\n");
        exit(1);
    }
    
    Card topCard = deck->cards[0];
    
    for (int i = 0; i < deck->size - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }
    
    deck->size--;
    return topCard;
}

Card CardDeck_removeCardAtIndex(CardDeck* deck, int index) {
    if (index < 0 || index >= deck->size) {
        fprintf(stderr, "Invalid index for card removal\n");
        exit(1);
    }
    
    Card removedCard = deck->cards[index];
    
    for (int i = index; i < deck->size - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }
    
    deck->size--;
    return removedCard;
}

Card CardDeck_getCardAtIndex(const CardDeck* deck, int index) {
    if (index < 0 || index >= deck->size) {
        fprintf(stderr, "Invalid index for card access\n");
        exit(1);
    }
    
    return deck->cards[index];
}

void CardDeck_addStandardPack(CardDeck* deck) {
    Suit suits[] = {CLUB, SPADE, HEART, DIAMOND};
    Rank ranks[] = {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
    int numSuits = 4;
    int numRanks = 13;
    
    for (int i = 0; i < numSuits; i++) {
        for (int j = 0; j < numRanks; j++) {
            CardDeck_addCardToTop(deck, (Card){suits[i], ranks[j]});
        }
    }
}

void CardDeck_shuffle(CardDeck* deck) {
    CardDeck tempDeck;
    CardDeck_init(&tempDeck);
    int currentSize = deck->size;
    
    while (currentSize > 0) {
        int randomIndex = rand() % currentSize;
        
        Card randomCard = CardDeck_removeCardAtIndex(deck, randomIndex);
        CardDeck_addCardToTop(&tempDeck, randomCard);
        
        currentSize--;
    }
    
    while (!CardDeck_isEmpty(&tempDeck)) {
        CardDeck_addCardToTop(deck, CardDeck_removeCardFromTop(&tempDeck));
    }
    
    CardDeck_cleanup(&tempDeck);
}

void CardDeck_sort(CardDeck* deck) {
    for (int i = 0; i < deck->size - 1; i++) {
        for (int j = 0; j < deck->size - i - 1; j++) {
            if (compareCards(&deck->cards[j + 1], &deck->cards[j])) {
                Card temp = deck->cards[j];
                deck->cards[j] = deck->cards[j + 1];
                deck->cards[j + 1] = temp;
            }
        }
    }
}

int compareCards(const Card* a, const Card* b) {
    if (a->suit != b->suit) {
        return a->suit < b->suit;
    }
    return a->rank < b->rank;
}

const char* suitToString(Suit suit) {
    switch (suit) {
        case CLUB: return "Club";
        case SPADE: return "Spade";
        case HEART: return "Heart";
        case DIAMOND: return "Diamond";
        default: return "Unknown";
    }
}

const char* rankToString(Rank rank) {
    switch (rank) {
        case TWO: return "Two";
        case THREE: return "Three";
        case FOUR: return "Four";
        case FIVE: return "Five";
        case SIX: return "Six";
        case SEVEN: return "Seven";
        case EIGHT: return "Eight";
        case NINE: return "Nine";
        case TEN: return "Ten";
        case JACK: return "Jack";
        case QUEEN: return "Queen";
        case KING: return "King";
        case ACE: return "Ace";
        default: return "Unknown";
    }
}

const char* cardToString(Card card) {
    static char buffer[50];
    snprintf(buffer, sizeof(buffer), "%s of %ss", rankToString(card.rank), suitToString(card.suit));
    return buffer;
}