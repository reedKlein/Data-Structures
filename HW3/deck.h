#pragma once
#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Deck
{
private:
    Card* top = nullptr;
    Card* tail = nullptr;
    const int HIGHEST_VALUE = 14;
    int numberOfCardsInDeck = 0;
public:
    Deck();
    void MakeFullDeck();
    void Push(int value);
    void Discard(Card* card);
    void addCard(Card* card);
    Card* TakeFromTop();
    Card* Try();
    int Peek();
    void Shuffle();
    void InsertAt(Card* card, int index);
    void printDeck();
    int GetNumCards();

};
#endif
