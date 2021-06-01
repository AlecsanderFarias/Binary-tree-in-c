#ifndef FILECONTROL
#define FILECONTROL

#include "tree.h"

typedef struct Head
{
    int pos_root;
    int pos_top;
    int pos_free;
} Head;

//print header of file
//header = header of file, can not be NULL
void printHeader(Head* header);

//write MaterialNode pointer on file
//arq = file opened to work with
//x = materialNode pointer to write on file, can not be null
//pos = position to write on file
void writeNodeOnFile(FILE *arq, MaterialNode *x, int pos);

//read a position on file
//arq = file opened to work with
//pos = position to read on file
//return a MaterialNode in memnory
MaterialNode* getNodeByPosition(FILE *arq, int pos);

//read the header on file
//arq = file opened to work with
Head* readHead(FILE *arq);

//write header of file
//arq = file opened to work with
//header = header of file, can not be NULL
void writeHead(FILE *arq, Head *header);


#endif