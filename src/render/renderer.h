#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_video.h>

#include "util/array.h"
#include "math/camera.h"
#include "math/vectors.h"
#include "util/hashmap.h"
#include "render/shader.h"

#include <glad/glad.h>

#define RENDERER_2D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec4 color;\nuniform mat4 model = mat4(1);\nout vec4 vColor;\nvoid main() { gl_Position = model * vec4(aPos, 1.0); vColor = color; }"
#define RENDERER_2D_DEFAULT_FSH_S "#version 330\nin vec4 vColor;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = vColor; }"

#define RENDERER_3D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nuniform mat4 model = mat4(1);\nuniform mat4 view;\nuniform mat4 projection;\nvoid main() { gl_Position = projection * view * model * vec4(aPos, 1.0); }"
#define RENDERER_3D_DEFAULT_FSH_S "#version 330\nuniform vec4 color;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = color; fragmentColor *= gl_FrontFacing ? 1 : 0.5; }"

#endif // !RENDERER_H
