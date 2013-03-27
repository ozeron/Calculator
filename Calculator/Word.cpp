#include "Word.h"


Word::Word()
{
	strcpy(word,"");
	type = null;

}
Word::Word(char ch)
{
	word[0] = ch;
	word[1] = '\0';
	type = null;
}
Word::Word(char *arr)
{
	int n = strlen(arr);
	strcpy(this->word,arr);
	type = null;
}
Word::Word(char *arr, int n)
{
	for(int i=0;i<n;i++)
		word[i]=arr[i];
	word[n]='\0';
	type = null;
}
Word::Word(const Word& right)
{
	std::strcpy(word,right.word);
	this->type = right.type;
}
/*
bool Word::operator==(Word right ) const
{
	bool eqWord = !strcmp(this->word,right.word);
	bool eqType = this->type == right.type;
	if (eqWord && eqType)
		return true;
	else
		return false;
}
bool Word::operator==(char *right) const
{
	bool eqWord = !strcmp(this->word,right);
	if (eqWord)
		return true;
	else
		return false;
}*/
void Word::setWord(char ch)
{
	word[0] = ch;
	word[1] = '\0';
}
void Word::setWord(char *arr)
{
	int n = strlen(arr);
	strncpy(this->word,arr,n+1);
}
void Word::setWord(char *arr, int n)
{
	for(int i=0;i<n;i++)
		word[i]=arr[i];
	word[n]='\0';
}
char* Word::getWord()
{
	return &word[0];
}
void Word::setType( cast kind)
{
	this->type = kind;
}
Word::cast Word::getType(void)
{
	return type;
}

Word& Word::operator=( const Word & right)
{
	if(this == &right)
		return *this;
	if (right.word != nullptr){
		int wSize = strlen(right.word);
		std::strcpy(this->word,right.word);
		this->type = right.type;
		return *this;
	}
}

bool Word::operator==( Word right) const
{
	bool eqWord = !strcmp(this->word,right.word);
	bool eqType = this->type == right.type;
	if (eqWord && eqType)
		return true;
	else
		return false;
}

bool Word::operator==( char* right) const
{
	bool eqWord = !strcmp(this->word,right);
	if (eqWord)
		return true;
	else
		return false;
}
