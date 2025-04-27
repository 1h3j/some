#ifndef VECTORS_H
#define VECTORS_H

struct vec3d_t {
  double x, y, z;
};

struct vec3i_t {
  int x, y, z;
};

struct vec3f_t {
  float x, y, z;
};
struct vec4f_t {
  float x, y, z, w;
};

struct vec2f_t {
  float x, y;
};

struct vec3d_t vec3d_add(struct vec3d_t a, struct vec3d_t b);
struct vec3d_t vec3d_sub(struct vec3d_t a, struct vec3d_t b);
struct vec3d_t vec3d_mul_sc(struct vec3d_t a, double b);
struct vec3d_t vec3d_normalize(struct vec3d_t a);

struct vec3f_t vec3f_add(struct vec3f_t a, struct vec3f_t b);
struct vec3f_t vec3f_sub(struct vec3f_t a, struct vec3f_t b);
struct vec3f_t vec3f_mul_sc(struct vec3f_t a, double b);
struct vec3f_t vec3f_normalize(struct vec3f_t a);

struct vec3i_t vec3i_add(struct vec3i_t a, struct vec3i_t b);
struct vec3i_t vec3i_sub(struct vec3i_t a, struct vec3i_t b);
struct vec3f_t vec3d_to_vec3f(struct vec3d_t a);

#endif // !VECTORS_H
