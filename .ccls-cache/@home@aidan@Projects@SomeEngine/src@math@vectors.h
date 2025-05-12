#ifndef VECTORS_H
#define VECTORS_H

#include <math.h>

//// 2D Vector ////
struct vec2d_t { double x, y; };
struct vec2i_t { int    x, y; };
struct vec2f_t { float  x, y; };

#define vec2_add(a, b) {a.x + b.x, a.y + b.y}
#define vec2_sub(a, b) {a.x - b.x, a.y - b.y}
#define vec2_scale(a, s) {a.x * s, a.y * s}

#define vec2_dot(a, b) a.x * b.x + a.y * b.y
#define vec2_self_dot(a) vec2_dot(a, a)

#define vec2_dist(a, b) sqrt(vec2_self_dot(vec2_sub(a, b)))
#define vec2_sq_dist(a, b) vec2_self_dot(vec2_sub(a, b))


//// 3D Vector ////
struct vec3d_t { double x, y, z; };
struct vec3i_t { int    x, y, z; };
struct vec3f_t { float  x, y, z; };

#define vec3_add(a, b) {a.x + b.x, a.y + b.y, a.z + b.z}
#define vec3_sub(a, b) {a.x - b.x, a.y - b.y, a.z - b.z}
#define vec3_scale(a, s) {a.x * s, a.y * s, a.z * s}

#define vec3_dot(a, b) a.x * b.x + a.y * b.y + a.z * b.z
#define vec3_self_dot(a) vec3_dot(a, a)

#define vec3_dist(a, b) sqrt(vec3_self_dot(vec3_sub(a, b)))
#define vec3_sq_dist(a, b) vec3_self_dot(vec3_sub(a, b))


//// 4D Vector ////
struct vec4d_t { double x, y, z, w; };
struct vec4i_t { int    x, y, z, w; };
struct vec4f_t { float  x, y, z, w; };

#define vec4_add(a, b) {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}
#define vec4_sub(a, b) {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}
#define vec4_scale(a, s) {a.x * s, a.y * s, a.z * s, a.w * s}

#define vec4_dot(a, b) a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w 
#define vec4_self_dot(a) vec4_dot(a, a)

#define vec4_dist(a, b) sqrt(vec4_self_dot(vec4_sub(a, b)))
#define vec4_sq_dist(a, b) vec4_self_dot(vec4_sub(a, b))

#endif // !VECTORS_H
