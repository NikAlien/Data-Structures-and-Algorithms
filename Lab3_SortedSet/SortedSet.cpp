#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

void SortedSet::resize()
{
	/*
	It copies each element and than establishes the next for the new added cells
		Theta(n)
	*/
	DLLANode* e = new DLLANode[this->capacity * 2];
	int current = head;
	while(current != -1)
	{
		e[current].elem = this->nodes[current].elem;
		e[current].next = this->nodes[current].next; 
		e[current].prev = this->nodes[current].prev; 
		current = this->nodes[current].next;
	}

	for(int i = this->capacity; i < this->capacity * 2 - 1; i++)
		e[i].next = i + 1;
	e[capacity * 2 - 1].next = -1;

	delete[] this->nodes;
	this->nodes = e;
	firstFree = this->capacity;
	this->capacity *= 2;
}

int SortedSet::nextFree()
{
	/*
		No present loops
		Theta(1)
	*/
	if(this->firstFree == -1)
		this->resize();

	int newFreePos = firstFree;
	firstFree = this->nodes[firstFree].next;
	return newFreePos;
}

void SortedSet::freeP(int pos)
{
	/*
		No present loops
		Theta(1)
	*/
	this->nodes[pos].next = firstFree;
	this->firstFree = pos;
}

SortedSet::SortedSet(Relation r)
{
    this->head = -1;
	this->tail = -1;
	this->capacity = 1;
	this->rel = r;
	this->nrElements = 0;
	this->firstFree = 0;
	this->nodes = new DLLANode[1];
	this->nodes[firstFree].next = -1;
}

bool SortedSet::add(TComp e) {
	/*
		Best Case: There are no elements in the set or first element is equal to e, Theta(1)
		Worst Case: The element is not in the set or by relation is the last Theta(n)

		Total: O(n)
	*/
	int nextIndex = this->head;
	int index = this->head;

	while (index != -1 && nodes[index].elem != e)
	{
		index = nodes[index].next;
	}
	if(index != -1)
		return false;

	int pos = this->nextFree();
	if(this->head == -1)
	{
		nodes[pos].elem = e;
		nodes[pos].prev = -1;
		nodes[pos].next = -1;
		this->head = pos;
		this->tail = pos;
	}
	else
	{
		while(nextIndex != -1 && this->rel(e, this->nodes[nextIndex].elem) == false)
			nextIndex = nodes[nextIndex].next;
		if(nextIndex == this->head)
		{
			nodes[pos].elem = e;
			nodes[pos].next = this->head;
			nodes[pos].prev = -1;
			nodes[this->head].prev = pos;
			this->head = pos;
		}
		else if (nextIndex == -1)
		{
			nodes[pos].elem = e;
			nodes[pos].next = nodes[this->tail].next;
			nodes[pos].prev = this->tail;
			nodes[this->tail].next = pos;
			this->tail = pos;
		}
		else
		{
			nodes[pos].elem = e;
			nodes[pos].next = nextIndex;
			nodes[pos].prev = nodes[nextIndex].prev;

			nodes[nodes[pos].prev].next = pos;
			nodes[nextIndex].prev = pos;
			// std::cout << "\n Done: " << nodes[pos].elem << " "<< nodes[pos].next << " "<< nodes[pos].prev << "\n";
			// std::cout << "\n nx: " << nodes[nodes[pos].prev].elem << " "<< nodes[nodes[pos].prev].next<< " "<< nodes[nodes[pos].prev].prev << "\n";
			// std::cout << "\n pr: " << nodes[nextIndex].elem << " "<< nodes[nextIndex].next<< " "<< nodes[nextIndex].prev << "\n";
		}
	}
	this->nrElements++;
	int indexp = this->head;
	// std::cout << "Done all: " << firstFree << " " << head<< " " << tail<< "\n";
	// while(indexp != -1)
	// { 
	// 	std::cout << "Index: " << indexp<< "\n";
	// 	std::cout<< nodes[indexp].elem << " "<< nodes[indexp].next << " "<< nodes[indexp].prev << "\n";
	// 	indexp = nodes[indexp].next;
	// }
	return true;
}


bool SortedSet::remove(TComp elem) {
	/*
		Best Case: The element we want to remove is the head or no elements in set, Theta(1)
		Worst Case: The element is not in the set or is the last Theta(n)

		Total: O(n)
	*/
	int index = this->head;

	while (index != -1 && nodes[index].elem != elem)
	{
		index = nodes[index].next;
	}
	if(index != -1)
	{
		if (index == this->head)
		{
			this->head = nodes[index].next;
			nodes[nodes[index].next].prev = -1;
		}
		else if(index == this->tail)
		{
			this->tail = nodes[index].prev;
			nodes[nodes[index].prev].next = -1;
		}
		else
		{
			nodes[nodes[index].next].prev = nodes[index].prev;
			nodes[nodes[index].prev].next = nodes[index].next;
		}
		freeP(index);
	// 	int indexp = this->head;
	// std::cout << "\nRem all: " << firstFree << "\n";
	// while(indexp != -1)
	// {
	// 	std::cout<< nodes[indexp].elem << " ";
	// 	indexp = nodes[indexp].next;
	// }
		this->nrElements--;
		return true;
	}
	return false;
	
}


bool SortedSet::search(TComp elem) const {
	/*
		Best Case: There are no elements in the set or first element is equal to e, Theta(1)
		Worst Case: The element is not in the set or by relation is the last Theta(n)

		Total: O(n)
	*/
	int index = this->head;
	bool found = false;

	while(index != -1 && found == false)
	{
		if(this->nodes[index].elem == elem)
			found = true;
		else
			index = nodes[index].next;
	}
	return found;
}


int SortedSet::size() const {
	/*
		No present loops
		Theta(1)
	*/
	return this->nrElements;
}

bool SortedSet::isEmpty() const {
	/*
		No present loops
		Theta(1)
	*/
	if(this->nrElements == 0)
		return true;
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	delete[] this->nodes;
}


