  
#include<iostream>
#include "side.h"

Side::Side() {
	m_size = 5;
	m_head = 0;
	for (int i = 0; i < m_size; i++) {
		sideArray[i] = 0;
	}
}

Side::~Side() {
	delete[] sideArray;
}

void Side::push(Card* card) {
	//check for overflow
	sideArray[m_head] = card;
	m_head++;
}

Card* Side::pop(){
	//check for underflow

	m_head--;
	Card* card_ptr = sideArray[m_head];
	return card_ptr;
}

int Side::length() {
	return m_head;
}
