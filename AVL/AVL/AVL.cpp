#include<iostream>
#include<queue>
#include "Header.h"
using namespace std;


struct treenode
{
	int key;
	List data;
	int height;
	treenode* left_child;
	treenode* right_child;

	treenode()
	{
		key = 0;
		//data = new List();
		height = -1;
		left_child = NULL;
		right_child = NULL;
	}

	treenode(int k, string d)
	{
		key = k;
		data.append(d);
		height = 0;
		left_child = NULL;
		right_child = NULL;
	}
};

class tree
{
	treenode* root;

	int getheight(treenode* node)
	{
		if (node == NULL)
			return -1;
		return node->height;
	}

	int max(int i1, int i2)
	{
		return (i1 > i2 ? i1 : i2);
	}

	int getbalancefactor(treenode* node)
	{
		if (node == NULL)
			return 0;
		return getheight(node->left_child) - getheight(node->right_child);
	}

	void inorder(treenode* currnode)
	{
		if (currnode != NULL)
		{
			inorder(currnode->left_child);
			cout << currnode->key << "  ";
			currnode->data.display();
			inorder(currnode->right_child);
		}
	}

	treenode* singlerotationwithright_child(treenode* previousroot)
	{
		treenode* newroot = previousroot->left_child;
		treenode* temp = newroot->right_child;

		newroot->right_child = previousroot;
		previousroot->left_child = temp;

		previousroot->height = max(getheight(previousroot->left_child),
			getheight(previousroot->right_child)) + 1;

		newroot->height = max(getheight(newroot->left_child),
			getheight(newroot->right_child)) + 1;

		return newroot;
	}

	treenode* singlerotationwithleft_child(treenode* previousroot)
	{
		treenode* newroot = previousroot->right_child;
		treenode* temp = newroot->left_child;

		newroot->left_child = previousroot;
		previousroot->right_child = temp;

		previousroot->height = max(getheight(previousroot->left_child), getheight(previousroot->right_child)) + 1;

		newroot->height = max(getheight(newroot->left_child), getheight(newroot->right_child)) + 1;

		return newroot;
	}

	treenode* doublerotationright_childleft_child(treenode* previousroot)
	{
		previousroot->right_child = singlerotationwithright_child(previousroot->right_child);
		treenode* newroot = singlerotationwithleft_child(previousroot);

		return newroot;
	}

	treenode* doublerotationleft_childright_child(treenode* previousroot)
	{
		previousroot->left_child = singlerotationwithleft_child(previousroot->left_child);
		treenode* newroot = singlerotationwithright_child(previousroot);

		return newroot;
	}

	treenode* AVLinsertion(int key, string d, treenode* currnode)
	{
		if (currnode == NULL)
		{
			currnode = new treenode(key, d);
			return currnode;
		}
		else if (key < currnode->key)
		{
			currnode->left_child = AVLinsertion(key, d, currnode->left_child);
			if (getbalancefactor(currnode) == 2)
			{
				if (key < currnode->left_child->key)
				{
					currnode = singlerotationwithright_child(currnode); //RR rotation	
				}
				else
				{
					currnode = doublerotationleft_childright_child(currnode); //LR rotation 	
				}
			}
		}
		else if (key > currnode->key)
		{
			currnode->right_child = AVLinsertion(key, d, currnode->right_child);
			if (getbalancefactor(currnode) == -2)
			{
				if (key > currnode->right_child->key)
				{
					currnode = singlerotationwithleft_child(currnode); //LL rotation	
				}
				else
				{
					currnode = doublerotationright_childleft_child(currnode); //RL rotation	
				}
			}
		}
		else if (key == currnode->key)
		{
			if (currnode->data.duplicate(d) == true)
			{
				currnode->data.append(d);
			}
			else if (currnode->data.duplicate(d) == false)
			{
				cout << "Duplicate found in the list. Data is not entered on key "<<key << endl;
			}
			

			//check if data is already prsent, if data is not prsent then append to list
		}
		currnode->height = max(getheight(currnode->left_child), getheight(currnode->right_child)) + 1;

		return currnode;
	}

