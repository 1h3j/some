#ifndef ANGLES_H
#define ANGLES_H

typedef float AngleRad;
typedef float AngleDeg;

typedef struct {
  AngleDeg yaw;
  AngleDeg pitch;
  AngleDeg roll;
} Rotation3f;

/**
 * Convert from radians to degrees
*/
AngleDeg radians_to_degrees(AngleRad radians);

/**
 * Convert from degrees to radians
*/
AngleRad degrees_to_radians(AngleDeg degrees);

#endif // !ANGLED_H
