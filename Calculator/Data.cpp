#include "Data.h"
#include "Tree.h"




Data::Data(void){
	name = nullptr;
	doesDataInited = false;
	tree = nullptr;
	doesTreeInited = false;
	type = Word::cast::null;
	int priority = 100;
}
Data::Data(Word right){
	int wordLen = strlen(right.word);
	this->name = new char[wordLen+1];
	strcpy(this->name,right.word);
	if (right.type == Word::cast::number){
		storedData = Number(right);
		doesDataInited = true;
	} else {
		storedData = Number(0);
		storedData.decimalSystem = -1;
		doesDataInited = false;
	}
	tree = nullptr;
	doesTreeInited = false;
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
	tree = nullptr;
	doesTreeInited = false;
	this->type = right.type;
	this->priority = right.priority;
}
Data::~Data(void){
	delete [] this->name;
	name = nullptr;

	delete [] this->tree;
	tree = nullptr;
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
	tree = nullptr;
	doesTreeInited = false;
	this->type = right.type;
	this->priority = right.priority;
	return *this;
}
bool Data::operator==(Data &right) const
{
	bool eqWord = !strcmp(this->name,right.name);
	bool eqData = this->storedData == right.storedData;
	bool eqTree = this->tree == right.tree;
	bool eqType = this->type == right.type;
	bool eqPriority;
	if (this->type == Word::cast::variable)
		return eqWord&&eqType;
	eqPriority = this->priority == right.priority;
	return (eqWord&&eqData&&eqTree&&eqPriority);
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
		priority = 14;
		return;
	}
	if (!strcmp(name,"-")){
		priority = 15;
		return;
	}	 
	if (!strcmp(name,"<2>")){
		priority = 16;
		return;
	}
	if (!strcmp(name,"*")){
		priority = 16;
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
		priority = 21;
		return;
	}	 
	if (!strcmp(name,"<4>")){
		priority = 22;
		return;
	}
	if (!strcmp(name,"<5>")){
		priority = 23;
		return;
	}
	if (!strcmp(name,"<6>")){
		priority = 24;
		return;
	}	 
	if (!strcmp(name,"<7>")){
		priority = 25;
		return;
	}
	if (!strcmp(name,"<8>")){
		priority = 26;
		return;
	}
	if (!strcmp(name,"<9>")){
		priority = 27;
		return;
	}
	int priority = 0;
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
Number Data::evalute(Number a , Number b)
{
	Number (*callFunc)(Number& , Number &);
	int n = this->priority%50;
	switch (n)
	{
	case 6:callFunc=or;
		break;
	case 7:callFunc=and;
		break;
	case 8:callFunc=equal;
		break;
	case 9:callFunc=notEqual;
		break;
	case 10:callFunc=biggerEq;
		break;
	case 11:callFunc=bigger;
		break;
	case 12:callFunc=lessEq;
		break;
	case 13:callFunc=less;
		break;
	case 14:callFunc=plus;
		break;
	case 15:callFunc=subtraction;
		break;
	case 16:callFunc=production;
		break;
	case 19:callFunc=division;
		break;
	case 20:callFunc=remainder;
		break;
	case 21:callFunc=exponent;
		break;
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:this->storedData = levlNOper(a,b);
			this->doesDataInited = true;
			return storedData;
	default:callFunc=plus;
			break;
	}
	this->storedData = (*callFunc)(a,b);
	this->doesDataInited = true;
	return storedData;
}
Number and(Number& a,Number& b){
	Number result,tA,tB;
	if (biggerEq(a,Number(1,1))==Number(1,1))
		tA.setValue(1,1);
	else 
		tA.setValue(0,1);
	if (biggerEq(b,Number(1,1))==Number(1,1))
		tB.setValue(1,1);
	else 
		tB.setValue(0,1);
	if (equal(tA,tB) == Number(1,1) && tA==Number(1,1))
		result.setValue(1,1);
	else
		result.setValue(0,1);
	result.ifBool = true;
	return result;
}
Number or(Number&a,Number&b){
	Number result,tA,tB;
	if (biggerEq(a,Number(1,1))==Number(1,1))
		tA.setValue(1,1);
	else 
		tA.setValue(0,1);
	if (biggerEq(b,Number(1,1))==Number(1,1))
		tB.setValue(1,1);
	else 
		tB.setValue(0,1);
	if (equal(tA,tB) == Number(1,1) && tA==Number(0,1))
		result.setValue(0,1);
	else
		result.setValue(1,1);
	result.ifBool = true;
	return result;
}
Number equal( Number&a,Number &b)
{
	Number result(0);
	result.ifBool = true;
	if (a==b){
		result.setValue(1,1);
		return result;
	} else {
		result.setValue(0,1);
		return result;
	}
}
Number notEqual(Number&a,Number&b){
	Number result;
	result = equal(a,b);
	if (result==Number(1,1))
		result.setValue(0,1);
	else
		result.setValue(1,1);
	return result;
}
Number less(Number&a,Number&b){
	Number result(0);
	result.ifBool = true;
	long double aD,bD;
	aD=static_cast<long double>(a.nomerator)/a.denomerator;
	bD=static_cast<long double>(b.nomerator)/b.denomerator;
	if (aD<bD){
		result.setValue(1,1);
		return result;
	} else {
		result.setValue(0,1);
		return result;
	}
}
Number lessEq(Number&a,Number&b){
	Number result;
	result = bigger(a,b);
	if (result==Number(1,1))
		result.setValue(0,1);
	 else
		 result.setValue(1,1);
	return result;
}
Number bigger(Number&a,Number&b){
	Number result(0);
	result.ifBool = true;
	long double aD,bD;
	aD=static_cast<long double>(a.nomerator)/a.denomerator;
	bD=static_cast<long double>(b.nomerator)/b.denomerator;
	if (aD>bD){
		result.setValue(1,1);
		return result;
	} else {
		result.setValue(0,1);
		return result;
	}
}
Number biggerEq(Number&a,Number&b){
	Number result;
	result = less(a,b);
	if (result==Number(1,1))
		result.setValue(0,1);
	else
		result.setValue(1,1);
	return result;
}
Number plus(Number &a,Number &b)
{	
	Number temp(0);
	 long long gcd = 0;

	a.nomerator = (a.decimalSystem == -1)? 0 : a.nomerator;
	b.nomerator = (b.decimalSystem == -1)? 0 : b.nomerator;
	
	temp.nomerator = a.nomerator*b.denomerator + b.nomerator*a.denomerator;
	temp.denomerator = a.denomerator*b.denomerator;
	gcd = GCD(temp.nomerator, temp.denomerator);
	temp.nomerator /= gcd;
	temp.denomerator /= gcd;
	temp.updateDecimalSystem(a,b);
	return temp;
}
Number subtraction(Number&a,Number&b){
	Number temp(0);
	 long long gcd = 0;

	 if (a.decimalSystem == -1 && b.decimalSystem!=-1){
		 temp.nomerator = -b.nomerator;
		 temp.denomerator = b.denomerator;
		 if (temp.nomerator<0 && temp.denomerator<0){
			 temp.nomerator=-temp.nomerator;
			 temp.denomerator=-temp.denomerator;
		 }
	 } else if (b.decimalSystem == -1 && a.decimalSystem!=-1){
		 temp=a;
		 temp.nomerator = -a.nomerator;
		 temp.denomerator = a.denomerator;
		 if (temp.nomerator<0 && temp.denomerator<0){
			 temp.nomerator=-temp.nomerator;
			 temp.denomerator=-temp.denomerator;
		 }
	 } else {
		temp.nomerator = a.nomerator*b.denomerator - b.nomerator*a.denomerator;
		temp.denomerator = a.denomerator*b.denomerator;
	 }
	gcd = GCD(temp.nomerator, temp.denomerator);
	temp.nomerator /= gcd;
	temp.denomerator /= gcd;
	temp.updateDecimalSystem(a,b);
	return temp;
}
Number production( Number& a,Number& b)
{
	Number temp(0);
	 long long gcd = 0;
	a.nomerator = (a.decimalSystem == -1)? 1 : a.nomerator;
	b.nomerator = (b.decimalSystem == -1)? 1 : b.nomerator;
	temp.nomerator = a.nomerator*b.nomerator;
	temp.denomerator = a.denomerator*b.denomerator;
	gcd = GCD(temp.nomerator, temp.denomerator);
	temp.nomerator /= gcd;
	temp.denomerator /= gcd;
	temp.updateDecimalSystem(a,b);
	return temp;
}
Number division(Number &a,Number &b){
	Number temp(0);
	long long gcd = 0;
	if (b.nomerator==0){
		temp.setValue(INT64_MAX,1);
		temp.ifINF=true;
		return temp;
	}
	a.nomerator = (a.decimalSystem == -1)? 1 : a.nomerator;
	b.nomerator = (b.decimalSystem == -1)? 1 : b.nomerator;
	temp.nomerator = a.nomerator*b.denomerator;
	temp.denomerator = a.denomerator*b.nomerator;
	gcd = GCD(temp.nomerator, temp.denomerator);
	temp.nomerator /= gcd;
	temp.denomerator /= gcd;
	temp.updateDecimalSystem(a,b);
	return temp;
}
Number exponent(Number&a,Number&b){
	int dec = 1000000000;
	 long long gcd;
	Number result;
	long double temp=0;
	a.nomerator = (a.decimalSystem == -1)? 1 : a.nomerator;
	b.nomerator = (b.decimalSystem == -1)? 1 : b.nomerator;
	temp = static_cast<double>(a.nomerator)/a.denomerator;
	if ((static_cast<double>(b.nomerator)/b.denomerator)<0)// Check when exponent is less then zero
		temp = pow(temp,static_cast<double>(b.denomerator)/b.nomerator*(-1));
	else 
		temp = pow(temp,static_cast<double>(b.nomerator)/b.denomerator);
	if (temp >= INT64_MAX){
		result.nomerator=INT64_MAX;
		result.updateDecimalSystem(a,b);
		result.ifINF = true;
		return result;
	}
	if (abs(ceil(temp)-temp)<0.00000001){
		result.nomerator = static_cast< long long>(ceil(temp));
		result.updateDecimalSystem(a,b);
		return result;
	}
	if (abs(floor(temp)-temp)<0.00000001){
		result.nomerator = static_cast< long long>(floor(temp));
		result.updateDecimalSystem(a,b);
		return result;
	}
	long long nextDenomerator = 1;
	while(temp<dec){
		temp*=10;
		nextDenomerator*=10;
	}
	if(static_cast< long long>(temp*10)%10<5)
		result.nomerator=static_cast< long long>(floor(temp));
	else
		result.nomerator=static_cast< long long>(ceil(temp));
	result.denomerator = nextDenomerator;
	gcd = GCD(result.nomerator,result.denomerator);
	if (gcd!=0){
		result.nomerator/=gcd;
		result.denomerator/=gcd;
	}
	result.updateDecimalSystem(a,b);
	return result;
}
Number remainder(Number&a,Number&b){
	Number temp;
	a.nomerator = (a.decimalSystem == -1)? 1 : a.nomerator;
	b.nomerator = (b.decimalSystem == -1)? 1 : b.nomerator;
	temp.denomerator = 1;
	temp.nomerator = (int)(float(a.nomerator/a.denomerator)/float(b.nomerator/b.denomerator));
	temp.nomerator *= float(b.nomerator/b.denomerator);
	temp.nomerator = (a.nomerator/a.denomerator)-temp.nomerator;
	temp.updateDecimalSystem(a,b);
	return temp;
}
Number Data::levlNOper(Number& a ,Number& b)
{
	int n = this->priority%50-18;
	return recLevNOper(a,b,n);
}



Number recLevNOper( Number& a,Number& b, int n)
{
	a.nomerator = (a.decimalSystem == -1)? 1 : a.nomerator;
	b.nomerator = (b.decimalSystem == -1)? 1 : b.nomerator;
	Number temp = a;
	if (n==3)
		return exponent(a,b);
	int amount = b.nomerator/b.denomerator-1;
	if (amount == 2077252341)
		return 9223372036854;
	for(int i=0;i<amount;i++)
		temp = recLevNOper(temp,temp,n-1);
	return recLevNOper(a,temp,n-1);
}
