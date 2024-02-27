#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	currentElem = c.head;
	currentFr = 1;
}

void BagIterator::first() {
	currentElem = bag.head;
	currentFr = 1;
}


void BagIterator::next() {
	if(currentElem == nullptr)
		throw exception();
	currentFr += 1;
	if(currentFr > currentElem->frequency)
	{
		currentElem = currentElem->next;
		currentFr = 1;
	}
}


bool BagIterator::valid() const {
	return currentElem != nullptr;
}

TElem BagIterator::getCurrent() const
{
	if(currentElem == nullptr)
		throw exception();
	return currentElem->elem;
}
