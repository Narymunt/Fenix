#pragma once

#include <stdio.h>
#include "Game.h"
//#include "ZipCheckbox.h"

class CGameSettings
{

public:

	CGameSettings();
    ~CGameSettings();
    
    bool    bLoad(void);
    bool    bSave(void);   

	bool	isFullscreen(void);
	bool	isMSX(void);
	bool	isSFX(void);

	void	isFullscreen(bool bState);
	void	isMSX(bool bState);
	void	isSFX(bool bState);

private:
    
    char    m_cFullscreen;
    char    m_cMusic;
    char    m_cSoundEffects;
    
    char    m_cSelectedLanguage;
    
};

