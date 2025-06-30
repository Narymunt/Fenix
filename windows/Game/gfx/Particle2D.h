/**
   Particle2D.h

   Klasa zawiera informacje o pojedy�czej cz�stce. 
   Jest u�ywana przez managera do stworzenia efektu.
   Ta klasa nie renderuje cz�stki, odpowiada za to manager.

   @author Jaros�aw Ro�y�ski
   
*/

#pragma once

#include <time.h>
#include "../Game.h"

class Particle2D
{
	
public: 
	
    Particle2D(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime);
    ~Particle2D();            
    
    void regenerate(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime);  

    int update(unsigned long ulTimer);       // update parameters
    
    inline void x(double x) { _x = x; }
    inline double x(void) { return _x; }

    inline void y(double y) { _y = y; }
    inline double y(void) { return _y; }
    
    double           _x, _y;
    double           _dAlpha, _dAngle;
    
    double           _dIncAlpha, _dIncAngle;    

    double           _dIncX, _dIncY;   
    
    unsigned long    _ulTimer;         // aktualny czas

    unsigned long    _ulStartTime;     // czas pocz�tku renderowania
    unsigned long    _ulLifeTime;      // czas �ycia cz�stki
    
    bool			      _isActive;            
	
};

