#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "math/vectors.h"

typedef struct {
  unsigned int tex;
  Vec2i size;
} Texture2D;

/**
 * Loads a .bmp file using SDL and then creates a texture with it.
 *
 * @param path           Path to the bitmap file.
 * @param mag_filter     Sampling filter to be applied when magnified, either GL_LINEAR or GL_NEAREST.
 * @param min_filter     Sampling filter to be applied when minified, could be GL_LINEAR, GL_NEAREST, or GL_LINEAR_MIPMAP_LINEAR.
 * @param wrap_x         Texture wrapping to be used in the x direction. Could be GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER.
 * @param wrap_y         Texture wrapping to be used in the y direction. Could be GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER.
 * @param create_mipmaps Boolean value that tells the function whether or not to create mipmaps for the texture.
 * @return Allocated texture object, NULL on failure. Will automatically log error.
*/
Texture2D *texture2d_load_bmp(const char* path, GLenum mag_filter, GLenum min_filter, GLenum wrap_x, 
                            GLenum wrap_y, bool create_mipmaps);

/**
 * Frees resources used by the texture.
 *
 * @param tex Texture object to be freed
*/
void texture2d_destroy(Texture2D *tex);

#endif // TEXTURE_H
