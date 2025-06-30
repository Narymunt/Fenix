/**
   Particle2DManager.h

   Generuje potrzebne cz¹stki i zarz¹dza nimi. 
   Trzyma informacje o texturach, ¿eby nie powielaæ sprite dla ka¿dej cz¹stki z osobna.

   @author Jaros³aw Ro¿yñski
   
*/

#pragma once

#include <time.h>
#include <vector>
#include "../../Game.h"
#include "Particle2D.h"
#include "Screen.h"
#include "Sprite.h"

using namespace std;

class CParticle2DManager
{

public: 
	
	// inicjalizowane razem z grafika

    CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                     double fX1, double fY1, double fX2, double fY2, 
                     double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                     double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                     double fAngle, double fMinIncAngle, double fMaxIncAngle,
                     unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime, CScreen *pScreen);

	// inicjalizowane ze wskaznikiem na istniejacy juz sprite jako particle

	CParticle2DManager(CSprite *pImage, unsigned long ulCount,
		double fX1, double fY1, double fX2, double fY2,
		double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
		double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
		double fAngle, double fMinIncAngle, double fMaxIncAngle,
		unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);

    ~CParticle2DManager();            

	// zmieniamy wszystkie parametry

	void Reset(CSprite *pImage, unsigned long ulCount,
		double fX1, double fY1, double fX2, double fY2,
		double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
		double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
		double fAngle, double fMinIncAngle, double fMaxIncAngle,
		unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);

	// zmianiamy wszystkie parametry poza wskaznikiem na sprite

	void Reset(unsigned long ulCount,
		double fX1, double fY1, double fX2, double fY2,
		double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
		double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
		double fAngle, double fMinIncAngle, double fMaxIncAngle,
		unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime);

	void Restart(unsigned long ulCount);
	void Restart(void);

    int Render(unsigned long ulTimer);       // render, return state 
    
    void Regenerate(unsigned long ulIndex);  // regenerate parameters at requested index
    
	double Randomdouble(double a, double b);

   inline void	ulCount(unsigned long ulCount) { _ulCount = ulCount; }
   inline unsigned long ulCount(void) { return _ulCount; }

   // ustalanie zakresu dla losowanych wspolrzednych oraz minimalnego i maksymalnego odchylenia per tick

   inline double dMinIncX(void) { return _dMinIncX; }
   inline void dMinIncX(double d) { _dMinIncX = d; }

   inline double dMinIncY(void) { return _dMinIncY; }
   inline void dMinIncY(double d) { _dMinIncY = d; }

   inline double dMaxIncX(void) { return _dMaxIncX; }
   inline void dMaxIncX(double d) { _dMaxIncX = d; }

   inline double dMaxIncY(void) { return _dMaxIncY; }
   inline void dMaxIncY(double d) { _dMaxIncY = d; }

   inline double x1(void) { return _x1;} 
   inline void x1(double d) { _x1 = d; }

   inline double y1(void) { return _y1;} 
   inline void y1(double d) { _y1 = d; }

   inline double x2(void) { return _x2;} 
   inline void x2(double d) { _x2 = d; }

   inline double y2(void) { return _y2;} 
   inline void y2(double d) { _y2 = d; }

	void	SetXY(double x1, double y1, double x2, double y2);
	void	SetInc(double minX, double minY, double maxX, double maxY);

   // ustawienie przeŸroczystoœci, minimalnego i maksymalnego odchylenia per tick

   inline void dAlpha(double d) { _dAlpha = d; }
   inline double dAlpha(void) { return _dAlpha; }

   inline void dMinIncAlpha(double d) { _dMinIncAlpha = d; }
   inline double dMinIncAlpha(void) { return _dMinIncAlpha; }

   inline void dMaxnIncAlpha(double d) { _dMaxIncAlpha = d; }
   inline double dMaxIncAlpha(void) { return _dMaxIncAlpha; }

	void	SetAlpha(double alpha, double min, double max);

   // ustawienie konta, minimalnego i maksymalnego odchylenia konta per tick

   inline void dAngle(double d) { _dAngle = d; }
   inline double dAngle(void) { return _dAngle; }

   inline void dMinIncAngle(double d) { _dMinIncAngle = d; }
   inline double dMinIncAngle(void) { return _dMinIncAngle; }

   inline void dMaxnIncAngle(double d) { _dMaxIncAngle = d; }
   inline double dMaxIncAngle(void) { return _dMaxIncAngle; }

	void	SetAngle(double angle, double min, double max);

   // ustawienie cyklu ¿ycia, minimalnego i maksymalnego

   inline void ulMinLifeTime(unsigned long l) { _ulMinLifeTime = l; }
   inline unsigned long ulMinLifeTime(void) { return _ulMinLifeTime; }

   inline void ulMaxLifeTime(unsigned long l) { _ulMaxLifeTime = l; }
   inline unsigned long ulMaxLifeTime(void) { return _ulMaxLifeTime; }

   // zmiana koloru dla textury

	void	Color(float r, float g, float b, float a);
	void	Color(float r, float g, float b);

   // ustawienie sprite dla cz¹stek

	inline void pImage(CSprite *p) { _pImage = p; }
	inline CSprite *pImage(void) { return _pImage;	}

   // czy powtarzamy odtwarzanie na koniec cyklu ¿ycia cz¹stki

	inline void isLoop(bool b) { _isLoop = b; }
	inline bool isLoop(void) { return _isLoop; }

private:	
    
	bool			_isLoop;							// czy particle ktore skonczyly sie, maja byc regenerowane ? 

    unsigned long   _ulCount;  // how many particles ? 
    
    unsigned long   _ulTimer;  // current time 
    unsigned long   _ulStart;  // start time 
    
    double           _x1, _y1, _x2, _y2;
    double           _dMinIncX, _dMinIncY, _dMaxIncX, _dMaxIncY;
    double           _dAlpha, _dMinIncAlpha, _dMaxIncAlpha;
    double           _dAngle, _dMinIncAngle, _dMaxIncAngle;
    
    unsigned long   _ulMinLifeTime, _ulMaxLifeTime;
    
    bool            _isActive;        

    vector <CParticle2D*>   _pParticles;
    
	CSprite                 *_pImage;  // particle image 
	
	float			_r, _g, _b, _a;

};

