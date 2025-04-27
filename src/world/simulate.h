#ifndef SIMULATE_H
#define SIMULATE_H

#ifndef SIM_MAX_STEPS
#define SIM_MAX_STEPS 100
#endif

#include "math/vectors.h"

struct obj_info_t {
  double power, gravity, drag;
};

// TODO: FINISH WORKING ON THIS
void simulateThrow(struct vec3d_t position, struct vec3d_t direction,
                   struct obj_info_t obj_info, struct vec3d_t **out) {

  struct vec3d_t current_vel = {direction.x, direction.y, direction.z};
  current_vel = vec3d_mul_sc(current_vel, obj_info.power);

  for (int i = 0; i < SIM_MAX_STEPS; i++) {
    position = vec3d_add(position, current_vel);
    current_vel.y -= obj_info.gravity;
    current_vel = vec3d_mul_sc(current_vel, obj_info.drag);

    // finish here
  }
}

#endif // !SIMULATE_H