	treenode* AVLdeletion(int key, string value, treenode* currnode)
	{
		if (currnode == NULL)
		{
			return NULL;
		}

		else if (key < currnode->key)
		{
			currnode->left_child = AVLdeletion(key, value, currnode->left_child);
		}
		else if (key > currnode->key)
		{
			currnode->right_child = AVLdeletion(key, value, currnode->right_child);
		}
		else if (key == currnode->key)
		{
			cout << "here" << endl;
			currnode->data.display();
			currnode->data.removeubaid(value);
			if (currnode->data.isempty())
			{
				if (currnode->left_child == NULL && currnode->right_child == NULL)
				{
					delete currnode;
					currnode = NULL;
				}
				else if (currnode->left_child == NULL)
				{
					treenode* temp = currnode;
					currnode = currnode->right_child;

					delete temp;
				}
				else if (currnode->right_child == NULL)
				{
					treenode* temp = currnode;
					currnode = currnode->left_child;

					delete temp;
				}
				else
				{
					treenode* temp = currnode->right_child;
					while (temp->left_child)
					{
						temp = temp->left_child;
					}

					currnode->key = temp->key;
					cout << "here" << endl;
					currnode->data.display();
					currnode->data = temp->data;

					currnode->right_child = AVLDeletionUsingKey(temp->key, currnode->right_child);
				}
			}
			
		}
		
		if (currnode == NULL)
		{
			return NULL;
		}

		//calculating height after deletion
		currnode->height = max(getheight(currnode->left_child), getheight(currnode->right_child)) + 1;

		//left_child subtree is heavy
		if (getbalancefactor(currnode) == 2)
		{
			//checking if left_child child of left_child subtree exists or not
			if (getbalancefactor(currnode->left_child) >= 0)
			{
				currnode = singlerotationwithright_child(currnode);
			}
			else if (getbalancefactor(currnode->left_child) < 0)
			{
				currnode = doublerotationleft_childright_child(currnode);
			}
		}

		//right_child subtree is heavy
		else if (getbalancefactor(currnode) == -2)
		{
			//checking if right_child child or right_child subtree exists or not
			if (getbalancefactor(currnode->right_child) <= 0)
			{
				currnode = singlerotationwithleft_child(currnode);
			}
			else if (getbalancefactor(currnode->left_child) > 0)
			{
				currnode = doublerotationright_childleft_child(currnode);
			}
		}

		return currnode;
	}
	treenode* AVLDeletionUsingKey(int key, treenode* currnode)
	{
		if (currnode == NULL)
		{
			return NULL;
		}

		else if (key < currnode->key)
		{
			currnode->left_child = AVLDeletionUsingKey(key, currnode->left_child);
		}
		else if (key > currnode->key)
		{
			currnode->right_child = AVLDeletionUsingKey(key, currnode->right_child);
		}
		else if (key == currnode->key)
		{
			treenode* temp = currnode;
			currnode = currnode->left_child;
			temp->data.clear();
			delete temp;
		}

		

		if (currnode == NULL)
		{
			return NULL;
		}

		//calculating height after deletion
		currnode->height = max(getheight(currnode->left_child), getheight(currnode->right_child)) + 1;

		//left_child subtree is heavy
		if (getbalancefactor(currnode) == 2)
		{
			//checking if left_child child of left_child subtree exists or not
			if (getbalancefactor(currnode->left_child) >= 0)
			{
				currnode = singlerotationwithright_child(currnode);
			}
			else if (getbalancefactor(currnode->left_child) < 0)
			{
				currnode = doublerotationleft_childright_child(currnode);
			}
		}

		//right_child subtree is heavy
		else if (getbalancefactor(currnode) == -2)
		{
			//checking if right_child child or right_child subtree exists or not
			if (getbalancefactor(currnode->right_child) <= 0)
			{
				currnode = singlerotationwithleft_child(currnode);
			}
			else if (getbalancefactor(currnode->left_child) > 0)
			{
				currnode = doublerotationright_childleft_child(currnode);
			}
		}

		return currnode;
	}
public:
	tree() :root(NULL) {};

	treenode* getroot()
	{
		return root;
	}
	/*void Split(int key, treenode* currnode, tree& prevMachineTree, tree& nextMachineTree)
	{
		if (currnode == NULL)
		{
			return;
		}
		if (currnode->key <= key)
		{
			prevMachineTree.root = AVLinsertion(currnode->key, currnode->data, prevMachineTree.root);
		}
		if (currnode->key > key)
		{
			nextMachineTree.root = AVLinsertion(currnode->key, currnode->data, nextMachineTree.root);
		}
		Split(key, currnode->left_child, prevMachineTree, nextMachineTree);
		Split(key, currnode->right_child, prevMachineTree, nextMachineTree);
	}

	void Split(int key, tree newMachineTree, tree& prevMachineTree, tree& nextMachineTree)
	{
		Split(key, newMachineTree.root, prevMachineTree, nextMachineTree);
	}
	void NewInsert(treenode* currnode, tree& newMachineTree)
	{
		if (currnode == NULL)
		{
			return;
		}
		else
		{
			newMachineTree.root = AVLinsertion(currnode->key, currnode->data, newMachineTree.root);
			NewInsert(currnode->left_child, newMachineTree);
			NewInsert(currnode->right_child, newMachineTree);
		}
	}

	void Merge(tree& newMachineTree, tree prevMachineTree, tree nextMachineTree)
	{
		newMachineTree = prevMachineTree;
		NewInsert(nextMachineTree.root, newMachineTree);
	}*/
	void displayIO()
	{
		inorder(root);
	}

	void insert(int key, string data)
	{
		root = AVLinsertion(key, data, root);
	}

	void remove(int key, string data)
	{
		root = AVLdeletion(key, data, root);
	}

	void clear()//to delete all elements that are in queue
	{
		if (root != NULL)
		{
			queue<treenode*> Q;
			treenode* currnode = NULL;
			Q.push(root);

			while (!Q.empty())
			{
				currnode = Q.front();
				Q.pop();

				if (currnode->left_child != NULL)
				{
					Q.push(currnode->left_child);
				}
				if (currnode->right_child != NULL)
				{
					Q.push(currnode->right_child);
				}

				delete currnode;
			}

			root = NULL;
		}
	}

	~tree()
	{
		clear();
	}
};

int main()
{
	tree obj;

	obj.insert(2, "zumna");		
	obj.insert(2, "xyz");
	obj.insert(3, "uzair");
	obj.insert(2, "zumna");		//duplicate
	obj.insert(3, "abc");
	obj.insert(3, "uzair");		//duplicate

	obj.displayIO();
	cout << "removing" << endl;
	obj.remove(2, "xyz");
	obj.displayIO();

}