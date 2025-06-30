#ifndef _igame_debug_
#define _igame_debug_

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

void DebugText(int iX, int iY, char cText[])
{
    KGraphic	*	kDebugText;
    
    kDebugText = KPTK::createKGraphic();
    kDebugText->loadText(cText, "Arial", 24);
    kDebugText->setBlitColor(1,0,0,1);
    
    kDebugText->blitAlphaRectFx(0, 0, kDebugText->getTextureWidth(), kDebugText->getTextureHeight(), iX, iY, 0, 1, 1); 
    
}


#endif
