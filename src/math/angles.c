#include "math/angles.h"
#include <math.h>

inline AngleDeg radians_to_degrees(AngleRad radians) {
  return radians * (180.0f / M_PI);
}

inline AngleRad degrees_to_radians(AngleDeg degrees) {
  return degrees * (M_PI / 180.0f);
}
