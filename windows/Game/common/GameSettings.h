// ustawienia uzytkownika, ktora sa zapisywane do pliku

#pragma once

#include <stdio.h>
#include "../Game.h"

class CGameSettings
{

public:

	CGameSettings();
    ~CGameSettings();
    
    bool    load(void);
    bool    save(void);   
    
    char    _isFullscreen;

	char    _isMSX;			// char zeby latwiej bylo to zapisac w pliku
    char    _isSFX;			// MSX = muzyka, SFX = efekty dzwiekowe
    
    char    _language;
    
};

