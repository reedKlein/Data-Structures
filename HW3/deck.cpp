#include "deck.h"

Deck::Deck()
{
    Card* top = nullptr;
    Card* tail = nullptr;
    int numberOfCardsInDeck = 0;
}

// double check that Number of cards is proper and there are no extra 1 values
void Deck::MakeFullDeck() //this populates a deck with values 2-14 twice, each deck ( the player and computer) is fair
{ 
    int count = 0;
    while (count < 2){
      for (int i = HIGHEST_VALUE; i > 1; i--) {
          Push(i);
      }
      count = count + 1;
      numberOfCardsInDeck = numberOfCardsInDeck +1;
    }
}

void Deck::Push(int value) //used for the small side piles (acts as a stack)
{
    //Creates a new Card from the passed in value and puts it on top of the Deck.
    Card* c = new Card(value, nullptr, nullptr);
    if (top != nullptr) {
        top->SetPrev(c);
        c->SetNext(top);
    }
    top = c;
    numberOfCardsInDeck++;
}

void Deck::Discard(Card* card)
//void Deck::Discard()       can we change this to return the popped value 
{
    if (numberOfCardsInDeck == 0) {
        return;
    }
    //Similar to Push but takes in a Card* instead of making a new Card.
    Card* prev = card->GetPrev();
    Card* next = card->GetNext();
    if (prev != nullptr) {
        prev->SetNext(next);
    }
    else {
        top = next;
    }

    if (next != nullptr) {
        next->SetPrev(prev);
    }
    numberOfCardsInDeck--;
    delete card;
}

void Deck::addCard(Card* cardAdded) { // adds card to bottom
    Card* tail = new Card;
    if (top != nullptr) {
        tail = top;
        while (tail->GetNext() != nullptr) { //
            tail = tail->GetNext();
        }
        tail->next = cardAdded;
        tail = cardAdded;
        tail->next = nullptr;
    }
    else {
        top = cardAdded; // if we dont have a list, we make cardAdded be the top
    }
    numberOfCardsInDeck++;
}

Card* Deck::TakeFromTop() //used by shuffle
{
    //Removes the Card from the top of the Deck and returns it.
    if (numberOfCardsInDeck == 0) {
        return nullptr;
    }
    Card* c = top;
    top = top->GetNext();
    if (top != nullptr)
        top->SetPrev(nullptr);
    numberOfCardsInDeck--;
    return c;
}

Card* Deck::Try() 
{
    //Removes the Card from the top of the Deck and sends it to add card
    if (numberOfCardsInDeck == 0) {
        return nullptr;
    }
    Card* c = top;
    top = top->GetNext();
    addCard(c);
    if (top != nullptr)
        top->SetPrev(nullptr);
    numberOfCardsInDeck--;
    //addCard(c);
    return 0;
}

int Deck::Peek()
{
    //Returns the value of the Card on top of the Deck without removing the Card.
    if (numberOfCardsInDeck == 0) {
        return -1;
    }
    return top->GetValue();
}

void Deck::Shuffle()
{
    int size = numberOfCardsInDeck;
    int iterations = 100;
    while (iterations-- > 0) {
        Card* c = TakeFromTop();
        int index = rand() % (numberOfCardsInDeck - 1);
        InsertAt(c, index);
    }
}

void Deck::InsertAt(Card* card, int index)
{
    //Inserts a Card at the given position, starting from 0.
    if (index == 0) {
        card->SetNext(top);
        if (top != nullptr) {
            top->SetPrev(card);
        }
        top = card;
    }
    else {
        Card* prev = top;
        while (prev != nullptr && index != 1) {
            prev = prev->GetNext();
            index--;
        }

        if (prev != nullptr) {
            card->SetNext(prev->GetNext());
            card->SetPrev(prev);
            if (card->GetNext() != nullptr) {
                card->GetNext()->SetPrev(card);
            }
            prev->SetNext(card);
        }
    }
    numberOfCardsInDeck++;
}

void Deck::printDeck() {
    if (numberOfCardsInDeck == 0) {
        cout << "EMPTY DECK" << endl;
    }
    else {
        cout << "Num Cards: " << numberOfCardsInDeck << endl;
        Card* x = top;
        while (x->GetNext() != nullptr) {
            cout << x->GetValue() << " ";
            x = x->GetNext();
        }
        cout << x->GetValue();
        cout << endl;
    }
}

int Deck::GetNumCards(){
  return numberOfCardsInDeck;
}
