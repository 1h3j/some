#include "primitives.h"
#include <glad/glad.h>
#include <stdlib.h>
#include <stdbool.h>

ObjectTriangle *triangle_create(PrimitiveTriangle triangle) {
  ObjectTriangle *t = (ObjectTriangle *) malloc(sizeof(ObjectTriangle));

  t->info = triangle;

  glGenVertexArrays(1, &t->vao);
  glGenBuffers(1, &t->pos_vbo);
  glGenBuffers(1, &t->col_vbo);

  glBindVertexArray(t->vao);

  glBindBuffer(GL_ARRAY_BUFFER, t->pos_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(t->info.points), t->info.points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vec3f), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, t->col_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4f), &t->info.color, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vec4f), (void *)0);
  glVertexAttribDivisor(1, 1);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return t;
}

void triangle_destroy(ObjectTriangle *tri) {
  glDeleteBuffers(1, &tri->pos_vbo);
  glDeleteBuffers(1, &tri->col_vbo);
  glDeleteVertexArrays(1, &tri->vao);
  free(tri);
}

void triangle_draw(ObjectTriangle *tri) {
  glBindVertexArray(tri->vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

ObjectQuad *quad_create(PrimitiveQuad quad) {
  ObjectQuad *t = (ObjectQuad *) malloc(sizeof(ObjectQuad));

  t->info = quad;

  glGenVertexArrays(1, &t->vao);
  glGenBuffers(1, &t->pos_vbo);
  glGenBuffers(1, &t->col_vbo);

  glBindVertexArray(t->vao);

  glBindBuffer(GL_ARRAY_BUFFER, t->pos_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(t->info.points), t->info.points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vec3f), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, t->col_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4f), &t->info.color, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vec4f), (void *)0);
  glVertexAttribDivisor(1, 1);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return t;
}

void quad_destroy(ObjectQuad *quad) {
  glDeleteBuffers(1, &quad->pos_vbo);
  glDeleteBuffers(1, &quad->col_vbo);
  glDeleteVertexArrays(1, &quad->vao);
  free(quad);
}

void quad_draw(ObjectQuad *quad) {
  glBindVertexArray(quad->vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
