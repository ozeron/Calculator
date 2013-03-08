#pragma once


#include "Data.h"
#include "List.h"

#if !defined(TREE)
#define TREE

class Tree
{
public:
	struct Node{
		Data data;
		//Word::cast type;
		Node *parent;
		Node *left, *right;

		Node():parent(nullptr),left(nullptr),right(nullptr)
		{};
		Node(Word);
		bool appDad(Node* dad);//append dad
		bool appSon(Node* dad, Node* son);//append son
		Number getValue();
		Number evaluteNode();
		void destructNode();
		char* getCharNode();
		~Node();
	};
	Node *root;
	List<Data> var;
public:
	Tree();
	~Tree();

	bool addNode(Node*);
	bool addNode(Node* &,Node*);//For sub trees, 
							  //were subRoot!=root
	Number EvaluteTree();
	bool buildTree(List<Word> &);
	Node* buildSubTree(List<Word>::Node* &);

	char* getTreeCharArr();
};

#endif // TREE