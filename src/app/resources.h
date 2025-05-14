#ifndef RESOURCES_H
#define RESOURCES_H

typedef enum {
  RESOURCE_TYPE_SHADER = 0,
  RESOURCE_TYPE_IMAGE = 1,
  RESOURCE_TYPE_TEXT = 2,
} resource_type_e;

typedef struct {
  resource_type_e type;
  void *data;
} resource_t;

typedef struct {
  resource_t *arr;
  unsigned long size;
} resource_stack_t;

/**
 * Allocate a new resource stack
 *
 * @return Pointer to a resource stack
*/
resource_stack_t *resource_stack_create();

/**
 * Append a new resource to the resource stack
 * 
 * @param stack Pointer to a resource stack
 * @param data  Raw data or can be pointer to a variable.
 * @param type  The type of resource. This is only used for hinting..
*/
void resource_stack_append(resource_stack_t *stack, void* data, resource_type_e type);

#endif // RESOURCES_H
