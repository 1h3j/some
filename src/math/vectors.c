#include "math/vectors.h"
#include <math.h>

// Double
struct vec3d_t vec3d_add(struct vec3d_t a, struct vec3d_t b) {
  return (struct vec3d_t){a.x + b.x, a.y + b.y, a.z + b.z};
}

struct vec3d_t vec3d_sub(struct vec3d_t a, struct vec3d_t b) {
  return (struct vec3d_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

struct vec3d_t vec3d_mul_sc(struct vec3d_t a, double b) {
  return (struct vec3d_t){a.x * b, a.y * b, a.z * b};
}

struct vec3d_t vec3d_normalize(struct vec3d_t a) {
  double length = 1.0l / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);

  if (length == 0)
    return (struct vec3d_t){0, 0, 0};
  return vec3d_mul_sc(a, length);
}

// Float
struct vec3f_t vec3f_add(struct vec3f_t a, struct vec3f_t b) {
  return (struct vec3f_t){a.x + b.x, a.y + b.y, a.z + b.z};
}

struct vec3f_t vec3f_sub(struct vec3f_t a, struct vec3f_t b) {
  return (struct vec3f_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

struct vec3f_t vec3f_mul_sc(struct vec3f_t a, double b) {
  return (struct vec3f_t){a.x * b, a.y * b, a.z * b};
}

struct vec3f_t vec3f_normalize(struct vec3f_t a) {
  double length = 1.0l / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);

  if (length == 0)
    return (struct vec3f_t){0, 0, 0};
  return vec3f_mul_sc(a, length);
}

// Int
struct vec3i_t vec3i_add(struct vec3i_t a, struct vec3i_t b) {
  return (struct vec3i_t){a.x + b.x, a.y + b.y, a.z + b.z};
}

struct vec3i_t vec3i_sub(struct vec3i_t a, struct vec3i_t b) {
  return (struct vec3i_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

struct vec3f_t vec3d_to_vec3f(struct vec3d_t a) {
  return (struct vec3f_t){(float)a.x, (float)a.y, (float)a.z};
}
