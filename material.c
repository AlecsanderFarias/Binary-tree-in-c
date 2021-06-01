#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "material.h"

Material* createMaterial(int code, char name[],int qtd,float price,char location[]){

  Material* newMaterial = (Material *)malloc(sizeof(Material));

  newMaterial->code = code;
  newMaterial->qtd = qtd;
  newMaterial->price = price; 


  //copy strings
  strcpy(newMaterial->name,name); 
  strcpy(newMaterial->location,location);

  return newMaterial;
}

Material* editMaterial(Material* material,int preSelect,char value[]){

  int option = -1;

  Material* newEditMaterial = (Material *)malloc(sizeof(Material));

  newEditMaterial->code = material->code;
  newEditMaterial->qtd = material->qtd;
  newEditMaterial->price = material->price; 

  //copy strings
  strcpy(newEditMaterial->location,material->location);
  strcpy(newEditMaterial->name,material->name); 


  if(preSelect != -1){
    option = preSelect;
  }else {
    printf("Selecione o que deseja alterar: \n 1-> Estoque\n 2-> Preco\n 3-> Localizacao\n Outro -> cancelar\n");
    scanf("%d",&option);
  }

  printf("\n\n");

  switch(option){
    case 1: {
      if(value != NULL){
        newEditMaterial->qtd = atoi(value);
      }else{
        int teste;
        printf("Insira o novo estoque: ");
        scanf("%d",&newEditMaterial->qtd);
      }
      break;
    }

    case 2: {
      if(value != NULL){
        newEditMaterial->price = atof(value);
      }else{
        printf("Insira o novo preco: ");
        scanf("%f",&newEditMaterial->price);
      }
      break;
    }

    case 3: {
      if(value != NULL){
        strcpy(newEditMaterial->location,value);
      }else{
        printf("Insira a nova localizacao: ");
        scanf("%s",newEditMaterial->location);
      }
      break;
    }

    default: {
      printf("\n\n Operacao cancelada!! \n\n");
      break;
    }
  }

  return newEditMaterial;


}

void printMaterial(Material* material){
  printf("\n\n");
  
  printf("codigo: %d\n",material->code);
  printf("nome: %s\n",material->name);
  printf("preco: %f\n",material->price);
  printf("estoque atual: %d\n",material->qtd);
  printf("localizacao: %s\n",material->location);

  printf("\n\n");
}
