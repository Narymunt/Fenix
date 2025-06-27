// profile - profil gracza 
// zawiera w srodku profile dla 8 uzytkownikow / graczy

#pragma once

#include <stdio.h>
#include <string.h>
#include "config.h"

class CScreen
{

public:

	CScreen(int iOS);
	~CScreen();

    inline int iSizeX(void) { return _iSizeX; }
    inline void iSizeX(int i) { _iSizeX = i; }
    
    inline int iSizeY(void) { return _iSizeY; }
    inline void iSizeY(int i) { _iSizeY = i; }
    
    inline int iOS(void) { return _iOS; }
    inline void iOS(int i) { _iOS = i; }
    
private:

    int             _iSizeX;
    int             _iSizeY;
    int             _iOS;
    

};

