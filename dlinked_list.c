#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Doubly linked list 




*/

struct node_s {
  int value;
  struct node_s* prev;
  struct node_s* next;
};

typedef struct node_s node_t;

struct list_s {
  node_t* first;
  node_t* last;
  size_t size;
};

typedef struct list_s list_t;


int main() {
  return 0;
}


