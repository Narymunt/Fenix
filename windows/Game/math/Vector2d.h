#pragma once

class Vector2D
{
	
public:

	Vector2D(float x, float y);
	Vector2D(float x1, float y1, float x2, float y2);
	~Vector2D();

	void	set(float nx, float ny);
	void	set(float x1, float y1, float x2, float y2);
	
	void	get(float *nx, float *ny);
	void	get(float *x1, float *y1, float *x2, float *y2);

	float	fX(void);
	void	fX(float v);

	float	fY(void);
	void	fY(float v);

	float	fX1(void);
	void	fX1(float v);

	float	fY1(void);
	void	fY1(float v);

	float	fX2(void);
	void	fX2(float v);

	float	fY2(void);
	void	fY2(float v);

	float		_fX, _fY;
	float		_fX1, _fY1, _fX2, _fY2;

};