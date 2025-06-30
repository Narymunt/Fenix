// do sprawdzania kolizji, oraz czy jeden prostokat jest w drugim

#pragma once

class Box
{

public:

	Box();
	Box(float x1, float y1, float x2, float y2);
	~Box();

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
	
	bool	sort(void);		// posortuj wierzcholki przed sprawdzeniem intersekcji, tak aby x1,y1 to byl zawsze lewy gorny rog, zwraca true jezeli wierzcholki pokrywaja sie
	bool	isIntersect(Box box1, Box box2);
	bool	isInside(Box box1, Box box2);

	float	m_fX1, m_fY1, m_fX2, m_fY2;

}; 