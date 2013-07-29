#include "stdafx.h"
#include "tree.h"

Tree::Tree() : left(0), right(0), parent(0), red(false), value(0)
{
}

Tree::Tree(int val) : left(0), right(0), parent(0), value(val), red(false)
{
}

Tree::~Tree()
{
	if(left)
		delete left;
	if(right)
		delete right;
}

Tree::Tree(const Tree *t)
{
	//copy constructor
	this->value = t->value;
	if(t->right)
	{
		right = new Tree(t->right);
	}
	if(t->left)
	{
		left = new Tree(t->left);
	}
}

Tree& Tree::operator=(const Tree *t)
{
	//make sure we delete all the children first
	clear();
	this->value = t->value;
	if(t->right)
	{
		right = new Tree(t->right);
	}
	if(t->left)
	{
		left = new Tree(t->left);
	}
	return *this;
}

void Tree::push(int val)
{
	
	if(val < value)
	{
		//lesser than
		//go to left node
		if(left)
		{
			left->push(val);
		}
		else
		{
			//create new node
			Tree* new_node = new Tree(val);
			new_node->red = true;
			left = new_node;
			left->parent = this;
		}
	}
	else if(val > value)
	{
		//greater than
		if(right)
		{
			right->push(val);
		}
		else
		{
			Tree* new_node = new Tree(val);
			new_node->red = true;
			right = new_node;
			right->parent = this;
		}
	}
	else
	{
		//found the same value so we don't do anything
		//for future use, we could add somethingn like a list to each value
	}
	//check for balance
	rebalance();
	return;
}

void Tree::erase(int val)
{
	//find value first
	if(val < value)
	{
		//go left
		left->erase(val);
	}
	else if(val > value)
	{
		//go right
		right->erase(val);
	}
	else
	{

		//found it so do actual deletion stuff

	}
}


void Tree::clear()
{
	//delete everything in here
	if(left)
		delete left;
	if(right)
		delete right;
}

void Tree::rebalance()
{
	if(!parent)
	{
		//we're at the root, which should always be black so
		red = false;
	}
	if(left)
	{
		if(red && left->red)
		{
			//unbalanced
			//left imbalance
			//now we have to determine if its a right-left or a left-left
			//we shouldn't check if it doesnt have a parent because that would mean its the root
			//and if the root is red we dun goof'd somewhere
			if(parent->right == this)
			{
				//right-left
				rotate_right(this);
				rotate_left(parent);
				red = false;
				parent->red = true;
				left->red = false;
			}
			else
			{
				//left left
				//do a single rightward rotation
				//save the pointers for easy color changing
				//remember that we didnt swap the pointers
				Tree *l = parent;
				Tree *r = left;
				red = false;
				l->red = true;
				r->red = false;
				rotate_right(parent);
				//and change the colors

			}
		}
	}
	if(right)
	{
		if(red && right->red)
		{
			//right imbalance
			if(parent->right == this)
			{
				//right-right imbalance
				rotate_left(parent);
				//and change the colors
				red = false;
				right->red = false;
				parent->red = true;
			}
			else
			{
				Tree *l = parent;
				Tree *r = right;
				//right - left imbalance
				rotate_left(this);
				rotate_right(parent);
				red = false;
				l->red =true;
				r->red = false;
			}
		}
	}
	if(!parent)
		red = false;
}

void Tree::rotate_right(Tree *n)
{
	//rotates with its left child rightward
	//dont check if left exists because we already did that in rebalance()

	//do pointer swapping
	//just swap the values
	
	Tree *a = n->left->left;
	Tree *b = n->left->right;
	Tree *c = n->right;
	Tree *p = n->left;
	int t = n->value;
	n->value = n->left->value;
	n->left->value = t;

	//swap pointers and set parents
	n->right = p;
	if(p)
		p->parent = n;
	n->left = a;
	if(a)
		a->parent = n;
	n->right->right = c;
	if(c)
		c->parent = n->right;
	n->right->left = b;
	if(b)
		b->parent = n->right;

}

void Tree::rotate_left(Tree *n)
{
	//rotate with the right child leftward
	Tree *a = n->left;
	Tree *b = n->right->left;
	Tree *c = n->right->right;
	Tree *q = n->right;

	int t = n->value;
	n->value = n->right->value;
	n->right->value = t;

	//swap pointers and set parents
	n->right = c;
	if(c)
		c->parent = n;
	n->left = q;
	if(q)
		q->parent = n;
	n->left->left = a;
	if(a)
		a->parent = n->left;
	n->left->right = b;
	if(b)
		b->parent = n->left;
}
