#ifndef _igame_box_
#define _igame_box_

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

// stan w trakcie wczytywania zasobów

class CBox
{

	
public: 
	
    CBox(float x1, float y1, float x2, float y2);
    ~CBox();            // destruktor automatycznie zamyka stan
    
    void Update(float x1, float y1, float x2, float y2);

    float   m_fx1, m_fy1, m_fx2, m_fy2;
    
private:	

    
	
};

#endif
