#include "GameSettings.h"

#pragma warning(disable : 4996)

CGameSettings::CGameSettings()
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    m_cMusic = 1;
    m_cSoundEffects = 1;
    
    m_cSelectedLanguage = 1;
    
    _iStartCount = 0;            // 0 = to jest pierwsze uruchomienie

    _iStartCount =  [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_iStartCount"];

    if (_iStartCount==0)    // zapisujemy nowe ustawienia jezeli to pierwszy raz
    {
        m_cMusic = 1;
        m_cSoundEffects = 1;
        m_cSelectedLanguage = 1;
        bSave();
    }

    _iStartCount++;
    
    [defaults setInteger:_iStartCount forKey:@"SHODAN9_GemsOfAtlantis_iStartCount"];
    
}

CGameSettings::~CGameSettings()
{
    
}

bool CGameSettings::bLoad(void)
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    _iStartCount =  [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_iStartCount"];

    m_cMusic =  [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_cMusic"];
    m_cSoundEffects =  [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_cSoundEffects"];
    m_cSelectedLanguage =  [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_cSelectedLanguage"];
    
    return true;
    
}

bool CGameSettings::bSave(void)
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    [defaults setInteger:_iStartCount forKey:@"SHODAN9_GemsOfAtlantis_iStartCount"];

    [defaults setInteger:m_cMusic forKey:@"SHODAN9_GemsOfAtlantis_cMusic"];
    [defaults setInteger:m_cSoundEffects forKey:@"SHODAN9_GemsOfAtlantis_cSoundEffects"];
    [defaults setInteger:m_cSelectedLanguage forKey:@"SHODAN9_GemsOfAtlantis_cSelectedLanguage"];
    
    [defaults synchronize];
    
    return true;
}


bool CGameSettings::isMSX(void)
{
	return m_cMusic;
}

bool CGameSettings::isSFX(void)
{
	return m_cSoundEffects;
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


	