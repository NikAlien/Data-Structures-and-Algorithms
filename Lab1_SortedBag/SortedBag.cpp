#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

using namespace std;

SortedBag::SortedBag(Relation r) {
	this->nrElements = 0;
	this->capacity = 1;
	this->elements = new TComp[1];
	this->rel = r;
}

void SortedBag::add(TComp e) {
	/*
		best case: the element is in the last position, Theta(1)
		worst case: the element is in the first position so we need to move each element one position up, Theta(n)
		total case: O(n)
	*/
	if(this->nrElements == this->capacity)
		resize();

	int index = this->nrElements - 1;
	while(index >= 0 && this->rel(this->elements[index], e) == false)
	{
		this->elements[index + 1] = this->elements[index];
		index--;
	}

	this->elements[index + 1] = e;
	this->nrElements++;
}


bool SortedBag::remove(TComp e) {
	/*
		best case, worst case and average case are Theta(n)
		We need to go through the bag from first element till we find the first occurance of e,
		and from that index until n to move each element one postion down
		total case: O(n)
	*/
	int index = 0;
	bool found = false;

	while(index < this->nrElements && found == false)
	{
		if(this->elements[index] == e)
			found = true;
		else
			index++;
	}

	if(found == false)
		return false;
	else
	{
		this->nrElements--;
		for(int j = index; j < this->nrElements; j++)
			this->elements[j] = this->elements[j + 1];
		return true;
	}
}


bool SortedBag::search(TComp elem) const {
	/*
		best case: the first element is the one we are looking for, Theta(1)
		worst case: the element is the last position or not even in the bag, Theta(n)
		total case: O(n)

		Binary search better!!!!
	*/
	int index = 0;
	bool found = false;

	while(index < this->nrElements && found == false)
	{
		if(this->elements[index] == elem)
			found = true;
		else
			index++;
	}
	return found;
}


int SortedBag::nrOccurrences(TComp elem) const {
	/*
		best case: If the element we are looking for is the first one and is only one, Theta(1)
		worst case: If all elements are the same and are the given one 
					or the element is not in the bag at all
					Theta(n)
		Total case: O(n)
	*/
	int index = 0;
	int count = 0;

	while(index < this->nrElements && this->elements[index] != elem)
		index++;

	while(index < this->nrElements && this->elements[index] == elem)
	{
		count++;
		index++;
	}
	return count;
}

int SortedBag::size() const {
	/*
		best case, worst case and average case are all O(1)
	*/
	return this->nrElements;
}


bool SortedBag::isEmpty() const {
	/*
		best case, worst case and average case are all O(1)
	*/
	if(this->nrElements == 0)
		return true;
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] this->elements; 
}

void SortedBag::resize()
{
	/*
		Bestcase, worst case, average case are all O(n)
	*/
	TComp* e = new TComp[this->capacity * 2];

	for(int i = 0; i < this->nrElements; i++)
		e[i] = this->elements[i];

	delete[] this->elements;
	this->elements = e;
	this->capacity *= 2; 
}

int SortedBag::removeOccurrences(int nr, TElem elem)
{
	/*
		Best case: if the element is the first, it has only one occurence and nr is 0 then Theta(1) 
		Worst case: all the elements of the bag are equal with elem and nrElements is smaller than nr., Theta(n)
		Total complexity: O(n)
	*/
	if(nr < 0)
	{
		throw exception();
	}

	int occurrences = nrOccurrences(elem);
	if(occurrences >= nr || occurrences == 0)
		return 0;
	else
	{
		int index = 0;
		while(index < this->nrElements && this->elements[index] != elem)
			index++;
		
		for(int j = index; j < this->nrElements - occurrences; j++)
			this->elements[j] = this->elements[j + occurrences];
		
		this->nrElements  -= occurrences;
		return occurrences;
	}
}
