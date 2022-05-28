#include "vec2.h"

Vec2 vec2_new(const float32 x, const float32 y) {
	Vec2 vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

Vec2 vec2_add(const Vec2 a, const Vec2 b) {
	Vec2 vec;
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	return vec;
}

Vec2 vec2_sub(const Vec2 a, const Vec2 b) {
	Vec2 vec;
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	return vec;
}

Vec2 vec2_mul(const Vec2 a, const Vec2 b) {
	Vec2 vec;
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	return vec;
}

Vec2 vec2_div(const Vec2 a, const Vec2 b) {
	Vec2 vec;
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	return vec;
}

Vec2 vec2_scale(const Vec2 a, const float32 b) {
	Vec2 vec;
	vec.x = a.x * b;
	vec.y = a.y * b;
	return vec;
}

Vec2 vec2_lerp(const Vec2 a, const Vec2 b, const float32 t) {
	Vec2 vec;
	vec.x = a.x + ((b.x - a.x) * t);
	vec.y = a.y + ((b.y - a.y) * t);
	return vec;
}

Vec2 vec2_one() {
	Vec2 vec;
	vec.x = 1.0f;
	vec.y = vec.x;
	return vec;
}

Vec2 vec2_zero() {
	Vec2 vec;
	vec.x = 0.0f;
	vec.y = vec.x;
	return vec;
}
