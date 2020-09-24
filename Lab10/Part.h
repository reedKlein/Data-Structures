#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Part {
private:
	string SKU;
	string description;
	int price;
	string UOM;
	int quantityOnHand;
	int leadTime;
public:
	Part() {
		SKU = "";
		description = "";
		price = 0;
		UOM = "";
		quantityOnHand = 0;
		leadTime = 0;
	}
	Part(string SKU, string description = "", int price = 0, string UOM = "", int quantityOnHand = 0) {
		this->SKU = SKU;
		this->description = description;
		this->price = price;
		this->UOM = UOM;
		this->quantityOnHand = quantityOnHand;
	}

	string getSKU() {
		return SKU;
	}

	void setSKU(string input) {
		SKU = input;
	}

	string GetPartInfo() {
		string ret_str = SKU + ": " + description;
		return ret_str;
	}
	int getPrice() {
		return price;
	}
	bool InStock() {
		return quantityOnHand > 0;
	}

	bool Available(string currDate) {
		size_t currentIndex = 0;
		size_t previousIndex = 0;

		//Find day
		currentIndex = currDate.find('/');
		int month = stoi(currDate.substr(0, currentIndex));

		//Find month
		previousIndex = currentIndex + 1;
		currentIndex = currDate.find('/', previousIndex);
		int day = stoi(currDate.substr(previousIndex, currentIndex));

		//Find year
		previousIndex = currentIndex + 1;
		int year = stoi(currDate.substr(previousIndex, currDate.size()));

		//Get total days from jan 1st
		int numDays = day + getNumberOfDays(month, year);

		//Product is available
		if (quantityOnHand > 0) {
			return true;
		}
		// Product will/wont be available then
		else
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);
			return numDays > (leadTime + ltm->tm_yday);
		}

	}

	//Function to return total number of days
	int getNumberOfDays(int month, int year)
	{
		if (month == 1) {
			return 31;
		}
		//Leap year condition, if month is 2
		if (month == 2) {
			if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
				return 29 + getNumberOfDays(month - 1, year);
			}
			else {
				return 28 + getNumberOfDays(month - 1, year);
			}
		}
		//Months which have 31 days
		else if (month == 3 || month == 5 || month == 7 || month == 8
			|| month == 10 || month == 12) {
			return 31 + getNumberOfDays(month - 1, year);
		}
		else {
			return 30 + getNumberOfDays(month - 1, year);
		}
	}

	void resetPart() {
		SKU = "";
		description = "";
		price = 0;
		UOM = "";
		quantityOnHand = 0;
		leadTime = 0;
	}

	// Overloaded string cast
	operator string() const {
		return SKU;
	}

	bool operator==(Part const& obj) {
		return SKU == obj.SKU;
	}
	bool operator>(Part const& obj) {
		return SKU > obj.SKU;
	}
	bool operator<(Part const& obj) {
		return SKU < obj.SKU;
	}

	void display() {
		cout << "#-----------------------------------------------------------#" << endl;
		cout << "# Price: " << price << endl;
		cout << "# Stock Keeping Number: " << SKU << endl;
		cout << "# Sold by the " << UOM << endl;
		cout << "# " << description << endl;
		cout << "#-----------------------------------------------------------#" << endl;
	}
};