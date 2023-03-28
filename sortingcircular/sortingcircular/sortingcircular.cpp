#include<iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};
class List
{
	Node* head;
public:
	List()
	{
		head = NULL;
	}
	void sortedinsert(int newvalue)
	{
		Node* currnode = head;
		Node* newnode = new Node();
		newnode->data = newvalue;

		if (head == NULL)
		{
			newnode->next = newnode;
			head = newnode;
		}
		else if (currnode->data > newnode->data)
		{
			while (currnode->next != head)
			{
				currnode = currnode->next;
			}
			currnode->next = newnode;
			newnode->next = head;
			head = newnode;
		}
		else if (currnode->data < newnode->data)
		{
			while (currnode->next->data < newvalue && currnode->next != head)
			{
				currnode = currnode->next;
			}
			newnode->next = currnode->next;
			currnode->next = newnode;
		}
		else
		{
			cout << "Duplicate found in the list" << endl;		//collission handled
		}
	}
	void display()
	{
		if (head == NULL)
		{
			return;
		}

		Node* ptr = head;
		do {
			cout << ptr->data << " ";
			ptr = ptr->next;
		} while (ptr != head);
	}
};

int main()
{
	List obj;

	obj.sortedinsert(4);
	obj.sortedinsert(8);
	obj.sortedinsert(2);
	obj.sortedinsert(9);
	obj.sortedinsert(1);

	obj.display();
}