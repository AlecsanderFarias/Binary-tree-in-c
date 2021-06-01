#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"
#include "tree.h"
#include "fileControl.h"

#define file "arvore.bin"


void initTree()
{
  FILE *arq = fopen(file, "wb+");

  Head *header = (Head *)malloc(sizeof(Head));
  header = readHead(arq);

  header->pos_root = -1;
  header->pos_free = -1;
  header->pos_top = 0;

  writeHead(arq,header);
  

  fclose(arq);
}

int getFatherPositionToAdd(FILE *arq,int code){
  Head* head = readHead(arq);

  //dont need to register on father
  if(head->pos_root == -1){
    return -1;
  }else {
    MaterialNode* pivot = NULL;
    pivot = getNodeByPosition(arq,head->pos_root);
    int fatherPosition = head->pos_root;

    while(
      (pivot->left != -1 && code < pivot->material->code) ||  
      (pivot->right != -1 && code > pivot->material->code))
    {
      if(code < pivot->material->code){
        fatherPosition = pivot->left;
        pivot = getNodeByPosition(arq,pivot->left);
      }else {
        fatherPosition = pivot->right;
        pivot = getNodeByPosition(arq,pivot->right);
      }
    }

    if(pivot->material->code == code){
      //alread exists this code
      return -2;
    }else {
      return fatherPosition;
    }

  }

}

int getPositionFree(FILE *arq){
  Head* head = readHead(arq);
  int position;


  if(head->pos_free == -1){
    //has not free spots
    position = head->pos_top;
    head->pos_top = position + 1;

  }else{
    //has free spot
    position = head->pos_free;
    MaterialNode* freeSpot = getNodeByPosition(arq,position);
    head->pos_free = freeSpot->father;

  }

  if(head->pos_root == -1){
    head->pos_root = position;
  }


  writeHead(arq,head);

  return position;

}

void addMaterial(Material *material){
  FILE *arq = fopen(file, "rb+");

  MaterialNode* newNode = (MaterialNode *)malloc(sizeof(MaterialNode));

  newNode->material = material;
  newNode->left = -1;
  newNode->right = -1;

  int fatherPosition = getFatherPositionToAdd(arq,material->code);

  if(fatherPosition == -2){
    printf("Ja existe um material registrado com esse código\n");
  }else {
    newNode->father = fatherPosition;

    int positionToAdd  = getPositionFree(arq);

    //have to update father
    if(fatherPosition != -1){
      MaterialNode* father = getNodeByPosition(arq,fatherPosition);

      if( material->code < father->material->code){
        //write on left
        father->left = positionToAdd;
      }else {
        //write on right
        father->right = positionToAdd;
      }

      //write father
      writeNodeOnFile(arq,father,fatherPosition);

    }

    //write newNode
    writeNodeOnFile(arq,newNode,positionToAdd); 
  }

  Head *header = readHead(arq);

  fclose(arq);
}

int getMaterialPositionByCode(int code){
  FILE *arq = fopen(file, "rb+");

  Head* header = readHead(arq);

  int position = header->pos_root;

  if(position == -1){
    fclose(arq);
    return -1;
  }

  MaterialNode* pivot = getNodeByPosition(arq,position);

  while(pivot != NULL && pivot->material->code != code && position != -1){
      if(code < pivot->material->code){
        //go to left  

        if(pivot->left == -1){
          break;
        }

        position = pivot->left;
        pivot = getNodeByPosition(arq,pivot->left);
      }else {
        //go to right

        if(pivot->right == -1){
          break;
        }

        position = pivot->right;
        pivot = getNodeByPosition(arq,pivot->right);
    }
  }

  fclose(arq);
  

  return pivot != NULL && pivot->material->code ==code && position != -1 ? position : -1;
}

MaterialNode* getMaterialByCode(int code){
  FILE *arq = fopen(file, "rb+");

  Head* header = readHead(arq);

  if(header->pos_root == -1){
    fclose(arq);
    return NULL;
  }


  MaterialNode* pivot = getNodeByPosition(arq,header->pos_root);

  while(pivot != NULL && pivot->material->code != code){
    if(code < pivot->material->code){
      //go to left
      if(pivot->left == -1){
        //has no node on left
        break;
      }else {
        pivot = getNodeByPosition(arq,pivot->left);
      }
    }else {
      //go to right
      if(pivot->left == -1){
        //has no node on right
        break;
      }else {
        pivot = getNodeByPosition(arq,pivot->right);
      }
    }
  }

  fclose(arq);

  return pivot != NULL && pivot->material->code ==code ? pivot : NULL;

}

int minNodePos(FILE *arq, int pos){
  if(pos == -1){
    return -1;
  }

  MaterialNode* materialNode = getNodeByPosition(arq,pos);

  if(materialNode->left != -1){
    return minNodePos(arq,materialNode->left);
  }

  return pos;
  
}

