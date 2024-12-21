#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    maxCap = MAX_CAPACITY;
    firstEmpty = 0;
    sizeBag = 0;
    head = -1;
    Nodes = new Node[maxCap];
    
    //init
    for (int i = 0; i < maxCap; i++) {
        Nodes[i].pair = NULL_TELEM;
        if (i < maxCap - 1) {
            Nodes[i].next = i + 1;
        } else {
            Nodes[i].next = -1;
        }
    }
}


void MultiMap::resize() {
    int oldCap = maxCap;
    maxCap *= 2;
    Node * newNodes = new Node[maxCap];
    
    
    for (int i=0; i<oldCap; i++) {
        newNodes[i] = Nodes[i];
    }
    
    
    for (int i = oldCap; i < maxCap; i++) {
        if (i < maxCap-1) {
            newNodes[i].next = i+1;
        } else {
            newNodes[i].next = -1;
        }
    }
    firstEmpty = oldCap;
    delete [] Nodes;
    Nodes = newNodes;
}


void MultiMap::add(TKey c, TValue v) {
    // Check if the free list is empty
    if (firstEmpty == -1) {
        resize(); // Expand the array if no free space is available
    }

    // Allocate a new node
    int newIndex = firstEmpty;           // Get the first free position
    firstEmpty = Nodes[firstEmpty].next; // Update firstEmpty to the next free node

    // Set the key-value pair and link the new node to the current head
    Nodes[newIndex].pair = std::make_pair(c, v);
    Nodes[newIndex].next = head;         // New node points to the current head

    // Update the head pointer to the new node
    head = newIndex;

    // Increment the size of the multimap
    sizeBag++;
}


bool MultiMap::remove(TKey c, TValue v) {
    //list empty
    if (head == -1) {
        return false;
    }
    int current = head;
    int prev = -1;
    //search for elem
    while (current != -1){
        if (Nodes[current].pair.first == c && Nodes[current].pair.second == v) {
            // Case 2: Found the node to remove
            if (current == head) {
                // Case 2a: Removing the head node
                head = Nodes[current].next; // Update head to the next node
            } else {
                // Case 2b: Removing a node in the middle or end
                Nodes[prev].next = Nodes[current].next; // Bypass the current node
            }
            Nodes[current].pair = NULL_TELEM;        // Mark as free
            Nodes[current].next = firstEmpty;       // Link to the current free list head
            firstEmpty = current;                   // Update firstEmpty to this node
            sizeBag--; // Decrease size
            return true; // Successfully removed
        }
        prev = current;
        current = Nodes[current].next;
    }
    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> result;
    int nomad = head;
    
    while (nomad != -1) {
        if (Nodes[nomad].pair.first == c) {
            result.push_back(Nodes[nomad].pair.second);
        }
        nomad = Nodes[nomad].next;
    }
    return result;
}


int MultiMap::size() const {
    return sizeBag;
}


bool MultiMap::isEmpty() const {
    return sizeBag == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    delete [] Nodes;
}

