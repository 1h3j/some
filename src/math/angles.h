#ifndef ANGLES_H
#define ANGLES_H

typedef float radians_angle_t;
typedef float degrees_angle_t;

struct rotation_t {
  degrees_angle_t yaw;
  degrees_angle_t pitch;
  degrees_angle_t roll;
};

degrees_angle_t radians_to_degrees(radians_angle_t radians);

radians_angle_t degrees_to_radians(degrees_angle_t degrees);

#endif // !ANGLED_H
