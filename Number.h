#include "Word.h"

#if !defined(NUMBER)
#define NUMBER
class Number
{
public:
	int nomerator, denomerator;
	int decimalSystem;
public:
	Number();
	Number(int);
	Number(int,int);
	Number(Word);
	~Number(void);
};

#endif // NUMBER