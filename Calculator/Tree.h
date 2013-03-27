#pragma once


#include "Data.h"
#include "List.h"

#if !defined(TREE)
#define TREE

class Tree
{
public:	struct Node{
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
			bool appSonL(Node* dad, Node* son);
			Number getValue();
			Number evaluteNode(List<Data>&);
			Number assign(Node*,Node*,List<Data>&);
			char* getCharNode();
			~Node();
		};
public:
	Tree();
	bool operator==(Tree&) const;
	~Tree();
	void removeNode(Node*);

	bool addNode(Node*);
	bool addNode(Node* &,Node*);//For sub trees, 
	//were subRoot!=root
	Number EvaluteTree(List<Data>&);
	bool buildTree(List<Word> &);
	bool AltBuild(List<Word>::Node*);
	Node* buildSubTree_(List<Word>::Node* &);
	Node* backToPeviousSubTreeLvl(Node*&dad,List<Word>::Node* &);
	Node* buildSubTree(List<Word>::Node* &);
	char* getTreeCharArr();
	
private:
	Node *root;
};

#endif // TREE