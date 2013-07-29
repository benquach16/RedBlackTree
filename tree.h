#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>

//tree class

class Tree
{
public:
	//most of these function should be recursive
	//default constructor
	Tree();
	//parameterized constructor
	Tree(int val);
	//copy constructor
	Tree(const Tree *t);
	//assignment operator
	Tree &operator=(const Tree *t);
	//destructor
	~Tree();
	//adds another value to the tree
	void push(int val);
	//erase function
	void erase(int val);
	//simply returns true if the value is in the tree or not
	bool find(int val);
	void clear();
	void print()
	{
		std::cout << "parent - " << value << " color - " << red << std::endl;
		if(left)
		{
			std::cout << "parent - " << value << "left - " << left->value << std::endl;
			left->print();
		}
		if(right)
		{
			std::cout << "parent - " << value << "right - " << right->value << std::endl;
			right->print();
		}
	}
	
private:
	//private functions
	void rebalance();
	void rotate_right(Tree *n);
	void rotate_left(Tree *n);
	Tree *right;
	Tree *left;
	Tree *parent;
	bool red;
	int value;
};

#endif