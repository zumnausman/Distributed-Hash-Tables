#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<ctime>
using namespace std;

struct RTNode
{
	int index;
	//MachineNode * machine;
};
class RoutingTable
{
	RTNode* head;
public:
	RoutingTable()
	{
		head = NULL;
	}

};
struct AVLNode
{

};
class AVLTree
{
	AVLNode* root;
public:
	AVLTree()
	{
		root = NULL;
	}
};

struct MachineNode
{
	//RoutingTable rt;
	//AVLtree avl;
	int data;
	MachineNode* next;
};
class MachineList		//singly circular for machine IDs
{
	MachineNode* head;
public:
	MachineList()
	{
		head = NULL;
	}
	void insert(int id)
	{
		if (head != NULL)
		{
			MachineNode* currnode = head;
			while (currnode->next != head)
			{
				currnode = currnode->next;
			}
			currnode->next = new MachineNode();
			currnode->next->data = id;
			currnode->next->next = head;
		}
		else
		{
			head = new MachineNode();
			head->data = id;
			head->next = head;
		}
	}
	void display()
	{
		if (head == NULL)
		{
			return;
		}
		int i = 1;
		MachineNode* ptr = head;
		do {
			cout << endl << "Machine ID " << i << ": " << ptr->data;
			ptr = ptr->next;
			i++;
		} while (ptr != head);
	}
};

int main()
{
	MachineList obj;
	int nummachines, identifiersize, range, ch1;

	cout << "Enter size of identifier space in bits: ";
	cin >> identifiersize;
	while (identifiersize < 0)
	{
		cout << "Enter valid size of identifier space in bits: ";
		cin >> identifiersize;
	}
	range = pow(2, identifiersize) - 1;

	cout << endl << "Your range of identifier space is: 0-" << range << endl << endl;

	cout << "Enter number of machines: ";
	cin >> nummachines;
	while (nummachines < 0 || nummachines > range)
	{
		cout << "Enter valid number of machines: ";
		cin >> nummachines;
	}
	int* mid = new int(nummachines);
	cout << "Do you want to:\n1. Assign machine IDs manually\n2. Assign machine IDs randomly" << endl;
	cin >> ch1;

	if (ch1 == 1)
	{
		cout << endl << "Please remember to enter machine ID in range 0-" << range << endl;
		for (int i = 0; i < nummachines; i++)
		{
			cout << "Enter ID of machine " << i + 1 << ": ";
			cin >> mid[i];
			while (mid[i] < 0 || mid[i] > range)
			{
				cout << "Enter valid ID of machine " << i + 1 << ": ";
				cin >> mid[i];
			}
			obj.insert(mid[i]);
		}
	}
	else if (ch1 == 2)
	{
		cout << "Machine IDs will be generated randomly within the range of 0-" << range;
		srand(time(0));
		for (int i = 0; i < nummachines; i++)
		{
			mid[i] = (rand() % range) + 1;
			//check to make sure ID isnt same of 2 machines
			obj.insert(mid[i]);
		}
	}
	else
	{
		cout << "Invalid Input" << endl;
	}

	obj.display();



}