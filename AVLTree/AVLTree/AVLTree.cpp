#include<iostream>
using namespace std;

struct AVLNode
{
	int data;
	AVLNode* left;
	AVLNode* right;
	int heightoftree;
	AVLNode()
	{
		data = 0;
		heightoftree = -1;
		left = NULL;
		right = NULL;
	}
	AVLNode(int d)
	{
		data = d;
		heightoftree = 0;
		left = NULL;
		right = NULL;
	}

};
class AVLTree
{
	AVLNode* root;
public:
	AVLTree()
	{
		root = NULL;
	}
	AVLNode* leftrotation(AVLNode* n)
	{
		AVLNode* n2 = n->right;		//new root
		AVLNode* temp = n2->left;		//left tree of new root that has to be placed in left subtree
		n2->left = n;				//prev root will become left of newroot
		n->right = temp;			//left of newroot will become right of prev root
		return n2;					//new root returned
	}
	AVLNode* rightrotation(AVLNode* n)
	{
		AVLNode* n2 = n->left;		//new root
		AVLNode* temp = n2->right;		//left tree of new root that has to be placed in left subtree
		n2->right = n;				//prev root will become left of newroot
		n->left = temp;			//left of newroot will become right of prev root
		return n2;
	}
	AVLNode* rightleft(AVLNode* n)
	{
		AVLNode* p;
		AVLNode* tp;
		AVLNode* tp2;
		p = n;
		tp = p->right;
		tp2 = p->right->left;

		p->right = tp2->left;
		tp->left = tp2->right;
		tp2->left = p;
		tp2->right = tp;

		return tp2;
	}
	AVLNode* leftright(AVLNode* n)
	{
		AVLNode* p;
		AVLNode* tp;
		AVLNode* tp2;
		p = n;
		tp = p->left;
		tp2 = p->left->right;

		p->left = tp2->right;
		tp->right = tp2->left;
		tp2->right = p;
		tp2->left = tp;

		return tp2;
	}
	int height(AVLNode* AVLNodeptr)
	{
		if (AVLNodeptr == NULL)
		{
			return -1;		//because height of leaf AVLNode is -1
		}
		else
		{
			int lh = height(AVLNodeptr->left);
			int rh = height(AVLNodeptr->right);

			if (lh > rh)	//compares height of both subtrees and returns greater height
			{
				return lh + 1;
			}
			else
			{
				return rh + 1;
			}
		}
	}
	int height()
	{
		return height(root);
	}
	AVLNode* insert(int value, AVLNode* n)
	{
		if (n == NULL)
		{
			n = new AVLNode();
			n->data = value;
			n->left = n->right = NULL;
		}
		else if (value < n->data)
		{
			n->left = insert(value, n->left);
			if (height(n->left) - height(n->right) == -2)
			{
				if (value < n->left->data)
				{
					n = leftrotation(n);
				}
				else
				{
					n = rightleft(n);
				}
			}
		}
		else if (value > n->data)
		{
			n->right = insert(value, n->right);
			if (height(n->right) - height(n->left) == -2)
			{
				if (value < n->right->data)
				{
					n = rightrotation(n);
				}
				else
				{
					n = leftright(n);
				}
			}
		}
		n->heightoftree = max(height(n->left), height(n->right)) + 1;
		return n;

	}
	void insert(int value)
	{
		root = insert(value, root);
	}
	int max(int a, int b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
	void displayInOrder()
	{
		displayInOrder(root);
	}
	void displayInOrder(AVLNode* n)
	{
		if (n != NULL)
		{
			displayInOrder(n->left);
			cout << n->data << endl;
			displayInOrder(n->right);
		}
	}

};

int main()
{
	AVLTree obj;
	obj.insert(1);
	obj.insert(2);
	obj.insert(3);
	obj.insert(4);
	obj.insert(5);
	obj.insert(6);
	obj.insert(7);
	//obj.insert(2);

	int height = obj.height();

	cout << endl << endl << "Height of tree: " << height << endl << endl;

	obj.displayInOrder();

}