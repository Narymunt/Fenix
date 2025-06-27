#pragma once

#include <stdio.h>
#include <string.h>

class CGameSettings
{

public:

	CGameSettings();
    ~CGameSettings();
    
    bool    bLoad(void);
    bool    bSave(void);   

	bool	isMSX(void);
	bool	isSFX(void);

	void	isFullscreen(bool bState);
	void	isMSX(bool bState);
	void	isSFX(bool bState);

	inline char	cSelectedLanguage(void) { return m_cSelectedLanguage; }
	inline void	cSelectedLanguage(char c) { m_cSelectedLanguage = c; }

private:
    
    char    m_cMusic;
    char    m_cSoundEffects;
    
    char    m_cSelectedLanguage;
    
    int     _iStartCount;               // licznik uruchomien, jezeli 0 - to jest to pierwsze uruchomienie i zapisujemy nowe ustawienia
    
};

