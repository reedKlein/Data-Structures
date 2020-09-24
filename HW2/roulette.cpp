#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;

class wheel { //wheel class
public:
    void spin() { //spins and returns possible values for the spin
        spinVal = (1 + (rand() % possVal));
    }
    int possVal;
    int spinVal;
};

class player { //player class
public:
    wheel w1; //instantiate wheel class inside of player class
    double getTotalMoney() { //getter function for totalMoney
        return totalMoney;
    }
    void setTotalMoney(double totalMoney) { //setter function for totalMoney
        this->totalMoney = totalMoney;
    }
private:
    double totalMoney;

};

int gettingRange() { //challenge mode
    int range;
    range = 10; // default values on wheel are 1-10
    char change;
    cout << "Would you like to use a different range of values from the default 1-10? (y/n)\n";

    bool moveOn = false;
    while (moveOn == false) { // this while loop assures that the user enters a proper input, y/n
        cin >> change;
        if (change == 'y') {
            cout << "Would what range of numbers would you like to use?" << endl;
            cin >> range;
            while (range < 6 || range > 20) { // assures that the range of numbers is between 6 and 20, if no, then asked again.
                cout << "Enter a value for the range that is between 6 and 20: ";
                cin >> range;
            }
            moveOn = true;
        }
        else if (change == 'n') {
            moveOn = true;
        }
        else {
            cout << "Invalid input. please enter y or n.\n";
        }
    }
    return range;
};

int getHousenum(int possVal) {
    return (1 + (rand() % possVal));
};

int betAmount(double totalMoney) { // prompts the user for how much they want to bet. 
    int betAmount;
    cout << "Your current money total is: " << totalMoney << endl << endl;
    cout << "How much would you like to bet?\n";
    cin >> betAmount;
    while (betAmount > totalMoney || betAmount <= 0) { // can't bet more than they have, can't bet nothing / 0
        cout << "Invalid bet amount. Make sure your bet is greater than 0 and below the total amount of money you have. The total amount of money you have is: " << totalMoney << endl;
        cin >> betAmount;
    };
    return betAmount;
};

double doubleBet(double betAmount, int possVal, int spinVal, double totalMoney) {
    double newDoubledBet = 2 * betAmount; //doubling the bet money
    cout << "You're confident! Your bet is now: " << newDoubledBet << endl << endl;

    double newTotalMoney;
    int houseVal1;
    int houseVal2;
    houseVal1 = getHousenum(possVal); //getting random numbers for house ball values
    houseVal2 = getHousenum(possVal);
    cout << "The house's balls landed on " << houseVal1 << " and " << houseVal2 << endl;
    if (houseVal1 >= spinVal || houseVal2 >= spinVal) { // only one house value needs to be greater for the house to win
        newTotalMoney = totalMoney - newDoubledBet; //newTotal = total - doubled bet becaues you lost!
        cout << "You only landed on: " << spinVal << endl;
        cout << "The house won. Your total is now: " << newTotalMoney << endl;
    }
    else {
        newTotalMoney = totalMoney + newDoubledBet; //newTotal - total + doubled bet because you won!
        cout << "You landed on: " << spinVal << endl;
        cout << "You won. Your total is now: " << newTotalMoney << endl;
    }
    return newTotalMoney;
};

double regBet(double betAmount, int possVal, int spinVal, double totalMoney) {
    cout << "Alright, sticking to your guns. Let's see how the house plays.\n";
    double newTotalMoney;
    int houseVal1;
    houseVal1 = getHousenum(possVal); //grab house ball valuevalue
    cout << "The house's ball landed on " << houseVal1 << endl;
    if (houseVal1 >= spinVal) {
        newTotalMoney = totalMoney - betAmount; // new total = total - bet amount because you lost
        cout << "You only landed on: " << spinVal << endl;
        cout << "The house won. Your total is now: " << newTotalMoney << endl;
    }
    else {
        newTotalMoney = totalMoney + betAmount; // new total = total + bet amount because you won
        cout << "You landed on: " << spinVal << endl;
        cout << "You won. Your total is now: " << newTotalMoney << endl;
    }
    return newTotalMoney;
};

