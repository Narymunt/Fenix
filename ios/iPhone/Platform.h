#ifndef _igame_platform_
#define _igame_platform_

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Box.h"        // bounding box
#include "Touch.h"
#include "Sprite.h"
#include "Anim.h"

// stan w trakcie wczytywania zasobów

class CPlatform
{
	
public: 
	
    CPlatform(char cFilename[], float fX, float fY, float m_fSizeX, float m_fSizeY);
    ~CPlatform();            // destruktor automatycznie zamyka stan
    
    void SetPosition(float fX, float fY);
    void SetForce(float fX, float fY);
    void IncForce(float fX, float fY);

    float fGetForceX(void);
    float fGetForceY(void);     
    
    int Render(CTouch *pTouch, unsigned long ulTimer);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    bool isActive(void);    // czy dane wczytane ? 

    CBox *eGetBBox(void);    // zwraca bounding box    
    
    template< class T > void SafeDelete( T*& pVal )
    {
        delete pVal;
        pVal = NULL;
    }
    
    template< class T > void SafeDeleteArray( T*& pVal )
    {
        delete[] pVal;
        pVal = NULL;
    }
    
    
private:	    
   
    bool        m_bActive;
    
    float       m_fX, m_fY, m_fIncX, m_fIncY;   
    
    float       m_fSizeX, m_fSizeY; // clipping, potrzebne zeby zapamietac rozmiar platformy, ktory jest rozny od rozmiaru tekstury
    
    CSprite     *m_pImage;   
	
    CBox        *m_pBoundBox;
    
};

#endif
