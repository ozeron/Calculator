#include "Word.h"


Word::Word()
{
	word = nullptr;
	type = null;

}
Word::Word(char ch)
{
	word = new char[2];
	word[0] = ch;
	word[1] = '\0';



	type = null;
}
Word::Word(char *arr)
{
	int n = strlen(arr);
	word = new char [n+1];
	strcpy(this->word,arr);
	type = null;
}
Word::Word(char *arr, int n)
{
	word = new char [n+1];
	for(int i=0;i<n;i++)
		word[i]=arr[i];
	word[n]='\0';
	type = null;
}
Word::Word(const Word& right)
{
	if (right.word != nullptr){
		int wSize = strlen(right.word);
		word = new char [wSize+1];
		std::strcpy(word,right.word);
	} else
		this->word = nullptr;
	this->type = right.type;
}

Word& Word::operator=(const Word &right)
{
	if(this == &right)
		return *this;
	delete[] this->word;
	
	if (right.word != nullptr){
		int wSize = strlen(right.word);
		this->word = new char [wSize+1];
		std::strcpy(this->word,right.word);
	} else
		this->word = nullptr;

	this->type = right.type;
	return *this;
}
bool Word::operator==(Word right ) const
{
	bool eqWord = !strcmp(this->word,right.word);
	bool eqType = this->type == right.type;
	if (eqWord && eqType)
		return true;
	else
		return false;
}

void Word::setWord(char ch)
{
	delete word;
	word = new char[2];
	word[0] = ch;
	word[1] = '\0';
}
void Word::setWord(char *arr)
{
	delete word;
	int n = strlen(arr);
	word = new char [n+1];
	strcpy(this->word,arr);
}
void Word::setWord(char *arr, int n)
{
	delete word;
	word = new char [n+1];
	for(int i=0;i<n;i++)
		word[i]=arr[i];
	word[n]='\0';
}
char* Word::getWord()
{
	return word;
}
void Word::setType( cast kind)
{
	this->type = kind;
}
Word::cast Word::getType()
{
	return type;
}


Word::~Word()
{
	delete[] this->word;

	word = nullptr;
	//delete[] this->type;
	type = null;
}