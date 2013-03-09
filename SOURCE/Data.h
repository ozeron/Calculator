#include "Number.h"
#include "Word.h"
#include <cmath>
#include <cstdlib>

#if !defined(DATA)
#define DATA
#define INT64_MAX 9223372036854775807
class Tree;

class  Data
{

public:
	char* name;
	Number storedData;
	bool doesDataInited;

	Tree *tree;
	bool doesTreeInited;

	Word::cast type;
	int priority;
public:
	Data(void);
	Data(Word right);
	Data(const Data&);
	~Data(void);
	Data& Data::operator=(const Data &right);
	bool operator==(Data&) const;
	int getPriority();
	void initPriority();
	Number getValue();
	Word::cast getType();
	Number evalute(Number, Number);
	Number levlNOper(Number&,Number&);
};
Number and(Number&,Number&);
Number or(Number&,Number&);
Number equal(Number&,Number&);
Number notEqual(Number&,Number&);
Number less(Number&,Number&);
Number lessEq(Number&,Number&);
Number bigger(Number&,Number&);
Number biggerEq(Number&,Number&);
Number plus(Number&,Number&);
Number subtraction(Number&,Number&);
Number production(Number&,Number&);
Number division(Number&,Number&);
Number exponent(Number&,Number&);
Number remainder(Number&,Number&);

Number recLevNOper(Number&,Number&,int);

#endif 