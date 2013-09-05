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
	//we have multiple deletion functions to cover all the cases
	void delete_case1();
	void delete_case2();
	void delete_case3();
	void delete_case4();
	void delete_case5();
	void delete_case6();
	//get the farthest left child pointer for deletion
	Tree *get_left();
	Tree *get_right();
	//get sibling
	Tree *sibling();

	Tree *right;
	Tree *left;
	Tree *parent;
	bool red;
	int value;
};

#endif