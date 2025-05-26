#include "math/angles.h"
#include <math.h>

inline degrees_angle_t radians_to_degrees(radians_angle_t radians) {
  return radians * (180.0f / M_PI);
}

inline radians_angle_t degrees_to_radians(degrees_angle_t degrees) {
  return degrees * (M_PI / 180.0f);
}
