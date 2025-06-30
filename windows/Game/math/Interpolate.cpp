#include "Interpolate.h"
#include <math.h>

// Easing functions based on equations by Robert Penner
// Ported to C++ by Jesus Gollonet: https://github.com/jesusgollonet/ofpennereasing

//t - current time
//b - beginning
//c - change
//d - destination time

//Public function parameters are different because of my habits.
//a - beginning
//b - end
//t - current time
//d - destination time

const float PI = 3.14159265f;

float Interpolate::backIn(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float postFix = t /= d;
	return c*(postFix)*t*((s + 1)*t - s) + b;
}

float Interpolate::backOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	return c*((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
}

float Interpolate::backInOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	if ((t /= d / 2) < 1) return c / 2 * (t*t*(((s *= (1.525f)) + 1)*t - s)) + b;
	float postFix = t -= 2;
	return c / 2 * ((postFix)*t*(((s *= (1.525f)) + 1)*t + s) + 2) + b;
}

float Interpolate::bounceIn(float t, float b, float c, float d)
{
	return c - bounceOut(d - t, 0, c, d) + b;
}

float Interpolate::bounceOut(float t, float b, float c, float d)
{
	if ((t /= d) < (1 / 2.75f)) {
		return c*(7.5625f*t*t) + b;
	}
	else if (t < (2 / 2.75f)) {
		float postFix = t -= (1.5f / 2.75f);
		return c*(7.5625f*(postFix)*t + .75f) + b;
	}
	else if (t < (2.5 / 2.75)) {
		float postFix = t -= (2.25f / 2.75f);
		return c*(7.5625f*(postFix)*t + .9375f) + b;
	}
	else {
		float postFix = t -= (2.625f / 2.75f);
		return c*(7.5625f*(postFix)*t + .984375f) + b;
	}
}

float Interpolate::bounceInOut(float t, float b, float c, float d)
{
	if (t < d / 2) return bounceIn(t * 2, 0, c, d) * .5f + b;
	else return bounceOut(t * 2 - d, 0, c, d) * .5f + c*.5f + b;
}

float Interpolate::circIn(float t, float b, float c, float d)
{
	return -c * (sqrtf(1 - (t /= d)*t) - 1) + b;
}

float Interpolate::circOut(float t, float b, float c, float d)
{
	return c * sqrtf(1 - (t = t / d - 1)*t) + b;
}

float Interpolate::circInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1) return -c / 2 * (sqrtf(1 - t*t) - 1) + b;
	return c / 2 * (sqrtf(1 - t*(t -= 2)) + 1) + b;
}

float Interpolate::cubicIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t*t + b;
}

float Interpolate::cubicOut(float t, float b, float c, float d)
{
	return c*((t = t / d - 1)*t*t + 1) + b;
}

float Interpolate::cubicInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1) return c / 2 * t*t*t + b;
	return c / 2 * ((t -= 2)*t*t + 2) + b;
}

float Interpolate::elasticIn(float t, float b, float c, float d)
{
	if (t == 0) return b;  if ((t /= d) == 1) return b + c;
	float p = d*.3f;
	float a = c;
	float s = p / 4;
	float postFix = a*powf(2, 10 * (t -= 1)); // this is a fix, again, with post-increment operators
	return -(postFix * sinf((t*d - s)*(2 * PI) / p)) + b;
}

float Interpolate::elasticOut(float t, float b, float c, float d)
{
	if (t == 0) return b;  if ((t /= d) == 1) return b + c;
	float p = d*.3f;
	float a = c;
	float s = p / 4;
	return (a*powf(2, -10 * t) * sinf((t*d - s)*(2 * PI) / p) + c + b);
}

float Interpolate::elasticInOut(float t, float b, float c, float d)
{
	if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
	float p = d*(.3f*1.5f);
	float a = c;
	float s = p / 4;

	if (t < 1) {
		float postFix = a*powf(2, 10 * (t -= 1)); // postIncrement is evil
		return -.5f*(postFix* sinf((t*d - s)*(2 * PI) / p)) + b;
	}
	float postFix = a*powf(2, -10 * (t -= 1)); // postIncrement is evil
	return postFix * sinf((t*d - s)*(2 * PI) / p)*.5f + c + b;
}

float Interpolate::expoIn(float t, float b, float c, float d)
{
	return (t == 0) ? b : c * powf(2, 10 * (t / d - 1)) + b;
}

float Interpolate::expoOut(float t, float b, float c, float d)
{
	return (t == d) ? b + c : c * (-powf(2, -10 * t / d) + 1) + b;
}

