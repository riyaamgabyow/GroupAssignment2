#pragma once
#include "Card.h"
#include <string>

class CardDeck {
private:
    Card* cards;
    int size;
    int capacity;
    void resize(int newCapacity);

public:
    CardDeck();
    CardDeck(int numPacks);
    CardDeck(const CardDeck& other);
    CardDeck& operator=(const CardDeck& other);
    ~CardDeck();

    int getSize() const;
    bool isEmpty() const;
    void addCardToTop(const Card& card);
    Card removeCardFromTop();
    Card removeCardAtIndex(int index);
    Card getCardAtIndex(int index) const;

    void shuffle();
    void sort();
    void addStandardPack();
};

bool compareCards(const Card& a, const Card& b);
std::string cardToString(const Card& card);
std::string suitToString(Suit suit);
std::string rankToString(Rank rank);