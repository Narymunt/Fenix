#pragma once

// klasa do wczytywania plik�w z file.apk/assets/

#include <stdio.h>
#include <stdlib.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include "SDL.h"

class CAndroidFile
{

public:
	explicit		CAndroidFile(char cFilename[]);
	virtual			~CAndroidFile();

	inline unsigned int uiSize(void) { return _uiSize; }
	inline char *pBuffer(void) { return _pBuffer; }

private:

	unsigned int	_uiSize;
	char 	*_pBuffer;

};

