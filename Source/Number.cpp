#include "Number.h"


Number::Number(void)
{
	nomerator = 1;
	denomerator = 1;
	decimalSystem = 10;
}
Number::Number(int right)
{
	nomerator = right;
	denomerator = 1;
	decimalSystem = 10;
}
Number::Number(int n ,int d)
{
	nomerator = n;
	denomerator = d;
	decimalSystem = 10;
}
Number::Number(Word right)
{
	int i = 0;
	nomerator = 0;
	denomerator = 1;
	while (right.word[i]!='\0')
	{
		nomerator = nomerator*10 + (right.word[i]-'0');
		i++;
	}
	decimalSystem = 10;
}

Number::~Number(void)
{
}
