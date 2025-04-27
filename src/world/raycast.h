#ifndef RAYCAST_H
#define RAYCAST_H

#include "math/vectors.h"
#include "world/world.h"

#include <math.h>

#ifndef RAYCAST_MAX_STEPS
#define RAYCAST_MAX_STEPS 200
#endif // !RAYCAST_MAX_STEPS

enum which_side_e { SIDE_X, SIDE_Y, SIDE_Z };
// DDA Implementation
bool world_raycast(struct world_t *world, struct vec3d_t start,
                   struct vec3d_t end, struct vec3d_t *out) {
  struct vec3i_t step,
      map_pos = (struct vec3i_t){(int)start.x, (int)start.y, (int)start.z};

  enum which_side_e side;

  struct vec3d_t direction = vec3d_normalize(vec3d_sub(end, start));

  struct vec3d_t delta_dist =
      (struct vec3d_t){(direction.x == 0) ? 1e30 : fabs(1.0 / direction.x),
                       (direction.y == 0) ? 1e30 : fabs(1.0 / direction.y),
                       (direction.z == 0) ? 1e30 : fabs(1.0 / direction.z)};

  struct vec3d_t side_dist;

  if (direction.x < 0) {
    step.x = -1;
    side_dist.x = (start.x - map_pos.x) * delta_dist.x;
  } else {
    step.x = 1;
    side_dist.x = (map_pos.x + 1.0 - start.x) * delta_dist.x;
  }

  if (direction.y < 0) {
    step.y = -1;
    side_dist.y = (start.y - map_pos.x) * delta_dist.y;
  } else {
    step.y = 1;
    side_dist.y = (map_pos.y + 1.0 - start.y) * delta_dist.y;
  }

  if (direction.z < 0) {
    step.z = -1;
    side_dist.z = (start.z - map_pos.z) * delta_dist.z;
  } else {
    step.z = 1;
    side_dist.z = (map_pos.z + 1.0 - start.z) * delta_dist.z;
  }

  *out = direction;

  for (int i = 0; i < RAYCAST_MAX_STEPS; i++) {
    if (side_dist.x > side_dist.y) {
      side_dist.y += delta_dist.y;
      map_pos.y += step.y;
      side = SIDE_Y;
    } else if (side_dist.y > side_dist.z) {
      side_dist.z += delta_dist.z;
      map_pos.z += step.z;
      side = SIDE_Z;
    } else {
      side_dist.x += delta_dist.x;
      map_pos.x += step.x;
      side = SIDE_X;
    }

    // clang-format off
    if (map_pos.x >= world->radius) break;
    if (map_pos.y >= world->radius) break;
    if (map_pos.z >= world->radius) break;
    // clang-format on

    if (world_get(world, map_pos)) {
      if (side == SIDE_X) {
        *out = vec3d_mul_sc(*out, (double)side_dist.x - delta_dist.x);
      } else if (side == SIDE_Y) {
        *out = vec3d_mul_sc(*out, (double)side_dist.y - delta_dist.y);
      } else {
        *out = vec3d_mul_sc(*out, (double)side_dist.z - delta_dist.z);
      }

      return true;
    }
  }

  return false;
}

#endif // !RAYCAST_H
