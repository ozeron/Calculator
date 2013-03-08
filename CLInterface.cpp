#include "CLInterface.h"

int cli(FILE* mainio)
{
	char buf[1024];
	List<Word> *inputData;
	int i = 0;
	while (buf[0]!='q'){
		fprintf(stdout,"#");
		fgets(buf,1023,mainio);
		if (buf[0]=='q')
			continue;
		//TODO: Implement all CLI commands
		inputData = stringParse(buf);
		improveInput(*inputData);
		inputData->insertAfter(0,Word("+"));
		Tree my;
		my.buildTree(*inputData);

		std::cout << my.getTreeCharArr() << std::endl;
		Number rez;
		rez= my.EvaluteTree();
		std::cout << rez.nomerator << std::endl;
		delete inputData;
	}
	return 0;
}

//Attention awfull code next!!!
/*
List<Word>* stringParse(char* arr)
{
	List<Word> *list = new List<Word>();
	Word *next;
	Word::cast type;
	int p = 0, i=1;
	int size = bufSize(arr);
	for(;p<size;p++)
	{
		if	(arr[p] == '(' || arr[p] == ')') {
			next = new Word(arr[p]);
			type = Word::delimiter;
			next->setType(type);
			list->add(*next);
			delete next;
		} else if (arr[p] - '1' <= 8 && arr[p]-'1' >= 0) {
			int i = 0;
			while (arr[p+i]!='\n' && arr[p+i]-'0'<=9 && arr[p+i]-'0'>=0)
				i++;
			next = new Word(arr+p,i);
			type = Word::dNum;
			next->setType(type);
			list->add(*next);
			delete next;
			p = p+i-1;
		} else if (arr[p] == '0'){
			int i = 0;
			//int decSize=10;
			bool nextChOptCh = ((arr[p+1]>47 && arr[p+1] < 57) || (arr[p+1]>64 && arr[p+1] < 91) || arr[p+1]=='b' || arr[p+1]=='d' || arr[p+1] == 'e' || arr[p+1] == 'h' || arr[p+1]=='o' || arr[p+1] == 'r'  || arr[p+1] == 'x' );
			if (!nextChOptCh) {
				next = new Word(arr[p]);
				type = Word::dNum;
				next->setType(type);
				list->add(*next);
				delete next;
			}
			// TODO: Implement different decimal systems
			/*else {
				i++;
				if (arr[p+i]-'')
			}
		} else if (arr[p] == '+' || arr[p] == '-' || arr[p] == '*' || arr[p] == '/' || arr[p] == '%' || arr[p] == '^'){
			if (arr[p] =='-'){//Trying to solve -5 problem
				int i = 1;
				while(arr[p+i] == ' ')
					i++;
				p+=i;
				int j = 0;
				while (arr[p+j]!='\n' && arr[p+j]-'0'<=9 && arr[p+j]-'0'>=0)
					j++;
				char *arr=new char[j+2];
				strcpy(arr,"-");
				strncat(arr,arr+p,j);
				next = new Word(arr);
				type = Word::dNum;
				next->setType(type);
				list->add(*next);
				delete next;
				p = p+i-1;
			}
			next = new Word(arr[p]);
			type = Word::delimiter;
			next->setType(type);
			list->add(*next);
			delete next;
		} else if (arr[p]=='&' || arr[p]=='|' || arr[p]=='@' || arr[p]=='?' || arr[p]==':') {
			next = new Word(arr[p]);
			type = Word::delimiter;
			next->setType(type);
			list->add(*next);
			delete next;
		} else if (arr[p]=='<') {
			if ((arr[p+1]>=48  || arr[p+1]<=57) && arr[p+2]=='>'){
				next = new Word(arr+p,3);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
				p+=2;
			} else if(arr[p+1] == '='){
				next = new Word(arr+p,2);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
				p+=1;
			} else {
				next = new Word(arr+p,1);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
			}
		} else if (arr[p]=='>'){
			if (arr[p+1] == '='){
				next = new Word(arr+p,2);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
				p+=1;
			} else {
					next = new Word(arr+p,1);
					type = Word::delimiter;
					next->setType(type);
					list->add(*next);
					delete next;
			}
		} else if (arr[p]=='='){
			if (arr[p+1]=='='){
				next = new Word(arr+p,2);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
				p+=1;
			} else {
				while(arr[p+i] == ' ')
					i++;
				if (arr[p+i]=='['){
					next = new Word("=[");
					type = Word::delimiter;
					next->setType(type);
					list->add(*next);
					delete next;
					p+=i;
				} else {
					next = new Word(arr+p,1);
					type = Word::delimiter;
					next->setType(type);
					list->add(*next);
					delete next;
				}
			}
		} else if (arr[p]=='['){
			int i =1;
			while(arr[p+i] == ' ')
					i++;
			if (arr[p+i]=='='){
				next = new Word("]=");
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
				p+=1;
			}
		} else if (arr[p]=='!'){
			if (arr[p+1]=='='){
				next = new Word(arr+p,2);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
				p+=1;
			} else {
				next = new Word(arr+p,1);
				type = Word::delimiter;
				next->setType(type);
				list->add(*next);
				delete next;
			}
		}else if (arr[p] == ','){
			next = new Word(arr[p]);
			type = Word::delimiter;
			next->setType(type);
			list->add(*next);
			delete next;
		} else if ((arr[p]>64&&arr[p]<91) || (arr[p]>96&&arr[p]<123)) {
			int i = 0;
			while ((arr[p+i]>64&&arr[p]<91) || (arr[p+i]>96&&arr[p+i]<123))
				i++;
			next = new Word(arr+p,i);
			type = Word::variable;
			next->setType(type);
			list->add(*next);
			delete next;
			p +=i-1;
		}
	}
	return list;
}*/

