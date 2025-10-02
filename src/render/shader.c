#include "render/shader.h"
#include "glad/glad.h"
#include "math/matrix.h"
#include "util/logging.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Shader *create_shader(const char *vsh_code, const char *fsh_code) {
  int success;
  char status[512];

  Shader *shader = (Shader *)malloc(sizeof(Shader));

  shader->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader->vertex_shader, 1, &vsh_code, NULL);
  glCompileShader(shader->vertex_shader);

  glGetShaderiv(shader->vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader->vertex_shader, sizeof(status), NULL, status);
    log_error("Failed to compile vertex shader:\n%s", status);
  }

  shader->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader->fragment_shader, 1, &fsh_code, NULL);
  glCompileShader(shader->fragment_shader);

  glGetShaderiv(shader->fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader->fragment_shader, sizeof(status), NULL, status);
    log_error("Failed to compile fragment shader:\n%s", status);
  }

  shader->program = glCreateProgram();
  glAttachShader(shader->program, shader->vertex_shader);
  glAttachShader(shader->program, shader->fragment_shader);

  glLinkProgram(shader->program);
  glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader->program, sizeof(status), NULL, status);
    log_error("Failed to link shader program:\n%s", status);
    return NULL;
  }

  return shader;
}

Shader *load_shader(const char *vsh_fpath, const char *fsh_fpath) {
  Shader *shader;
  long fsize;

  FILE *file_vsh = fopen(vsh_fpath, "r");
  if (file_vsh == NULL) {
    log_error("Can't open file for reading: %s", vsh_fpath);
    return NULL;
  }

  fseek(file_vsh, 0, SEEK_END);
  fsize = ftell(file_vsh);
  fseek(file_vsh, 0, SEEK_SET);

  char *vsh_source = malloc(fsize + 1);
  fread(vsh_source, fsize, 1, file_vsh);
  vsh_source[fsize] = '\0';


  FILE *file_fsh = fopen(fsh_fpath, "r");
  if (file_fsh == NULL) {
    log_error("Can't open file for reading: %s", fsh_fpath);
    return NULL;
  }

  fseek(file_fsh, 0, SEEK_END);
  fsize = ftell(file_fsh);
  fseek(file_fsh, 0, SEEK_SET);

  char *fsh_source = malloc(fsize + 1);
  fread(fsh_source, fsize, 1, file_fsh);
  fsh_source[fsize] = '\0';

  shader = create_shader(vsh_source, fsh_source);

  free(fsh_source);
  fclose(file_fsh);

  free(vsh_source);
  fclose(file_vsh);

  if (shader != NULL) {
    log_info("Successfully loaded shader program: V:%s, F:%s", vsh_fpath,
             fsh_fpath);
  } else {
    log_error("Failed to laod program: V:%s, F:%s", vsh_fpath, fsh_fpath);
  }

  return shader;
}

void free_shader(Shader *shader) {
  glDeleteProgram(shader->program);
  glDeleteShader(shader->vertex_shader);
  glDeleteShader(shader->fragment_shader);
  free(shader);
}

void shader_use(Shader *shader) { glUseProgram(shader->program); }

void shader_uniform_vec3f(Shader *shader, const char *name,
                          Vec3f value) {
  shader_use(shader);
  int location = glGetUniformLocation(shader->program, name);
  glUniform3f(location, value.x, value.y, value.z);
}

void shader_uniform_vec4f(Shader *shader, const char *name,
                          Vec4f value) {
  shader_use(shader);
  int location = glGetUniformLocation(shader->program, name);
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void shader_uniform_mat4x4f(Shader *shader, const char *name,
                            Matrix_4x4f *value) {
  shader_use(shader);
  int location = glGetUniformLocation(shader->program, name);
  glUniformMatrix4fv(location, 1, GL_TRUE, &value->m[0][0]); // lmao
}

void shader_uniform_texture2d(Shader *shader, const char *name,
                            Texture2D *texture, int texture_location)
{
  shader_use(shader);
  int location = glGetUniformLocation(shader->program, name);

  glActiveTexture(GL_TEXTURE0 + texture_location);
  glBindTexture(GL_TEXTURE_2D, texture->tex);

  glUniform1i(location, texture_location);
}
