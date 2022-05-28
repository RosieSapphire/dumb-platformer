#ifndef VEC2_H
#define VEC2_H

#include "datatypes.h"
#include <SFML/System/Vector2.h>

sfVector2f sfVector2f_new(const float32 x, const float32 y);
sfVector2f sfVector2f_add(const sfVector2f a, const sfVector2f b);
sfVector2f sfVector2f_sub(const sfVector2f a, const sfVector2f b);
sfVector2f sfVector2f_mul(const sfVector2f a, const sfVector2f b);
sfVector2f sfVector2f_div(const sfVector2f a, const sfVector2f b);
sfVector2f sfVector2f_scale(const sfVector2f a, const float32 b);
sfVector2f sfVector2f_lerp(const sfVector2f a, const sfVector2f b, const float32 t);

sfVector2f sfVector2f_one();
sfVector2f sfVector2f_zero();

#endif
