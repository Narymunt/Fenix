#ifndef _igame_touchbutton_
#define _igame_touchbutton_

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


class CTouchButton
{
	
public: 
	
    CTouchButton(int iX1, int iY1, int iX2, int iY2, char cIdle[], char cOnOver[],char cOnClick[]); // przycisk utworzony z 3 plikow
    
    CTouchButton(int iX1, int iY1, int iX2, int iY2, 
                 int iU1, int iV1, int iDU1, int iDV1, 
                 int iU2, int iV2, int iDU2, int iDV2, 
                 int iU3, int iV3, int iDU3, int iDV3,
                 char cTexture[]);  // przycisk utworzony z jednej textury np. 256x256
    
    ~CTouchButton();            // destruktor automatycznie zamyka stan   

    int Render(CTouch *pTouch);       // render zwraca info czy powinien być zamknięty i/lub przejść do innego stanu
    
    void SetPosition(int iX1, int iY1);
    void SetSize(int iXSize, int iYSize);
    
    void SetHotCoords(int iX1, int iY1, int iX2, int iY2);
    
    void SetUV(int iU1, int iV1, int iDU1, int iDV1, 
               int iU2, int iV2, int iDU2, int iDV2, 
               int iU3, int iV3, int iDU3, int iDV3);   // ustawia wspolrzedne z tekstury
    
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
    
    int         m_iU1, m_iV1, m_iDU1, m_iDV1;   // wspolrzedne idle na teskturze
    int         m_iU2, m_iV2, m_iDU2, m_iDV2;   // wspolrzedne idle na teskturze
    int         m_iU3, m_iV3, m_iDU3, m_iDV3;   // wspolrzedne idle na teskturze
    
    char        m_cType;        // 1 - tekstura
                                // 3 - 3 pliki 
    
    bool        m_bActive;
    
    CSprite     *m_pTexture;    // textura dla przycisku gdzie wszystkie stany są w jednym pliku
                 
    CSprite     *m_pIdle;       // stan idle
    CSprite     *m_pOnOver;     // palec znajduje się nad przyciskiem
    CSprite     *m_pOnClick;    // palec zdjęty z przycisku
	
};

#endif