double halfBet(double betAmount, int possVal, int spinVal, double totalMoney) {
    double newHalfBet = betAmount / 2;
    cout << "You're playing it safe! Your bet is now: " << newHalfBet << endl;

    double newTotalMoney;
    int houseVal1;
    int houseVal2;
    houseVal1 = getHousenum(possVal); //getting two house values
    houseVal2 = getHousenum(possVal);
    cout << "The house's balls landed on " << houseVal1 << " and " << houseVal2 << endl;
    if (houseVal1 >= spinVal && houseVal2 >= spinVal) { // both house values need to be greater than yours
        newTotalMoney = totalMoney - newHalfBet; //new total = total - half bet because you lost
        cout << "You only landed on: " << spinVal << endl;
        cout << "The house won. Your total is now: " << newTotalMoney << endl;
    }
    else {
        newTotalMoney = totalMoney; // new total = total (this is because you give the house half of your bet (-half) and then you won the bet so (+half) and they cancel each other and the player is left with the same total)
        cout << "You landed on: " << spinVal << endl;
        cout << "You won. Your total is now: " << newTotalMoney << endl;
    }
    return newTotalMoney;
};

int changeBet() { //option function for choosing how you want to bet
    int option;
    cout << "Would you like to:\n 1: Double your bet\n 2: Keep your bet the same\n 3: Halve your bet?" << endl << endl;
    cout << "Please enter 1,2 or 3.\n";
    cin >> option;
    while (option > 3 || option < 1) {
        cout << "Invalid choice. Please enter 1, 2 or 3.\n";
        cin >> option;
    };
    return option;
};

int main() {
    srand(time(0));
    player p1; // creating objects
    int myChoice;
    double THEbetAmount;
    double moneyInput;
    p1.w1.possVal = gettingRange(); // gets range of values on the wheel
    cout << "How much money does Player 1 have in total to play with?\n";
    cin >> moneyInput;
    p1.setTotalMoney(moneyInput); // sets totalMoney to proper value since totalMoney is private

    bool rechoose = false; //this is used as a check to assure that the operaion preformed on the bet (double half, or stay same) is valid 
    char keepGoing = 'y'; //this is used as a check to see if the user wants to keep playing roulette

    while (keepGoing == 'y' && p1.getTotalMoney() > 0) { //the parameters check if the user wants to keep going and if the user still has money to play with

        THEbetAmount = betAmount(p1.getTotalMoney()); //calls betAmount function and assigns it to a variable.
        cout << "Nice, lets spin the wheel and see where your ball lands...\n";
        p1.w1.spin();                                //calls the spin class function to generate a value that the wheel lands on
        cout << "Your ball landed on: " << p1.w1.spinVal << endl << endl;
        do {
            myChoice = changeBet();// calls change bet function to see if user wants to double, half, or not change bet
            if (myChoice == 1) { // passes if user wants to double their bet
                if ((THEbetAmount * 2) > p1.getTotalMoney()) { // this checks if the user doubling their bet is valid. 
                    cout << "Unable to double bet becuase it exceeds the total amount of money you have. Try again.\n";
                    rechoose = true; // this has the user rechoose an operation to preform on their bet, since doubling their bet it invalid
                }
                else {
                    p1.setTotalMoney(doubleBet(THEbetAmount, int(p1.w1.possVal), int(p1.w1.spinVal), double(p1.getTotalMoney()))); //amount bet, the possible values that the house could land on, the value the player landed on, the total amount of money that p1 has
                    rechoose = false; // operation on bet is valid
                }
            }
            else if (myChoice == 2) { //passes if user wants to keep their bet the same
                p1.setTotalMoney(regBet(THEbetAmount, int(p1.w1.possVal), int(p1.w1.spinVal), double(p1.getTotalMoney())));
                rechoose = false;// operation on bet is valid
            }
            else if (myChoice == 3) {//passes if user wants to halve their bet
                p1.setTotalMoney(halfBet(THEbetAmount, int(p1.w1.possVal), int(p1.w1.spinVal), double(p1.getTotalMoney())));
                rechoose = false; // operation on bet is valid
            }
            else {
                cout << "Invalid choice, please enter 1, 2 or 3.\n";//makes sure that the user enters a proper option
                rechoose = true; // makes the user choose again/go through lop again
            }
        } while (rechoose == true);

        cout << "Would you like to keep playing? (y/n)\n ";
        cin >> keepGoing;
        while (keepGoing != 'y' && keepGoing != 'n') { //assures keepGoing is proper(eithery/n)
            cout << "Please enter a valid value, y or n. " << endl;
            cin >> keepGoing;
        }
    };

    if (p1.getTotalMoney() <= 0) {
        cout << "You ran out of money... Sorry mate.\n";
    }
    cout << "Thank you for playing.";

    return 0;
}
