#include<iostream>
using namespace std;

class Node
{
public:
	string value;
	Node* next;
	Node()
	{
		value = "";
		next = NULL;
	}
	Node(string n)
	{
		value = n;
		next = NULL;
	}
};

class List
{
public:
	Node* head;
	List()
	{
		head = NULL;
	}
	void append(string value)
	{
		if (head)
		{
			Node* currnode = head;
			while (currnode->next != NULL)
			{
				currnode = currnode->next;
			}
			currnode->next = new Node(value);
		}
		else
		{
			head = new Node(value);
		}
	}

	void insertAt(string value, int index)
	{

		int currIndex = 1;
		Node* currnode = head;

		while (currnode->next && index > currIndex)
		{
			currnode = currnode->next;
			currIndex++;
		}


		Node* newnode = new Node();
		newnode->value = value;

		if (index == 0)
		{

			newnode->next = head;
			head = newnode;

		}

		else
		{
			newnode->next = currnode->next;
			currnode->next = newnode;
		}

		//return newNode;
	}

	void remove(string value)
	{
		Node* prevnode = NULL;
		Node* currnode = head;
		int currindex = 1;

		while (currnode && currnode->value != value)
		{
			prevnode = currnode;
			currnode = currnode->next;
			currindex++;
		}
		if (currnode)
		{
			if (prevnode)
			{
				prevnode->next = currnode->next;
				delete currnode;
			}
			else
			{
				head = currnode->next;
				delete currnode;
			}
		}
	}

	void replace(string value, string newvalue)
	{
		Node* currnode = head;
		int currindex = 1;

		while (currnode && currnode->value != value)
		{
			currnode = currnode->next;
			currindex++;
		}

		if (currnode)
		{
			currnode->value = newvalue;
		}


	}

	bool isempty()
	{
		Node* currnode = head;
		bool found = false;
		if (currnode == NULL)
		{
			found = true;
			return found;
		}
	}

	/*Node* split(string value)
	{
		Node* currnode = head;
		while (currnode && currnode->value != value)
		{
			currnode = currnode->next;
		}
		Node* head2 = currnode->next;
		currnode->next = NULL;
		return head2;
	}*/

	void clear()
	{
		Node* currnode = head;
		Node* newnode = NULL;

		while (currnode != NULL)
		{
			newnode = currnode->next;
			delete currnode;
			currnode = newnode;
		}
		head = NULL;
	}

	~List(void)
	{
		cout << endl << "Destructor Called" << endl;
	}

	void display()
	{
		int num = 0;

		Node* currnode = head;
		while (currnode != NULL)
		{
			cout << currnode->value << endl;
			currnode = currnode->next;
			num++;
		}
		cout << endl << "Total number of Nodes are: " << num << endl << endl;
	}
};



int main()
{
	List p;
	bool empty;
	cout << endl << "Append Function" << endl;
	p.append("A");
	p.display();
	cout << endl << "Insert in Middle Function" << endl;
	p.insertAt("B", 2);
	p.display();
	cout << endl << "Remove Function" << endl;
	p.remove("B");
	p.display();
	cout << endl << "Replace Function" << endl;
	p.replace("A", "B");
	p.display();
	cout << endl << "Is empty Function" << endl;
	empty = p.isempty();
	if (empty == true)
	{
		cout << endl << "List is empty" << endl;
	}
	else
	{
		cout << endl << "List is not empty" << endl;
	}
	cout << endl << "Adding new Nodes for split function" << endl;
	p.insertAt("A", 2);
	p.insertAt("C", 3);
	p.insertAt("D", 4);
	p.display();
	cout << endl << "Split Function" << endl;
	List p2;
	//p2.head = p.split("A");
	p2.display();
	p.display();
	cout << endl << "Clear Function" << endl;
	p.clear();
	p.display();
	p.~List();
}