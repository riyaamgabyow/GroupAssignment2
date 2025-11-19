#pragma once

enum class Suit {
    CLUB,
    SPADE,
    HEART,
    DIAMOND
};

enum class Rank {
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
};

struct Card {
    Suit suit;
    Rank rank;

    Card() : suit(Suit::CLUB), rank(Rank::TWO) {}

    Card(Suit s, Rank r) : suit(s), rank(r) {}
};