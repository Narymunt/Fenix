/**
   Particle2D.h

   Klasa zawiera informacje o pojedy�czej cz�stce. 
   Jest u�ywana przez managera do stworzenia efektu.
   Ta klasa nie renderuje cz�stki, odpowiada za to manager.

   @author Jaros�aw Ro�y�ski
   
*/

#pragma once

#include <time.h>
#include "../../Game.h"

class CParticle2D
{
	
public: 
	
    CParticle2D(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime);
    ~CParticle2D();            
    
    void Regenerate(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime);  

    int Update(unsigned long ulTimer);       // update parameters
    
    inline void x(double x) { _x = x; }
    inline double x(void) { return _x; }

    inline void y(double y) { _y = y; }
    inline double y(void) { return _y; }

    inline void dAlpha(double a) { _dAlpha = a; }
    inline double dAlpha(void) { return _dAlpha; }

    inline void dIncAlpha(double a) { _dIncAlpha = a; }
    inline double dIncAlpha(void) { return _dIncAlpha; }

    inline void dAngle(double a) { _dAngle = a; }
    inline double dAngle(void) { return _dAngle; }

    inline void dIncAngle(double a) { _dIncAngle = a; }
    inline double dIncAngle(void) { return _dIncAngle; }
    
    inline void isActive(bool b) { _isActive = b; }
    inline bool isActive(void) { return _isActive; }    

private:	
    
    double           _x, _y;
    double           _dAlpha, _dAngle;
    
    double           _dIncAlpha, _dIncAngle;    

    double           _dIncX, _dIncY;   
    
    unsigned long    _ulTimer;         // aktualny czas

    unsigned long    _ulStartTime;     // czas pocz�tku renderowania
    unsigned long    _ulLifeTime;      // czas �ycia cz�stki
    
    bool			      _isActive;            
	
};

