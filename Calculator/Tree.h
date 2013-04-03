#pragma once


#include "Data.h"
#include "List.h"

#if !defined(TREE)
#define TREE

struct Node{
	Data data;
	//Word::cast type;
	Node *left, *right,*parent;
	Node(void);
	Node(Word&);
	~Node();
	bool compareWithNode(Node&) const;
	bool appDad(Node* dad);//append dad
	Number getValue();
	Number evaluteNode(List<Data>&);
	void cutNode();
	void removeNods();
	bool ifHasAssign();
	char* getCharNode();
};
bool appSon(Node* dad, Node* son);//append son
bool appSonL(Node* dad, Node* son);
Node *assign_(Node*,Node*,List<Data>&);
class Tree
{
public:
	Tree();
	bool operator==(Tree&) const;
	bool clearTree(void);
	~Tree();
	void removeNode(Node*);

	bool addNode(Node*);
	bool addNode(Node* &,Node*);//For sub trees, 
															//were subRoot!=root
	Number EvaluteTree(List<Data>&);
	bool AltBuild(List<Word>::Node*);
	Node* buildSubTree_(List<Word>::Node* &);
	Node* backToPeviousSubTreeLvl(Node*&dad,List<Word>::Node* &);

	char* getTreeCharArr();
public:
	Node *root;

};

#endif // TREE