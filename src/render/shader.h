#ifndef SHADER_H
#define SHADER_H

#include "math/vectors.h"
#include "math/matrix.h"
#include "texture.h"

#include <glad/glad.h>

typedef struct {
  GLuint program, vertex_shader, fragment_shader;
} Shader;

/**
 * Allocate a shader object and compile the shaders.
 *
 * @param vsh_code The GLSL vertex shader code
 * @param fsh_code The GLSL fragment shader code
 * @return Pointer to a shader object
*/
Shader *create_shader(const char *vsh_code, const char *fsh_code);

/**
 * Loads a file and creates a shader object from the paths given.
 *
 * @param vsh_fpath Path to a vertex shader file.
 * @param fsh_fpath Path to a fragment shader file.
 * @return Pointer to a shader object
*/
Shader *load_shader(const char *vsh_fpath, const char *fsh_fpath);

/**
 * Frees the resources associated with the shder object.
 *
 * @param shader Shader object
*/
void free_shader(Shader *shader);

/**
 * Binds the shader object for usage
 *
 * @param shader Shader object
*/
void shader_use(Shader *shader);

/**
 * Set the uniform value on a shader
 *
 * @param shader Shader object
 * @param name   Name of the uniform
 * @param value  Value of the uniform
*/
void shader_uniform_vec3f(Shader *shader, const char *name,
                          Vec3f value);

/**
 * Set the uniform value on a shader
 *
 * @param shader Shader object
 * @param name   Name of the uniform
 * @param value  Value of the uniform
*/
void shader_uniform_vec4f(Shader *shader, const char *name,
                          Vec4f value);

/**
 * Set the uniform value on a shader
 *
 * @param shader Shader object
 * @param name   Name of the uniform
 * @param value  Value of the uniform
*/
void shader_uniform_mat4x4f(Shader *shader, const char *name,
                            Matrix_4x4f *value);

/**
 * Set the uniform texture on a shader
 *
 * @param shader           Shader object
 * @param name             Name of the uniform
 * @param texture          Texture object
 * @param texture_location Location of a texture object (0 - 16)
*/
void shader_uniform_texture2d(Shader *shader, const char *name,
                            Texture2D *texture, int texture_location);

#endif // !SHADER_H
