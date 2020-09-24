  
#include <iostream>
#include "deck.h"

void Play(Deck PD, Deck CD){
  if(CD.Peek() >= PD.Peek()){
    cout << "Computer Wins" << endl;
    CD.Try();
    CD.addCard(PD.TakeFromTop());
    PD.printDeck();
    CD.printDeck();
  }else{
    cout << "Player Wins" << endl;
    PD.Try();
    PD.addCard(CD.TakeFromTop());
    PD.printDeck();
    CD.printDeck();
  }
}

int main() {
    Deck PlayerDeck;
    Deck ComputerDeck;

    PlayerDeck.MakeFullDeck();
    PlayerDeck.printDeck();
    ComputerDeck.MakeFullDeck();
    ComputerDeck.printDeck();

    PlayerDeck.Shuffle();
    ComputerDeck.Shuffle();
    PlayerDeck.printDeck();
    ComputerDeck.printDeck();
    
    Play(PlayerDeck,ComputerDeck);
    cout << ComputerDeck.Peek() << endl;
    cout << PlayerDeck.Peek();


  
    /*char character = 'y';
    while (character =='y'){
      Play(PlayerDeck,ComputerDeck);
      cout << endl;
      if (PlayerDeck.GetNumCards() == 0){
        cout << "Computer Wins"<< endl;
        character = 'n';
      }else if (ComputerDeck.GetNumCards() == 0){
        cout << "Player Wins"<< endl;
        character = 'n';
      }else{
        cout << "Would you like to continue?"<< endl;
        cin >> character;
      }
    }*/
   
}
