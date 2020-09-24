#pragma once
#include <iostream>
#include <string>

using namespace std;

// Class to hold data for each node in Binary Tree
// Contains a count for contained word and the word itself
class NodeData {
public:
    int m_count;
    string m_word;

    // Default Constructor
    NodeData() {
        m_count = 1;
        m_word = "";
    }

    // Overloaded Constructor
    NodeData(string word) {
        m_count = 1;
        m_word = word;
    }

    // Deconstructor
    ~NodeData() {

    }

    // Resets all object members
    void reset() {
        m_count = 1;
        m_word = "";
    }

    bool operator<(const NodeData rhs) const {
        return this->m_word < rhs.m_word;
    }

    bool operator>(const NodeData rhs) const {
        return this->m_word > rhs.m_word;
    }

    bool operator==(const NodeData rhs) const {
        return this->m_word == rhs.m_word;
    }
};