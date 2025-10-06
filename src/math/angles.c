#include "math/angles.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323
#endif // M_PI

inline AngleDeg radians_to_degrees(AngleRad radians) {
  return radians * (180.0f / M_PI);
}

inline AngleRad degrees_to_radians(AngleDeg degrees) {
  return degrees * (M_PI / 180.0f);
}
