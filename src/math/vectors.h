#ifndef VECTORS_H
#define VECTORS_H

#include <math.h>


//// 2D Vector ////
typedef struct { double x, y; } Vec2d; 
typedef struct { int    x, y; } Vec2i; 
typedef struct { float  x, y; } Vec2f; 

#define vec2_add(a, b) {a.x + b.x, a.y + b.y}
#define vec2_sub(a, b) {a.x - b.x, a.y - b.y}
#define vec2_scale(a, s) {a.x * s, a.y * s}

#define vec2_dot(a, b) a.x * b.x + a.y * b.y
#define vec2_self_dot(a) vec2_dot(a, a)

#define vec2_dist(a, b) sqrt(vec2_self_dot(vec2_sub(a, b)))
#define vec2_sq_dist(a, b) vec2_self_dot(vec2_sub(a, b))


//// 3D Vector ////
typedef struct { double x, y, z; } Vec3d;
typedef struct { int    x, y, z; } Vec3i;
typedef struct { float  x, y, z; } Vec3f;

#define vec3_add(type, a, b) (type){a.x + b.x, a.y + b.y, a.z + b.z}
#define vec3_sub(type, a, b) (type){a.x - b.x, a.y - b.y, a.z - b.z}
#define vec3_scale(type, a, s) (type){a.x * s, a.y * s, a.z * s}

#define vec3_dot(a, b) a.x * b.x + a.y * b.y + a.z * b.z
#define vec3_self_dot(a) vec3_dot(a, a)

#define vec3_dist(a, b) sqrt(vec3_self_dot(vec3_sub(a, b)))
#define vec3_sq_dist(a, b) vec3_self_dot(vec3_sub(a, b))


//// 4D Vector ////
typedef struct { double x, y, z, w; } Vec4d;
typedef struct { int    x, y, z, w; } Vec4i;
typedef struct { float  x, y, z, w; } Vec4f;

#define vec4_add(a, b) {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}
#define vec4_sub(a, b) {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}
#define vec4_scale(a, s) {a.x * s, a.y * s, a.z * s, a.w * s}

#define vec4_dot(a, b) a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w 
#define vec4_self_dot(a) vec4_dot(a, a)

#define vec4_dist(a, b) sqrt(vec4_self_dot(vec4_sub(a, b)))
#define vec4_sq_dist(a, b) vec4_self_dot(vec4_sub(a, b))

#endif // !VECTORS_H
