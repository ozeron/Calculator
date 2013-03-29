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
	dad->left = this;
	this->parent = dad;
	return true;
}
bool appSon(Node *dad, Node* son)
{
	Node* temp;
	
	if (dad->right == nullptr) {
		dad->right = son;
		son->parent = dad;
		return true;
	}																//   Implemet this:    + <- 7"28"
	if (dad->right->data.getPriority() < son->data.getPriority()) { //					 3	  *"16" 
		appSon(dad->right,son);								//
	} else if (dad->right->data.getPriority() > son->data.getPriority()) {
		temp = dad->right;											//   Implement this:   + <- *"16"
		dad->right = son;										  	//					       3      7"28"										//
		son = temp;
		appSonL(dad->right,temp);
	} else {
		if (dad->data.getPriority() < 19 && dad->data.getPriority()>13){
			temp = dad->right;   // Changing places dad->right and son, 
			dad->right = son;    // then assinging son->right value of dad->right
			son = temp;
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
	if (this==nullptr){
		Number res(1,0);
		res.decimalSystem = 0;
		return res;
	}
	if (this->data.type == Word::cast::number)
		return this->getValue();
	if (this->data.type == Word::cast::variable){

		//TODO: Find by name, not by value!
		List<Data>::Node* mem = var.search(this->data);
		if (mem!=nullptr && mem->data.doesTreeInited)
			return mem->data.tree->evaluteNode(var);
		else{
			var.add(this->data);
			var.head->data.doesDataInited=false;
			var.head->data.doesTreeInited=false;
			Number res(0,1);
			res.decimalSystem = -2;
			var.head->data.storedData=res;
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
		if (isAssign)
			return assign(this->right,this->left,var);
		Number a,b;

		if(this->left!=nullptr)
			a = this->left->evaluteNode(var);
		else
			a.decimalSystem=-1;

		if(this->right!=nullptr)
			b = this->right->evaluteNode(var);
		else
			b.decimalSystem=-1;
		return this->data.evalute(a,b);
	}
	return Number(0,0);
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
		if (dad->data.getPriority() < 19 && dad->data.getPriority()>13){
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
	if (static_cast<double>(result.nomerator)/result.denomerator >= INT_MAX-10)
		result.ifINF = true;
	if (static_cast<double>(result.nomerator)/result.denomerator <=-(INT_MAX-10))
		result.ifINF = true;
	return result;
}

Number assign(Node*r,Node* l,List<Data>& var){
	//TODO: Check bugs
	if (l==nullptr && r!=nullptr)
		return (r->data.doesTreeInited)? r->data.tree->evaluteNode(var) : r->data.storedData;
	if (r==nullptr && l!=nullptr)
		return (l->data.doesTreeInited)? l->data.tree->evaluteNode(var) : l->data.storedData;
	if (l==nullptr && r==nullptr)
		return Number(0,1);
	Number result;
	if (l->data.type != Word::variable && r->data.type != Word::variable)
	{
		//Maybe add false assingning parametr
		result.setValue(0,1);
		result.ifBool = true;
		return result;
	}
	if (l->data.type == Word::cast::number && r->data.type == Word::cast::variable || l->data.type == Word::cast::variable && r->data.type == Word::cast::number)
	{
		if (l->data.type == Word::number){
			Node* temp = l; l = r; r = temp;
		}

		List<Data>::Node* mem = var.search(l->data);
		if (mem!=nullptr){
			mem->data.doesDataInited=false;
			mem->data.doesTreeInited=true;
			*mem->data.tree = *r;
			return r->evaluteNode(var);
		} else {
			var.add(l->data);
			var.head->data.doesDataInited=false;
			var.head->data.doesTreeInited=true;
			var.head->data.tree=r;
			return r->evaluteNode(var);
		}
	}
	if (l->data.type == Word::cast::delimiter && r->data.type == Word::cast::variable || l->data.type == Word::cast::variable && r->data.type == Word::cast::delimiter ){
		if (l->data.type == Word::delimiter){
			Node* temp = l; l = r; r = temp;
		}
		List<Data>::Node* mem = var.search(l->data);
		if (mem!=nullptr){
			mem->data.doesTreeInited=true;
			*mem->data.tree = *r;
			return r->evaluteNode(var);
		} else {
			var.add(l->data);
			var.head->data.doesDataInited=false;
			var.head->data.doesTreeInited=true;
			var.head->data.tree=r;
			return r->evaluteNode(var);
		}
	}
	if (l->data.type == Word::cast::variable && r->data.type == Word::cast::variable){
		List<Data>::Node* mem1 = var.search(l->data);
		List<Data>::Node* mem2 = var.search(r->data);
		if (mem1==mem2 && mem1 == nullptr){
			var.add(l->data);
			var.head->data.storedData.setValue(0,1);
			var.head->data.doesDataInited=false;
			var.head->data.doesTreeInited=false;
			var.add(r->data);
			var.head->data.storedData.setValue(0,1);
			var.head->data.doesDataInited=false;
			var.head->data.doesTreeInited=false;
			return Number(0,1);
		} else if (mem1 == mem2){
			if (mem1->data.doesTreeInited == true)
				return mem1->data.tree->evaluteNode(var);
			else
				return mem1->data.storedData;
		} else if (mem1 == nullptr && mem2!=nullptr){
				var.add(l->data);
				if (mem2->data.doesTreeInited){
					var.head->data.doesDataInited=false;
					appSon(var.head->data.tree,mem2->data.tree);
					return var.head->data.tree->evaluteNode(var);
				} else {
					var.head->data.doesDataInited=true;
					var.head->data.storedData = mem2->data.storedData;
					return var.head->data.storedData;
				}
		} else if (mem2 == nullptr && mem1!=nullptr){
				var.add(r->data);
				if (mem1->data.doesTreeInited){
					var.head->data.doesDataInited=false;
					delete var.head->data.tree;
					var.head->data.tree = mem1->data.tree;
					return var.head->data.tree->evaluteNode(var);
				} else {
					var.head->data.doesDataInited=true;
					var.head->data.storedData = mem1->data.storedData;
					return var.head->data.storedData;
				}
		} else { // if two variables inited assign left to the right
				var.add(r->data);
				if (mem2->data.doesTreeInited){
					var.head->data.doesDataInited=false;
					//delete var.head->data.tree;
					var.head->data.tree = mem2->data.tree;
					return var.head->data.tree->evaluteNode(var);
				} else {
					mem1->data.doesDataInited=true;
					mem1->data.storedData = mem2->data.storedData;
					return mem1->data.storedData;
				}
			}
		}		
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

void Node::removeNods()
{
	if (this == 0)
		return;
	delete this;
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




