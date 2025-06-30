#include "Screen.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 4715)

CScreen::CScreen(int iX, int iY, int iBpp,bool bFullScreen):
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false)
{

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
	return ;

	if (bFullScreen)
	{
		oglInit(iX, iY, iBpp, SDL_FULLSCREEN);
	}
	else
	{
		oglInit(iX, iY, iBpp, 0);
	}

	_iSizeX = iX;
	_iSizeY = iY;
	_iBpp = iBpp;
	_bFullscreen = bFullScreen;

	if (iX == 1024 && iY == 768) _isSDS = true;
	if (iX == 1366 && iY == 768) _isSDW = true;
	if (iX == 1920 && iY == 1080) _isHDW = true;
	if (iX == 2560 && iY == 1440) _isHDS = true;

	printf("manual screen %dx%d\n",iX,iY);

	Precalc();
}

// po kolei wybieramy najlepsze rozdzielczosci pelnoekranowe
// w koncu gdy nie uda sie ustalic zadnej, to ustawiamy rozdzielczosc biurka

CScreen::CScreen(bool bFullScreen) :
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false)
{
	const	SDL_VideoInfo	*pVideoInfo;

	_iSizeX = _iSizeY = 0;

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
	return ;

	// iMac 27"
	// pomimo tego ze ta rozdzielczosc nie jest kwadratowa, uzywamy opisu takiego jak dla 2048x1536

	if (oglInit(2560,1440,32,SDL_FULLSCREEN))
	{
		_iSizeX = 2560;
		_iSizeY = 1440;
		_bFullscreen = true;
		_iBpp = 32;
		_isHDS = true;
		printf("screen 2560x1440\n");
		return;
	}

	// HD

	if (oglInit(1920,1080,32,SDL_FULLSCREEN))
	{
		_iSizeX = 1920;
		_iSizeY = 1080;
		_bFullscreen = true;
		_iBpp = 32;
		_isHDW = true;
		printf("screen 1920x1080\n");
		return;
	}

	// half HD

	if (oglInit(1366,768,32,SDL_FULLSCREEN))
	{
		_iSizeX = 1366;
		_iSizeY = 768;
		_bFullscreen = true;
		_iBpp = 32;
		_isSDW = true;
		printf("screen 1366x768\n");
		return;
	}

	// 1024x768

	if (oglInit(1024,768,32,SDL_FULLSCREEN))
	{
		_iSizeX = 1024;
		_iSizeY = 768;
		_bFullscreen = true;
		_iBpp = 32;
		_isSDS = true;
		printf("screen 1024x768\n");
		return;
	}

	// poddaje sie - ustawiam rozdzielczosc biurka

	pVideoInfo = SDL_GetVideoInfo();

	_iSizeX = pVideoInfo->current_w;
	_iSizeY = pVideoInfo->current_h;
	_bFullscreen = bFullScreen;
	_iBpp = 32;

	if (bFullScreen)
	{
		oglInit(_iSizeX, _iSizeY, _iBpp, SDL_FULLSCREEN);
	}
	else
	{
		_iSizeX /=2 ; _iSizeY/=2;

		oglInit(_iSizeX, _iSizeY, _iBpp, 0);
	}

	Precalc();
}

CScreen::~CScreen()
{
	for (int i=0; i<_pDict.size(); i++)
		delete _pDict[i];

	_pDict.clear();
}

// wczytaj wszystkie wpisy <sprite>

