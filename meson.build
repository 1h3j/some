project(
  'some',
  'c',
  version: '1.0',
)

cc = meson.get_compiler('c')

opencv_dep = dependency('sdl3', required: true)
math_dep = cc.find_library('m', required: true)

includes = include_directories('src', 'glad/include')

some_sources = [
  'src/app/resources.c',
  'src/event/callback.c',
  'src/event/events.c',
  'src/math/angles.c',
  'src/math/camera.c',
  'src/math/matrix.c',
  'src/math/projection.c',
  'src/math/transform.c',
  'src/render/primitives.c',
  'src/render/renderer.c',
  'src/render/shader.c',
  'src/render/texture.c',
  'src/render/vertex.c',
  'src/util/array.c',
  'src/util/logging.c',
]

gl_sources = [
  'glad/src/glad.c',
]

test_sources = [
  'src/test.c',
]

defines = [
  '-DLOGGING_COLOR'
]

executable(
  'build',
  some_sources,
  gl_sources,
  test_sources,

  include_directories: includes,
  dependencies: [opencv_dep, math_dep],

  c_args: defines,

  install: false
)
