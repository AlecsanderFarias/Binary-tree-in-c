#ifndef GRUPO
#define GRUPO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"
//include material lib

typedef struct no
{    
  struct Material* material;
  int left;
  int right;
  int father;

} MaterialNode;

//open file and fix to init program
void initTree();

//get father position to every logic that need it
//arq = file already opened to work with
//code = code that you want to add 
//if code already exists on tree returns -2
//if tree is empty return -1
//return the father node position
int getFatherPositionToAdd(FILE *arq,int code);


//add material on tree
//material = material to add on tree , can not be NULL
void addMaterial(Material *material);

//get the material position on file if exists
//code = code on material that you want to search , can not be 0
//return the position on file
int getMaterialPositionByCode(int code);

//get the material on file using the code
//code = the material code, can not be 0
//return the material in memory
MaterialNode* getMaterialByCode(int code);

//get the smaller code position on file
//arq = file opened to work with
//pos = position to start looking on file
int minNodePos(FILE *arq, int pos);

//remove material on tree by code
//arq = file opened to work with
//pos = position to start looking on file
//code = code to remove
//return the position of node to write on father or on header
int removeMaterialByCode(FILE* arq,int pos,int code);

//opens file and start to remove material by code on file
//code = material code to remove
void initRemoveMaterialByCode(int code);

//calc tree height starting from pos
//arq = file opened to work with
//pos = position to start calc height
int calcTreeHeight(FILE *arq, int pos);

//print all material on tree
//arq = file opened to work with
//pos = position to start print
void printTreeMaterials(FILE *arq,int pos);

//print only a unic level from tree
//arq = file opened to work with
//pos = position to start navigate
//printLevel = level to print
//actualLevel = actual level to navigate, has to start with 0
void printTreeLevel(FILE *arq,int pos, int printLevel, int actualLevel);

//print all leves of tree
void pritTreeByLevel();

//print all materials of tree
void initPrintTreeMaterial();

//write a edited material by code on file
//code = code to edit, can not be 0
//material = edited materialNode , can not be NULL
void editMaterialByCode(int code, MaterialNode *material);



#endif