float Interpolate::expoInOut(float t, float b, float c, float d)
{
	if (t == 0) return b;
	if (t == d) return b + c;
	if ((t /= d / 2) < 1) return c / 2 * powf(2, 10 * (t - 1)) + b;
	return c / 2 * (-powf(2, -10 * --t) + 2) + b;
}

float Interpolate::linear(float t, float b, float c, float d)
{
	return c*t / d + b;
}

float Interpolate::quadIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t + b;
}

float Interpolate::quadOut(float t, float b, float c, float d)
{
	return -c *(t /= d)*(t - 2) + b;
}

float Interpolate::quadInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1) return ((c / 2)*(t*t)) + b;
	return -c / 2 * (((t - 2)*(--t)) - 1) + b;
	/*
	originally return -c/2 * (((t-2)*(--t)) - 1) + b;
	I've had to swap (--t)*(t-2) due to diffence in behaviour in
	pre-increment operators between java and c++, after hours
	of joy
	*/

}

float Interpolate::quartIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t*t*t + b;
}

float Interpolate::quartOut(float t, float b, float c, float d)
{
	return -c * ((t = t / d - 1)*t*t*t - 1) + b;
}

float Interpolate::quartInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1) return c / 2 * t*t*t*t + b;
	return -c / 2 * ((t -= 2)*t*t*t - 2) + b;
}

float Interpolate::quintIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t*t*t*t + b;
}

float Interpolate::quintOut(float t, float b, float c, float d)
{
	return c*((t = t / d - 1)*t*t*t*t + 1) + b;
}

float Interpolate::quintInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1) return c / 2 * t*t*t*t*t + b;
	return c / 2 * ((t -= 2)*t*t*t*t + 2) + b;
}

float Interpolate::sineIn(float t, float b, float c, float d)
{
	return -c * cosf(t / d * (PI / 2)) + c + b;
}

float Interpolate::sineOut(float t, float b, float c, float d)
{
	return c * sinf(t / d * (PI / 2)) + b;
}

float Interpolate::sineInOut(float t, float b, float c, float d)
{
	return -c / 2 * (cosf(PI*t / d) - 1) + b;
}

float Interpolate::Angle(float a, float b, float t, float d, InterpolateType type)
{
	float diff = b - a;

	a -= (int)(a / 360.0f);
	b -= (int)(b / 360.0f);

	if (diff > 180)
	{
		a += 360.0f;
	}
	else if (diff < -180)
	{
		a -= 360.0f;
	}

	return Float(a, b, t, d, type);
}

float Interpolate::Float(float a, float b, float t, float d, InterpolateType type)
{
	t = t < 0 ? 0 : t;
	t = t > d ? d : t;

	switch (type)
	{
	case InBack:		return backIn(t, a, (b - a), d);
	case OutBack:		return backOut(t, a, (b - a), d);
	case InOutBack:		return backInOut(t, a, (b - a), d);
	case InBounce:		return bounceIn(t, a, (b - a), d);
	case OutBounce:		return bounceOut(t, a, (b - a), d);
	case InOutBounce:	return bounceInOut(t, a, (b - a), d);
	case InCirc:		return circIn(t, a, (b - a), d);
	case OutCirc:		return circOut(t, a, (b - a), d);
	case InOutCirc:		return circInOut(t, a, (b - a), d);
	case InCubic:		return cubicIn(t, a, (b - a), d);
	case OutCubic:		return cubicOut(t, a, (b - a), d);
	case InOutCubic:	return cubicInOut(t, a, (b - a), d);
	case InElastic:		return elasticIn(t, a, (b - a), d);
	case OutElastic:	return elasticOut(t, a, (b - a), d);
	case InOutElastic:	return elasticInOut(t, a, (b - a), d);
	case InExpo:		return expoIn(t, a, (b - a), d);
	case OutExpo:		return expoOut(t, a, (b - a), d);
	case InOutExpo:		return expoInOut(t, a, (b - a), d);
	case Linear:		return linear(t, a, (b - a), d);
	case InQuad:		return quadIn(t, a, (b - a), d);
	case OutQuad:		return quadOut(t, a, (b - a), d);
	case InOutQuad:		return quadInOut(t, a, (b - a), d);
	case InQuart:		return quartIn(t, a, (b - a), d);
	case OutQuart:		return quartOut(t, a, (b - a), d);
	case InOutQuart:	return quartInOut(t, a, (b - a), d);
	case InQuint:		return quintIn(t, a, (b - a), d);
	case OutQuint:		return quintOut(t, a, (b - a), d);
	case InOutQuint:	return quintInOut(t, a, (b - a), d);
	case InSine:		return sineIn(t, a, (b - a), d);
	case OutSine:		return sineOut(t, a, (b - a), d);
	case InOutSine:		return sineInOut(t, a, (b - a), d);
	default:			return linear(t, a, (b - a), d);
	}
}
