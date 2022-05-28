#ifndef VEC2_H
#define VEC2_H

#include "datatypes.h"

typedef struct {
	float32 x, y;
} Vec2;

Vec2 vec2_new(const float32 x, const float32 y);
Vec2 vec2_add(const Vec2 a, const Vec2 b);
Vec2 vec2_sub(const Vec2 a, const Vec2 b);
Vec2 vec2_mul(const Vec2 a, const Vec2 b);
Vec2 vec2_div(const Vec2 a, const Vec2 b);
Vec2 vec2_scale(const Vec2 a, const float32 b);
Vec2 vec2_lerp(const Vec2 a, const Vec2 b, const float32 t);

Vec2 vec2_one();
Vec2 vec2_zero();

#endif
