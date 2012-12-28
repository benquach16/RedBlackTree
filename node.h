//node.h
//Header file for main node class

#ifndef _NODE_H_
#define _NODE_H_

#pragma once

enum NODE_COLOR
{
	BLACK = 0,
	RED = 1,
};

class CNode
{
public:
	//Constructor
	//The default color is Red because all newly added nodes should be red
	//for the purposes of balancing
	CNode(int value, NODE_COLOR color = RED) : m_value (value), m_color(color)
	{
		//Lets make sure we assign everything 0 value pointers
		//So we can tell if it has a child and parent
		m_left = 0;
		m_right = 0;
		m_parent = 0;
	}
	~CNode();

	//Assigns a child to the node
	//Returns true if it was successful in adding the child (it had no child in that slot)
	//Returns false if it already has a child where we wanted to assign it
	bool assignChild(CNode *child);

	//Manually sets the child, because we don't want to deal with setting null pointers
	//When we are rebalancing the tree
	void setLeftChild(CNode *left);
	void setRightChild(CNode *right);
	void setParent(CNode *parent);
	
	//Return functions
	int getValue()
	{
		return m_value;
	}
	CNode *getLeftChild()
	{
		return m_left;
	}
	CNode *getRightChild()
	{
		return m_right;
	}
	CNode *getParent()
	{
		return m_parent;
	}
	NODE_COLOR getNodeColor()
	{
		return m_color;
	}
	void setNodeColor(NODE_COLOR new_color)
	{
		m_color = new_color;
	}

private:
	//Left child node
	CNode *m_left;
	//Right Child Node
	CNode *m_right;
	//Parent node
	CNode *m_parent;
	//Value of the node
	int m_value;
	//Color of the node
	NODE_COLOR m_color;
};

#endif