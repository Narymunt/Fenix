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
    
    int iGetX(void);
    int iGetY(void);
    
    int iGetTap(void);
    
private:
	
    bool    m_bPressed;
    bool    m_bReleased;
    
    int     m_iX, m_iY;
    
    int     m_iTap;    
	
	
};

#endif