List<Word>* stringParse(char* arr)
{
	char* ariph = "+-*/%^**";
	char* level = "<1><2><3><4><5><6><7><8><9>";
	char* logic = "?:@|& == != >= <=";
	char* more  = ",=()[]";
	char* dump  = " _#$~`\";{}\\.\n\t";
	char* numb  = "0123456789";
	char* letter= "abcdefghjklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char *subStr = new char[1024];
	List<Word> *list = new List<Word>();
	Word *next;
	Word::cast type;

	int size = strlen(arr);
	
	int i=0;
	while (i<size-1){
		strcpy(subStr,"");
		strncat(subStr,arr+i,1);
		if (strstr(dump,subStr) != nullptr){ //find  /0/n#$~`\";{}\\.
			i++;
			continue;
		}

		if (strstr(more,subStr) != nullptr){ //find  ,=()[]
			next = new Word (subStr);
			type = Word::delimiter;
			next->setType(type);            // add to word
			list->add(*next);
			delete next;
			i++;
			continue;
		}

		if (strstr(ariph,subStr) != nullptr){ //find +-*/%^
			next = new Word (subStr);
			type = Word::delimiter;
			next->setType(type);            // add to word
			list->add(*next);
			delete next;
			i++;
			continue;
		}

		if (strstr("<",subStr) != nullptr){ //find <n>
			if (i+2 < size-1){ // check if array border don't crossed
				strcpy(subStr,"");
				strncat(subStr,arr+i,3);
				if (strstr(level,subStr) != nullptr){
					next = new Word (arr+i,3);
					type = Word::delimiter;
					next->setType(type);            // add to word
					list->add(*next);
					delete next;
					i+=3;
					continue;
				}
			}
		}

		if (strstr(logic,subStr) != nullptr){// find ?:@|& == != >= <="
			strcpy(subStr,"");
			strncat(subStr,arr+i,2);
			if (strstr(logic,subStr) != nullptr){// check if in == != >= <=
				next = new Word (subStr);
				i+=2;
			} else {
				next = new Word (arr[i]);
				i++;
			}
			type = Word::delimiter;
			next->setType(type);            // add to word
			list->add(*next);
			delete next;
			continue;
		}

		if (strstr(letter,subStr) != nullptr){// find word
			int j = 0;
			while (i+j<size-1 && strstr(letter,subStr)!=nullptr) { 
				j++;
				strcpy(subStr,"");
				strncat(subStr,arr+i,j+1);
			}
			strcpy(subStr,"");
			strncat(subStr,arr+i,j);
			next = new Word (subStr);
			type = Word::variable;
			next->setType(type);            // add to word
			list->add(*next);
			delete next;
			i+=j;
			continue;
		}

		if (strstr(numb,subStr) != nullptr){//find number
			int j = 0;
			if (strstr("0",subStr) != nullptr)//additional decimal systems
			{
				j++;
				strcpy(subStr,"");
				strncat(subStr,arr+i,j);
				if (strstr("0b 0x 0h",subStr) == nullptr)// if no additional decimal systems
					j--;									 // j--
			}

			while (i+j<size-1 && strstr("0123456789ABCDEF",subStr)!=nullptr) { 
				j++;
				strcpy(subStr,"");
				strncat(subStr,arr+i,j+1);
			}
			strcpy(subStr,"");
			strncat(subStr,arr+i,j);
			next = new Word (subStr);
			type = Word::number;
			next->setType(type);            // add to word
			list->add(*next);
			delete next;
			i+=j;
			continue;
		}
	}
	return list;
}
bool improveInput(List<Word> &list)
{

	int size = list.getSize();
	for(int i = 0; i < size-1; i++)
	{
		if (list.at(i).word == "-" && list.at(i+1).type == Word::cast::number){
			
		}
	}
	return true;
}

void CLITEST()
{
	cli(stdin);
	/*char buf[1024];
	List<Word> *inputData;
	fgets(buf,1023,stdin);
	inputData = stringParse(buf);
	delete inputData;*/
}