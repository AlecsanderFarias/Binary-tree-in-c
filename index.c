#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menuControl.h"
#include "tree.h"


//command to build:
//gcc index.c fileControl.c material.c menuControl.c tree.c 


int main(){
  initTree();
  
  int option = -1;

  printf("Bem vindo ao Sitemas de gestão de produtos em C !!\n");

  while(option != 9){
    option = selectMenuOption();
    
    switch(option){

      case 1:{
        menuOption1();
        break;
      }
      
      case 2:{
        menuOption2();
        break;
      }
      
      case 3:{
        menuOption3();
        break;
      }
      
      case 4:{
        menuOption4();
        break;
      }
       
      case 5:{
        menuOption5();
        break;
      }
      
      case 6:{
        menuOption6();
        break;
      }
      
      case 7:{
        menuOption7();
        break;
      }
      
      case 8:{
        menuOption8();
        break;
      } 
      
      case 9:{
        break;
      }

      default: {
        break;
      }

    }
  
  }


}