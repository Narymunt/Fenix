// sprite class

#include "Sprite.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CSprite::CSprite() :
_r(1), _g(1), _b(1), _a(1), _fSizeX(0), _fSizeY(0), _fOriginalSizeX(0), _fOriginalSizeY(0),m_bVisible(true)
{
    m_bVisible = false; // na razie bez obrazu więc nie renderujemy

    m_fAngle = 0.0f;
    m_fScale = 1.0f;
    m_fAlfa = 1.0f;
    m_fX = 0.0f;
    m_fY = 0.0f;
    
    m_iX1 = 0;
    m_iY1 = 0;
    m_iX2 = 0;
    m_iY2 = 0;  
    
}

// konstruktor z inicjalizacją

CSprite::CSprite(char cFilename[], int x1, int y1, int x2, int y2) :
_r(1), _g(1), _b(1), _a(1)
{
    bool isLoad = false;
    
    m_pImage = KPTK::createKGraphic();
    
    isLoad = m_pImage->loadPicture(cFilename);

    if (!isLoad)
        printf("[ERROR]: nie znaleziono żadnego pliku dla %s\n",cFilename);
    
    m_fAngle = 0.0f;
    m_fScale = 1.0f;
    m_fAlfa = 1.0f;
    m_fX = 0.0f;
    m_fY = 0.0f;  
    
    // wspolrzedne na teksturze
    
    m_iX1 = x1; 
    m_iY1 = y1; 
    m_iX2 = x2; 
    m_iY2 = y2; 
    
    _fOriginalSizeX = x2 - x1;
    _fOriginalSizeY = y2 - y1;
    
    _fSizeX = _fOriginalSizeX;
    _fSizeY = _fOriginalSizeY;
    
    m_bVisible = true;  // bedzie renderowany w kolejce
}

CSprite::CSprite(char cFilename[]) :
_r(1), _g(1), _b(1), _a(1)
{
    bool isLoad = false;
    
    m_pImage = KPTK::createKGraphic();
    
    isLoad = m_pImage->loadPicture(cFilename);
    
    if (!isLoad)
        printf("[ERROR]: nie znaleziono żadnego pliku dla %s\n",cFilename);
    
    m_iX1 = m_iY1 = 0;
    
    m_iX2 = m_pImage->getTextureWidth();
    m_iY2 = m_pImage->getTextureHeight();
    
    m_fAngle = 0.0f;
    m_fScale = 1.0f;
    m_fAlfa = 1.0f;
    m_fX = 0.0f;
    m_fY = 0.0f;
    
    // wspolrzedne na teksturze
   
    
    _fOriginalSizeX = m_iX2 - m_iX1;
    _fOriginalSizeY = m_iY2 - m_iY1;
    
    _fSizeX = _fOriginalSizeX;
    _fSizeY = _fOriginalSizeY;
    
    m_bVisible = true;  // bedzie renderowany w kolejce
}



