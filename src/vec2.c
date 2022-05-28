#include "vec2.h"

sfVector2f sfVector2f_new(const float32 x, const float32 y) {
	sfVector2f vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

sfVector2f sfVector2f_add(const sfVector2f a, const sfVector2f b) {
	sfVector2f vec;
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	return vec;
}

sfVector2f sfVector2f_sub(const sfVector2f a, const sfVector2f b) {
	sfVector2f vec;
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	return vec;
}

sfVector2f sfVector2f_mul(const sfVector2f a, const sfVector2f b) {
	sfVector2f vec;
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	return vec;
}

sfVector2f sfVector2f_div(const sfVector2f a, const sfVector2f b) {
	sfVector2f vec;
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	return vec;
}

sfVector2f sfVector2f_scale(const sfVector2f a, const float32 b) {
	sfVector2f vec;
	vec.x = a.x * b;
	vec.y = a.y * b;
	return vec;
}

sfVector2f sfVector2f_lerp(const sfVector2f a, const sfVector2f b, const float32 t) {
	sfVector2f vec;
	vec.x = a.x + ((b.x - a.x) * t);
	vec.y = a.y + ((b.y - a.y) * t);
	return vec;
}

sfVector2f sfVector2f_one() {
	sfVector2f vec;
	vec.x = 1.0f;
	vec.y = vec.x;
	return vec;
}

sfVector2f sfVector2f_zero() {
	sfVector2f vec;
	vec.x = 0.0f;
	vec.y = vec.x;
	return vec;
}
