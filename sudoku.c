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

int is_valid(Node* n){

   int j, k, f, c;
   
    for (j = 0; j < 9; j++) 
    {
       int numF[10] = {0};
       for (k = 0; k < 9; k++) 
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
   
   for (k = 0; k < 9; k++) 
   {
      int numC[10] = {0};
      for (j = 0; j < 9; j++) 
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
   
   for (j = 0; j < 9; j += 3) 
   {
      for (k = 0; k < 9; k += 3) 
      {
         int numSM[10] = {0};
         for (f = j; f < j + 3; f++) 
         {
            for (c = k; c < k + 3; c++) 
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
   int create = 0;
   
   for(int j = 0; j < 9; j++)
   {
      for(int k = 0; k < 9; k++)
      {
         if(n->sudo[j][k] == 0)
         {
            create = 1;
            for(int i = 0; i < 9; i++, num++)
            {
               Node* newNode = copy(n);
               newNode->sudo[j][k] = num;
               if(is_valid(newNode) == 1)
               {
                  pushBack(adjList, newNode);
               }
            }
         }
         if(create) break;
      }
      if(create) break;
   }   
   return adjList;
}


int is_final(Node* n){
   for(int j = 0; j < 9; j++)
   {
      for(int k = 0; k < 9; k++)
      {
         if(n->sudo[j][k] == 0)
         {
            return 0;
         }
      }
   }
   
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* pilaNodos = createStack();
   push(pilaNodos, initial);

   while(top(pilaNodos) != NULL)
   {
      Node* firstNode = top(pilaNodos); cont++;
      pop(pilaNodos);
      if(is_final(firstNode))
      {
         return firstNode;
      }
      List* listaAdj = get_adj_nodes(firstNode);
      Node* aux = first(listaAdj);
      
      for(int i = 0; i < get_size(listaAdj); i++)
      {
         push(pilaNodos, aux);
         aux = next(listaAdj);
      }
      free(firstNode);
   }
   free(pilaNodos);
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