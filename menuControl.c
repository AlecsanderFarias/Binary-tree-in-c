#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"
#include "tree.h"
#include "fileControl.h"

#define file "arvore.bin"


int selectMenuOption(){
  int option = -1;

  printf("\n\nMenu principal\n\n");
  printf("Selecione uma das opcoes abaixo\n\n");

  printf("1-> Inserir material\n"); //ok
  printf("2-> Remover material\n"); //ok
  printf("3-> Alterar material\n"); //ok
  printf("4-> Ver informacoes de um material\n"); //ok
  printf("5-> Lista materiais\n"); //ok
  printf("6-> Carregar informacoes de arquivo texto\n"); //doing
  printf("7-> Imprimir arvore\n"); //ok
  printf("8-> Imprimir posicoes livres\n"); //ok
  printf("9-> Sair\n\n");

  printf("Opcao desejada: ");
  scanf("%d",&option);
  printf("\n");

  return option;

}

void menuOption1(){
  printf("Inserir um material\n");
  printf("Inserir os dados: \n");

  int code;
  printf("Codigo: ");
  scanf("%d",&code);
  printf("\n");

  MaterialNode* alreadyExistCode = getMaterialByCode(code);

  if(alreadyExistCode != NULL){
    printf("\n\n !!! Parece que esse código ja existe no sistema !!!\n");
    printf("Cadastro cancelado devido ao codigo repetido!\n\n");

    return;
  }

  char name[50];
  int qtd;
  float price;
  char location[100];

  printf("Nome: ");
  scanf("%s",name);
  printf("\n");

  printf("Estoque: ");
  scanf("%d",&qtd);
  printf("\n");

  printf("Preco: ");
  scanf("%f",&price);
  printf("\n");

  printf("Localizacao: ");
  scanf("%s",location);
  printf("\n");

  
  Material* newMaterial = createMaterial(code,name,qtd,price,location);

  addMaterial(newMaterial);

  printf("\n\n Material adicionada com sucesso!! \n\n");

};

void menuOption2(){
  printf("Remover um material\n");
  printf("Inserir o código do material a ser alterado: \n");

  int code;
  printf("Codigo: ");
  scanf("%d",&code);
  printf("\n");

  int materialPosition = getMaterialPositionByCode(code);

  if(materialPosition == -1){
    printf("\n\n !!! Parece que esse codigo nao existe no sistema !!!\n");
    printf("Remocao cancelada devido ao codigo nao existente!\n\n");

    return;
  }

  printf("position to remove: %d \n",materialPosition);

  initRemoveMaterialByCode(code);


  printf("Material removido com sucesso!! \n\n");
}

void menuOption3(){
  printf("Alterar um material\n");
  printf("Inserir o código do material a ser alterado: \n");

  int code;
  printf("Codigo: ");
  scanf("%d",&code);
  printf("\n");

  int materialPosition = getMaterialPositionByCode(code);

  if(materialPosition == -1){
    printf("\n\n !!! Parece que esse codigo nao existe no sistema !!!\n");
    printf("Edicao cancelada devido ao codigo nao existente!\n\n");

    return;
  }

  FILE *arq = fopen(file, "rb+");

  MaterialNode* nodeMaterial = getNodeByPosition(arq,materialPosition);

  nodeMaterial->material = editMaterial(nodeMaterial->material,-1,NULL);

  writeNodeOnFile(arq,nodeMaterial,materialPosition);

  fclose(arq);
}

void menuOption4(){
  printf("Ver informacoes de um produot\n");
  printf("Inserir o código do material a ser visualizado: \n");

  int code;
  printf("Codigo: ");
  scanf("%d",&code);
  printf("\n");

  int nodePosition = getMaterialPositionByCode(code);

  if(nodePosition == -1){
    printf("\n\n !!! Parece que esse codigo nao existe no sistema !!!\n");
    printf("Edicao cancelada devido ao codigo nao existente!\n\n");

    return;
  }

  FILE *arq = fopen(file, "rb+");

  MaterialNode * materialNode = getNodeByPosition(arq,nodePosition);

  printMaterial(materialNode->material);

  fclose(arq);
}

void menuOption5(){
  printf("Listar materiais\n");

  initPrintTreeMaterial();

}

void menuOption6(){
  printf("Carregar informacoes de arquivo texto\n");

  FILE *arq = fopen("enter.text", "r");
  int bufferLength = 255;
  char buffer[bufferLength];

  while (fgets(buffer, bufferLength, arq)) {
    

    char * token = strtok(buffer, ";");

    if(strcmp(token,"I")== 0){
      //insert
      char * code = strtok(NULL, ";");
      char * name = strtok(NULL, ";");
      char * qtd = strtok(NULL, ";");
      char * price = strtok(NULL, ";");
      char * location = strtok(NULL, ";");

      Material* materialToAdd = createMaterial(atoi(code),name,atoi(qtd),atof(price),location);

      addMaterial(materialToAdd);
    }

    if(strcmp(token,"R") == 0){
      //remove
      char * code = strtok(NULL, ";");

      initRemoveMaterialByCode(atoi(code));
    }

    if(strcmp(token,"A") == 0){
      //edit
    /*   char * code = strtok(NULL, ";");
      char * name = strtok(NULL, ";");  //dont use
      char * qtd = strtok(NULL, ";");
      char * price = strtok(NULL, ";");
      char * location = strtok(NULL, ";");

      int position = getMaterialPositionByCode(atoi(code));

       printf("code = %s name = %s qtd = %s price = %s location = %s \n",
        code != NULL ? code : "NULL",
        name != NULL ? name : "NULL",
        qtd != NULL ? qtd : "NULL",
        price != NULL ? price : "NULL",
        location != NULL ? location : "NULL");

      if(position != -1){
        MaterialNode* node = getMaterialByCode(atoi(code));

        if(qtd != NULL){
          //update qtd
          node->material = editMaterial(node->material,1,qtd);
        }

        if(price != NULL){
          //update qtd
          node->material = editMaterial(node->material,2,price);
        }

        if(location != NULL){
          //update qtd
          node->material = editMaterial(node->material,3,location);
        }

        FILE *arq2 = fopen(file, "rb+");


        writeNodeOnFile(arq2,node,position);

        fclose(arq2);

      } 
 */

    }


   
  }

  fclose(arq);
}

void menuOption7(){
  printf("Imprimir arvore\n");

  pritTreeByLevel();
}

void menuOption8(){
  printf("Imprimir posicoes livres\n");

  FILE *arq = fopen(file, "rb+");
  Head* header = readHead(arq);
  

  if(header->pos_free == -1){
    printf("Sem posições livres!!\n");
  }

  int position = header->pos_free;

  MaterialNode* pivot ;
  
  while(position != -1){
    printf("%d ",position);
    pivot = getNodeByPosition(arq,position);

    position = pivot->father;
  }

  fclose(arq);
}

