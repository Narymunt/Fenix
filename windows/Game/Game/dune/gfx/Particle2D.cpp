/**
   Particle2D.cpp

   @author Jaros³aw N. Ro¿yñski
   @version 2014-09-04
   
*/

#include "Particle2D.h"

/**
   Konstruktor klasy.

   @param fX wspó³rzêdna X na ekranie
   @param fY wspó³rzêdna Y na ekranie
   @param fAlpha startowa wartoœæ przeŸroczystoœci
   @param fAngle startowy k¹t
   @param fIncX o ile ma byæ zwiêkszona wspó³rzêdna X per tick
   @param fIncY o ile ma byæ zwiêkszona wspó³rzêdna Y per tick
   @param fIncAlpha o ile ma byæ zwiêkszona przeŸroczystoœæ per tick 
   @param fIncAngle o ile ma byæ zwiêkszony k¹t per tick
   @param ulLifeTime czas ¿ycia cz¹stki
   
   @return none
*/

CParticle2D::CParticle2D(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime) :
   _x(fX),
   _y(fY),
   _dAlpha(fAlpha),
   _dAngle(fAngle),
   _dIncX(fIncX),
   _dIncY(fIncY),
   _dIncAlpha(fIncAlpha),
   _dIncAngle(fIncAngle),
   _ulLifeTime(ulLifeTime),
   _ulStartTime(0),
   _isActive(false)
{
    
}

/**
   Destruktor klasy.

   @param none
   @return none

*/

CParticle2D::~CParticle2D()
{
}

/**
   Regeneracja martwej cz¹stki, ustawienie nowych parametrów.

   @param fX wspó³rzêdna X na ekranie
   @param fY wspó³rzêdna Y na ekranie
   @param fAlpha startowa wartoœæ przeŸroczystoœci
   @param fAngle startowy k¹t
   @param fIncX o ile ma byæ zwiêkszona wspó³rzêdna X per tick
   @param fIncY o ile ma byæ zwiêkszona wspó³rzêdna Y per tick
   @param fIncAlpha o ile ma byæ zwiêkszona przeŸroczystoœæ per tick 
   @param fIncAngle o ile ma byæ zwiêkszony k¹t per tick
   @param ulLifeTime czas ¿ycia cz¹stki
   
   @return none
*/

void CParticle2D::Regenerate(double fX, double fY, double fAlpha, double fAngle, double fIncX, double fIncY, double fIncAlpha, double fIncAngle, unsigned long ulLifeTime)
{
    _x = fX; 
    _y = fY;
    
    _dAlpha = fAlpha; 
    _dAngle = fAngle;
    
    _dIncX = fIncX; 
    _dIncY = fIncY; 
    
    _dIncAngle = fIncAngle;
    _dIncAlpha = fIncAlpha;
    
    _ulStartTime =0; 
    
    _ulLifeTime = ulLifeTime;
    
    _isActive = false;    
    
}

/**
   Aktualizuj parametry na podstawie nowego czasu.

   @param ulTimer aktualny czas
   @return 0 je¿eli cz¹stka jest ju¿ martwa, 1 je¿eli parametry zosta³y zaktualizowane

*/

int CParticle2D::Update(unsigned long ulTimer)
{
    if (_ulStartTime == 0)
    {
        _ulStartTime = ulTimer;
        _isActive = true;
    }
    
    _ulTimer = ulTimer - _ulStartTime;
    
    if (_ulTimer > _ulLifeTime) 
       return 0;
    
    if (_isActive)
    {
        _x += _dIncX; 
        _y += _dIncY; 
        
        _dAlpha += _dIncAlpha; 
        
        if (_dAlpha>1.0f) 
			_dAlpha=1.0f;
        
		if (_dAlpha<0.0f) 
			_dAlpha=0.0f;
        
        _dAngle += _dIncAngle;
        
    }    
    
    return 1;   // do nothing 
}
