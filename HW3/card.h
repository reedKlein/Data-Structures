#pragma once
#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

class Card
{
private:
    int value;
public:
    Card* prev;
    Card* next;
    Card();
    Card(int value, Card* prev = nullptr, Card* next = nullptr);
    void SetNext(Card* next);
    void SetPrev(Card* prev);
    int GetValue();
    Card* GetNext();
    Card* GetPrev();
};
#endif
