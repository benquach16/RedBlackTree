//tree.cpp
//Source file for the red-black tree

#include "stdafx.h"
#include "tree.h"

//constructor
CTree::CTree() : m_median(0)
{

	//Root should be black
	
	m_median = new CNode(50, BLACK);
	CNode *test = new CNode(17);
	CNode *n = new CNode(14);
	CNode *r = new CNode(64);
	CNode *l = new CNode(100);
	CNode *e = new CNode(72);
	CNode *p = new CNode(110);
	CNode *o = new CNode(120);

	addNode(test);
	addNode(n);
	addNode(r);
	addNode(l);
	addNode(e);
	addNode(p);
	addNode(o);
	
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
	push(node);
	node->setNodeColor(RED);
	
	while((node != m_median) && (node->getParent()->getNodeColor() == RED))
	{
		//we have double red
		//so we start transformations
		std::cout << "balancing " << node->getValue() << std::endl;
		std::cout << "root " << m_median->getValue() << std::endl;
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

		node = node->getParent();

	}
	

	//make sure root is black after this
	//so we don't accidently change it
	m_median->setNodeColor(BLACK);
	
}

void CTree::push(CNode *node)
{
	CNode *root = m_median;
	std::cout << "adding value " << node->getValue() << std::endl;
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
		while(root->assignChild(node) == false)
		{
			if(node->getValue() < root->getValue())
			{
				//left
				root = root->getLeftChild();
			}
			else
			{
				//right
				root = root->getRightChild();
			}
		}
	}
}

CNode* CTree::findValue(int value)
{
	//we'll return 0 if it wasn't found

	CNode *node = m_median;
	while(value != node->getValue())
	{
		std::cout << "checking value " << node->getValue() << std::endl;
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
	if(grandparent == m_median)
	{
		//grandparent was the root
		m_median = parent;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(grandparent == grandparent->getParent()->getLeftChild())
		{
			//was a left child
			grandparent->getParent()->setLeftChild(parent);
		}
		else
		{
			//right child
			grandparent->getParent()->setRightChild(parent);
		}
	}
	//parent will be the new red node
	//parent of the parent and node will become black
	//parent of parent becomes the new right and node becomes left
	//parent is a left child node
	grandparent->setLeftChild(parent->getRightChild());

	parent->setRightChild(grandparent);
	parent->setLeftChild(node);
	//quick and easy
	//since parent and node are red, we fix that
	node->setNodeColor(BLACK);
	grandparent->setNodeColor(BLACK);
	std::cout << "left " << node->getValue() << " parent " << parent->getValue() << " right " << grandparent->getValue() << std::endl;
}

void CTree::fixLeftRightRedImbalance(CNode *node)
{
	//similar to above function but
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	if(parent->getParent() == m_median)
	{
		//parents parent was the root
		//maake sure we don't 'lose' the old root though
		m_median = node;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(grandparent == grandparent->getParent()->getLeftChild())
		{
			//was a left child
			grandparent->getParent()->setLeftChild(node);
		}
		else
		{
			//right child
			grandparent->getParent()->setRightChild(node);
		}
	}
	//since the new node is on the right side, it becomes the new root of this sub branch
	//why? because by being placed on the right side, it means its the median number
	//so we reassign it
	if(node->getLeftChild() != 0)
	{
		parent->setRightChild(node->getLeftChild());
	}

	grandparent->setLeftChild(node->getRightChild());

	node->setLeftChild(parent);
	node->setRightChild(grandparent);
	//node remains red
	//parent goes black
	parent->setNodeColor(BLACK);
	grandparent->setNodeColor(BLACK);
	std::cout << "left " << parent->getValue() << " parent " << node->getValue() << " right " << grandparent->getValue() << std::endl;
}

void CTree::fixRightLeftRedImbalance(CNode *node)
{
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	//new node is now root
	if(parent->getParent() == m_median)
	{
		//parents parent was the root
		m_median = node;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(grandparent == grandparent->getParent()->getLeftChild())
		{
			//was a left child
			grandparent->getParent()->setLeftChild(node);
		}
		else
		{
			//right child
			grandparent->getParent()->setRightChild(node);
		}
	}
	if(node->getRightChild() != 0)
	{
		parent->setLeftChild(node->getRightChild());
	}

	grandparent->setRightChild(node->getLeftChild());

	node->setRightChild(parent);
	node->setLeftChild(grandparent);
	parent->setNodeColor(BLACK);
	grandparent->setNodeColor(BLACK);
	std::cout << "left " << grandparent->getValue() << " parent " << node->getValue() << " right " << parent->getValue() << std::endl;
}

void CTree::fixRightRightRedImbalance(CNode *node)
{
	CNode *parent = node->getParent();
	CNode *grandparent = node->getParent()->getParent();
	//parent is now root
	if(parent->getParent() == m_median)
	{
		//parents parent was the root
		m_median = parent;
	}
	else
	{
		//we reassign the root cause we just broke a chain
		if(grandparent == parent->getParent()->getParent()->getLeftChild())
		{
			//was a left child
			grandparent->getParent()->setLeftChild(parent);
		}
		else
		{
			//right child
			grandparent->getParent()->setRightChild(parent);
		}
	}


	grandparent->setRightChild(parent->getLeftChild());
	
	parent->setLeftChild(grandparent);
	parent->setRightChild(node);
	node->setNodeColor(BLACK);
	grandparent->setNodeColor(BLACK);
	std::cout << "left " << grandparent->getValue() << " parent " << parent->getValue() << " right " << node->getValue() << std::endl;
}

