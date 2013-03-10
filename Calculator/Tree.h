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
		bool compareWithNode
			(Node&) const;
		Node(Word&);
		bool appDad(Node* dad);//append dad
		bool appSon(Node* dad, Node* son);//append son
		Number getValue();
		Number evaluteNode(Tree&);
		Number assign(Node*,Node*,Tree&);
		void destructNode();
		char* getCharNode();
		~Node();
	};
	Node *root;
	List<Data> var;
public:
	Tree();
	bool operator==(Tree&) const;
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