#pragma once
#if !defined(WORD)
#define WORD


#include <cstring>


class Word
{
public:
	char* word;
	enum cast {null,variable,number,delimiter} 
			type;
public:
	Word();
	Word(char );
	Word(char *);
	Word(char *, int);
	Word(const Word&);
	
	Word& operator=(const Word &);
	bool operator==(Word) const;

	void setWord(char);
	void setWord(char *);
	void setWord(char*, int);
	char* getWord();

	void setType(cast);
	cast getType(void);

	~Word();
};

#endif // WORD