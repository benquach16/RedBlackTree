//tree.cpp
//Source file for the red-black tree

#include "stdafx.h"
#include "tree.h"

//constructor
CTree::CTree() : m_median(0)
{

	//Root should be black
	/*
	m_median = new CNode(50, BLACK);
	CNode *test = new CNode(17);
	CNode *n = new CNode(14);
	CNode *r = new CNode(64);
	CNode *l = new CNode(100);
	CNode *e = new CNode(72);
	CNode *p = new CNode(5);

	addNode(test);
	addNode(n);
	addNode(r);
	addNode(l);
	addNode(e);
	addNode(p);
	*/
}

int CTree::findNumLeftChildren(CNode *node)
{
	//Recursively determines how many left children there are
	//debugging function, we should'nt actually use this in the tree
	int num = 0;
	if(node->getLeftChild()!=0)
	{
		num++;
		num+=findNumLeftChildren(node->getLeftChild());
	}
	return num;
}

int CTree::findNumRightChildren(CNode *node)
{
	//Another recursive function
	int num = 0;
	if(node->getRightChild()!=0)
	{
		num++;
		num+=findNumRightChildren(node->getLeftChild());
	}
	return num;
}

bool CTree::isNodeBalanced(CNode *node)
{
	//if node is red both of its children must be black
	//null pointers are black
	if(node->getNodeColor() == RED)
	{
		if(node->getLeftChild() != 0)
		{
			if(node->getLeftChild()->getNodeColor() != BLACK)
			{
				//left node is red
				return false;
			}
		}
		if(node->getRightChild() != 0)
		{
			if(node->getRightChild()->getNodeColor() != BLACK)
			{
				return false;
			}
		}
		if(node->getParent()->getNodeColor() == RED)
		{
			//red cannot have a parent that is red
			return false;
		}
	}
}

void CTree::addNode(CNode *node)
{
	//go down the tree, adding it where its appropriate
	//then balance
	//we set newly added nodes as red
	//node->setNodeColor(RED);
	CNode *root = m_median;
	if(root == 0)
	{
		//If there was no root to begin with
		//we'll make it the root
		m_median = node;
	}
	else
	{
		//since the assignchild memberfunction returns false
		//when the node already has a child, we keep going down
		//until we find one without a child
		while(!root->assignChild(node))
		{
			//theres children already so we check them
			//then we set root to the child
			if(node->getValue() < root->getValue())
			{
				root = root->getLeftChild();
			}
			if(node->getValue() > root->getValue())
			{
				root = root->getRightChild();
			}
		}
		//once its added, we check if its parent is red
		if(node->getParent()->getNodeColor() == RED)
		{
			//we have double red
			//so we start transformations

			if(node->getParent()->getValue() < node->getParent()->getParent()->getValue())
			{
				//left sided
				if(node == node->getParent()->getLeftChild())
				{
					//left left side double red
					fixLeftLeftRedImbalance(node);
				}
				else
				{
					//has to be right sided then
					fixLeftRightRedImbalance(node);
				}
			}
			else
			{
				//right sided
				if(node == node->getParent()->getRightChild())
				{
					fixRightRightRedImbalance(node);
				}
				else
				{
					fixRightLeftRedImbalance(node);
				}
			}
		}
	}
	//make sure root is black after this
	//so we don't accidently change it
	m_median->setNodeColor(BLACK);
	
}

CNode* CTree::findValue(int value)
{
	//we'll return 0 if it wasn't found

	CNode *node = m_median;

	while(value != node->getValue())
	{
		//std::cout << "checking value " << node->getValue() << std::endl;
		if(value < node->getValue())
		{
			//check the left child
			if(node->getLeftChild() != 0)
			{
				node = node->getLeftChild();
			}
			else
			{
				//no more to check
				return 0;
			}
		}
		else
		{
			//had to be greater than
			if(node->getRightChild() !=0)
			{
				node = node->getRightChild();
			}
			else
			{
				return 0;
			}
		}
	}
	return node;
}

void CTree::fixLeftLeftRedImbalance(CNode *node)
{
	//Based off Chris Okasaki's red black tree
	//Check the header file for a rough diagram of what it does
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	if(parent->getParent()->getParent() == 0)
	{
		//parents parent was the root
		m_median = parent;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(parent->getParent() == parent->getParent()->getParent()->getLeftChild())
		{
			//was a left child
			parent->getParent()->getParent()->setLeftChild(parent);
		}
		else
		{
			//right child
			parent->getParent()->getParent()->setRightChild(parent);
		}
	}
	//parent will be the new red node
	//parent of the parent and node will become black
	//parent of parent becomes the new right and node becomes left
	//parent is a left child node
	if(parent->getRightChild() !=0)
	{
		parent->getParent()->setLeftChild(parent->getRightChild());
	}
	parent->setRightChild(grandparent);
	//quick and easy
	//since parent and node are red, we fix that
	node->setNodeColor(BLACK);
}

void CTree::fixLeftRightRedImbalance(CNode *node)
{
	//similar to above function but
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	if(parent->getParent()->getParent() == 0)
	{
		//parents parent was the root
		//maake sure we don't 'lose' the old root though
		m_median = node;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(parent->getParent() == parent->getParent()->getParent()->getLeftChild())
		{
			//was a left child
			parent->getParent()->getParent()->setLeftChild(node);
		}
		else
		{
			//right child
			parent->getParent()->getParent()->setRightChild(node);
		}
	}
	//since the new node is on the right side, it becomes the new root of this sub branch
	//why? because by being placed on the right side, it means its the median number
	//so we reassign it
	if(node->getLeftChild() != 0)
	{
		parent->setRightChild(node->getLeftChild());
	}
	if(node->getRightChild() !=0)
	{
		parent->getParent()->setLeftChild(node->getRightChild());
	}
	node->setLeftChild(parent);
	node->setRightChild(grandparent);
	//node remains red
	parent->setNodeColor(BLACK);
}

void CTree::fixRightLeftRedImbalance(CNode *node)
{
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	//new node is now root
	if(parent->getParent()->getParent() == 0)
	{
		//parents parent was the root
		m_median = node;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(parent->getParent() == parent->getParent()->getParent()->getLeftChild())
		{
			//was a left child
			parent->getParent()->getParent()->setLeftChild(node);
		}
		else
		{
			//right child
			parent->getParent()->getParent()->setRightChild(node);
		}
	}
	if(node->getRightChild() != 0)
	{
		parent->setLeftChild(node->getRightChild());
	}
	if(node->getLeftChild() != 0)
	{
		parent->getParent()->setRightChild(node->getLeftChild());
	}
	node->setRightChild(parent);
	node->setLeftChild(grandparent);
	parent->setNodeColor(BLACK);
	parent->getParent()->setNodeColor(BLACK);
}

void CTree::fixRightRightRedImbalance(CNode *node)
{
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	//parent is now root
	if(parent->getParent()->getParent() == 0)
	{
		//parents parent was the root
		m_median = parent;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(parent->getParent() == parent->getParent()->getParent()->getLeftChild())
		{
			//was a left child
			parent->getParent()->getParent()->setLeftChild(parent);
		}
		else
		{
			//right child
			parent->getParent()->getParent()->setRightChild(parent);
		}
	}

	if(parent->getLeftChild() != 0)
	{
		parent->getParent()->setRightChild(parent->getLeftChild());
	}
	parent->setLeftChild(grandparent);
	node->setNodeColor(BLACK);
}
