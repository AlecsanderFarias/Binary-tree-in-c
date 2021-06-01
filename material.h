#ifndef MATERIAL
#define MATERIAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Material
{   
  int code;
  char name[50];
  int qtd;
  float price;
  char location[100];
} Material;


typedef union editContent {
  int qtd;
  float price;
  char location[100];
} EditContent;

//create material in memory
//return material in memory (malloc)
//code = code to new material
//name = name to new material
//qtd = qtd to new material
//price = price to new material
//location = location to new material
Material* createMaterial(int code, char name[],int qtd,float price,char location[]);

//edit a material from the material you send on parameters
//create a copy of the material on parameters on memory and edit only the necessary
//material = material to edit , can not be NULL
//preSelect = pre select field to edit , 1 = qtd , 2 = price , 3 = location 
//preContent = value pre filled to change on material without typing
//return a new material (in memory) with the current edit
Material*  editMaterial(Material* material,int preSelect, char value[]);

//print material on terminal
//material = material to print , can not be NULL
void printMaterial(Material* material);


#endif