#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	current = m.head;
}

void SortedSetIterator::first() {
	current = multime.head;
}


void SortedSetIterator::next() {
	if(current == -1)
		throw exception();
	
	current = multime.nodes[current].next;
}


TElem SortedSetIterator::getCurrent()
{
	if (current == -1) 
		throw exception();
	return multime.nodes[current].elem;
}

bool SortedSetIterator::valid() const {
	return current != -1;
}

