#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
   Node* nodeNew = new Node; // create new node 
   nodeNew->payload = payload; // set payload for new node
   nodeNew->next = nullptr; // set the next as null
   return nodeNew; // return the new node
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr; // initialize head as null
    Node* prev = nullptr; // initialize prev as null
    string name; // declare name string

    for (int i = 0; i < n; ++i) { // while less than number of people
        name = names.at(i); // set name within vector of strings
        if (head == nullptr) { // if empty
            head = newNode(name); // set head to new node of new name
            prev = head; // set prev to head
        } else {
            prev->next = newNode(name); // set next of prev to new node of new name
            prev = prev->next; // move to next node
        }
    }

    if (prev != nullptr) {
        prev->next = head; // make circular by pointing prev's next to head
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start; // start at beginning
    while (curr != nullptr) { // while not at end
        cout << curr->payload << endl; // output payload
        curr = curr->next; // move to next node
        if (curr == start) { // if back to start
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr ) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
            prev = curr; // move to next node
            curr = curr->next; // move to next node
        }

       // delete kth node
        prev->next = curr->next; // skip over kth node
        delete curr; // delete kth node
        curr = curr->next; // mpve to next node
    }
    
    cout << curr->payload; // output payload

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

