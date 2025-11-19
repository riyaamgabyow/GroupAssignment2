#include <iostream>
#include "CardDeck.h"

using namespace std;

int main() {
    cout << "Testing Card and CardDeck implementation..." << endl;

    CardDeck deck(1);
    cout << "Created deck with " << deck.getSize() << " cards" << endl;

    deck.shuffle();
    cout << "Deck shuffled" << endl;

    cout << "First 5 cards:" << endl;
    for (int i = 0; i < 5 && i < deck.getSize(); i++) {
        cout << "  " << cardToString(deck.getCardAtIndex(i)) << endl;
    }

    deck.sort();
    cout << "Deck sorted" << endl;

    cout << "First 5 cards after sorting:" << endl;
    for (int i = 0; i < 5 && i < deck.getSize(); i++) {
        cout << "  " << cardToString(deck.getCardAtIndex(i)) << endl;
    }

    return 0;
}