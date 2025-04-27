#ifndef WOLRD_H
#define WOLRD_H

#include "math/vectors.h"
#include <stdbool.h>
#include <stdlib.h>

struct world_t {
  int radius;
  unsigned char *data;
};

struct world_t *create_world(int radius) {
  struct world_t *world = (struct world_t *)malloc(sizeof(struct world_t));
  world->data = (unsigned char *)malloc(radius * radius * radius * 4);
  world->radius = radius;

  return world;
}

void free_world(struct world_t *world) {
  free(world->data);
  free(world);
}

bool world_get(struct world_t *world, struct vec3i_t pos) {
  // clang-format off
  // The Great clang-format Barrier (Obviously not a reference to touhou) 
  if (abs(pos.x) > world->radius || 
      abs(pos.y) > world->radius ||
      abs(pos.z) > world->radius) {
    return false;
  }

  pos = vec3i_add(pos, (struct vec3i_t){world->radius, world->radius, world->radius});

  return world->data[ pos.x + 
                      pos.y * world->radius * 2 +
                      pos.z * world->radius * world->radius * 4 ];
  // clang-format on
}

void world_set(struct world_t *world, struct vec3i_t pos, unsigned char value) {
  // clang-format off
  if (abs(pos.x) > world->radius || 
      abs(pos.y) > world->radius ||
      abs(pos.z) > world->radius) {
    return;
  }

  pos = vec3i_add(pos, (struct vec3i_t){world->radius, world->radius, world->radius});

  world->data[pos.x + 
              pos.y * world->radius * 2 +
              pos.z * world->radius * world->radius * 4 ] = value;
  // clang-format on
}

#endif // !WOLRD_H
