#include "CLInterface.h"

int cli(FILE* mainio)
{
	char buf[1024];
	List<Word> *inputData;
	List<Data> memory;
	Tree *my;
	int i = 0;
	while (buf[0]!='q'){
		my = new Tree;
		
		fprintf(stdout,"#");
		fgets(buf,1023,mainio);
		if (buf[0]=='q')
			continue;
		if (!strncmp(buf,"h",1)){
			printHelp(stdout);
			continue;
		}
		if (!strncmp(buf,"mem",3)){
			memOut(stdout,memory);
			continue;
		}
		//TODO: Implement all CLI commands
		inputData = stringParse(buf);
		improveInput(*inputData);

		my->AltBuild(inputData->tail);
		Node *p = my->root;
		std::cout << my->getTreeCharArr() << std::endl;
		Number rez;
		rez=my->EvaluteTree(memory);
		char out[100]("") ;
		strcpy(out, rez.getNumberString());
		std::cout  << out<<std::endl;
		delete inputData;
	}
	return 0;
}

List<Word>* stringParse(char* arr)
{
	char* ariph = "+-*/%^**";
	char* level = "<1><2><3><4><5><6><7><8><9>";
	char* logic = "?:@|& == != >= <=";
	char* more  = ",=()[]";
	char* dump  = " _#$~`\";{}\\.\n\t";
	char* numb  = "0123456789";
	char* letter= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
				} else {
					strcpy(subStr,"");
					strncat(subStr,arr+i,1);
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

		if (strstr(letter,subStr) != nullptr){// find word
			int j = 0;
			while (i+j<size-1 && strstr(letter,subStr)!=nullptr) { 
				j++;
				strcpy(subStr,"");
				strncat(subStr,arr+i+j,1);
			}
			strcpy(subStr,"");
			strncat(subStr,arr+i,j);
			next = new Word (subStr);
			type = Word::variable;
			if (strstr("-INF",subStr)!=nullptr)
				type = Word::number;
			next->setType(type);            // add to word
			list->add(*next);
			delete next;
			i+=j;
			continue;
		}

		if (strstr(numb,subStr) != nullptr){//find number
			int j = 1;
			if (strstr("0",subStr) != nullptr)//additional decimal systems
			{
				strcpy(subStr,"");
				strncat(subStr,arr+i,2);
				if (strstr("0b 0x 0h",subStr) != nullptr)// if no additional decimal systems
					j++;									 // j--
			}
			strcpy(subStr,"");
			strncat(subStr,arr+i+j,1);
			while (i+j<size-1 && strstr("0123456789ABCDEF",subStr)!=nullptr) { 
				j++;
				strcpy(subStr,"");
				strncat(subStr,arr+i+j,1);
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
		i++;
	}
	return list;
}
bool improveInput(List<Word> &list)
{

	int size = list.getSize();
	for(int i = 0; i < size-1; i++)
	{
		if (list.at(i)->data.type != Word::delimiter && list.at(i+1)->data.type != Word::delimiter){
			list.insertAfter(i,Word("+"));
			list.at(i+1)->data.setType(Word::cast::delimiter);
			size++;
			i=0;
		}
		if (list.at(i)->data.type == Word::cast::number && !strcmp(list.at(i+1)->data.word,"(")){
			list.insertAfter(i,Word("*"));
			list.at(i+1)->data.setType(Word::cast::delimiter);
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,")") && list.at(i+1)->data.type == Word::cast::number){
			list.insertAfter(i,Word("*"));
			list.at(i+1)->data.setType(Word::cast::delimiter);
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"-") &&!strcmp(list.at(i+1)->data.word,"-")){
			list.at(i+1)->data.setWord("+");
			list.del(list.at(i));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"=") &&!strcmp(list.at(i+1)->data.word,"=")){
			list.at(i+1)->data.setWord("==");
			list.del(list.at(i));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"=") &&!strcmp(list.at(i+1)->data.word,"[")){
			list.at(i+1)->data.setWord("=[");
			list.del(list.at(i));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"]") &&!strcmp(list.at(i+1)->data.word,"=")){
			list.at(i+1)->data.setWord("]=");
			list.del(list.at(i));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"-") &&!strcmp(list.at(i+1)->data.word,"+")){
			list.del(list.at(i+1));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"+") &&!strcmp(list.at(i+1)->data.word,"-")){
			list.del(list.at(i));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"+") &&!strcmp(list.at(i+1)->data.word,"+")){
			list.del(list.at(i));
			size--;
			i=0;
		}
		if (!strcmp(list.at(i)->data.word,"*") &&!strcmp(list.at(i+1)->data.word,"*")){
			list.at(i+1)->data.setWord("**");
			list.del(list.at(i));
			size--;
			i=0;
		}
	}
	return true;
}

void CLITEST()
{
	cli(stdin);
	Word a('c');
	Word b;
	Word c("love");
	Word d("love",2);
	Word e =c;
	Word f =c;
	List<Word> list;

}

void memOut( FILE * out, List<Data> &mem)
{
	if(mem.head==nullptr){
		fprintf(out,"EMPTY\n");
		return;
	}
	List<Data>::Node *current = mem.tail;
	Number memVal;
	Data * dat = nullptr;
	fprintf(out,"%-8s%-20s%-20s%-12s\n","Name","Tree","Value","Tree Address");
	while(current!=nullptr)
	{
		dat = &current->data;
		fprintf(out,"%-8s",dat->name);	
		fprintf(out,"%-20s",dat->tree->getCharNode());
		char val[54];
		memVal = dat->tree->evaluteNode(mem);
		strcpy(val,memVal.getNumberString());
		fprintf(out,"%-20s",val);
		fprintf(out,"%-12p\n",dat->tree);
		current=current->next;
	}
}

void printHelp( FILE * out)
{

	fprintf(out,"Type exspression in single row, you can use variables,\n they defined when you first time call variable;\n");
	fprintf(out,"Calculator support different decimal systems: binary(\"0b\"), oct(\"0\"), dec(standart) and hex(\"0x\")\n");
	fprintf(out,"If you use bigger numbers than have current decimal system,\n it will change current decimal system to the bigger one.\n");
	fprintf(out,"Press \"h\" for help");
	fprintf(out,"Type \"mem\" to see memory state.\n");
	fprintf(out,"Press \"q\" for exit.\n");
}

void undefine (char* arr)
{

}
