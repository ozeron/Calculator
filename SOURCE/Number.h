#include "Word.h"

#if !defined(NUMBER)
#define NUMBER
class Number
{
public:
	long long nomerator, denomerator;
	int decimalSystem;
	bool ifINF, ifBool;
public:
	Number();
	Number( long long);
	Number( long long, long long);
	Number(Word&);
	void setValue( long long, long long);
	bool operator==(Number&) const;
	void updateDecimalSystem(Number&,Number&);
	~Number(void);
};
 long long GCD( long long a, long long b);
int nextDecSystem(int);

#endif // NUMBER