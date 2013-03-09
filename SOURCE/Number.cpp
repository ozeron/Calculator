#include "Number.h"
#define INT64_MAX 9223372036854775807

Number::Number(void)
{
	nomerator = 1;
	denomerator = 1;
	decimalSystem = 10;
	ifBool = false;
	if (this->nomerator == INT64_MAX)
		ifINF = true;
	else
		ifINF = false;
}
Number::Number( long long right)
{
	nomerator = right;
	denomerator = 1;
	decimalSystem = 10;
	ifBool = false;
	if (this->nomerator == INT64_MAX)
		ifINF = true;
	else
		ifINF = false;
}
Number::Number( long long n , long long d)
{
	nomerator = n;
	denomerator = d;
	decimalSystem = 10;
	ifBool = false;
	long long gcd = GCD(this->nomerator,this->denomerator);
	if (gcd!=0){
		this->nomerator/=gcd;
		this->denomerator/=gcd;
	}
	if (this->nomerator == INT64_MAX)
		ifINF = true;
	else
		ifINF = false;
}
Number::Number(Word &right)
{
	int i = 0,a=0;
	nomerator = 0;
	denomerator = 1;
	decimalSystem = 10;
	bool minusSign = false;
	ifBool = false;
	if(right.word[i]=='-'){
		minusSign = true;
		i++;
	}
	if(right.word[i]=='0'){
		decimalSystem = 8;
	} 
	if(right.word[i]=='0' && right.word[i+1]=='\0'){
		decimalSystem = 10;
		i+=2;
		return;
	} 
	if(right.word[i]=='0' && right.word[i+1]=='b'){
		decimalSystem=2;
		i+=2;
	} 
	if(right.word[i]=='0' && right.word[i+1]=='d'){
		decimalSystem=10;
		i+=2;
	} 
	if(right.word[i]=='0' && (right.word[i+1]=='h'||right.word[i+1]=='x')){
		decimalSystem=16;
		i+=2;
	}
	int nextNum = 0;
	while (right.word[i]!='\0')
	{
		a = (right.word[i]-48<=9)?48:55;
		nextNum = right.word[i] - a;//ASCII code 'A' = 65
		if (decimalSystem==2 && nextNum >1)
			decimalSystem = nextDecSystem(nextNum);
		if (decimalSystem==8 && nextNum >7)
			decimalSystem = nextDecSystem(nextNum);
		if (decimalSystem==10 && nextNum >9)
			decimalSystem = nextDecSystem(nextNum);
		nomerator = nomerator*decimalSystem + nextNum;
		i++;
	}
	if (minusSign)
		nomerator *= -1; 
	long long gcd = GCD(this->nomerator,this->denomerator);
	if (gcd!=0){
		this->nomerator/=gcd;
		this->denomerator/=gcd;
	}
	if (this->nomerator == INT64_MAX)
		ifINF = true;
	else
		ifINF = false;
}

Number::~Number(void)
{
}

bool Number::operator==( Number& right) const
{
	bool eqNomerator = this->nomerator==right.nomerator;
	bool eqDenomerator = this->denomerator==right.denomerator;
	if (eqNomerator && eqDenomerator)
		return true;
	else
		return false;
}

void Number::updateDecimalSystem( Number&a,Number& b)
{
	if (a.decimalSystem == -1)
		this->decimalSystem = b.decimalSystem;
	if (b.decimalSystem == -1)
		this->decimalSystem = a.decimalSystem;
	if (a.decimalSystem == -1 && b.decimalSystem == -1)
		this->decimalSystem = 10;
	if (a.decimalSystem != -1 && b.decimalSystem == -1)
		this->decimalSystem = a.decimalSystem;
}

void Number::setValue( long long a, long long b)
{
	nomerator = a;
	denomerator = b;
	long long gcd = GCD(this->nomerator,this->denomerator);
	if (gcd!=0){
		this->nomerator/=gcd;
		this->denomerator/=gcd;
	}
	ifINF = false;
}

int nextDecSystem( int a )
{
	if (a>1 && a<1)
		return 2;
	if (a>1&&a<8)
		return 8;
	if (a>1 && a<10)
		return 10;
	if (a>1 && a<16)
		return 16;
}


long long GCD( long long a, long long b) {
	return b?GCD(b,a%b):a;
}

