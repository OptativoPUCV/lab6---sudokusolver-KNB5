#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {

    for (int j = 0; j < 9; j++) 
    {
       int numF[10] = {0};
       for (int k = 0; k < 9; k++) 
       {
          if (n->sudo[j][k] != 0 && numF[n->sudo[j][k]] == 1) 
          {
             return 0; 
          } 
          else 
          {
             numF[n->sudo[j][k]] = 1;
          }
       }
    }
   
   for (int k = 0; k < 9; k++) 
   {
      int numC[10] = {0};
      for (int j = 0; j < 9; j++) 
      {
         if (n->sudo[j][k] != 0 && numC[n->sudo[j][k]] == 1) 
         {
            return 0; 
         }
         else 
         {
            numC[n->sudo[j][k]] = 1;
         }
      }
   }
   
   for (int j = 0; j < 9; j += 3) 
   {
      for (int k = 0; k < 9; k += 3) 
      {
         int numSM[10] = {0};
         for (int f = j; f < j + 3; f++) 
         {
            for (int c = k; c < k + 3; c++) 
            {
               if (n->sudo[f][c] != 0 && numSM[n->sudo[f][c]] == 1) 
               {
                  return 0;
               } 
               else 
               {
                  numSM[n->sudo[f][c]] = 1;
               }
            }
         }
      }
   }
   
   return 1;
}

List* get_adj_nodes(Node* n){
   List* adjList = createList();
   int num = 1;
   for(int i = 0; i < 9 && num < 10; i++)
      {
         if(n->sudo[0][2] == 0)
         {
            Node* newNode = copy(n);
            newNode->sudo[0][2] = num;
            pushBack(adjList, newNode);
            num++;
         }
      }
   return adjList;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/