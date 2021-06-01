#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"
#include "tree.h"
#include "fileControl.h"


void printHeader(Head* header) {
  printf("raiz : %d\n topo: %d\n vazia:%d\n",header->pos_root,header->pos_top,header->pos_free);
}

void writeNodeOnFile(FILE *arq, MaterialNode *x, int pos)
{   
    fseek(arq, 0, SEEK_SET); //posiciona no in ́ıcio do arquivo
    fseek(arq, sizeof(Head) + pos * sizeof(MaterialNode), SEEK_SET);
    fwrite(x, sizeof(MaterialNode), 1, arq);
}

MaterialNode* getNodeByPosition(FILE *arq, int pos)
{
    MaterialNode *x = malloc(sizeof(MaterialNode));
    fseek(arq, 0, SEEK_SET); // posiciona no in ́ıcio do arquivo
    fseek(arq, sizeof(Head) + pos * sizeof(MaterialNode), SEEK_SET);
    fread(x, sizeof(MaterialNode), 1, arq);
    return x;
}

Head* readHead(FILE *arq)
{
    Head *header = (Head *)malloc(sizeof(Head));
    fseek(arq, 0, SEEK_SET); // posiciona no in ́ıcio do arquivo
    fread(header, sizeof(Head), 1, arq);
    return header;
}

void writeHead(FILE *arq, Head *header)
{
    fseek(arq, 0, SEEK_SET); //posiciona no in ́ıcio do arquivo
    fwrite(header, sizeof(Head), 1, arq);
}

