#ifndef SHADER_H
#define SHADER_H

#include "math/matrix.h"
#include "math/vectors.h"
#include <glad/glad.h>

struct shader_t {
  GLuint program, vertex_shader, fragment_shader;
};

struct shader_t *create_shader(const char *vsh_code, const char *fsh_code);

struct shader_t *load_shader(const char *vsh_fpath, const char *fsh_fpath);

void free_shader(struct shader_t *shader);

void shader_use(struct shader_t *shader);

void shader_uniform_vec3f(struct shader_t *shader, const char *name,
                          struct vec3f_t value);

void shader_uniform_vec4f(struct shader_t *shader, const char *name,
                          struct vec4f_t value);

void shader_uniform_mat4x4f(struct shader_t *shader, const char *name,
                            struct matrix_4x4f_t *value);

#endif // !SHADER_H
