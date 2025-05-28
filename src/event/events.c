#include "events.h"
#include <stdlib.h>

FuncPtrArr *callback_array_create() {
  FuncPtrArr *arr = (FuncPtrArr *)malloc(sizeof(FuncPtrArr));

  arr->ptrs = malloc(sizeof(void *));
  arr->size = 0;

  return arr;
}

void callback_array_append(void* ptr, FuncPtrArr *arr) {
  if (arr->size != 0) arr->ptrs = (void**)realloc(arr->ptrs, (arr->size + 1) * sizeof(void*));
  arr->ptrs[arr->size++] = ptr;
}

void create_event(FuncPtrArr *event_type, EventInfo *info) {
  for (int i = 0; i < event_type->size; i++) {
    if (event_type->ptrs[i] == NULL) continue;

    ((void (*)(EventInfo *))(event_type->ptrs[i]))(info);
  }
}

void callback_array_free(FuncPtrArr *arr) {
  free(arr->ptrs);
  free(arr);
}
