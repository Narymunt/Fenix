#include "AndroidFile.h"

CAndroidFile::CAndroidFile(char cFilename[])
{
	SDL_RWops	*plik = SDL_RWFromFile(cFilename, "rb");
	int iSize = 0;

	if (plik==NULL)
	{
		SDL_Log("[ERROR] : Nie mozna znalezc pliku: %s\n",cFilename);
	}
	else
	{
		SDL_RWseek(plik, 0, SEEK_END);
		iSize = SDL_RWtell(plik);
		SDL_RWseek(plik, 0, SEEK_SET);

		_pBuffer = new char[iSize];
		plik->read(plik,_pBuffer,iSize,1);

		SDL_FreeRW(plik);
	}

}

CAndroidFile::~CAndroidFile()
{

	delete []_pBuffer;
}


