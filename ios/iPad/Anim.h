#ifndef _igame_anim_
#define _igame_anim_

#include "config.h"

#include <time.h>
#include <vector>
#include <list>

#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Touch.h"
#include "Sprite.h"

using namespace std;

// animacja (jako stos klatek)

class CAnim
{
	
public: 
	
    CAnim(char cFilename[], int iCount, int iSizeX, int iSizeY);
    ~CAnim(); 

    void Render(int iFrame);       // render na ekranie
    void Render(int iFrame, int iX, int iY);
    
    void    SetRotation(float fAngle);  // obracanie
    float   fGetRotation(void);         // zwraca kat
    
    void    SetAlfa(float fAlfa);       // ustawia przeźroczystość
    float   fGetAlfa(void);             // zwraca aktualną przeźroczystość
    
    void    SetPosition(float fX, float fY);    // ustawia współrzędne na ekranie
    void    AddPosition(float fAddX, float fAddY);      // zwiększa współrzędne
    
    void    SetPositionX(float fX);
    void    SetPositionY(float fY);
    
    float   fGetX(void);    // zwraca aktualny X
    float   fGetY(void);    // zwraca aktualny Y
    
    void    SetScale(float fScale);     // ustawia rozmiar 
    float   fGetScale(void);            // zwraca rozmiar
    
    void    SetVisible(bool bState);    // czy renderowany w kolejce ? 
    bool    bGetVisible(void);          // zwraca stan      

    int     iGetFrameCount(void);
    
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
    
    inline int iFrameCount(void) { return m_iCount; }
    
private:	
    
    int         m_iCount;       // ile klatek w animacji

    float       m_fAngle;       // aktualny kąt
    float       m_fX, m_fY;     // współrzędne na ekranie
    float       m_fScale;       // aktualna skala
    float       m_fAlfa;        // przezroczystość
    
    bool        m_bVisible;     // czy renderowany w kolejce 
    
    vector <CSprite*> m_pAnimation;
	
};

#endif
