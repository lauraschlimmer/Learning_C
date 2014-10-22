#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct slot_s {
  int key;
  int value;
  int used;
};

typedef struct slot_s slot_t;

struct hashmap_s {
  size_t size;
  slot_t* slots;
};

typedef struct hashmap_s hashmap_t;

void init(hashmap_t* map, unsigned int size) {
  map->size = size;
  map->slots = malloc(sizeof(slot_t) * map->size);
  memset(map->slots, 0, sizeof(slot_t) * map->size);
}

void init_resized_map(hashmap_t* map, size_t size) {
  map->size = size;
  map->slots = malloc(sizeof(slot_t) * size);
  memset(map->slots, 0, sizeof(slot_t) * size);
}


struct slot_s* get_slot(hashmap_t* map, int slot_key ) {
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


void copy(hashmap_t* old_map, hashmap_t* new_map) {
  int n;
  for (n = 0; n < old_map->size; n++) {
    if (old_map->slots[n].used == 1) {
      slot_t* slot = get_slot(new_map, old_map->slots[n].key);
      slot->used = 1;
      slot->key = old_map->slots[n].key;
      slot->value = old_map->slots[n].value;
    }
  }
}

void resize(hashmap_t* old_map) {
  hashmap_t new_map;
  init_resized_map(&new_map, old_map->size*2);
  copy(old_map, &new_map);
  free(old_map->slots);
  old_map->size = old_map->size * 2;
  old_map->slots = new_map.slots;
}


int get(hashmap_t* map, int key) {
  slot_t* slot = get_slot(map, key);
  if (slot->used == 0) {
    return 0;
  }
  return slot->value;
}

float num_entries = 0.0;

void set(hashmap_t* map, int key, int value) {
  slot_t* slot = get_slot(map, key);
  if (slot->used == 0) {
    slot->used = 1;
    num_entries++;
  }
  slot->key = key;
  slot->value = value;
  if (num_entries / (float)map->size > 0.7) {
    resize(map);
  }
}

int main() {
  hashmap_t map;
  init(&map, 5);
  int val = get(&map, 5);
  set(&map, 11, 11);
  set(&map, 22, 22);
  set(&map, 10, 12);
  set(&map, 2, 3);
  set(&map, 4, 9);
  return 0;
};

