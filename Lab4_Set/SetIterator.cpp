#include "SetIterator.h"
#include "Set.h"
#include <exception>

using namespace std;

SetIterator::SetIterator(const Set& m) : set(m)
{
	this->current = 0;
}


void SetIterator::first() {
	/*
		m - set capacity
		Best Case: If the first element is in the first position, Theta(1)
		Worst Case: The first element is present in the last position or not in the set, Theta(m)

		Total: O(m)
	*/
	this->current = 0;
	while(current < this->set.capacity && this->set.elements[current] == NULL_TELEM)
			this->current++;
}


void SetIterator::next() {
	/*
		m - set capacity
		Best Case: If the next element is right after the current one in the array, Theta(1)
		Worst Case: The current element is present in the first position and the next in the last, Theta(m)

		Total: O(m)
	*/
	if(this->current >= this->set.capacity || this->set.elements[current] == NULL_TELEM)
	{
		throw exception();
	}
	else
	{
		this->current++;
		while(current < this->set.capacity && this->set.elements[current] == NULL_TELEM)
			this->current++;
	}
}

TElem SetIterator::getCurrent()
{
	if(this->current >= this->set.capacity || this->set.elements[current] == NULL_TELEM)
	{
		throw exception();
	}
	return this->set.elements[this->current];
}

bool SetIterator::valid() const {
	if(this->current >= this->set.capacity || this->set.elements[current] == NULL_TELEM || this->current < 0)
	{
		return false;
	}
	return true;
}

void SetIterator::previous()
{
	/*
		m - set capacity
		Best Case: If the previous element is right before the current one in the array, Theta(1)
		Worst Case: The current element is present in the last position and the previous in the first, Theta(m)

		Total: O(m)
	*/
	if(this->current < 0 || this->set.elements[current] == NULL_TELEM)
	{
		throw exception();
	}
	this->current--;
	while(current > 0 && this->set.elements[current] == NULL_TELEM)
		this->current--;
}
