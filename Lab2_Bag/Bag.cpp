#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::SLLNode::SLLNode(TElem e, int fr, PNode n)
{
	this->elem = e;
	this->frequency = fr;
	this->next = n;
}

Bag::Bag() {
	this->head = nullptr;
	this->length = 0;
}

void Bag::add(TElem elem) {
	/*
		best case: it's the first element, Theta(1)
		worst case: the element has no occurance in the bag or it is equal to the last element, Theta(n)
		total case: O(n)
	*/
	if(head == nullptr)
	{
		PNode p = new SLLNode(elem, 1, nullptr);
		p->next = head;
		head = p;
	}
	else
	{
		PNode prev = nullptr;
		PNode current = head;
		bool found = false;
		while(current != nullptr)
		{
			if(current->elem == elem)
			{
				current->frequency++;
				found = true;
				break;
			}
			prev = current;
			current = current->next;
		}
		if(!found)
		{
			PNode p = new SLLNode(elem, 1, nullptr);
			prev->next = p;
		}
	}
	this->length++;
}


bool Bag::remove(TElem elem) {
	/*
		best case: the element is the first one, Theta(1)
		worst case: the element is the last one or is not in the bag, Theta(n)
		total case: O(n)
	*/
	PNode prev = nullptr;
	PNode current = head;
	while(current != nullptr && current->elem != elem)
	{
		prev = current;
		current = current->next;
	}
	if(current != nullptr)
	{
		current->frequency--;
		if(current->frequency == 0)
		{
			if(prev == nullptr)
				head = head->next;
			else
				prev->next = current->next;
			delete current;
		}
		this->length--;
		return true;
	}
	return false;
}


bool Bag::search(TElem elem) const {
	/*
		best case: the element is the first one, Theta(1)
		worst case: the element is the last one or is not in the bag, Theta(n)
		total case: O(n)
	*/
	PNode aux = head;
	while(aux != nullptr)
	{
		if(aux->elem == elem)
			return true;
		aux = aux->next;
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	/*
		best case: the element is the first one, Theta(1)
		worst case: the element is the last one or is not in the bag, Theta(n)
		total case: O(n)
	*/
	PNode aux = head;
	while(aux != nullptr)
	{
		if(aux->elem == elem)
			return aux->frequency;
		aux = aux->next;
	}
	return 0;
}


int Bag::size() const {
	/*
		best case, worst case and total case are all Theta(1)

		it returns the bag's length 
	*/
	return this->length;
}


bool Bag::isEmpty() const {
	/*
		best case, worst case and total case are all Theta(1)
	*/
	if(head == nullptr)
		return true;
	return false;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	while (head != nullptr) {
		PNode p = head;
		head = head->next;
		delete p;
	}
}

void Bag::addOccurrences(int nr, TElem elem)
{
	/*
		best case: it's the first element, Theta(1)
		worst case: the element has no occurance in the bag or it is equal to the last element, Theta(n)
		total case: O(n)
	*/
	if(nr < 0)
		throw exception();

	if(nr == 0)
		return;

	if(head == nullptr)
	{
		PNode p = new SLLNode(elem, nr, nullptr);
		p->next = head;
		head = p;
		length += nr;
	}
	else
	{
		PNode prev = nullptr;
		PNode current = head;
		bool found = false;
		while(current != nullptr)
		{
			if(current->elem == elem)
			{
				current->frequency += nr;
				found = true;
				break;
			}
			prev = current;
			current = current->next;
		}
		if(!found)
		{
			PNode p = new SLLNode(elem, nr, nullptr);
			prev->next = p;
		}
		this->length += nr;
	}

}
