// particle manager
// generate particles with requested parameters

#pragma once

#include <time.h>
#include <vector>
#include "Game.h"
#include "Particle2D.h"
#include "Screen.h"
#include "Sprite.h"

using namespace std;

class CParticle2DManager
{

	
public: 
	
    CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                     double fX1, double fY1, double fX2, double fY2, 
                     double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                     double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                     double fAngle, double fMinIncAngle, double fMaxIncAngle,
                     unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime, CScreen *pScreen);
    ~CParticle2DManager();            


	void Restart(unsigned long ulCount);
	void Restart(void);

    int Render(unsigned long ulTimer);       // render, return state 
    
    void Regenerate(unsigned long ulIndex);  // regenerate parameters at requested index
    
	double Randomdouble(double a, double b);

    void	SetCount(unsigned long ulCount);
	unsigned long ulGetCount(void);

	double	dGetX1(void);
	double	dGetX2(void);
	double  dGetY1(void);
	double	dGetY2(void);

	void	SetX1(double x1);
	void	SetX2(double x2);
	void	SetY1(double y1);
	void	SetY2(double y2);

	void	SetXY12(double x1, double y1, double x2, double y2);

	double	dGetMinIncX(void);
	double	dGetMinIncY(void);
	double	dGetMaxIncX(void);
	double	dGetMaxIncY(void);

	void	SetMinIncX(double v);
	void	SetMinIncY(double v);
	void	SetMaxIncX(double v);
	void	SetMaxIncY(double v);

	void	SetInc(double minX, double minY, double maxX, double maxY);

	double	dGetAlpha(void);
	double	dGetAlphaMin(void);
	double	dGetAlphaMax(void);

	void	SetAlpha(double v);
	void	SetAlphaMin(double v);
	void	SetAlphaMax(double v);

	void	SetAlpha(double alpha, double min, double max);

	double	dGetAngle(void);
	double	dGetAngleMin(void);
	double	dGetAngleMax(void);

	void	SetAngle(double v);
	void	SetAngleMin(double v);
	void	SetAngleMax(double v);

	void	SetAngle(double angle, double min, double max);
	
	unsigned long	ulGetMinLifeTime(void);
	unsigned long	ulGetMaxLifeTime(void);

	void	SetMinLifeTime(unsigned long ulTime);
	void	SetMaxLifeTime(unsigned long ulTime);

private:	
    
    unsigned long   m_ulCount;  // how many particles ? 
    
    unsigned long   m_ulTimer;  // current time 
    unsigned long   m_ulStart;  // start time 
    
    double           m_fX1, m_fY1, m_fX2, m_fY2;
    double           m_fMinIncX, m_fMinIncY, m_fMaxIncX, m_fMaxIncY;
    double           m_fAlpha, m_fMinIncAlpha, m_fMaxIncAlpha;
    double           m_fAngle, m_fMinIncAngle, m_fMaxIncAngle;
    
    unsigned long   m_ulMinLifeTime, m_ulMaxLifeTime;
    
    bool            m_bActive;        

    vector <CParticle2D*>   m_pParticles;
    
	CSprite                 *m_pImage;  // particle image 
	
};

