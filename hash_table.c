#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct slot_s {
  int key;
  int value;
  int used;
};

struct hashmap_s {
  size_t size;
  struct slot_s* slots;
};

void init(struct hashmap_s* map) {
  map->size = 3;
  map->slots = malloc(sizeof(struct slot_s) * map->size);
  memset(map->slots, 0, sizeof(struct slot_s) * map->size);
}

void init_resized_map(struct hashmap_s* map, size_t size) {
  map->size = size;
  map->slots = malloc(sizeof(struct slot_s) * size);
  memset(map->slots, 0, sizeof(struct slot_s) * size);
}


struct slot_s* get_slot(struct hashmap_s* map, int slot_key ) {
  int key = slot_key;
  int pos = key % map->size;
  for (int counter = 0; counter < map->size; counter++) {
    if (map->slots[pos].used == 0 || map->slots[pos].key == slot_key) {
      return map->slots + pos;
    }
    pos = pos + 1 % map->size;
  }
  return NULL;
}


void copy(struct hashmap_s* old_map, struct hashmap_s* new_map) {
  int n;
  for (n = 0; n < old_map->size; n++) {
    if (old_map->slots[n].used == 1) {
      struct slot_s* slot = get_slot(new_map, old_map->slots[n].key);
      slot->used = 1;
      slot->key = old_map->slots[n].key;
      slot->value = old_map->slots[n].value;
    }
  }
}

void resize(struct hashmap_s* old_map) {
  struct hashmap_s new_map;
  init_resized_map(&new_map, old_map->size*2);
  copy(old_map, &new_map);
  free(old_map->slots);
  old_map = &new_map;
}


int get(struct hashmap_s* map, int key) {
  struct slot_s* slot = get_slot(map, key);
  if (slot->used == 0) {
    return 0;
  }
  return slot->value;
}

float num_entries = 0.0;

void set(struct hashmap_s* map, int key, int value) {
  struct slot_s* slot = get_slot(map, key);
  if (slot->used == 0) {
    slot->used = 1;
    num_entries++;
  }
  slot->key = key;
  slot->value = value;
  if (num_entries / (float)map->size > 0.5) {
    resize(map);
  }
}

int main() {
  struct hashmap_s map;
  init(&map);
  int val = get(&map, 5);
  printf("value %i\n ", val);
  set(&map, 11, 11);
  set(&map, 22, 22);
  set(&map, 10, 12);
  return 0;
};

