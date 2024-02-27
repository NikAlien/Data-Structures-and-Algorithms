#include "Matrix.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

void Matrix::inorder(PNode head)
{
    if (head != NULL) {
        inorder(head->left);
        cout << "("<< head->row << ", "<< head->column << ") " << head->elem << " ";
        inorder(head->right);
    }
}

Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->nrCol = nrCols;
	this->nrRow = nrLines;
	this->root = nullptr;
}


int Matrix::nrLines() const {
	/*
		Constant initialization
		Theta(1)
	*/
	return this->nrRow;
}


int Matrix::nrColumns() const {
	/*
		Constant initialization
		Theta(1)
	*/
	return this->nrCol;
}

void Matrix::resize(int newLines, int newCol)
{
	/*
		Best Case: the input nr of rows and cols is bigger than what we have or invalid, Theta(1)
		Worst Case: if we have newLines == newCol == 1, Theta(i*j)

		Total: O(i*j)
	*/
	if(newLines <= 0 || newCol <= 0)
	{
		throw exception();
	}
	if(newLines < this->nrRow || newCol < this->nrCol)
	{
		for(int i = newLines; i < this->nrRow; i++)
			for(int j = 0; j < this->nrCol; j++)
			{
				TElem flag = element(i, j);
				if(flag != NULL_TELEM){
					this->root = deleteNode(root, i, j, flag);
				}
			}
		for(int i = 0; i < newLines; i++)
			for(int j = newCol; j < this->nrCol; j++)
			{
				TElem flag = element(i, j);
				if(flag != NULL_TELEM){
					this->root = deleteNode(root, i, j, flag);
				}
			}
	}	
	
	this->nrRow = newLines;
	this->nrCol = newCol;
}


TElem Matrix::element(int i, int j) const {
	/*
		m - nrRow * nrCol
		Best Case: Throws exception or the element we are looking for is the root, Theta(1)
		Worst Case: The element is the last to be checked in the tree or it isn't there, Theta(m)

		Total: O(m)
	*/
	if(i >= nrRow || j >= nrCol || i < 0 || j < 0)
	{
		throw exception();
	}
	vector<PNode> s;
	if(root != nullptr)
		s.push_back(root);

	while (s.size() != 0)
	{
		PNode curNode = s[0];
		s.erase(s.begin());

		if(curNode->column == j && curNode->row == i)
			return curNode->elem;
		
		if(curNode->right != nullptr)
			s.push_back(curNode->right);
		if(curNode->left != nullptr)
			s.push_back(curNode->left);
	}
	return NULL_TELEM;
}

Matrix::PNode Matrix::deleteNode(PNode head, int i, int j, TElem e) {
	/*
		h - height of tree
		Best Case: We delete root with only one child, Theta(1)
		Worst Case: We delete a leaf with two children, Theta(h)

		Total: O(h)
	*/
	if(head == nullptr)
		return head;
	if(e < head->elem)
		head->left = deleteNode(head->left, i, j, e);

	else if(e > head->elem)
		head->right = deleteNode(head->right, i, j, e);
	
	else
	{
		if(head->row != i && head->column != j)
			head->left = deleteNode(head->left, i, j, e);

		else{
		if(head->left == nullptr && head->right == nullptr)
			return nullptr;
		
		else if(head->left == nullptr)
		{
			PNode temp = head->right;
			delete head;
			return temp;
		}
		else if(head->right == nullptr)
		{
			PNode temp = head->left;
			delete head;
			return temp;
		}

		PNode temp = head->right;
		while(temp && temp->left!= nullptr)
			temp = temp->left;

		head->elem = temp->elem;
		head->column = temp->column;
		head->row = temp->row;
		head->right = deleteNode(head->right, temp->row, temp->column, temp->elem);
		}
	}
	return head;
}

TElem Matrix::modify(int i, int j, TElem e) {
	/*
		Modify is based on other functions we call like deleteNode() and insert()
		So the total complexity is Theta(1)
	*/
	if(i >= nrRow || j >= nrCol || i < 0 || j < 0)
	{
		throw exception();
	}

	PNode p = new Node(e, i, j, nullptr, nullptr);
	TElem flag = element(i, j);

	if(flag == NULL_TELEM && e != 0)
		this->root = insert(p, root);
	else if(flag != NULL_TELEM)
	{
		this->root = deleteNode(root, i, j, flag);
		if(e != 0)
			this->root = insert(p, root);
	}
	return flag;
}

Matrix::Node::Node(TElem e, int ro, int c, PNode r, PNode l)
{
	/*
		Constant initialization
		Theta(1)
	*/
	this->elem = e;
	this->row = ro;
	this->column = c;
	this->right = r;
	this->left = l;
}

Matrix::PNode Matrix::insert(PNode node, PNode head)
{
	/*
		h - height of tree
		Best Case: We insert the first child, Theta(1)
		Worst Case: We insert any other child, Theta(h)

		Total: O(h)
	*/
	if (head == nullptr)
	{
		head = node;
	}
	else
	{
		if(node->elem <= head->elem)
			head->left = insert(node, head->left);
		else
			head->right = insert(node, head->right);
	}
	return head;
}

Matrix::~Matrix()
{/*
		m - nrRow * nrCol
		We go through every leaf to delete it

		Total: Theta(m)
	*/
	Node* current = root;
	Node** queue = new Node* [nrCol * nrRow];
	int front = 0, back = -1;

	queue[++back] = current;
	while (front <= back)
	{
		current = queue[front++];
		if(current == nullptr)
			break;
		
		if(current->left != nullptr)
			queue[++back] = current->left;
		if(current->right != nullptr)
			queue[++back] = current->right;
		delete(current);
	}
}
