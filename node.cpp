#include "stdafx.h"
#include "node.h"

bool CNode::assignChild(CNode *child)
{
	if(child->getValue() > getValue())
	{
		//Larger, so assign to right node
		//Check if the right node exists first
		if(m_right == 0)
		{
			//Had no right child, so it's easier to assign it
			m_right = child;
			child->setParent(this);
			return true;
		}
		else
		{
			//fill this shit in later
			return false;
		}
	}
	else if(child->getValue() < getValue())
	{
		//Smaller, so we check the left node
		if(m_left == 0)
		{
			//Had no left child
			m_left = child;
			child->setParent(this);
			return true;
		}
		else
		{
			return false; 
		}
	}
}

void CNode::setLeftChild(CNode *left)
{
	m_left = left;
	//unlikely that we'll be assigning null pointers
	//but just in case
	if(left != 0)
		m_left->setParent(this);
}

void CNode::setRightChild(CNode *right)
{
	m_right = right;
	if(right != 0)
		m_right->setParent(this);
}

void CNode::setParent(CNode *parent)
{
	//hokay, so heres a problem with simply setting a parent
	//the parent node will not immediately recognize it as a child node
	//in order to do so, we need to either replace the left or right
	//child node with this node
	//that is why we use left and right tree transformations instead of
	//moving nodes all willy nilly
	m_parent = parent;
}