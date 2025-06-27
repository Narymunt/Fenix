#pragma warning(disable : 4996)
#pragma warning(disable : 4800)

#include "GameSettings.h"

GameSettings::GameSettings()
{
	_isFullscreen = 1;
	_isMSX = 1;
	_isSFX = 1;
	_language = 0;	// 0 czyli nieustawiony
}

GameSettings::~GameSettings()
{
    
}

bool GameSettings::load(void)
{
    FILE *plik;
   
    plik = fopen(SETTINGS_FILE,"rb");
  
    if (plik == NULL)
        return false;
        
    fread(&_isFullscreen,1,1,plik);
    fread(&_isMSX,1,1,plik);
    fread(&_isSFX,1,1,plik);
    fread(&_language,1,1,plik);
    
    fclose(plik);
    
    return true;   
}

bool GameSettings::save(void)
{
    FILE *plik;
    
    plik = fopen(SETTINGS_FILE,"wb");
    
    if (plik == NULL)
        return false;
    
    fwrite(&_isFullscreen,1,1,plik);
    fwrite(&_isMSX,1,1,plik);
    fwrite(&_isSFX,1,1,plik);
    fwrite(&_language,1,1,plik);
    
    fclose(plik);
    
    return true;
}


	