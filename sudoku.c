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
  for (int i = 0; i < 9; i++) {
    int fil[10] = {0};
    int col[10] = {0};
    int sub[10] = {0};
    
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] != 0) {
        if (fil[n->sudo[i][j]] == 0) {
          fil[n->sudo[i][j]] = 1;
        }
        else {
          return 0;
        }
      }

      if (n->sudo[j][i] != 0) {
        if (col[n->sudo[j][i]] == 0) {
          col[n->sudo[j][i]] = 1;
        }
        else {
          return 0;
        }
      }

      int f=3*(i/3) + (j/3) ;
      int c=3*(i%3) + (j%3) ;
      if (n->sudo[f][c] != 0) {
        if (sub[n->sudo[f][c]] == 0) {
          sub[n->sudo[f][c]] = 1;
        }
        else {
          return 0;
        }
      }
      
   }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (n->sudo[i][j] == 0) {
          for (int k = 1; k < 10; k++) {
            Node *aux = createNode();
            aux = copy(n);
            aux->sudo[i][j] = k;
            if (is_valid(aux))
              pushBack(list, aux);
          }
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0)
        return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *pila = createStack();
  Node *aux;
  push(pila, initial);
  while (1) {
    aux = (Node*) top(pila);
    if (!aux) break;
    pop(pila);
    (*cont)++;
    if (is_final(aux)) 
      return aux;
    List *adj = get_adj_nodes(aux);
    for (int i = 0; i < get_size(adj); i++) {
      Node *temp;
      if (i == 0)
        temp = first(adj);
      else 
        temp = next(adj);
      push(pila, temp);
    }
    free(aux);
    
  }
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