void CScreen::InitDictionary(void)
{
	FILE	*plik;
	char linia[1024],cObjectName[512],cFullname[1024];
	int x,y;
	int	i=0,iCount=0;
	bool isCenter;
	float fPositionX, fPositionY, fPositionXI, fPositionYI;
	float fRotation, fRotationI, fAlfa, fAlfaI;
	float fScaleX, fScaleY, fScaleXI, fScaleYI;

	memset(linia,0,256);	// nie zawsze ta tablica jest czyszczona
	memset(cObjectName,0,256);
	memset(cFullname,0,256);

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
		printf("ERROR: no script file %s\n",SCRIPT_FILE);
	
	while (strcmp(linia,"<END>"))
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<SPRITE>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
			UpOnly(linia);

			fscanf(plik,"%d %d\n",&x,&y);	// wczytaj parametry ekranu

			if ((_iSizeX==x && _iSizeY==y)||(x==0 && y==0) )	// to jest wlasciwy obiekt
			{
				strcpy(cObjectName,linia);	// zachowaj nazwe
				
				fscanf(plik,"%s\n",linia);	// wczytaj nazwe pliku

				sprintf(cFullname,"%s",linia);	// przedrostek dodajemy samemu dla katalogu data/ , ale dla .zip i .dat juz nie

				fscanf(plik,"%s\n",linia);	// wczytaj parametr centrowania
				UpOnly(linia);

				!strcmp(linia,"C") ? isCenter = true : isCenter = false;

				fscanf(plik,"%f %f %f %f %f %f\n",&fPositionX, &fPositionY, &fScaleX, &fScaleY, &fRotation, &fAlfa);
				fscanf(plik,"%f %f %f %f %f %f\n",&fPositionXI, &fPositionYI, &fScaleXI, &fScaleYI, &fRotationI, &fAlfaI);

				_pDict.push_back(new CSpriteObject(cObjectName,x,y,cFullname));
				
				_pDict[iCount]->iScreenX(_iSizeX);
				_pDict[iCount]->iScreenY(_iSizeY);
				
				_pDict[iCount]->Position(fPositionX, fPositionY);
				_pDict[iCount]->PositionI(fPositionXI, fPositionYI);

				_pDict[iCount]->Scale(fScaleX, fScaleY);
				_pDict[iCount]->ScaleI(fScaleXI, fScaleYI);

				_pDict[iCount]->fRotation(fRotation);
				_pDict[iCount]->fRotationI(fRotationI);

				_pDict[iCount]->fAlfa(fAlfa);
				_pDict[iCount]->fAlfaI(fAlfaI);

				_pDict[iCount]->isCenter(isCenter);

//				printf("#%3d object : %s filename : %s\n",iCount,cObjectName,cFullname);

				iCount++;
			} // if 
		} // if <sprite>
	} // while <end>

	fclose(plik);

//	printf("%d objects created\n",_pDict.size());

}

int CScreen::iBpp(void)
{
	return _iBpp;
}

int CScreen::iSizeX(void)
{
	return _iSizeX;
}

int CScreen::iSizeY(void)
{
	return _iSizeY;
}

bool CScreen::isFullscreen(void)
{
	return _bFullscreen;
}

void CScreen::Precalc(void)
{
	float fIndex, fPixelSize;

	fIndex = 0;
	fPixelSize =  _iSizeX / 1920.0f  ;
	_fPixelX = fPixelSize;

	for (int i=0; i<1921; i++)
	{
		_iXTable[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	fIndex = 0;
	fPixelSize = _iSizeY / 1080.0f;
	_fPixelY = fPixelSize;

	for (int i=0; i<1081; i++)
	{
		_iYTable[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	printf("pixel size : %f x %f\n", _fPixelX, _fPixelY);
}

int CScreen::toX(int x)
{
	return _iXTable[x];
}

int CScreen::toY(int y)
{
	return _iYTable[y];
}

void CScreen::fPixelX(float f)
{
	_fPixelX = f;
}

float CScreen::fPixelX(void)
{
	return _fPixelX;
}

void CScreen::fPixelY(float f)
{
	_fPixelY = f;
}

float CScreen::fPixelY(void)
{
	return _fPixelY;
}

// zwraca nazwe dla danego numeru parametru
 
char *CScreen::pArg(int iParam)
{
	return _buffer;
}

// zwraca liczbe calkowita dla danego numeru parametru

int CScreen::iArg(int iParam)
{
	return 0;
}

// zwraca liczbe rzeczywista dla danego numeru parametru

float CScreen::fArg(int iParam)
{
	return 0.f;
}

char *CScreen::cObjectFilename(char cName[])		// zwroc nazwe pliku dla poszukiwanego obiektu
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->cFilename();
	}
}

float CScreen::fRotation(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fRotation();
	}
}

float CScreen::fRotationI(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fRotation();
	}
}

float CScreen::fPositionX(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionX();
	}
}

float CScreen::fPositionXI(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionXI();
	}
}

float CScreen::fPositionY(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionY();
	}
}

float CScreen::fPositionYI(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionYI();
	}
}

float CScreen::fScaleX(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleX();
	}
}

float CScreen::fScaleXI(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleXI();
	}
}

float CScreen::fScaleY(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleY();
	}
}

float CScreen::fScaleYI(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleYI();
	}
}

float CScreen::fAlfa(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fAlfa();
	}
}

float CScreen::fAlfaI(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fAlfaI();
	}
}

bool CScreen::isCenter(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->isCenter();
	}
}

bool CScreen::isSpriteObject(char cName[])
{
	for (int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return true;
	}
	return false;
}
