#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stdbool.h>

#if !defined(HASHMAP_DEFAULT_INITIAL_ELEMENTS)
#define HASHMAP_DEFAULT_INITIAL_ELEMENTS 256
#endif // HASHMAP_DEFAULT_INITIAL_ELEMENTS

#if !defined(HASHMAP_DEFAULT_INITIAL_LAYERS)
#define HASHMAP_DEFAULT_INITIAL_LAYERS   2
#endif // HASHMAP_DEFAULT_INITIAL_LAYERS

#if !defined(HASHMAP_FNV_BASE)
#define HASHMAP_FNV_BASE  0xcbf29ce484222325
#endif // HASHMAP_FNV_BASE

#if !defined(HASHMAP_FNV_PRIME)
#define HASHMAP_FNV_PRIME 0x100000001b3
#endif // HASHMAP_FNV_PRIME

#if !defined(HASHMAP_SALT)
#define HASHMAP_SALT      0x01
#endif // HASHMAP_SALT

#define HASHMAP_VACANT   0
#define HASHMAP_OCCUPIED 1

/*          | Key (as pointer) | Data  |
 *          |------------------|-------|
 * Layer #1=[ (void *)0x123... | value ]   Layer #2=[       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *          [       NULL       | value ]        ___ [ (void *)0xabc... | value ]
 *          [       NULL       | value ]       /    [       NULL       | value ]
 *          [       NULL       | value ] Added salt [       NULL       | value ]
 *          [ (void *)0x321... | value ] ____/      [       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *          [ (void *)0x1a4... | value ]            [       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *          [       NULL       | value ]            [       NULL       | value ]
 *
 * If the key pointer is NULL, that means it's unoccupied, the key used to access
 * the entry is allocated somewhere and pointer is stored next to data. If it is
 * not NULL, then it will check if the key given is exactly the same as the key on
 * the table. If it's the same, then it will return like normal. But if it's
 * already occupied or a collision, then a salt will be added to the seed for the
 * next layer. And this repeats until it finds the exact key.
 *
 * Yes, the number of layers can be infinite, this is designed as a security measure.
 * It prevents any collisions at all even if it's already got to 5 layers (not that
 * it would happen, but certainly it *may*).
 *
 * 2 Layers are the recommended amount for a very large hash table, but it might
 * need 3 layers if the hashing algorithm provided is either bad and collides all 
 * the time, the table is small, or the data takes up 90% of the table, or even
 * all of the above.
 *
 * ======= Structures that cannot be represented in C structs =======
 *
 * These structures can't be represented in the standard way of using C structs,
 * because they're dynamically sized, and it's also packed.
 *
 * Bucket -> [ KEYPOINTER, s:sizeof(void *) | Value, s:dynamic ]
 * Key    -> [ KEYLEN, s:sizeof(unsigned int) | KEYDATA, s:dynamic ]
*/

/***/

typedef struct {
  void* buckets;
  unsigned long entries;
} layer_t;

typedef struct {
  layer_t *layers;
  unsigned int layers_size;

  unsigned int element_bytes;

  uint64_t (*hash_function)(uint64_t, void *, int);
} map_t;

/**
 * Implementation of FNV-1a hashing function
 *
 * @param base  The "base" or seed of the funciton.
 * @param prime Changes how the function behaves.
 * @param data  Data as a pointer.
 * @param len   Length of data in bytes.
*/
uint64_t hash_fnv1a(uint64_t base, void* input, int len);

/**
 * Create a hash map object
 *
 * @param size         Size of an element
 * @param layers       Number of layers. Recommended amount is 2
 * @param element_size Size of an element in bytes
*/
map_t *map_create(unsigned long size, int layers, unsigned long element_size);

/**
 * Frees a map object.
 *
 * @param map Pointer to a hash map
*/
void map_free(map_t *map);

/**
 * Gives you a pointer to the location of what the key represents.
 *
 * @param map     Pointer to a hashmap.
 * @param key     Pointer to the key data.
 * @param key_len Size of the key data in bytes.
 *
 * @return Pointer assigned to the key in the map.
*/
void *map_at(map_t *map, void* key, unsigned int key_len);

/**
 * Sets the value at a given key.
 *
 * @param map     Pointer to a hashmap.
 * @param key     Pointer to the key data.
 * @param key_len Size of the key data in bytes.
 * @param data    Pointer containing the actual data.
*/
void map_set(map_t *map, void* key, unsigned int key_len, void* data);

/**
 * Get the pointer of value without creating an entry like `map_at`
 *
 * @param map     Pointer to a hashmap.
 * @param key     Pointer to the key data.
 * @param key_len Size of the key data in bytes.
*/
void* map_get(map_t *map, void *key, unsigned int key_len);

#define d_map_at(map, key) map_at(map, &key, sizeof(key))
#define d_map_set(map, key, data) map_set(map, &key, sizeof(key), data)
#define d_map_check(map, key) map_check(map, &key, sizeof(key))

#endif // HASHMAP_H
