#pragma warning(disable : 4996)
#pragma warning(disable : 4800)

#include "GameSettings.h"

CGameSettings::CGameSettings()
{
    m_cFullscreen = 1;
    m_cMusic = 1;
    m_cSoundEffects = 1;
    
    m_cSelectedLanguage = 1;
}

CGameSettings::~CGameSettings()
{
    
}

bool CGameSettings::bLoad(void)
{
    FILE *plik;
   
    plik = fopen(SETTINGS_FILE,"rb");
  
    if (plik == NULL)
        return false;
        
    fread(&m_cFullscreen,1,1,plik);
    fread(&m_cMusic,1,1,plik);
    fread(&m_cSoundEffects,1,1,plik);
    fread(&m_cSelectedLanguage,1,1,plik);
    
    fclose(plik);
    
    return true;
    
}

bool CGameSettings::bSave(void)
{
    FILE *plik;
    
    plik = fopen(SETTINGS_FILE,"wb");
    
    if (plik == NULL)
        return false;
    
    fwrite(&m_cFullscreen,1,1,plik);
    fwrite(&m_cMusic,1,1,plik);
    fwrite(&m_cSoundEffects,1,1,plik);
    fwrite(&m_cSelectedLanguage,1,1,plik);
    
    fclose(plik);
    
    return true;
    
}

bool CGameSettings::isFullscreen(void)
{
	return m_cFullscreen;
}

bool CGameSettings::isMSX(void)
{
	return m_cMusic;
}

bool CGameSettings::isSFX(void)
{
	return m_cSoundEffects;
}

void CGameSettings::isFullscreen(bool bState)
{
	if (bState)
	{
		m_cFullscreen = 1;
	}
	else
	{
		m_cFullscreen = 0;
	}
}

void CGameSettings::isMSX(bool bState)
{
	if (bState)
	{
		m_cMusic = 1;
	}
	else
	{
		m_cMusic = 0;
	}
}

void CGameSettings::isSFX(bool bState)
{
	if (bState)
	{
		m_cSoundEffects = 1;
	}
	else
	{
		m_cSoundEffects = 0;
	}
}


	