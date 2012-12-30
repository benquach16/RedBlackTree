//tree.h
//Header file for the main tree class

#ifndef _TREE_H_
#define _TREE_H_

#include "node.h"
#include "iostream"

class CTree
{
public:
	//Constructor
	CTree();
	//Destructor
	~CTree();

	//Recursive Function
	//Mostly used for debugging purposes
	//Finds the number of left children, recursively
	//going down the path until a null node is reached
	int findNumLeftChildren(CNode *node);
	//Recursive Function
	//Similar to above but for right paths
	int findNumRightChildren(CNode *node);

	//Balances the tree out while adding another node
	//tree only balances after a new node has been added
	//need to keep it fast, since balancing in logn time is a requirement
	//Essentially, if there is a red child to a red parent, then we need to
	//rebalance that branch of the tree
	//It doesn't fully optimize it, but its close enough
	void addNode(CNode *node);

	//simply adds without rebalancing
	void push(CNode *node);

	//Transformations
	//This function simply checks if there isn't red children to red parents
	bool isNodeBalanced(CNode *node);

	//Based off of Chris Okasaki's red black tree
	//Essentially, there are branches that work like so
	// [x]
	//	 \
	//	 [y]
	//	   \
	//	   [z]
	//Since y would be the middle value, we would reorganize it as so
	//		[y]
	//	   /   \
	//	 [x]   [z]
	void fixLeftLeftRedImbalance(CNode *node);
	void fixLeftRightRedImbalance(CNode *node);
	void fixRightRightRedImbalance(CNode *node);
	void fixRightLeftRedImbalance(CNode *node);




	//Search function
	//Returns node that matches that value
	CNode *findValue(int value);
	
	//returns root node
	CNode *getRootNode()
	{
		return m_median;
	}



private:
	CNode *m_median;

};

#endif