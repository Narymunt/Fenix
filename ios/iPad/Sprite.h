#ifndef _igame_sprite_
#define _igame_sprite_

#include "config.h"

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

// sprite opisuje pojedyńczy obraz i jego parametry

class CSprite
{
	
public:
	
    CSprite();
    CSprite(char cFilename[]);                                          // współrzędne textur odczytaj z pliku
    CSprite(char cFilename[], int x1, int y1, int x2, int y2);
    CSprite(char cFilename[], int iOS);                                 // nazwa sprite generowana, dla caloekranowych
	~CSprite();
    
    void    Render(void);                                               // rysuje obraz na ekranie
    
    void    Render(float fX, float fY);
    void    Render(float fX, float fY, float fAlpha);
    void    Render(float fX, float fY, float fAlpha, float fAngle);
    
    void    RenderC(void);
    
    inline void Render(int fX, int fY) { Render((float)fX,(float)fY); }
    
    void    SetRotation(float fAngle);                                  // obracanie
    float   fGetRotation(void);                                         // zwraca kat
    
    inline void fRotation(float f) { m_fAngle = f; }
    inline float fRotation(void) { return m_fAngle; }
    
    void    SetAlfa(float fAlfa);                                       // ustawia przeźroczystość
    float   fGetAlfa(void);                                             // zwraca aktualną przeźroczystość
    
    inline void fAlfa(float f) { m_fAlfa = f; }
    inline float fAlfa(void) { return m_fAlfa; }
    
    void    SetPosition(float fX, float fY);                            // ustawia współrzędne na ekranie
    void    AddPosition(float fAddX, float fAddY);                      // zwiększa współrzędne
    void    Position(float fX, float fY);
    
    void    SetPositionX(float fX);
    void    SetPositionY(float fY);
    
    float   fGetX(void);                                                // zwraca aktualny X
    float   fGetY(void);                                                // zwraca aktualny Y
    
    void    SetScale(float fScale);                                     // ustawia rozmiar
    float   fGetScale(void);                                            // zwraca rozmiar
    void    Scale(float x, float y);
    
    void    SetVisible(bool bState);                                    // czy renderowany w kolejce ?
    bool    bGetVisible(void);                                          // zwraca stan
    
    void    SetTexture(int x1, int y1, int x2, int y2);                 // zmiana współrzędnych tekstury
    
    int     iGetTextureX1(void);
    int     iGetTextureY1(void);
    int     iGetTextureX2(void);
    int     iGetTextureY2(void);    
    
    void    Color(float r, float g, float b, float a);
    void    Color(float r, float g, float b);
    
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
    
    
    inline void fSizeX(float f) { _fSizeX = f; }
    inline float fSizeX(void) { return _fSizeX; }

    inline void fSizeY(float f) { _fSizeY = f; }
    inline float fSizeY(void) { return _fSizeY; }
    
    inline void fOriginalSizeX(float f) { _fOriginalSizeX = f; }
    inline float fOriginalSizeX(void) { return _fOriginalSizeX; }
    
    inline void fOriginalSizeY(float f) { _fOriginalSizeY = f; }
    inline float fOriginalSizeY(void) { return _fOriginalSizeY; }
    
    
    
private:
	
    KGraphic	*m_pImage;		// sprite loaded from image ( JPEG, PNG, BMP.. )

    float       m_fAngle;       // aktualny kąt
    float       m_fX, m_fY;     // współrzędne na ekranie
    float       m_fScale;       // aktualna skala
    float       m_fAlfa;        // przezroczystość
    
    bool        m_bVisible;     // czy renderowany w kolejce 
	
    int         m_iX1, m_iY1, m_iX2, m_iY2;     // współrzędne na teksturze
	
    float       _r, _g, _b, _a;
  
    float       _fSizeX, _fSizeY;
    float       _fOriginalSizeX, _fOriginalSizeY;
    
};

#endif
