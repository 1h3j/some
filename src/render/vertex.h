#ifndef VERTEX_H
#define VERTEX_H

#include "glad/glad.h"
#include "util/array.h"
typedef struct {
  unsigned int vao;
} VertexArray;

typedef struct {
  unsigned int size, stride, offset;
  GLenum type;
} VertexData;

typedef struct {
  Array *vertex_data_arr;
} VectexBuffer;

#endif // VERTEX_H
