#pragma once

///A helper class for calculating interpolation using Robert Penner's Easing functions.

class Interpolate
{
private:
	static float backIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float backOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float backInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float bounceIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float bounceOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float bounceInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float circIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float circOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float circInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float cubicIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float cubicOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float cubicInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float elasticIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float elasticOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float elasticInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float expoIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float expoOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float expoInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float linear(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quadIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quadOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quadInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quartIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quartOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quartInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quintIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quintOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float quintInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float sineIn(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float sineOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);
	static float sineInOut(float t = 0.0f, float b = 0.0f, float c = 1.0f, float d = 1.0f);

public:

	Interpolate() {};
	~Interpolate() {};

	///The many types of easing functions, both intro, outtro and inouttros.

	enum InterpolateType
	{
		InBack,
		OutBack,
		InOutBack,
		InBounce,
		OutBounce,
		InOutBounce,
		InCirc,
		OutCirc,
		InOutCirc,
		InCubic,
		OutCubic,
		InOutCubic,
		InElastic,
		OutElastic,
		InOutElastic,
		InExpo,
		OutExpo,
		InOutExpo,
		Linear,
		InQuad,
		OutQuad,
		InOutQuad,
		InQuart,
		OutQuart,
		InOutQuart,
		InQuint,
		OutQuint,
		InOutQuint,
		InSine,
		OutSine,
		InOutSine,
		NumInterpolationTypes,
	};

	/**
	* Interpolates based on angle in degrees (0 - 360)
	* @param a Start point.
	* @param b Finish point.
	* @param t Current point in time.
	* @param d Total length of time.
	* @param type Easing function.
	*/
	static float Angle(float a, float b, float t, float d = 1.0f, InterpolateType type = Linear);

	/**
	* Interpolates standard float variables.
	* @param a Start point.
	* @param b Finish point.
	* @param t Current point in time.
	* @param d Total length of time.
	* @param type Easing function.
	*/
	static float Float(float a, float b, float t, float d = 1.0f, InterpolateType type = Linear);
};

