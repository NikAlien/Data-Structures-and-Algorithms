#include "Set.h"
#include "SetIterator.h"
#include <iostream>

int Set::h1(int k, int m)
{
	/*
		No present loops
		Theta(1)
	*/
	return k % m;
}

int Set::h2(int k, int m)
{
	/*
		No present loops
		Theta(1)
	*/
	int r = k % (m - 1);
	if(r % 2 == 1)
		return r;
	else
		return r + 1;
}

int Set::h(int k, int i, int m)
{
	/*
		No present loops
		Theta(1)
	*/
	return (h1(abs(k), m) + i * h2(abs(k), m)) % m;
}

Set::Set() {
	/*
		Constant initialization
		Theta(1)
	*/
	this->capacity = 4;
	this->nrElements = 0;
	this->elements = new TElem[4];
	for(int i = 0; i < this->capacity; i++)
		this->elements[i] = NULL_TELEM;
}

void Set::resize(TElem elem)
{
	/*
		m - set capacity

		Total: O(m^2)  - it needs to copy what's in the current set and rehash each based on the new capacity
	*/
	TElem* e = new TElem[this->capacity * 2];
	for(int i = 0; i < this->capacity * 2; i++)
		e[i] = NULL_TELEM;

	for(int i = 0; i < this->capacity; i++)
	{
		if(this->elements[i] != NULL_TELEM){
			int j = 0;
			int pos = this->h(this->elements[i], j, this->capacity * 2);
			while(j < this->capacity * 2 && e[pos] != NULL_TELEM)
			{
				pos = this->h(this->elements[i], j, this->capacity * 2); 
				j++;
			}
			e[pos] = this->elements[i];
		}
	}

	delete[] this->elements;
	this->elements = e;
	this->capacity *= 2;
	this->add(elem); 
}

bool Set::add(TElem elem) {
	/*
		m - set capacity
		Best Case: If the first probing offers an available position 
				   or element already present in first position, Theta(1)
		Worst Case: The set is completely full or element is present in its last probing, Theta(m)

		Total: O(m)
	*/
	int j = 0;
	int pos = this->h(elem, j, this->capacity);

	while(j < this->capacity && this->elements[pos] != NULL_TELEM)
	{
		pos = this->h(elem, j, this->capacity); 
		j++;
		if(this->elements[pos] == elem)
			return false;
	}

	if(j == this->capacity)
		resize(elem);
	else
	{
		this->elements[pos] = elem;
		this->nrElements++;
	}

	return true;
}


bool Set::remove(TElem elem) {
	/*
		m - set capacity
		Best Case: If the element already present in first position, Theta(1)
		Worst Case: The element is present in its last probing or not in the set, Theta(m)

		Total: O(m)
	*/
	int j = 0;
	int pos = this->h(elem, j, this->capacity);

	while(j < this->capacity)
	{
		pos = this->h(elem, j, this->capacity); 
		j++;
		if(this->elements[pos] == elem)
		{
			this->elements[pos] = NULL_TELEM;
			this->nrElements--;
			return true;
		}
	}
	return false;
}

bool Set::search(TElem elem) {
	/*
		m - set capacity
		Best Case: If the element already present in first position, Theta(1)
		Worst Case: The element is present in its last probing or not in the set, Theta(m)

		Total: O(m)
	*/
	int j = 0;
	int pos = this->h(elem, j, this->capacity);

	while(j < this->capacity)
	{
		pos = this->h(elem, j, this->capacity); 
		j++;
		if(this->elements[pos] == elem)
			return true;
	}
	return false;
}


int Set::size() const {
	/*
		No present loops
		Theta(1)
	*/
	return this->nrElements;
}


bool Set::isEmpty() const {
	/*
		No present loops
		Theta(1)
	*/
	if(this->nrElements == 0)
		return true;
	return false;
}


Set::~Set() {
	/*
		No present loops
		Theta(1)
	*/
	delete[] this->elements;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


