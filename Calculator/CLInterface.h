
#if !defined(HCLInterface)
#define HCLInterface

#include <cstdio>
#include <iostream>
#include <cmath>
#include "Word.h"
#include "List.h"
#include "Tree.h"
#include <iostream>



int cli(FILE*);

List<Word> *stringParse(char*);
bool improveInput(List<Word> &list);

void undefine(char*,List<Data>&);
void CLITEST();
void memOut(FILE *,List<Data>&);
void printHelp(FILE *);
#endif

