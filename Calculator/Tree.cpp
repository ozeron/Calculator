#include "Tree.h"

Node::Node (void):data()
{
	left=nullptr;
	right=nullptr;
	parent = nullptr;

}
bool Node::compareWithNode(Node& right) const
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
Node::Node( Word &input)
{
	data = input;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
Node::~Node()
{
	if (this == 0)
		return;
}

bool Node::appDad(Node* dad)
{
	if (this == nullptr) {
		return false;
	}
	this->parent = dad;
	dad->left = this;
	return true;
}
bool appSon(Node *dad, Node* son)
{
	Node* temp;

	if (dad->right == nullptr) {
		son->parent = dad;
		dad->right = son;
		return true;
	}																//   Implemet this:    + <- 7"28"
	if (dad->right->data.getPriority() < son->data.getPriority()) { //					 3	  *"16" 
		appSon(dad->right,son);								//
	} else if (dad->right->data.getPriority() > son->data.getPriority()) {
		temp = dad->right;											//   Implement this:   + <- *"16"
		dad->right = son;											//					 3    7"28"
		son->parent = dad;											//
		appSonL(dad->right,temp);
	} else {
		if (dad->right->data.getPriority() < 19 && dad->right->data.getPriority() > 13) {
			temp = dad->right;   // Changing places dad->right and son, 
			dad->right = son;    // then assinging son->right value of dad->right
			son->parent = dad;   //
			appSon(dad->right,temp);
		} else {
			appSon(dad->right,son);
		}
	}
	return true;
}
Number Node::getValue()
{
	return this->data.getValue();
}
Number Node::evaluteNode(List<Data> &var)
{
	Number ret(0,0);
	ret.decimalSystem = -1;
	ret.ifInited = false;
	ret.ifINF = false;

	static int recursiveDepth = 0;
	if (recursiveDepth == 25){
		ret.decimalSystem = -1;
		return ret;
	}
	if (this==nullptr){
		ret.decimalSystem = 0;
		return ret;
	}
	if (this->data.type == Word::cast::number)
		return this->getValue();
	if (this->data.type == Word::cast::variable){

		//TODO: Find by name, not by value!
		List<Data>::Node* mem = var.search(this->data);
		if (mem!=nullptr){
			recursiveDepth++;
			Number ret;
			if (mem->data.tree == nullptr) {
				ret.setValue(0,1);
				ret.decimalSystem = 10;
				ret.ifInited = true;
				ret.ifNumber = true;
			} else
				 ret = mem->data.tree->evaluteNode(var);
			recursiveDepth--;	
			return ret;
		}else{
			Number res(0,1);
			res.decimalSystem = -2;
			return res;
		}
	}
	if (this->data.type == Word::cast::delimiter){

		//Special construction for "="
		bool isAssign = !strncmp(this->data.name,"=",1);
		if (!strncmp(this->data.name,"==",2))
			isAssign = false;
		if (!strncmp(this->data.name,"]=",2))
			isAssign = true;
		if (!strncmp(this->data.name,"=[",2))
			isAssign = true;
		if (isAssign){
			recursiveDepth++;
			Node* ret = assign_(this->left,this->right,var);
			Number result = ret->evaluteNode(var);
			recursiveDepth--;
			return result;
		}
		Number a,b;

		if(this->left!=nullptr){
			recursiveDepth++;
			a = this->left->evaluteNode(var);
			recursiveDepth--;
		}else
			a.decimalSystem=-1;

		if(this->right!=nullptr){
			recursiveDepth++;
			b = this->right->evaluteNode(var);
			recursiveDepth--;
		} else
			b.decimalSystem=-1;
		recursiveDepth++;
		Number ret = this->data.evalute(a,b);
		recursiveDepth--;
		return ret;
	}
	return ret;
}

char* Node::getCharNode()
{
	if (this==0)
		return "";
	(Node *)0xfeeefeee;
	//if (this == (Node *)0xfeeefeee;)
		//return "";
	char *array, *a=nullptr, *b = nullptr;
	array = new char[1024];
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
		{;// 2 = (), and 1 = '\0'
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
}
void Tree::removeNode( Node* node)
{

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
		result = appSon(root,node);
	} else {
		if (root->data.getPriority()%50<19 && root->data.getPriority()%50>13){
			result = root->appDad(node);
			root=node;
		} else
			result = appSon(root,node);
	}
	return result;
}
bool Tree::addNode(Node* &dad, Node*node)
{
	bool result;
	if (dad == nullptr){
		dad = node;
		return true;
	}
	if (node == nullptr){
		return true;
	}
	if (dad->data.getPriority() > node->data.getPriority()){
		result = dad->appDad(node);
		dad=node;
	} else if (dad->data.getPriority() < node->data.getPriority()){
		result = appSon(dad,node);
	} else {
		if (dad->data.getPriority() < 21 && dad->data.getPriority()>13){
			result = dad->appDad(node);
			dad=node;
		} else
			result = appSon(dad,node);
	}
	return result;
}

Number Tree::EvaluteTree(List<Data>& mem)
{ 
	Number result = this->root->evaluteNode(mem);
	if (static_cast<double>(result.nomerator)/result.denomerator >= INT64_MAX-10)
		result.ifINF = true;
	if (static_cast<double>(result.nomerator)/result.denomerator <=-(INT64_MAX-10))
		result.ifINF = true;
	return result;
}


bool appSonL( Node* dad, Node* son )
{
	if (dad->left == nullptr) {
		dad->left = son;
		son->parent = dad;
		return true;
	} else
		return appSon(dad,son);
}

Node * assign_( Node*l,Node*r,List<Data>& var)
{
	Node* result;
	if (l == nullptr || r==nullptr){
		result = (r==nullptr)? l : r;
		if (result == nullptr) {
			result = new Node;
			strcpy(result->data.name,"undef");
			result->data.doesDataInited = true;
			result->data.storedData.setValue(0,0);
			result->data.priority = 30;
			result->data.storedData.decimalSystem = -1;
			return result;
		} else 
			return result;
	}
	if (l->data.type != Word::variable && r->data.type != Word::variable)
	{
		result = new Node;
		strcpy(result->data.name,"undef");
		result->data.doesDataInited = true;
		result->data.storedData.setValue(0,0);
		result->data.storedData.ifBool = true;
		result->data.priority = 30;
		result->data.storedData.decimalSystem = -1;
		return result;
	}
	if				(l->data.type == Word::number    || r->data.type == Word::number)
	{
		if (l->data.type == Word::number){
			Node* temp = l; l = r; r = temp;
		}
		List<Data>::Node* mem  = var.search(l->data);
		if (mem!=nullptr){
			result = r;
			if (r->ifHasAssign())
				mem->data.tree = assign_(r->left,r->right,var);
			else {
				mem->data.tree = r;
				r->cutNode();
			}
			return mem->data.tree;
		} else {
			var.add(l->data);
			mem = var.head;
			mem->data.doesDataInited=false;
			mem->data.doesTreeInited=true;
			if (r->ifHasAssign())
				mem->data.tree = assign_(r->left,r->right,var);
			else {
				mem->data.tree = r;
				r->cutNode();
			}
			return mem->data.tree;
		}
	} else if (l->data.type == Word::delimiter || r->data.type == Word::delimiter)
	{
		if (l->data.type == Word::delimiter){
			Node* temp = l; l = r; r = temp;
		}
		List<Data>::Node* mem  = var.search(l->data);
		if (mem!=nullptr){
			result = r;
			if (r->ifHasAssign())
				mem->data.tree = assign_(r->left,r->right,var);
			else{
				mem->data.tree = r;
				r->cutNode();
			}
			return mem->data.tree;
		} else {
			var.add(l->data);
			mem = var.head;
			mem->data.doesDataInited=false;
			mem->data.doesTreeInited=true;
			if (r->ifHasAssign())
				mem->data.tree = assign_(r->left,r->right,var);
			else {
				mem->data.tree = r;
				r->cutNode();
			}
			return mem->data.tree;
		}
	} else if (l->data.type == Word::variable  && r->data.type == Word::variable)
	{
		List<Data>::Node* memL = var.search(l->data);
		List<Data>::Node* memR = var.search(r->data);
		if				(memL == nullptr && memR == nullptr){
			var.add(l->data);
			var.head->data.tree= r;
			r->cutNode();
			return r;
		} else if (memL != nullptr && memR != nullptr){
				memL->data.tree = r;
			r->cutNode();
			return memL->data.tree;
		} else if (memL == nullptr && memR != nullptr){
			var.add(l->data);
			var.head->data.tree = r;
			r->cutNode();
			return var.head->data.tree;
		} else{
			memL->data.tree = r;
			r->cutNode();
			return r;
		}

		
	} else {
		result = new Node;
		result->data.doesDataInited = true;
		result->data.storedData.setValue(0,0);
		result->data.storedData.ifBool = true;
		result->data.priority = 30;
		result->data.storedData.decimalSystem = -1;
		return result;
	}
	return result;
}

void Node::removeNods()
{
	if (this == 0)
		return;
	delete this;
}

void Node::cutNode()
{
	if (this == nullptr)
		return;
	Node *node =this->parent;
	
	if (node->parent != nullptr && node->parent->left == node){
		node->parent->left = this;
		this->parent = node->parent;
		node->parent = nullptr;
	} else if (node->parent != nullptr && node->parent->right == node){
		node->parent->right = this;
		this->parent = node->parent;
		node->parent = nullptr;
	}
	if (node->parent != nullptr &&  node->left == this){
		node->left = nullptr;
		delete node->right;
		delete node;
	}
	if (node->parent != nullptr &&  node->right == this){
		node->right = nullptr;
		delete node->left;
		delete node;
	}
}

bool Node::ifHasAssign()
{
	bool isNameRight = strchr(this->data.name,61) != nullptr; 
	bool isDelimiter = this->data.type == Word::delimiter;
	if (isDelimiter && isNameRight)
		return true;
	else 
		return false;
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

bool Tree::AltBuild( List<Word>::Node* word)
{
	this->root = 0;
	addNode(this->root,buildSubTree_(word));
	while(word != 0){
		backToPeviousSubTreeLvl(root,word);
	}
	if (root != 0)
		return true;
	else
		return false;
}
Node* Tree::buildSubTree_( List<Word>::Node* & word)
{
	Node* root = 0;
	Node* node;
	if (word == nullptr)
		return root;
	while (word != 0) {
		if (!strncmp(word->data.word,")",1)){
			word = word->next;
			break;
		}
		if (!strncmp(word->data.word,"(",1)){
			word = word->next;
			node = buildSubTree_(word);
			addNode(root,node);
			continue;
		} else
			node = new Node(word->data);
		addNode(root,node);
		if (word!= nullptr)
			word = word->next;
	}
	if (root!=nullptr)
		root->data.priority +=50;
	return root;
}

Node* Tree::backToPeviousSubTreeLvl( Node* &dad,List<Word>::Node* & word)
{
	Node* node;
	if (word == nullptr)
		return dad;
	while (word != 0) {
		if (!strncmp(word->data.word,")",1)){
			word = word->next;
			break;
		}
		if (!strncmp(word->data.word,"(",1)){
			word = word->next;
			node = buildSubTree_(word);
		} else
			node = new Node(word->data);
		addNode(dad,node);
		if (word!= nullptr)
			word = word->next;
	}
	dad->data.priority +=50;
	return dad;
}

bool Tree::clearTree( void )
{
	removeNode(this->root);
	this->root = 0;
	return true;
}




