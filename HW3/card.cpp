  
#include "card.h"

Card::Card() {
    value = 0;
    prev = nullptr;
    next = nullptr;
}

Card::Card(int value, Card* prev, Card* next)
{
    this->value = value;
    this->prev = prev;
    this->next = next;
}

void Card::SetNext(Card* next)
{
    this->next = next;
}

void Card::SetPrev(Card* prev)
{
    this->prev = prev;
}

int Card::GetValue()
{
    return value;
}

Card* Card::GetNext()
{
    return next;
}

Card* Card::GetPrev()
{
    return prev;
}
