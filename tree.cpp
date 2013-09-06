#include "stdafx.h"
#include "tree.h"

//constructors
Tree::Tree() : left(0), right(0), parent(0), red(false), value(0)
{
}

Tree::Tree(int val) : left(0), right(0), parent(0), value(val), red(false)
{
}

//destructor
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
	//massive function of mostly dealing with cases
	//find value first
	if(val < value)
	{
		//go left
		if(left)
			left->erase(val);
		return;
	}
	else if(val > value)
	{
		//go right
		if(right)
			right->erase(val);
		return;
	}
	else if(val == value)
	{

		//found it so do actual deletion stuff
		if(parent)
		{
			//if no children
			
			if(!left && !right)
			{
				if(red)
				{
					//this is a recently added node so removal is easy
					if(this == parent->left)
						parent->left = 0;
					else
						parent->right = 0;
					delete this;
					return;
				}
			}
			//if we have children this is a bit more problematic
			//swap with a childless node
			else if(!left)
			{
				//if has a right child
				//we check if the right has children
				if(!(right->right) && !(right->left))
				{
					//no children so we can just swap with the right child
					int t = right->value;
					right->value = value;
					value = t;
					right->erase(val);
				}
				else if(!(right->right))
				{
					//has a left child
					//so we recusively find the leaf node
					Tree *leaf_node = right->left->get_left();
					//swap with that and call erase
					int t = leaf_node->value;
					leaf_node->value = value;
					value = t;
					leaf_node->erase(val);
				}
				else if(!(right->left))
				{
					//has a right child but no left
					//swap with the right->right child since that is a leaf node
					int t = right->right->value;
					right->right->value = value;
					value = t;
					right->right->erase(val);
				}
				else
				{
					//right has two children
					Tree *leaf_node = right->left->get_left();
					//swap with that and call erase
					int t = leaf_node->value;
					leaf_node->value = value;
					value = t;
					leaf_node->erase(val);
				}
				return;
			}
			else if(!right)
			{
				//has a left child
				//do the same things with right but flipped
				if(!(left->right) && !(left->left))
				{
					//no left family
					int t = left->value;
					left->value = value;
					value = t;
					left->erase(val);
				}
				else if(!(left->left))
				{
					//left has a right so we find the leaf node
					Tree *leaf_node = left->right->get_right();
					int t = leaf_node->value;
					leaf_node->value = value;
					value = t;
					leaf_node->erase(val);
				}
				else if(!(left->right))
				{
					//has a left left
					//so swap with that
					int t = left->left->value;
					left->left->value = value;
					value = t;
					left->left->erase(val);
				}
				else
				{
					//left has two children
					Tree *leaf_node = left->right->get_right();
					int t = leaf_node->value;
					leaf_node->value = value;
					value = t;
					leaf_node->erase(val);
				}
				return;
			}
			else
			{
				//has two children
				//swap with a leaf node
				if(right->left)
				{
					Tree *leaf_node = right->left->get_left();
					//swap with that and call erase
					int t = leaf_node->value;
					leaf_node->value = value;
					value = t;
					leaf_node->erase(val);
				}
				else if(left->right)
				{
					Tree *leaf_node = left->right->get_right();
					int t = leaf_node->value;
					leaf_node->value = value;
					value = t;
					leaf_node->erase(val);
				}
				else if (right->right)
				{
					//if right has a right we swap 
					int t = right->right->value;
					right->right->value = value;
					value = t;
					right->right->erase(val);
				}
				else if (left->left)
				{
					int t = left->left->value;
					left->left->value = value;
					value = t;
					left->left->erase(val);
				}
				else
				{
					//children has no children so swapping with either is fine
					int t = left->value;
					left->value = value;
					value = t;
					left->erase(val);
				}
				return;
			}
			delete_case1();
			if(this == parent->right)
			{
				parent->right = 0;
				delete this;
			}
			else
			{
				parent->left = 0;
				delete this;
			}
		}
		else
		{
			//this is the root
			clear();
			delete this;
		}
	}
	//rebalance();
	return;
}


void Tree::clear()
{
	//delete everything in here
	if(left)
		delete left;
	if(right)
		delete right;
}

//private functions
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
				//make sure to change colors before we change pointers or we could jsut save the pointers
				red = false;
				parent->red = true;
				left->red = false;
				//right-left
				rotate_right(this);
				rotate_left(parent);

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
				red = false;
				right->red = false;
				parent->red = true;
				//right-right imbalance
				rotate_left(parent);
				//and change the colors

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

//private function
void Tree::delete_case1()
{
	//make sure we have a parent or else we would go into an infinite loop
	if(parent)
		delete_case2();
}

//private function
void Tree::delete_case2()
{
	//so if our sibling is red we know the parent is black
	//then we can flip the colors and do a rotation to maintain 
	//equal number of black nodes
	if(sibling()->red)
	{
		//create black node as the grandparent
		//which is the former sibling
		parent->red = true;
		sibling()->red = false;
		if(this == parent->left)
			rotate_left(parent);
		else
			rotate_right(parent);
	}
	//if its a black node we ignore keeping the invarient and go onto 
	//the next case
	delete_case3();
}

void Tree::delete_case3()
{
	if(!(parent->red) && !(sibling()->red))
	{
		//so assuming that we didn't go through the previous case
		//and have black parent and black sibling
		//we have to fix the fact that we will be removing 
		//a black node from a path
		//so we turn sibling red and repeat everything on the parent
		sibling()->red = true;
		parent->delete_case1();
	}
	else
		//if we went through delete_case2 rotations go straigth through
		delete_case4();
}

void Tree::delete_case4()
{
	//if parent is red and siblings family is black
	//we add another black to current nodes path by making parent red
	//and removing a black from siblings path
	if(parent->red && !(sibling()->red) &&
		!(sibling()->left->red) && !(sibling()->right->red))
	{
		sibling()->red = true;
		parent->red = false;
		return;
	}
	else
		delete_case5();

}

void Tree::delete_case5()
{
	//if sibling is black
	if(!(sibling()->red))
	{
		//if siblings family has a single red, we have to make sure that the opposite
		//child of the sibling is red which case 6 solvse
		if(this == parent->left && !sibling()->right->red && sibling()->left->red)
		{
			sibling()->red = true;
			sibling()->left->red = false;
			rotate_right(sibling());
		}
		else if(this == parent->right && 
			!sibling()->left->red && sibling()->right->red)
		{
			sibling()->red = true;
			sibling()->right->red = false;
			rotate_left(sibling());
		}
	}
	delete_case6();
}

void Tree::delete_case6()
{
	//we make the sibling have the same color as the parent
	//then we make the parent black and rotate
	sibling()->red = parent->red;
	parent->red = false;
	if(this == parent->left)
	{
		sibling()->right->red = false;
		rotate_left(parent);
	}
	else if (this == parent->right)
	{
		if(sibling()->left)
			sibling()->left->red = false;
		rotate_right(parent);
	}

}

Tree* Tree::get_left()
{
	if(left)
		left->get_left();
	else
		return this;
}

Tree* Tree::get_right()
{
	if(right)
		right->get_right();
	else
		return this;
}

//private function
//helper function designed to find sibling nodes
Tree* Tree::sibling()
{
	if(parent)
	{
		if(this == parent->left)
		{
			return parent->right;
		}
		else
		{
			return parent->left;
		}
	}
	else
		return 0;
}
