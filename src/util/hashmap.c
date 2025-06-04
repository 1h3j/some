#include "hashmap.h"

#include "logging.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

uint64_t hash_fnv1a(uint64_t base, void* input, int len) {
  uint64_t h = base;

  for (int i=0; i<len; i++) {
    h ^= (uint64_t) *((uint8_t *)(input + i));
    h *= HASHMAP_FNV_PRIME;
  }

  return h;
}

HashMap *map_create(unsigned long size, int layers, unsigned long element_size) {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->layers = (HashMapLayer *)malloc(sizeof(HashMapLayer) * layers);

  map->hash_function = &hash_fnv1a;

  // Extra bytes is for storing the key's pointer
  element_size += sizeof(void*); 

  map->element_bytes = element_size;
  map->layers_size = layers;

  for (int l=0; l<layers; l++) {
    HashMapLayer *layer = map->layers + l;
    layer->buckets = malloc(element_size * size);

    layer->entries = size;

    memset(layer->buckets, 0, element_size * size);
  }

  return map;
}

void map_free(HashMap *map) {
  for (int l=0; l < map->layers_size; l++) {
    HashMapLayer *layer = map->layers + l;

    for (int e=0; e < layer->entries; e++) {
      // [ (void *)0x123... | value ]
      //  ^                   ^
      //  \                   ptr + sizeof(void*)
      //  ptr

      void *ptr = layer->buckets + e * map->element_bytes;

      void **key_ptr = (void **) ptr;

      if (*key_ptr != NULL) free(*key_ptr);
    }
  }

  free(map->layers);
  free(map);
}

void *map_at(HashMap *map, void *key, unsigned int key_len) {
  uint64_t seed = HASHMAP_FNV_BASE;

  void* ptr = NULL;

  for (unsigned int l=0; l < map->layers_size; l++) {
    HashMapLayer *layer = &(map->layers[l]);

    uint64_t hash = map->hash_function(seed, key, key_len);
    unsigned int index = (unsigned int)(hash % layer->entries);

    ptr = layer->buckets + (index * map->element_bytes);
    void **key_ptr_ptr = (void **) ptr;

    if (*key_ptr_ptr == NULL) {
      *key_ptr_ptr = malloc(key_len + sizeof(unsigned int));
      *(unsigned int *)(* key_ptr_ptr) = key_len;

      memcpy(*key_ptr_ptr + sizeof(unsigned int), 
             key, 
             key_len);

      break;
    }

    // For optimization, because memcmp is slow.
    if (*(char *)key == *(char *) (*key_ptr_ptr + sizeof(unsigned int))) {
      if (memcmp(key, *key_ptr_ptr + sizeof(unsigned int), key_len) == 0) {
        break;
      }
    }

    seed += HASHMAP_SALT;
    ptr = NULL;
  }

  if (ptr == NULL) {
#ifndef SOME_DISABLE_WARNS
    log_warn("Could not find a spot. (Maybe try increasing map size or layers?)");
#endif
    return ptr;
  }

  return ptr + sizeof(void *);
}

void map_set(HashMap *map, void *key, unsigned int key_len, void *data) {
  void *ptr = map_at(map, key, key_len);
  memcpy(ptr, data, map->element_bytes - sizeof(void *));
}

void* map_get(HashMap *map, void *key, unsigned int key_len) {
  uint64_t seed = HASHMAP_FNV_BASE;

  void* ptr = NULL;

  for (unsigned int l=0; l < map->layers_size; l++) {
    HashMapLayer *layer = &(map->layers[l]);

    uint64_t hash = map->hash_function(seed, key, key_len);
    unsigned int index = (unsigned int)(hash % layer->entries);

    ptr = layer->buckets + (index * map->element_bytes);
    void **key_ptr_ptr = (void **) ptr;

    if (*key_ptr_ptr == NULL) {
      return NULL;
    }

    // For optimization, because memcmp is slow.
    if (*(char *)key == *(char *) (*key_ptr_ptr + sizeof(unsigned int))) {
      if (memcmp(key, *key_ptr_ptr + sizeof(unsigned int), key_len) == 0) {
        break;
      }
    }

    seed += HASHMAP_SALT;
    ptr = NULL;
  }

  if (ptr == NULL) {
    return ptr;
  }

  return ptr + sizeof(void *);
}
