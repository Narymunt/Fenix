/**
   Particle2DManager.h
   Generuje potrzebne cz¹stki i zarz¹dza nimi. 
   Trzyma informacje o texturach, ¿eby nie powielaæ sprite dla ka¿dej cz¹stki z osobna.
*/

#pragma once

#include <time.h>
#include <vector>
#include "../Game.h"
#include "Particle2D.h"
#include "Screen.h"
#include "Sprite.h"

using namespace std;

class Particle2DManager
{

public: 
	
	// inicjalizowane razem z grafika

    Particle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                     double fX1, double fY1, double fX2, double fY2, 
                     double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                     double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                     double fAngle, double fMinIncAngle, double fMaxIncAngle,
                     unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime, Screen *pScreen);

	// inicjalizowane ze wskaznikiem na istniejacy juz sprite jako particle

	Particle2DManager(Sprite *pImage, unsigned long ulCount,
		double fX1, double fY1, double fX2, double fY2,
		double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
		double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
		double fAngle, double fMinIncAngle, double fMaxIncAngle,
		unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);

    ~Particle2DManager();            

	// zmieniamy wszystkie parametry

	void reset(Sprite *pImage, unsigned long ulCount,
		double fX1, double fY1, double fX2, double fY2,
		double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
		double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
		double fAngle, double fMinIncAngle, double fMaxIncAngle,
		unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);

	// zmianiamy wszystkie parametry poza wskaznikiem na sprite

	void reset(unsigned long ulCount,
		double fX1, double fY1, double fX2, double fY2,
		double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
		double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
		double fAngle, double fMinIncAngle, double fMaxIncAngle,
		unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);

	void restart(unsigned long ulCount);
	void restart(void);

    int render(unsigned long ulTimer);       // render, return state 
    
    void regenerate(unsigned long ulIndex);  // regenerate parameters at requested index
    
	double randomDouble(double a, double b);

	void	setXY(double x1, double y1, double x2, double y2);
	void	setInc(double minX, double minY, double maxX, double maxY);

	void	alpha(double alpha, double min, double max);
	void	angle(double angle, double min, double max);

   // zmiana koloru dla textury

	void	color(float r, float g, float b, float a);
	void	color(float r, float g, float b);
    
	bool			_loop; // czy particle ktore skonczyly sie, maja byc regenerowane ? 
    unsigned long   _count; // how many particles ? 
    unsigned long   _timer; // current time 
    unsigned long   _start; // start time 
    
    double _x1, _y1, _x2, _y2;
    double _minIncX, _minIncY, _maxIncX, _maxIncY;
    double _alpha, _minIncAlpha, _maxIncAlpha;
    double _angle, _minIncAngle, _maxIncAngle;
    
    unsigned long _minLifeTime, _maxLifeTime;
    
    bool _active;        

    vector <Particle2D*> _particles;
	Sprite *_image;  // particle image 
	
	float			_r, _g, _b, _a;
};

