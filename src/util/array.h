#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  void *array;
  unsigned int allocated_length, content_length, element_size;
} array_t;

/**
 * Allocate an array object
 *
 * @param initial_length Allocate this much elements.
 * @param element_size   Size of an element in bytes.
 * @return A pointer to an array object
*/
array_t *array_create_r(unsigned int initial_length, unsigned int element_size);

/**
 * Free the resources used by the array.
 *
 * @param array Pointer to an array object
*/
void array_free(array_t *array);

/**
 * Append an object to the array.
 *
 * @param array Pointer to array object.
 * @param ptr   Pointer to data/object.
*/
void array_append_back(array_t *array, void* ptr);

/**
 * Macro version of array_create_r
 *
 * @param type   Type of object to use.
 * @param length Number of elements to start with.
*/
#define array_create(type, length) array_create_r(length, sizeof(type))

/**
 * Get the element at a location
 *
 * @param array    Pointer to an array object
 * @param type     Type of object
 * @param location Index of element
*/
#define array_at(arr, location) ((arr)->array + ((location) * (arr)->element_size))

#endif // ARRAY_H
