#ifndef _igame_touch_
#define _igame_touch_

#include "config.h"

// obsługa ekranu dotykowego, utrzymanie stanu

class CTouch
{
	
public:  
	
    CTouch();
    ~CTouch();

    void Update(bool bPressed, bool bReleased, int iX, int iY, int iTap);
    
    bool isPressed(void);
    bool isReleased(void);
    
    inline void isPressed(bool b) { m_bPressed = b; }
    inline void isReleased(bool b) { m_bReleased = b; }
    
    int iGetX(void);
    int iGetY(void);
    
    int iGetTap(void);
    
    void Reset(void);
    
    inline float fClickDeltaX(void) { return _fClickDeltaX; }
    inline void fClickDeltaX(float f) { _fClickDeltaX = f; }
    
    inline float fClickDeltaY(void) { return _fClickDeltaY; }
    inline void fClickDeltaY(float f) { _fClickDeltaY = f; }
    
    inline int iStartX(void) { return _iStartX; }
    inline void iStartX(int i) { _iStartX = i; }
    
    inline int iStartY(void) { return _iStartY; }
    inline void iStartY(int i) { _iStartY = i; }
    
private:
	
    bool    m_bPressed;
    bool    m_bReleased;
    
    int     m_iX, m_iY;
    
    int     m_iTap;    
	
    int     _iStartX;
    int     _iStartY;
    
    float   _fClickDeltaX;
    float   _fClickDeltaY;
	
};

#endif
