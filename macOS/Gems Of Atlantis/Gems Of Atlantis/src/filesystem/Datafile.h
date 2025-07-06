// plik z zakodowanymi danymi

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Game.h"

class CDatafile
{

public:

	CDatafile(unsigned long ulOffset, unsigned long ulSize);
	CDatafile(char cFilename[]);
	~CDatafile();

	void Load(unsigned long ulOffset, unsigned long ulSize);	// wczytaj dane

	unsigned char *pBuffer(void);	// potrzebujemy tylko wskaznik na dane
	unsigned long ulSize(void);		// rozmiar zaalokowanych danych, kopiujemy, nie ma mozliwosci zeby bylo 0

private:

	unsigned char *_pBuffer;
	unsigned long _ulSize;
};

