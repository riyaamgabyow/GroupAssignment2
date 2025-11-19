#include "CardDeck.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

bool randomInitialized = false;

CardDeck::CardDeck() : cards(nullptr), size(0), capacity(0) {
    if (!randomInitialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        randomInitialized = true;
    }
}

CardDeck::CardDeck(int numPacks) : cards(nullptr), size(0), capacity(0) {
    if (!randomInitialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        randomInitialized = true;
    }

    for (int i = 0; i < numPacks; i++) {
        addStandardPack();
    }
}

CardDeck::CardDeck(const CardDeck& other) : size(other.size), capacity(other.size) {
    cards = new Card[capacity];
    for (int i = 0; i < size; i++) {
        cards[i] = other.cards[i];
    }
}

CardDeck& CardDeck::operator=(const CardDeck& other) {
    if (this != &other) {
        delete[] cards;

        size = other.size;
        capacity = other.size;

        cards = new Card[capacity];
        for (int i = 0; i < size; i++) {
            cards[i] = other.cards[i];
        }
    }
    return *this;
}

CardDeck::~CardDeck() {
    delete[] cards;
}

void CardDeck::resize(int newCapacity) {
    Card* newCards = new Card[newCapacity];

    for (int i = 0; i < size; i++) {
        newCards[i] = cards[i];
    }

    delete[] cards;
    cards = newCards;
    capacity = newCapacity;
}

int CardDeck::getSize() const {
    return size;
}

bool CardDeck::isEmpty() const {
    return size == 0;
}

void CardDeck::addCardToTop(const Card& card) {
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 4 : capacity * 2;
        resize(newCapacity);
    }

    for (int i = size; i > 0; i--) {
        cards[i] = cards[i - 1];
    }

    cards[0] = card;
    size++;
}

Card CardDeck::removeCardFromTop() {
    if (isEmpty()) {
        throw runtime_error("Cannot remove card from empty deck");
    }

    Card topCard = cards[0];

    for (int i = 0; i < size - 1; i++) {
        cards[i] = cards[i + 1];
    }

    size--;

    return topCard;
}

Card CardDeck::removeCardAtIndex(int index) {
    if (index < 0 || index >= size) {
        throw runtime_error("Invalid index for card removal");
    }

    Card removedCard = cards[index];

    for (int i = index; i < size - 1; i++) {
        cards[i] = cards[i + 1];
    }

    size--;

    return removedCard;
}

Card CardDeck::getCardAtIndex(int index) const {
    if (index < 0 || index >= size) {
        throw runtime_error("Invalid index for card access");
    }

    return cards[index];
}

void CardDeck::addStandardPack() {
    Suit suits[] = { Suit::CLUB, Suit::SPADE, Suit::HEART, Suit::DIAMOND };
    Rank ranks[] = { Rank::TWO, Rank::THREE, Rank::FOUR, Rank::FIVE, Rank::SIX,
                   Rank::SEVEN, Rank::EIGHT, Rank::NINE, Rank::TEN, Rank::JACK,
                   Rank::QUEEN, Rank::KING, Rank::ACE };

    for (Suit suit : suits) {
        for (Rank rank : ranks) {
            addCardToTop(Card(suit, rank));
        }
    }
}

void CardDeck::shuffle() {
    CardDeck tempDeck;
    int currentSize = size;

    while (currentSize > 0) {
        int randomIndex = rand() % currentSize;

        Card randomCard = removeCardAtIndex(randomIndex);
        tempDeck.addCardToTop(randomCard);

        currentSize--;
    }

    while (!tempDeck.isEmpty()) {
        addCardToTop(tempDeck.removeCardFromTop());
    }
}

void CardDeck::sort() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compareCards(cards[j + 1], cards[j])) {
                Card temp = cards[j];
                cards[j] = cards[j + 1];
                cards[j + 1] = temp;
            }
        }
    }
}

bool compareCards(const Card& a, const Card& b) {
    if (a.suit != b.suit) {
        return static_cast<int>(a.suit) < static_cast<int>(b.suit);
    }
    return static_cast<int>(a.rank) < static_cast<int>(b.rank);
}

string suitToString(Suit suit) {
    switch (suit) {
    case Suit::CLUB: return "Club";
    case Suit::SPADE: return "Spade";
    case Suit::HEART: return "Heart";
    case Suit::DIAMOND: return "Diamond";
    default: return "Unknown";
    }
}

string rankToString(Rank rank) {
    switch (rank) {
    case Rank::TWO: return "Two";
    case Rank::THREE: return "Three";
    case Rank::FOUR: return "Four";
    case Rank::FIVE: return "Five";
    case Rank::SIX: return "Six";
    case Rank::SEVEN: return "Seven";
    case Rank::EIGHT: return "Eight";
    case Rank::NINE: return "Nine";
    case Rank::TEN: return "Ten";
    case Rank::JACK: return "Jack";
    case Rank::QUEEN: return "Queen";
    case Rank::KING: return "King";
    case Rank::ACE: return "Ace";
    default: return "Unknown";
    }
}

string cardToString(const Card& card) {
    return rankToString(card.rank) + " of " + suitToString(card.suit) + "s";
}