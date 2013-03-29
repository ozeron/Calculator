#include "Number.h"
#define INT64_MAX 9223372036854775807

Number::Number(void)
{
	nomerator = 1;
	denomerator = 1;
	decimalSystem = 10;
	ifBool = false;
	ifInited = false;
	if (abs(abs(static_cast<double>(this->nomerator)/this->denomerator)) == INT64_MAX)
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
	ifInited = true;
	if (abs(static_cast<double>(this->nomerator)/this->denomerator) == INT64_MAX)
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
	ifInited = true;
	long long gcd = GCD(this->nomerator,this->denomerator);
	if (gcd!=0){
		this->nomerator/=gcd;
		this->denomerator/=gcd;
	}
	if (abs(static_cast<double>(this->nomerator)/this->denomerator) == INT64_MAX)
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
	ifINF = false;
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
	if (abs(static_cast<double>(this->nomerator)/this->denomerator) == INT64_MAX)
		ifINF = true;
	else
		ifINF = false;
	ifInited = true;
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
	if (a.decimalSystem != -1 && b.decimalSystem != -1)
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

char* Number::getNumberString()
{
	char res[54](""),signum[2]("");
	char nom[24](""),denom[24]("");
	if (this->decimalSystem == 0)
		return "";
	if (this->ifInited == -1)
		return "mem_undef";
	if (this->nomerator == this->denomerator && this->nomerator == 0)
		return "undef";
	if (this->ifBool)// Check BOOL
	{
		if (this->nomerator==0)
			return "false";
		else 
			return "true";

	}
	if (static_cast<double>(nomerator)/denomerator<0) // Check signum
		strcpy(signum,"-");
	strcat(res,signum);

	if (this->ifINF){//return iINF
		strcat(res,"INF");
		return res;
	}

	switch (decimalSystem){
	case 2:strcat(res,"0b");
		break;
	case 8:strcat(res,"0");
		break;
	case 16:strcat(res,"0x");
		break;
	}
	strcat(res,lLong2Char(nomerator));
	if (denomerator!=1){
		strcat(res,"/");
		strcat(res,lLong2Char(denomerator));
	}
	return res;
}

char* Number::lLong2Char( long long n )
{
	if (n==INT64_MAX)
		return "INF";
	if (n==-INT64_MAX-1)
		return "INF";
	char hex[][2]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
	char reversed[24](""), normal[24]("");
	int nextNum;
	n=llabs(n);
	do {
		nextNum = n%decimalSystem;
		n=n/decimalSystem;
		strcat(reversed,hex[abs(nextNum)]);
	} while (n!=0);
	
	int len = strlen(reversed);
	for(int i=0; i<len;i++)
		normal[i]=reversed[len-1-i];
	return normal;
}

bool Number::printNumber( FILE * out)
{
	if (fprintf(out,this->getNumberString()))
		return true;
	else
		return false;
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

