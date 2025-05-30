#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "math/vectors.h"

typedef struct {
  Vec3f points[3];
  Vec4f color;
} PrimitiveTriangle;

typedef struct {
  Vec3f points[4];
  Vec4f color;
} PrimitiveQuad;

typedef struct {
  Vec3f points[2];
  Vec4f color;
} PrimitiveLine;

typedef struct {
  unsigned int vao;
  unsigned int pos_vbo;
  unsigned int col_vbo;
  PrimitiveTriangle info;
} ObjectTriangle;

typedef struct {
  unsigned int vao;
  unsigned int pos_vbo;
  unsigned int col_vbo;
  PrimitiveQuad info;
} ObjectQuad;

typedef struct {
  unsigned int vao;
  unsigned int pos_vbo;
  unsigned int col_vbo;
  PrimitiveLine info;
} ObjectLine;

// Triangle //

/**
 * Updates information in a triangle object
 *
 * @param tri Triangle object
*/
void triangle_update(ObjectTriangle *tri);

/**
 * Allocate a triangle object.
 *
 * @param triangle Information about the triangle
 * @return Pointer to the allocated triangle.
*/
ObjectTriangle *triangle_create(PrimitiveTriangle triangle);

/**
 * Draws a triangle
 *
 * @param tri Triangle object.
*/
void triangle_draw(ObjectTriangle *tri);

/**
 * Free resources used
 *
 * @param tri Triangle object
*/
void triangle_destroy(ObjectTriangle *tri);

// Quad //

/**
 * Updates information in a quad object
 *
 * @param quad Qaud object
*/
void quad_update(ObjectQuad *quad);

/**
 * Allocate a quad object.
 *
 * @param quad Information about the quad
 * @return Pointer to the allocated quad.
*/
ObjectQuad *quad_create(PrimitiveQuad quad);

/**
 * Draws a quad
 *
 * @param quad Quad object.
*/
void quad_draw(ObjectQuad *quad);

/**
 * Free resources used
 *
 * @param quad Quad object
*/
void quad_destroy(ObjectQuad *quad);

// Line //

/**
 * Updates information in a line object
 *
 * @param line Line object
*/
void line_update(ObjectLine *line);

/**
 * Allocate a line object.
 *
 * @param line Information about the line
 * @return Pointer to the allocated line.
*/
ObjectLine *line_create(PrimitiveLine line);

/**
 * Draws a line
 *
 * @param line Line object.
*/
void line_draw(ObjectLine *line);

/**
 * Free resources used
 *
 * @param line Line object.
*/
void line_destroy(ObjectLine *line);

#endif // PRIMITIVES_H