int removeMaterialByCode(FILE* arq,int pos, int code){

  if(pos == -1){
    return -1;
  }

  MaterialNode* materialNode = getNodeByPosition(arq,pos);
  int materialCode = materialNode->material->code;

  
  if(code < materialCode){
    //go to left
    materialNode->left = removeMaterialByCode(arq,materialNode->left,code);
  }

  if(code > materialCode){
    //go to right
    materialNode->right = removeMaterialByCode(arq,materialNode->right,code);
  }

  if(code == materialCode){
    //do logic

    if(materialNode->left == -1 && materialNode->right == -1){
      //is leaf

      //clean node on file

      materialNode->left = -1;
      materialNode->right = -1;
      materialNode->material = NULL;

      //get header free position
      Head *header = readHead(arq);
      materialNode->father = header->pos_free;
      header->pos_free = pos;

      //write node
      writeNodeOnFile(arq,materialNode,pos);

      //write header
      writeHead(arq,header);

      //return non exists node
      return -1;
    }

    if(materialNode->left == -1){
      //has only right children, return right children pos

      int childrenPos = materialNode->right;

      //update children to fix father pos
      MaterialNode* rightChildren = getNodeByPosition(arq,childrenPos);
      rightChildren->father = materialNode->father;

      //clean position
      materialNode->left = -1;
      materialNode->right = -1;
      materialNode->material = NULL;

      //get header free position
      Head *header = readHead(arq);
      materialNode->father = header->pos_free;
      header->pos_free = pos;
      

      //write children
      writeNodeOnFile(arq,rightChildren,childrenPos);

      //write node
      writeNodeOnFile(arq,materialNode,pos);

      //write header
      writeHead(arq,header);

      return childrenPos;
    }

    if(materialNode->right == -1){
      //has only left children, return left children pos

      int childrenPos = materialNode->left;

      //update children to fix father pos
      MaterialNode* leftChildren = getNodeByPosition(arq,childrenPos);
      leftChildren->father = materialNode->father;

      //clean position
      materialNode->left = -1;
      materialNode->right = -1;
      materialNode->material = NULL;

      //get header free position
      Head *header = readHead(arq);
      materialNode->father = header->pos_free;
      header->pos_free = pos;
      

      //write children
      writeNodeOnFile(arq,leftChildren,childrenPos);

      //write node
      writeNodeOnFile(arq,materialNode,pos);

      //write header
      writeHead(arq,header);

      return childrenPos;
    }

    //has 2 childrens
    
    int proxMinNodePos = minNodePos(arq,materialNode->right);
     
    MaterialNode* proxMinNode = getNodeByPosition(arq,proxMinNodePos);
    materialNode->material = proxMinNode->material;

    materialNode->right = removeMaterialByCode(arq,materialNode->right,proxMinNode->material->code);

    writeNodeOnFile(arq,materialNode,pos);

    return pos;
  }

  writeNodeOnFile(arq,materialNode,pos);

  return pos;
}

void initRemoveMaterialByCode(int code){
  FILE *arq = fopen(file, "rb+");

  Head* header = readHead(arq);

  int newPosRaiz = removeMaterialByCode(arq,header->pos_root,code);

  //read header again beacause its updating on remove
  header = readHead(arq);
  header->pos_root = newPosRaiz;

  writeHead(arq,header);

  fclose(arq);
}

void printTreeMaterials(FILE *arq,int pos){
  MaterialNode* materialNode = getNodeByPosition(arq,pos);

  if(materialNode->left != -1){
    printTreeMaterials(arq,materialNode->left);
  }

  printMaterial(materialNode->material);


  if(materialNode->right != -1){
    printTreeMaterials(arq,materialNode->right);
  }
  
}

int calcTreeHeight(FILE *arq, int pos){

  if(pos == -1) return 0;

  MaterialNode* materialNode = getNodeByPosition(arq,pos);

  int leftHeight = materialNode->left != -1 ? calcTreeHeight(arq,materialNode->left): 0;
  int rightHeight = materialNode->right != -1 ? calcTreeHeight(arq,materialNode->right): 0;

  int BiggestHeight = leftHeight >=rightHeight ? leftHeight : rightHeight;
  
  return 1 + BiggestHeight;
}

void printTreeLevel(FILE *arq,int pos, int printLevel, int actualLevel){

  if(pos != -1){
    MaterialNode* materialNode = getNodeByPosition(arq,pos);

    if(actualLevel == printLevel){

      printf("%d ",materialNode->material->code);
    }else if(printLevel > actualLevel){

      //go to left if exists
      if(materialNode->left != -1){
        printTreeLevel(arq,materialNode->left,printLevel,actualLevel +1);
      }

      //go to right if exists
      if(materialNode->right != -1){
        printTreeLevel(arq,materialNode->right,printLevel,actualLevel +1);
      }
    }
  }

  return;
}

void pritTreeByLevel(){
  FILE *arq = fopen(file, "rb+");

  Head *header = readHead(arq);

  int treeHeight = calcTreeHeight(arq,header->pos_root);

  for(int i = 1; i <= treeHeight; i++){
    printTreeLevel(arq,header->pos_root,i,1);
    printf("\n");
  }

  fclose(arq);
}

void initPrintTreeMaterial(){
  FILE *arq = fopen(file, "rb+");

  Head *header = readHead(arq);

  if(header->pos_root == -1){
    printf("\n\n Não tem materiais cadastrados!! \n\n");
  }else{
    printTreeMaterials(arq,header->pos_root);
  }

  fclose(arq);
}

void editMaterialByCode(int position, MaterialNode *material){
  FILE *arq = fopen(file, "rb+");

  writeNodeOnFile(arq,material,position);

  fclose(arq);
}