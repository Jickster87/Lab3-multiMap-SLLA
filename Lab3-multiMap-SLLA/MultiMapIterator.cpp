#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentElem = col.head;
}

TElem MultiMapIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }
    return col.Nodes[currentElem].pair;
}

bool MultiMapIterator::valid() const {
    return currentElem != -1;
}

void MultiMapIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentElem = col.Nodes[currentElem].next;
}

void MultiMapIterator::first() {
    currentElem = col.head;
}