CSprite::CSprite(char cFilename[], int iOS) :
m_iX1(0), m_iY1(0), m_fAngle(0.0f), m_fScale(1.0f), m_fAlfa(1.0f), _r(1), _g(1), _b(1), _a(1),m_fX(0.0f),m_fY(0.0f),m_bVisible(true)
{
    char cBuffer[200];
    bool isLoad;
    
    
    isLoad = false;
    m_pImage = KPTK::createKGraphic();
    
    switch (iOS)
    {
        case IPHONE4:
            sprintf(cBuffer,"%s_960.png",cFilename);
            m_iX2 = IPHONE4_X;
            m_iY2 = IPHONE4_Y;
        break;
            
        case IPHONE5:
            sprintf(cBuffer,"%s_1136.png",cFilename);
            m_iX2 = IPHONE5_X;
            m_iY2 = IPHONE5_Y;
            break;
        
        case IPAD:
            sprintf(cBuffer,"%s_1024.png",cFilename);
            m_iX2 = IPAD_X;
            m_iY2 = IPAD_Y;
            break;

        case IPAD_HD:
            sprintf(cBuffer,"%s_2048.png",cFilename);
            m_iX2 = IPAD_HD_X;
            m_iY2 = IPAD_HD_Y;
            break;
    }
    
    isLoad = m_pImage->loadPicture(cBuffer);
    
    if (isLoad)
    {
        m_bVisible = true;
        _fOriginalSizeX = m_iX2 - m_iX1;
        _fOriginalSizeY = m_iY2 - m_iY1;
        
        _fSizeX = _fOriginalSizeX;
        _fSizeY = _fOriginalSizeY;
        return;
    }

    switch (iOS)
    {
        case IPHONE4:
            sprintf(cBuffer,"%s_960.jpg",cFilename);
            m_iX2 = IPHONE4_X;
            m_iY2 = IPHONE4_Y;
            break;
            
        case IPHONE5:
            sprintf(cBuffer,"%s_1136.jpg",cFilename);
            m_iX2 = IPHONE5_X;
            m_iY2 = IPHONE5_Y;
            break;
            
        case IPAD:
            sprintf(cBuffer,"%s_1024.jpg",cFilename);
            m_iX2 = IPAD_X;
            m_iY2 = IPAD_Y;
            break;
            
        case IPAD_HD:
            sprintf(cBuffer,"%s_2048.jpg",cFilename);
            m_iX2 = IPAD_HD_X;
            m_iY2 = IPAD_HD_Y;
            break;
    }
    
    isLoad = m_pImage->loadPicture(cBuffer);
    
    if (isLoad)
    {
        m_bVisible = true;

        _fOriginalSizeX = m_iX2 - m_iX1;
        _fOriginalSizeY = m_iY2 - m_iY1;
        
        _fSizeX = _fOriginalSizeX;
        _fSizeY = _fOriginalSizeY;
        
        m_fX = 0.0f;
        m_fY = 0.0f;
        
        return;
    }

    
    // nie znaleziono o zadanym wymiarze, dobieramy ze zbliżonego *.PNG
    
    switch (iOS)
    {
        case IPHONE4:
            SafeDelete(m_pImage);
            m_pImage = KPTK::create(1136,640);
            sprintf(cBuffer,"%s_1136.png",cFilename);
            m_iX2 = IPHONE5_X;
            m_iY2 = IPHONE5_Y;
            m_fX = -88; // centrujemy w poziomie
            m_fY = 0;
            break;
            
        case IPAD_HD:
            SafeDelete(m_pImage);
            m_pImage = KPTK::create(1024,768);
            sprintf(cBuffer,"%s_1024.png",cFilename);
            m_iX2 = IPAD_X;
            m_iY2 = IPAD_Y;
            break;
    }
    
    isLoad = m_pImage->loadPicture(cBuffer);
    
    if (isLoad)
    {
        m_bVisible = true;
        _fOriginalSizeX = m_iX2 - m_iX1;
        _fOriginalSizeY = m_iY2 - m_iY1;
        
        _fSizeX = _fOriginalSizeX;
        _fSizeY = _fOriginalSizeY;
        
        m_fX = 0.0f;
        m_fY = 0.0f;
        
        return;
    }
    
    // nie znaleziono o zadanym wymiarze, dobieramy ze zbliżonego *.JPG
    
    switch (iOS)
    {
        case IPHONE4:
            SafeDelete(m_pImage);
            m_pImage = KPTK::create(1136,640);
            sprintf(cBuffer,"%s_1136.jpg",cFilename);
            m_iX2 = IPHONE5_X;
            m_iY2 = IPHONE5_Y;
            m_fX = -88; // centrujemy w poziomie
            
            break;
            
        case IPAD_HD:
            SafeDelete(m_pImage);
            m_pImage = KPTK::create(1024,768);
            sprintf(cBuffer,"%s_1024.jpg",cFilename);
            m_iX2 = IPAD_X;
            m_iY2 = IPAD_Y;
            break;
    }
    
    isLoad = m_pImage->loadPicture(cBuffer);
    
    if (isLoad)
    {
        m_bVisible = true;
        _fOriginalSizeX = m_iX2 - m_iX1;
        _fOriginalSizeY = m_iY2 - m_iY1;
        
        _fSizeX = _fOriginalSizeX;
        _fSizeY = _fOriginalSizeY;

        m_fX = 0.0f;
        m_fY = 0.0f;

        return;
    }
    
    
    if (!isLoad)
        printf("[ERROR]: nie znaleziono żadnego pliku dla %s\n",cFilename);
    

    
}

