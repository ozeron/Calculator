#include "Number.h"
#include "Word.h"


#if !defined(DATA)
#define DATA
class Tree;
class  Data
{
public:
	char* name;
	Number storedData;
	bool doesDataInited;
	Tree *tree;
	//bool doesTreeInited;
	Word::cast type;
	int priority;
public:
	Data(void);
	Data(Word right);
	Data(const Data&);
	~Data(void);
	Data& Data::operator=(const Data &right);
	int getPriority();
	void initPriority();
	Number evalute(Number, Number);
	Number getValue();
	Word::cast getType();
	Number plus(Number,Number);
};

int GCD(int a,int b);
#endif 