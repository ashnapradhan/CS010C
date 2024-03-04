#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Node {

    //node variables
    string small;
    string large;
    int count;

    //node pointers
    Node* left;
    Node* middle;
    Node* right;
    Node* parent;

    //node constructor
    Node(): small(""), large(""), count(0), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}
    Node(const string& input) : small(input), large(""), count(1), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}

};

