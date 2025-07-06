#pragma once

class CBox
{

public:

	CBox();
	CBox(float x1, float y1, float x2, float y2);
	CBox~();

	void set(float x1, float y1, float x2, float y2);
	void get(float *x1, float *y1, float *x2, float *y2);
	
	float	fX1(void);
	void	fX1(float v);

	float	fY1(void);
	void	fY1(float v);

	float	fX2(void);
	void	fX2(float v);

	float	fY2(void);
	void	fY2(float v);

	void	update();
	
	bool	isIntersect(CBox box1, CBox box2);
	bool	isInside(CBox box1, CBox box2);
	
protected:

	float	m_fX1, m_fY1, m_fX2, m_fY2;

};