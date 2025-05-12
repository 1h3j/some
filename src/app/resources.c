#include "resources.h"
#include <stdlib.h>

resource_stack_t *resource_stack_create() {
  resource_stack_t *stack = (resource_stack_t *)malloc(sizeof(resource_stack_t));

  stack->size = 0;
  stack->arr  = malloc(sizeof(void*));

  return stack;
}

void resource_stack_append(resource_stack_t *stack, void* data, resource_type_e type) {
  if (stack->size != 0) stack->arr = (resource_t *)realloc(stack->arr, stack->size * sizeof(void*));
  stack->arr[stack->size++] = (resource_t){ type, data };
}
