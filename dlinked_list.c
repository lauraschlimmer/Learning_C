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

void init(list_t* list) {
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
}

node_t* create_node() {
  node_t* node = malloc(sizeof(node_t));
  memset(node, 0, sizeof(node_t));
  return node;
}

void insert_first(list_t* list, int value) {
  node_t* node = create_node();
  node->value = value;
  if (list->first == NULL) {
    list->first = node;
    list->last = node;
    node->prev = NULL;
    node->next = NULL;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
    node->prev = NULL;
  }
  list->size++;
}

void remove_first(list_t* list) {
  if (list->first == NULL) {
    return;
  }
  if (list->first == list->last) {
    free(list->first);
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
  } else {
    node_t* new_first = list->first->next;
    free(list->first);
    list->first = new_first;
    list->first->prev = NULL;
    list->size--;
  }

}

/*
* Add a new node at the end of the list
*/
void add(list_t* list, int value) {
  node_t* node = create_node();
  node->value = value;

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
    node->prev = NULL;
    node->next = NULL;
  } else {
    node->prev = list->last;
    list->last->next = node;
    list->last = node;
    node->next = NULL;
  }

  list->size++;
}

void remove_last(list_t* list) {
  if (list->first == NULL) {
    return;
  }

  if (list->first == list->last) {
    free(list->first);
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
  } else {
    node_t* new_last = list->last->prev;
    free(list->last);
    list->last = new_last;
    list->last->next = NULL;
    list->size--;
  }
}

/*node_t* get(list_t* list, unsigned int index) {
  
}
*/
int sum(list_t* list) {
  int sum = 0;
  for (node_t* node = list->first; node != NULL; node = node->next) {
    sum += node->value;
  }
  return sum;
}

void print_list_forwards(list_t* list) {
  for (node_t* node = list->first; node != NULL; node = node->next) {
    printf("value: %i\n", node->value);
  }
}

void print_list_backwards(list_t* list) {
  for (node_t* node = list->last; node != NULL; node = node->prev) {
    printf("value: %i\n", node->value);
  }
}




int main() {
  list_t list;
  init(&list);
  insert_first(&list, 5);
  print_list_forwards(&list);
  add(&list, 10);
  int sum_of_list = sum(&list);
  printf("sum: %i\n", sum_of_list);
  print_list_backwards(&list);
  return 0;
}


