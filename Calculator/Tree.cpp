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
	if (this == 0)
		return;
	if (this->parent != 0)
		if (this == this->parent->left)
			this->parent->left = 0;
		else 
			this->parent->right = 0;
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
		this->appSonL(dad->right,temp);
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
Number Tree::Node::evaluteNode(List<Data> &var)
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
		if (mem!=nullptr &&mem->data.doesDataInited)
			return mem->data.getValue();
		else if (mem!=nullptr &&mem->data.doesTreeInited)
			return mem->data.tree->EvaluteTree(var);
		else{
			var.add(this->data);
			var.head->data.doesDataInited=true;
			var.head->data.doesTreeInited=false;
			Number res(0,1);
			res.decimalSystem = 10;
			var.head->data.storedData=res;
			return res;
		}
	}
	if (this->data.type == Word::cast::delimiter){
		//Special construction for "="
		bool isAssign = !strncmp(this->data.name,"=",1);
		if (!strncmp(this->data.name,"==",2))
			isAssign = false;
		if (isAssign)
			return this->assign(this->right,this->left,var);
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

char* Tree::Node::getCharNode()
{
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
	if (node == 0)
		return;
	removeNode(node->left);
	removeNode(node->right);
	delete node;
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
		if (root->data.getPriority()%50<19 && root->data.getPriority()%50>13){
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
	if (node == nullptr){
		return true;
	}
	if (dad->data.getPriority() > node->data.getPriority()){
		result = dad->appDad(node);
		dad=node;
	} else if (dad->data.getPriority() < node->data.getPriority()){
		result = dad->appSon(dad,node);
	} else {
		if (dad->data.getPriority() < 19 && dad->data.getPriority()>13){
			result = dad->appDad(node);
			dad=node;
		} else
			result = dad->appSon(dad,node);
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

Number Tree::Node::assign(Node*r,Node* l,List<Data>& var){
	//TODO: Check bugs
	if (l==nullptr && r!=nullptr)
		return (r->data.doesTreeInited)? r->data.tree->EvaluteTree(var) : r->data.storedData;
	if (r==nullptr && l!=nullptr)
		return (l->data.doesTreeInited)? l->data.tree->EvaluteTree(var) : l->data.storedData;
	if (l==nullptr && r==nullptr)
		return Number(0,1);
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
		List<Data>::Node* mem = var.search(r->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=l->data.storedData;
			return mem->data.storedData;
		}else if (mem!=nullptr){
			mem->data.storedData=l->data.storedData;
			mem->data.doesDataInited=true;
			return mem->data.storedData;
		} else {
			var.add(r->data);
			var.head->data.storedData=l->data.storedData;
			var.head->data.doesDataInited=true;
			var.head->data.doesTreeInited=false;
			return var.head->data.storedData;
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
		List<Data>::Node* mem = var.search(r->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=l->evaluteNode(var);
			return mem->data.storedData;
		}else if (mem!=nullptr){
			mem->data.storedData=l->evaluteNode(var);
			mem->data.doesDataInited=true;
			return mem->data.storedData;
		} else {
			var.add(l->data);
			var.head->data.storedData=l->evaluteNode(var);;
			var.head->data.doesDataInited=true;
			var.head->data.doesTreeInited=false;
			return var.head->data.storedData;
		}
	}
	if (l->data.type == Word::cast::variable && r->data.type == Word::cast::number){
		List<Data>::Node* mem = var.search(l->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=r->data.storedData;
			return mem->data.storedData;
		}else if (mem!=nullptr){
			mem->data.storedData=r->data.storedData;
			mem->data.doesDataInited=true;
			return mem->data.storedData;
		} else {
			var.add(l->data);
			var.head->data.storedData=r->data.storedData;
			var.head->data.doesDataInited=true;
			var.head->data.doesTreeInited=false;
			return var.head->data.storedData;
		}
	}
	if (l->data.type == Word::cast::variable && r->data.type == Word::cast::delimiter){
		List<Data>::Node* mem = var.search(l->data);
		if (mem!=nullptr && mem->data.doesTreeInited){
			delete mem->data.tree;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			mem->data.storedData=r->evaluteNode(var);
			return mem->data.storedData;
		}else if (mem!=nullptr){
			mem->data.storedData=r->evaluteNode(var);
			mem->data.doesDataInited=true;
			return mem->data.storedData;
		} else {
			var.add(l->data);
			mem=var.head;
			mem->data.storedData=r->evaluteNode(var);;
			mem->data.doesDataInited=true;
			mem->data.doesTreeInited=false;
			return mem->data.storedData;
		}
	}
	if (l->data.type == Word::cast::variable && r->data.type == Word::cast::variable){
		List<Data>::Node* mem1 = var.search(l->data);
		List<Data>::Node* mem2 = var.search(r->data);
		if (mem1==mem2 && mem1 == nullptr){
			var.add(l->data);
			var.head->data.storedData.setValue(0,1);
			var.head->data.doesDataInited=true;
			var.head->data.doesTreeInited=false;
			var.add(r->data);
			var.head->data.storedData.setValue(0,1);
			var.head->data.doesDataInited=true;
			var.head->data.doesTreeInited=false;
			return Number(0,1);
		} else if (mem1 == mem2){
			if (mem1->data.doesDataInited == true)
				return mem1->data.storedData;
			else
				return mem1->data.tree->EvaluteTree(var);
		} else if (mem1 == nullptr && mem2!=nullptr){
				var.add(l->data);

				if (mem2->data.doesDataInited){
						var.head->data.doesDataInited=true;
						var.head->data.storedData = mem2->data.storedData;
						return var.head->data.storedData;
				} else {
						var.head->data.doesDataInited=true;
						var.head->data.storedData = mem2->data.tree->EvaluteTree(var);
						return var.head->data.storedData;
				}
		} else if (mem2 == nullptr && mem1!=nullptr){
				var.add(r->data);
				if (mem1->data.doesDataInited){
					var.head->data.doesDataInited=true;
					var.head->data.storedData = mem1->data.storedData;
					return var.head->data.storedData;
				} else {
					var.head->data.doesDataInited=true;
					var.head->data.storedData = mem1->data.tree->EvaluteTree(var);
					return var.head->data.storedData;
				}
		} else { // if two variables inited assign left to the right
				if (mem2->data.doesDataInited){
					mem1->data.doesDataInited=true;
					mem1->data.storedData = mem2->data.storedData;
					return mem1->data.storedData;
				} else {
					mem1->data.doesDataInited=true;
					mem1->data.storedData = mem2->data.tree->EvaluteTree(var);
					return mem1->data.storedData;
				}
			}
		}		
	return result;
}

bool Tree::Node::appSonL( Node* dad, Node* son )
{
	if (dad->left == nullptr) {
		son->parent = dad;
		dad->left = son;
		return true;
	} else
		return appSon(dad,son);
}

Number Tree::Node::assign_( Node*l,Node*r,List<Data>& var, bool assignLeft)
{
	if (l==nullptr && r!=nullptr)
		return (r->data.doesTreeInited)? r->data.tree->EvaluteTree(var) : r->data.storedData;
	if (r==nullptr && l!=nullptr)
		return (l->data.doesTreeInited)? l->data.tree->EvaluteTree(var) : l->data.storedData;
	if (l==nullptr && r==nullptr)
		return Number(0,1);
	Number result;
	
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
Tree::Node* Tree::buildSubTree_( List<Word>::Node* & word)
{
	Tree::Node* root = 0;
	Tree::Node* node;
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
			node = new Tree::Node(word->data);
		addNode(root,node);
		if (word!= nullptr)
			word = word->next;
	}
	if (root!=nullptr)
		root->data.priority +=50;
	return root;
}

Tree::Node* Tree::backToPeviousSubTreeLvl( Node* &dad,List<Word>::Node* & word)
{
	Tree::Node* node;
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
			node = new Tree::Node(word->data);
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



