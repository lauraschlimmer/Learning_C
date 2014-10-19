#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* safe_malloc(size_t size) {
  void* ptr = malloc(size);
  if (ptr == NULL) {
    abort();
  }
  return ptr;
}

struct node_s {
  int data;
  struct node_s* next;
};

typedef struct node_s node_t;

struct list_s {
  node_t* first;
  unsigned int size;
};

typedef struct list_s list_t;

void init(list_t* list) {
  list->first = NULL;
}

node_t* create_node() {
  node_t* node = safe_malloc(sizeof(node_t));
  memset(node, 0, sizeof(node_t));
  return node;
}

/*
* Insert a node at the beginning of the list
*/
void insert_first(list_t* list, int value) {
  node_t* node = create_node();
  node->data = value;
  node->next = list->first;
  list->first = node;
  list->size++;
}

void remove_first(list_t* list) {
  if (list->first == NULL) {
    return;
  }

  node_t* new_first = list->first->next;
  free(list->first);
  list->first = new_first;
  list->size--;
}


node_t* get_last(list_t* list) {
  if (list->first == NULL) {
    return NULL;
  }
  node_t* node;
  for (node = list->first; node->next != NULL; node = node->next) {}
  return node;
}

/*
* Add a node at the end of the list
*/
void add(list_t* list, int value) {
  node_t* node = create_node();
  node->data = value;
  if (list->first != NULL) {
    node_t* old_last = get_last(list);
    old_last->next = node;
  } else {
    list->first = node;
  }
  list->size--;
}

/*
* Remove the last node
*/
void remove_last(list_t* list) {
  if (list->first == NULL) {
    return;
  }
  /*
  * or next_to_last = get(list->size-2)
  */
  node_t* last = list->first;
  node_t* next_to_last;
  while (last->next != NULL) {
    next_to_last = last;
    last = last->next;
  }
  next_to_last->next = NULL;
  free(last);

}

/*
* Get a node at a given index
*/
node_t* get(list_t* list, unsigned int index) {
  if ((list->first == NULL) || (index+1 > list->size)) {
    return NULL;
  }
  unsigned int count = 0;
  node_t* node = list->first;
  while ((count < index) && (node != NULL)) {
    node = node->next;
    count++;
  }
  return node;
}

/*
* Return the sum of all data elements in the list
*/
int sum(list_t* list) {
  int sum = 0;
  for (node_t* node = list->first; node != NULL; node = node->next) {
    sum += node->data;
  }
  return sum;
}

void print_list(list_t* list) {
  for (node_t* node = list->first; node != NULL; node = node->next) {
    printf("int data %i \n", node->data);
  }
}


int main() {
  list_t list;
  init(&list);
  remove_first(&list);
  insert_first(&list, 10);
  add(&list, 5);
  print_list(&list);
  return 0;
}
