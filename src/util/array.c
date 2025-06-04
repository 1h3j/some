#include "array.h"

#include <stdlib.h>
#include <string.h>

Array *array_create_r(unsigned int initial_length, unsigned int element_size) {
  Array *array = (Array *) malloc(sizeof(Array));
  
  array->array = malloc(initial_length * element_size);
  array->element_size = element_size;
  array->allocated_length = initial_length;
  array->content_length = 0;

  return array;
}

void array_free(Array *array) {
  free(array->array);
  free(array);
}

void array_append_back(Array *array, void* ptr) {
  if (array->allocated_length == array->content_length++) {
    array->array = reallocarray(array->array, ++array->allocated_length, array->element_size);
  }
  
  memcpy(array->array + array->content_length, ptr, array->element_size);
}
