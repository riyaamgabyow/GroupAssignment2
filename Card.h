#ifndef CARD_H
#define CARD_H

typedef enum {
    CLUB,
    SPADE,  
    HEART,
    DIAMOND
} Suit;

typedef enum {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

#endif