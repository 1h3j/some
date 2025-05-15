#include "array.h"

#include <stdlib.h>
#include <string.h>

array_t *array_create_r(unsigned int initial_length, unsigned int element_size) {
  array_t *array = (array_t *) malloc(sizeof(array_t));
  
  array->array = malloc(initial_length * element_size);
  array->element_size = element_size;
  array->allocated_length = initial_length;
  array->content_length = 0;

  return array;
}

void array_free(array_t *array) {
  free(array->array);
  free(array);
}

void array_append_back(array_t *array, void* ptr) {
  if (array->allocated_length == array->content_length++) {
    array->array = reallocarray(array->array, ++array->allocated_length, array->element_size);
  }
  
  memcpy(&array->array[array->content_length - 1], ptr, array->element_size);
}
