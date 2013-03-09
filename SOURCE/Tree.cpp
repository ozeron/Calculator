#include "Tree.h"

bool Tree::Node::compareWithNode(Node& right) const
{
	bool eqLeft,eqRight,eqData;

	if (this->left!=nullptr && right.left!=nullptr)
		eqLeft = this->left->compareWithNode(*right.left);
	else if (this->left==nullptr && right.left==nullptr)
		eqLeft = true;
	else 
		eqLeft = false;

	if (this->right!=nullptr && right.right!=nullptr)
		eqRight = this->right->compareWithNode(*right.right);
	else if (this->right==nullptr && right.right==nullptr)
		eqRight = true;
	else 
		eqRight = false;

	eqData = this->data == right.data;
	return (eqLeft && eqRight && eqData);
}
Tree::Node::Node( Word &input)
{
	data = input;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
Tree::Node::~Node()
{
	if (this->left!=nullptr)
		delete left;
	left = nullptr;
	if (this->right!=nullptr)
		delete right;
	right = nullptr;
	data.~Data();
}

bool Tree::Node::appDad(Node* dad)
{
	if (this == nullptr) {
		return false;
	}
	this->parent = dad;
	dad->left = this;
	return true;
}
bool Tree::Node::appSon(Node *dad, Node* son)
{
	Node* temp;
	if (dad->left == nullptr) {
		son->parent = dad;
		dad->left = son;
		return true;
	}
	if (dad->right == nullptr) {
		son->parent = dad;
		dad->right = son;
		return true;
	}																//   Implemet this:    + <- 7"28"
	if (dad->right->data.getPriority() < son->data.getPriority()) { //					 3	  *"16" 
		this->appSon(dad->right,son);								//
	} else if (dad->right->data.getPriority() > son->data.getPriority()) {
		temp = dad->right;											//   Implement this:   + <- *"16"
		dad->right = son;											//					 3    7"28"
		son->parent = dad;											//
		this->appSon(dad->right,temp);
	} else {
		if (dad->right->data.getPriority() < 19 ) {
			temp = dad->right;   // Changing places dad->right and son, 
			dad->right = son;    // then assinging son->right value of dad->right
			son->parent = dad;   //
			this->appSon(dad->right,temp);
		} else {
			this->appSon(dad->right,son);
		}
	}
	return true;
}
Number Tree::Node::getValue()
{
	return this->data.getValue();
}
Number Tree::Node::evaluteNode(Tree& dad)
{
	if (this->data.type == Word::cast::number)
		return this->getValue();
	if (this->data.type == Word::cast::variable){

		//TODO: Find by name, not by value!
		List<Data>::Node* mem = dad.var.search(this->data);
		if (mem!=nullptr &&mem->data.doesDataInited)
			return mem->data.getValue();
		else if (mem!=nullptr &&mem->data.doesTreeInited)
			return mem->data.tree->EvaluteTree();
		else{
			this->data.doesDataInited=false;
			this->data.doesTreeInited=false;
			dad.var.add(this->data);
			Number res(0,1);
			res.decimalSystem = -1;
			return res;
		}
	}
	if (this->data.type == Word::cast::delimiter){
		//Special construction for "="
		bool isAssign = strncmp(this->data.name,"=",1);
		if (!isAssign)
			return this->assign(this->right,this->left,dad);
		Number a,b;

		if(this->left!=nullptr)
			a = this->left->evaluteNode(dad);
		else
			a.decimalSystem=-1;

		if(this->right!=nullptr)
			b = this->right->evaluteNode(dad);
		else
			b.decimalSystem=-1;
		return this->data.evalute(a,b);
	}
	return Number(0,0);
}
void Tree::Node::destructNode()
{
	//Implementthis
}
char* Tree::Node::getCharNode()
{
	char *array=nullptr, *a=nullptr, *b = nullptr;
	int length = 0;
	if (this->left != nullptr)
		a = this->left->getCharNode();
	if (this->right!= nullptr)
		b = this->right->getCharNode();

	if (a!=nullptr)
		length += strlen(a);
	if (b!=nullptr)
		length += strlen(b);
	length += strlen(this->data.name);
	if (a!=nullptr || b!=nullptr)
	{
		array = new char [length+3];// 2 = (), and 1 = '\0'
		strcpy(array,"");
		if (this->data.getPriority() > 11)
			strcat(array,"(");
		if (a!=nullptr)
			strcat(array,a);
		strcat(array,data.name);
		if (b!=nullptr)
			strcat(array,b);
		if (this->data.getPriority() > 11)
			strcat(array,")");
	} else {
		array = new char [length+1];
		strcpy(array,this->data.name);
	}
	return array;
}
Tree::Tree(void)
{
	root = nullptr;
}
Tree::~Tree(void)
{
	delete root;
}
bool Tree::addNode(Node* node){
	bool result;
	if (root == nullptr){
		root = node;
		return true;
	}
	if (root->data.getPriority() > node->data.getPriority()){
		result = root->appDad(node);
		root=node;
	} else if (root->data.getPriority() < node->data.getPriority()){
		result = root->appSon(root,node);
	} else {
		if (root->data.getPriority() < 19){
			result = root->appDad(node);
			root=node;
		} else
			result = root->appSon(root,node);
	}
	return result;
}
bool Tree::addNode(Tree::Node* &dad, Tree::Node*node)
{
	bool result;
	if (dad == nullptr){
		dad = node;
		return true;
	}
	if (dad->data.getPriority() > node->data.getPriority()){
		result = dad->appDad(node);
		dad=node;
	} else if (dad->data.getPriority() < node->data.getPriority()){
		result = dad->appSon(dad,node);
	} else {
		if (dad->data.getPriority() < 19){
			result = dad->appDad(node);
			dad=node;
		} else
			result = dad->appSon(dad,node);
	}
	return result;
}

Number Tree::EvaluteTree()
{ return this->root->evaluteNode(*this);}
Number Tree::Node::assign(Node*l,Node* r,Tree& tree)
{//TODO: IMplement this!!!
	Number result;
	if (l->data.type == Word::cast::number && r->data.type == Word::cast::number){
		result.setValue(0,1);
		result.ifBool = true;
		return result;
	}
	if (l->data.type == Word::cast::number && r->data.type == Word::cast::delimiter){
		result.setValue(0,1);
		result.ifBool = true;
		return result;
	}
	if (l->data.type == Word::cast::number && r->data.type == Word::cast::variable){
		List<Data>::Node* mem = tree.var.search(r->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=l->data.storedData;
			return l->data.getValue();
		}else if (mem!=nullptr){
			mem->data.storedData=l->data.storedData;
			mem->data.doesDataInited=true;
			return l->data.getValue();
		} else {
			tree.var.add(r->data);
			tree.var.head->data.storedData=l->data.storedData;
			tree.var.head->data.doesDataInited=true;
			tree.var.head->data.doesTreeInited=false;
			return l->data.getValue();
		}
	}
	if (l->data.type == Word::cast::delimiter && r->data.type == Word::cast::number){
		result.setValue(0,1);
		result.ifBool = true;
		return result;
	}
	if (l->data.type == Word::cast::delimiter && r->data.type == Word::cast::delimiter){
		result.setValue(0,1);
		result.ifBool = true;
		return result;
	}
	if (l->data.type == Word::cast::delimiter && r->data.type == Word::cast::variable){
		List<Data>::Node* mem = tree.var.search(r->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=l->evaluteNode(tree);
			return tree.var.head->data.storedData;
		}else if (mem!=nullptr){
			mem->data.storedData=l->evaluteNode(tree);
			mem->data.doesDataInited=true;
			return tree.var.head->data.storedData;
		} else {
			tree.var.add(l->data);
			tree.var.head->data.storedData=l->evaluteNode(tree);;
			tree.var.head->data.doesDataInited=true;
			tree.var.head->data.doesTreeInited=false;
			return tree.var.head->data.storedData;
		}
	}
	if (l->data.type == Word::cast::variable && r->data.type == Word::cast::number){
		List<Data>::Node* mem = tree.var.search(l->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=r->data.storedData;
			return r->data.getValue();
		}else if (mem!=nullptr){
			mem->data.storedData=r->data.storedData;
			mem->data.doesDataInited=true;
			return r->data.getValue();
		} else {
			tree.var.add(r->data);
			tree.var.head->data.storedData=r->data.storedData;
			tree.var.head->data.doesDataInited=true;
			tree.var.head->data.doesTreeInited=false;
			return r->data.getValue();
		}
	}
	if (l->data.type == Word::cast::variable && r->data.type == Word::cast::delimiter){
		List<Data>::Node* mem = tree.var.search(l->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=r->evaluteNode(tree);
			return tree.var.head->data.storedData;
		}else if (mem!=nullptr){
			mem->data.storedData=r->evaluteNode(tree);
			mem->data.doesDataInited=true;
			return tree.var.head->data.storedData;
		} else {
			tree.var.add(r->data);
			tree.var.head->data.storedData=r->evaluteNode(tree);;
			tree.var.head->data.doesDataInited=true;
			tree.var.head->data.doesTreeInited=false;
			return tree.var.head->data.storedData;
		}
		if (l->data.type == Word::cast::variable && r->data.type == Word::cast::variable){
			List<Data>::Node* mem1 = tree.var.search(r->data);
			List<Data>::Node* mem2 = tree.var.search(r->data);
			if (mem1==mem2 && mem1 == nullptr){
				tree.var.add(l->data);
				tree.var.head->data.storedData.setValue(0,1);
				tree.var.head->data.doesDataInited=true;
				tree.var.head->data.doesTreeInited=false;
				tree.var.add(r->data);
				tree.var.head->data.storedData.setValue(0,1);
				tree.var.head->data.doesDataInited=true;
				tree.var.head->data.doesTreeInited=false;
			} else if (mem1 == mem2)
				if (mem1->data.doesDataInited == true)
					return mem1->data.storedData;
				else
					return mem2->data.tree->EvaluteTree();
			else if (mem1 == nullptr){
				tree.var.add(l->data);
				if (mem2->data.doesDataInited){
					tree.var.head->data.doesDataInited=true;
					tree.var.head->data.storedData = mem2->data.storedData;
				} else {
					tree.var.head->data.doesDataInited=true;
					tree.var.head->data.storedData = mem2->data.tree->EvaluteTree();
				}
			} else if (mem2 == nullptr)
			{
				tree.var.add(r->data);
				if (mem1->data.doesDataInited){
					tree.var.head->data.doesDataInited=true;
					tree.var.head->data.storedData = mem1->data.storedData;
				} else {
					tree.var.head->data.doesDataInited=true;
					tree.var.head->data.storedData = mem1->data.tree->EvaluteTree();
				}
			} else {
				if (mem2->data.doesDataInited){
					tree.var.head->data.doesDataInited=true;
					tree.var.head->data.storedData = mem2->data.storedData;
				} else {
					tree.var.head->data.doesDataInited=true;
					tree.var.head->data.storedData = mem2->data.tree->EvaluteTree();
				}
			}
	}
		

		
	return result;
}


bool Tree::buildTree(List<Word> &input)
{
	if (input.tail == nullptr)
		return false;
	List<Word>::Node* currentWord;
	currentWord = input.tail;
	Node* nextNode=nullptr, *subTreeRoot=nullptr;
	bool result = false;
	while(currentWord!=nullptr)
	{
		nextNode = new Node(currentWord->data);
		if (nextNode->data.priority == -1)
		{
			currentWord= currentWord->next;
			subTreeRoot = buildSubTree(currentWord);
			nextNode = subTreeRoot;
		}
		result = addNode(nextNode);
		if (result == false)
			break;
		if (currentWord == nullptr)
			continue;
		currentWord = currentWord->next;
	}
	return true;
}
Tree::Node* Tree::buildSubTree(List<Word>::Node* &currentWord)
{
	Tree::Node *subTreeRoot=nullptr, *mainRoot=nullptr;
	Node* nextNode;
	nextNode = new Node(currentWord->data);
	if (nextNode->data.priority == 2 || nextNode->data.priority == 1 && currentWord->prev!=nullptr){
		currentWord = currentWord->prev;
		return mainRoot;
	}
	do
	{		 
		if (nextNode->data.priority == -1)
		{
			currentWord= currentWord->next;
			subTreeRoot = buildSubTree(currentWord);
			nextNode = subTreeRoot;
		}
		addNode(mainRoot,nextNode);

		currentWord = currentWord->next;
		if (currentWord == nullptr)
			break;
		nextNode = new Node(currentWord->data);
	} while(nextNode->data.priority != -2 && nextNode->data.priority != 2 && nextNode->data.priority != 1);// -2 == ')'  1 == '=' 2 == ']=' || '=['
	if (nextNode->data.priority == 2 || nextNode->data.priority == 1 && currentWord->prev!=nullptr)
		currentWord = currentWord->prev;
	mainRoot->data.priority += 50;
	return mainRoot;
}

char* Tree::getTreeCharArr()
{
	char* outPut;
	if (this->root == nullptr)
		return "<EMPTY>";
	outPut = this->root->getCharNode();
	return outPut;
}

bool Tree::operator==( Tree& right) const
{
	bool result = this->root->compareWithNode(*right.root);
	return result;
}



