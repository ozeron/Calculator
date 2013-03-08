#include "Data.h"
#include "Tree.h"

Data::Data(void){
	name = nullptr;
	doesDataInited = false;
//	tree = nullptr;
//	doesTreeInited = false;
	type = Word::cast::null;
	int priority = 100;
}
Data::Data(Word right){
	int wordLen = strlen(right.word);
	this->name = new char[wordLen+1];
	strcpy(this->name,right.word);
	
	storedData = Number(right);
	doesDataInited = true;
//	tree = nullptr;
//	doesTreeInited = false;
	this->type = right.type;
	switch (right.type)
	{
	case Word::cast::number: priority = 29;
						   break;
	case Word::cast::variable: priority = 30;
							   break;
	case Word::cast::delimiter:initPriority();
							   break;
	default: priority = 100;
			 break;
	}
}
Data::Data(const Data& right)
{
	if (right.name!= nullptr){
		int wSize = strlen(right.name);
		this->name = new char [wSize+1];
		std::strcpy(this->name,right.name);
	} else
		this->name = nullptr;
	this->storedData = Number(right.storedData);
	this->doesDataInited = true;
//	tree = nullptr;
//	doesTreeInited = false;
	this->type = right.type;
	this->priority = right.priority;
}
Data::~Data(void){
	delete [] this->name;
	name = nullptr;
}
Data& Data::operator=(const Data &right)
{
	if(this == &right)
		return *this;
	
	delete[] this->name;
	if (right.name != nullptr){
		int wSize = strlen(right.name);
		this->name = new char [wSize+1];
		std::strcpy(this->name,right.name);
	} else
		this->name = nullptr;
	this->storedData = right.storedData;
	this->doesDataInited = right.doesDataInited;
//	tree = nullptr;
//	doesTreeInited = false;
	this->type = right.type;
	this->priority = right.priority;
	return *this;
}
int Data::getPriority()
{
	return this->priority;
}
void Data::initPriority()
{	
	if (!strcmp(name,")")){
		priority = -2;
		return;
	}	 
	if (!strcmp(name,"(")){
		priority = -1;
		return;
	}	 
	if (!strcmp(name,",")){
		priority = 0;
		return;
	}	 
	if (!strcmp(name,"=")){
		priority = 1;
		return;
	}
	if (!strcmp(name,"=[")){
		priority = 2;
		return;
	}
	if (!strcmp(name,"]=")){
		priority = 2;
		return;
	}
	if (!strcmp(name,"@")){
		priority = 3;
		return;
	}
	if (!strcmp(name,"?")){
		priority = 4;
		return;
	}	 
	if (!strcmp(name,":")){
		priority = 5;
		return;
	}
	if (!strcmp(name,"|")){
		priority = 6;
		return;
	}
	if (!strcmp(name,"&")){
		priority = 7;
		return;
	}	 
	if (!strcmp(name,"==")){
		priority = 8;
		return;
	}
	if (!strcmp(name,"!=")){
		priority = 9;
		return;
	}
	if (!strcmp(name,">=")){
		priority = 10;
		return;
	}	 
	if (!strcmp(name,">")){
		priority = 11;
		return;
	}
	if (!strcmp(name,"<=")){
		priority = 12;
		return;
	}
	if (!strcmp(name,"<")){
		priority = 13;
		return;
	}	 
	if (!strcmp(name,"<1>")){
		priority = 14;
		return;
	}
	if (!strcmp(name,"+")){
		priority = 15;
		return;
	}
	if (!strcmp(name,"-")){
		priority = 16;
		return;
	}	 
	if (!strcmp(name,"<2>")){
		priority = 17;
		return;
	}
	if (!strcmp(name,"*")){
		priority = 18;
		return;
	}
	if (!strcmp(name,"/")){
		priority = 19;
		return;
	}	 
	if (!strcmp(name,"%")){
		priority = 20;
		return;
	}
	if (!strcmp(name,"<3>")){
		priority = 21;
		return;
	}
	if (!strcmp(name,"^")){
		priority = 22;
		return;
	}	 
	if (!strcmp(name,"<4>")){
		priority = 23;
		return;
	}
	if (!strcmp(name,"<5>")){
		priority = 24;
		return;
	}
	if (!strcmp(name,"<6>")){
		priority = 25;
		return;
	}	 
	if (!strcmp(name,"<7>")){
		priority = 26;
		return;
	}
	if (!strcmp(name,"<8>")){
		priority = 27;
		return;
	}
	if (!strcmp(name,"<9>")){
		priority = 28;
		return;
	}
	int priority = 0;
}

Number Data::evalute(Number a , Number b)
{
	this->storedData = plus(a,b);
	doesDataInited = true;
	return storedData;
}
Number Data::plus(Number a,Number b)
{
	Number temp;
	if (temp.denomerator == temp.denomerator){
		temp.nomerator = a.nomerator + b.nomerator;
		return temp;
	}
	temp.nomerator = a.nomerator*b.denomerator + b.nomerator*a.denomerator;
	temp.denomerator = a.denomerator*b.denomerator;
	int gcd = GCD(temp.nomerator, temp.denomerator);
	temp.nomerator /= gcd;
	temp.denomerator /= gcd;
	return temp;
}

Number Data::getValue()
{
	if (doesDataInited)
		return storedData;
	else
		return Number();
}
Word::cast Data::getType()
{
	return this->type;
}



int GCD(int a,int b) {
  return b?GCD(b,a%b):a;
}