// destruktor

CSprite::~CSprite()
{
    SafeDelete(m_pImage);    
    m_bVisible = false;
    
}

// renderowanie na ekranie

void CSprite::Render(void)
{
    if (m_bVisible)
    {
        m_pImage->setBlitColor(_r, _g, _b, _a);
        m_pImage->blitAlphaRectFx(m_iX1, m_iY1, m_iX2, m_iY2, m_fX, m_fY, m_fAngle, m_fScale, m_fAlfa);         
    }

}

void CSprite::Render(float fX, float fY)
{
    SetPosition(fX,fY);

    if (m_bVisible)
    {
        m_pImage->setBlitColor(_r, _g, _b, _a);
        m_pImage->blitAlphaRectFx(m_iX1, m_iY1, m_iX2, m_iY2, m_fX, m_fY, m_fAngle, m_fScale, m_fAlfa);
    }
    
}

void CSprite::Render(float fX, float fY, float fAlpha, float fAngle)
{
    m_pImage->setBlitColor(_r, _g, _b, _a);
    SetPosition(fX,fY);
    SetAlfa(fAlpha);
    SetRotation(fAngle);
    Render();
}

void CSprite::Render(float fX, float fY, float fAlpha)
{
    m_pImage->setBlitColor(_r, _g, _b, _a);
    SetPosition(fX,fY);
    SetAlfa(fAlpha);
    Render();
}


void CSprite::RenderC(void)
{
    if (m_bVisible)
    {
        m_pImage->setBlitColor(_r, _g, _b, _a);
        m_pImage->blitAlphaRectFx(m_iX1, m_iY1, m_iX2, m_iY2, m_fX-(_fSizeX/2), m_fY-(_fSizeY/2), m_fAngle, m_fScale, m_fAlfa);
    }
}

void CSprite::Position(float fX, float fY)
{
    m_fX = fX;
    m_fY = fY;
}

// ustawianie kąta

void CSprite::SetRotation(float fAngle)
{
    m_fAngle = fAngle;
}

// zwraca kąta

float CSprite::fGetRotation(void)
{
    return m_fAngle;
}

// ustawianie alfy

void CSprite::SetAlfa(float fAlfa)
{
    m_fAlfa = fAlfa;
}

float CSprite::fGetAlfa(void)
{
    return m_fAlfa;
}

void CSprite::SetPosition(float fX, float fY)
{
    m_fX = fX;
    m_fY = fY;
}

void CSprite::AddPosition(float fAddX, float fAddY)
{
    m_fX += fAddX;
    m_fY += fAddY;    
}

void CSprite::SetPositionX(float fX)
{
    m_fX = fX;
}

void CSprite::SetPositionY(float fY)
{
    m_fY = fY;
}

float CSprite::fGetX(void)
{
    return m_fX;
}

float CSprite::fGetY(void)
{
    return m_fY;
}

void CSprite::SetScale(float fScale)
{
    m_fScale = fScale;
    
    _fSizeX = _fOriginalSizeX * m_fScale;
    _fSizeY = _fOriginalSizeY * m_fScale;
}

float CSprite::fGetScale(void)
{
    return m_fScale;
}

void CSprite::SetVisible (bool bState)
{
    m_bVisible = bState;
}

bool CSprite::bGetVisible(void)
{
    return m_bVisible;
}

void CSprite::SetTexture(int x1, int y1, int x2, int y2)
{
    m_iX1 = x1; 
    m_iY1 = y1; 
    m_iX2 = x2; 
    m_iY2 = y2;
}

int CSprite::iGetTextureX1(void)
{
    return m_iX1;
}

int CSprite::iGetTextureY1(void)
{
    return m_iY1;
}

int CSprite::iGetTextureX2(void)
{
    return m_iX2;
}

int CSprite::iGetTextureY2(void)
{
    return m_iY2;
}

void CSprite::Color(float r, float g, float b, float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

void CSprite::Color(float r, float g, float b)
{
    _r = r;
    _g = g;
    _b = b;
}

void CSprite::Scale(float x, float y)
{
    SetScale(x);
}
