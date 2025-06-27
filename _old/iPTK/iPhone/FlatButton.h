#ifndef _igame_flatbutton_
#define _igame_flatbutton_

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

#include "Touch.h"
#include "Sprite.h"


class CFlatButton
{
	
public: 
	
    CFlatButton(int iX1, int iY1, int iX2, int iY2, char cTexture[]); // przycisk utworzony z 1 obrazu
    
    CFlatButton(int iX1, int iY1, int iX2, int iY2, 
                 int iU1, int iV1, int iU2, int iV2, 
                 char cTexture[]);  // przycisk utworzony z jednej textury np. 256x256
    
    ~CFlatButton();            // destruktor automatycznie zamyka stan   

    int Render(CTouch *pTouch);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    int Render(CTouch *pTouch, int iX, int iY);
    
    void SetPosition(int iX1, int iY1);
    void SetSize(int iXSize, int iYSize);
    
    void SetHotCoords(int iX1, int iY1, int iX2, int iY2);
    
    void SetUV(int iU1, int iV1, int iU2, int iV2);   // ustawia wspolrzedne z tekstury
    
    bool isActive(void);    // czy dane wczytane ? 

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
    
    int         m_iX, m_iY;     // wspolrzedne na ekranie
    
    int         m_iXSize, m_iYSize; // rozmiar obrazka
    
    int         m_iHotX1, m_iHotY1, m_iHotX2, m_iHotY2;     // obszar w ktorym obiekt reaguje
    
    int         m_iU1, m_iV1, m_iU2, m_iV2;   // wspolrzedne idle na teskturze
       
    bool        m_bActive;
    
    CSprite     *m_pTexture;    // textura dla przycisku gdzie wszystkie stany są w jednym pliku                
	
};

#endif
