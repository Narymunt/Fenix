#pragma once

class CVector 2D
{
	
public:

	CVector2D(float x, float y);
	CVector2D(float x1, float y1, float x2, float y2);
	~CVector2D();

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

protected:

	float		m_fX, m_fY;
	float		m_fX1, m_fY1, m_fX2, m_fY2;

};