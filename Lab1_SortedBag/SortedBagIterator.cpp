#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->current = 0;
}

TComp SortedBagIterator::getCurrent() {
	/*
		best case, worst case and average case are all Theta(1)
	*/
	if(this->current >= this->bag.nrElements)
	{
		throw exception();
	}
	return this->bag.elements[this->current];
}

bool SortedBagIterator::valid() {
	/*
		best case, worst case and average case are all Theta(1)
	*/
	if(this->current < this->bag.nrElements)
	{
		return true;
	}
	return false;
}

void SortedBagIterator::next() {
	/*
		best case, worst case and average case are all Theta(1)
	*/
	if(this->current >= this->bag.nrElements)
	{
		throw exception();
	}
	else
	{
		this->current++;
	}
}

void SortedBagIterator::first() {
	/*
		best case, worst case and average case are all Theta(1)
	*/
	this->current = 0;
}

