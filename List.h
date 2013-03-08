#pragma once

#include <cstdlib>
#if !defined(LIST)
#define LIST


template <class T>
class List
{
public:
	struct Node
	{
		T data;
		Node  *next, *prev;
		Node(T,T);
		Node():data(),next(nullptr),prev(nullptr){}
		Node(T &smth):data(smth),next(nullptr),prev(nullptr){}
		~Node(){
			data.~T();
			next = nullptr;
			prev = nullptr;
		}

	};

	Node *head;
	Node *tail;
public:
	List()
	{
		head = nullptr;
		tail = nullptr;
	}
	~List()
	{
		if (head == nullptr && tail == nullptr)
			return;
		Node*n;
		while (head != nullptr)
		{
			n = head->prev;
			delete head;
			head = n;
		}
		head = nullptr;
		tail = nullptr;
	}
	void add(T &d)
	{
		Node *n = new Node(d);
		n->prev = head;
		n->next = nullptr;
		if (head!=nullptr)
			head->next = n;
		if(head == nullptr){
			head = n;
			tail = head;
		} else 
			head = n;
	}
	void insertAfter(int id, T &d)
	{
		Node* node = this->search(at(id));
		if (node == nullptr)
			return;
		if (node == this->head){
			add(d);
			return;
		}
		Node *n = new Node(d);
		n->prev = node;
		n->next = node->next;

		node->next->prev = n;
		node->next = n;
	}
	void insertAfter(Node *node, T &d)
	{
		if (node == nullptr)
			return;
		if (node == this->head){
			add(d);
			return;
		}
		Node *n = new Node(d);
		n->prev = node;
		n->next = node->next;

		node->next->prev = n;
		node->next = n;
	}
	Node* search(T goal)
	{
		Node* current = this->tail;
		while (current != nullptr){
			if (current->data == goal)
				break;
			current = current->next;
		}
		return current;
	}
	T at(int id)
	{
		int i = 0;
		Node* current = tail;
		for(;i<id;i++)
			current = current->next;
		return current->data;
	}
	int getPosition(Node *goal)
	{
		int i = 0;
		Node* current = tail;
		while (goal != current) {
			i++;
			current = current->next;
		}
		return i;
	}
	int getSize()
	{
		if (this->tail == nullptr)
			return 0;

		int i = 1;
		Node *current;
		current = tail;
		while (current != head)
		{
			current = current->next;
			i++;
		}
		return i;
	}
	void del(Node *node)
	{	
		if (head == node)
			head = node->prev;
		if (tail == node)
			tail = node->next;
		if (node->next != nullptr)
			node->next->prev = node->prev;
		if (node->prev != nullptr)
			node->prev->next = node->next;
		delete node;
	}
};


#endif // LIST