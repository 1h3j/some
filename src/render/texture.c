#include "texture.h"
#include "glad/glad.h"
#include "util/logging.h"

#include <stdlib.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>

Texture2D *texture2d_load_bmp(const char* path, GLenum mag_filter, GLenum min_filter, GLenum wrap_x, 
                            GLenum wrap_y, bool create_mipmaps) {
  Texture2D *t = (Texture2D *) malloc(sizeof(Texture2D));
  SDL_Surface *s = SDL_LoadBMP(path);

  if (s == NULL) {
    log_error("Error when loading BMP file: %s", SDL_GetError());
    return NULL;
  }

  SDL_Surface *converted_surface = SDL_ConvertSurface(s, SDL_PIXELFORMAT_RGBA32);
  SDL_DestroySurface(s);

  glGenTextures(1, &t->tex);
  glBindTexture(GL_TEXTURE_2D, t->tex);  

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_x);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_y);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0, GL_RGBA8, GL_UNSIGNED_BYTE, s->pixels);
  if (create_mipmaps) glGenerateMipmap(GL_TEXTURE_2D);

  SDL_DestroySurface(converted_surface);
  return t;
}

void texture2d_destroy(Texture2D *tex) {
  glDeleteTextures(1, &tex->tex);
  free(tex);
}
