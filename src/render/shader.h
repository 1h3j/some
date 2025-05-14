#ifndef SHADER_H
#define SHADER_H

#include "math/matrix.h"
#include "math/vectors.h"
#include <glad/glad.h>

struct shader_t {
  GLuint program, vertex_shader, fragment_shader;
};

/**
 * Allocate a shader object and compile the shaders.
 *
 * @param vsh_code The GLSL vertex shader code
 * @param fsh_code The GLSL fragment shader code
 * @return Pointer to a shader object
*/
struct shader_t *create_shader(const char *vsh_code, const char *fsh_code);

/**
 * Loads a file and creates a shader object from the paths given.
 *
 * @param vsh_fpath Path to a vertex shader file.
 * @param fsh_fpath Path to a fragment shader file.
 * @return Pointer to a shader object
*/
struct shader_t *load_shader(const char *vsh_fpath, const char *fsh_fpath);

/**
 * Frees the resources associated with the shder object.
 *
 * @param shader Shader object
*/
void free_shader(struct shader_t *shader);

/**
 * Binds the shader object for usage
 *
 * @param shader Shader object
*/
void shader_use(struct shader_t *shader);

/**
 * Set the uniform value of a shader
 *
 * @param shader Shader object
 * @param name   Name of the uniform
 * @param value  Value of the uniform
*/
void shader_uniform_vec3f(struct shader_t *shader, const char *name,
                          struct vec3f_t value);

/**
 * Set the uniform value of a shader
 *
 * @param shader Shader object
 * @param name   Name of the uniform
 * @param value  Value of the uniform
*/
void shader_uniform_vec4f(struct shader_t *shader, const char *name,
                          struct vec4f_t value);

/**
 * Set the uniform value of a shader
 *
 * @param shader Shader object
 * @param name   Name of the uniform
 * @param value  Value of the uniform
*/
void shader_uniform_mat4x4f(struct shader_t *shader, const char *name,
                            struct matrix_4x4f_t *value);

#endif // !SHADER_H
