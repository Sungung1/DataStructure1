#include <iostream>
using namespace std;



struct Node {
	string data;

	Node* next;

};



Node* head = nullptr;

int main()
{
	Node *remove(int index)
	{
		if (index < 0)
			return nullptr;

		if (index == 0)
			return remove_first();

		Node* prev = get_node(index - 1);
		if (prev == nullptr)
			return nullptr;
		else
			return remove_after(prev);
	}

	void ordered_insert(string item)
	{
		Node* p = head;
		Node* q = nullptr;
		while(p!= nullptr && p->data <= item)
		{
			q = p;
			p = p->next;
		}

		if (q == nullptr)
			add_first(item);
		else
			add_after(q, item);
	}
}