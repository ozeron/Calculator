#pragma once
#if !defined(TREE_)
#define TREE_

#include "Data.h"
#include "List.h"
struct Node
{
	Data data;
	Node *left, *right, *parent;

	Node(void);
	Node(Word&);
	char* getCharNode();
	~Node();
	Number evaluteNode(List<Data>&);


};

Number assign(Node*,Node*,List<Data>&);
bool appDad(Node* dad);//append dad
bool appSon(Node* dad, Node* son);//append son
bool appSonL(Node* dad, Node* son);

class Tree_
{
public:
	Tree_(void);
	~Tree_(void);
};

#endif // TREE
