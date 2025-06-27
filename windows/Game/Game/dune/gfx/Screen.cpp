/**
   Screen.cpp

   @author Jaros³aw N. Ro¿ynski

*/

#include "Screen.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 4715)

/**
   Konstruktor klasy.

   @param iX rozmiar x ekranu
   @param iY rozmiar y ekranu
   @param iBpp typ pixela
   @param bFullScreen czy tryb pe³noekranowy ?
*/

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

/**
   Konstruktor klasy.
   Po kolei wybieramy najlepsze rozdzielczosci pelnoekranowe
   W koncu gdy nie uda sie ustalic zadnej, to ustawiamy rozdzielczosc biurka

   @param iX rozmiar x ekranu
   @param iY rozmiar y ekranu
   @param iBpp typ pixela
   @param bFullScreen czy tryb pe³noekranowy ?
*/

CScreen::CScreen(bool bFullScreen) :
_isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false)
{
	const	SDL_VideoInfo	*pVideoInfo;
   float fPixelRatio;
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
      Precalc();
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
      Precalc();
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
      Precalc();
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
      Precalc();
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

   fPixelRatio = (float)(_iSizeX/_iSizeY);

   if (_iSizeX>=1500)
   {
      if (fPixelRatio > 1.5f)
         _isHDW = true;
      else
         _isHDS = true;
   }
   else
   {
      if (fPixelRatio > 1.5f)
         _isSDW = true;
      else
         _isSDS = true;
   }

	Precalc();
}

/**
   Destruktor klasy.

*/

CScreen::~CScreen()
{
	for (unsigned int i=0; i<_pDict.size(); i++)
		delete _pDict[i];

	_pDict.clear();
}

/**
   Wczytaj ca³y s³ownik, dziêki temu wyszukiwanie wpisów bêdzie odbywaæ siê w pamiêci, a nie w pliku. 
   Chodzi o to, aby unikn¹æ wczytywania non stop tego samego pliku przy wyszukiwaniu ka¿dego obiektu.
   Wyszukujemy wpisy <sprite>
*/

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

	memset(linia,0,1000);	// nie zawsze ta tablica jest czyszczona
	memset(cObjectName,0,500);
	memset(cFullname,0,1000);

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

				iCount++;
			} // if 
		} // if <sprite>
	} // while <end>

	fclose(plik);

}

/** 
   Przygotuj tablice przeliczeniowe.
*/

void CScreen::Precalc(void)
{
	float fIndex, fPixelSize;

   // HDW 1920x1080

	fIndex = 0;
	fPixelSize =  _iSizeX / 1920.0f  ;
	_fPixelX = fPixelSize;

	for (int i=0; i<1920; i++)
	{
		_iXTableHDW[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	fIndex = 0;
	fPixelSize = _iSizeY / 1080.0f;
	_fPixelY = fPixelSize;

	for (int i=0; i<1080; i++)
	{
		_iYTableHDW[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

   // HDS 2048x1536

	fIndex = 0;
	fPixelSize =  _iSizeX / 2048.0f  ;
	_fPixelX = fPixelSize;

	for (int i=0; i<2048; i++)
	{
		_iXTableHDS[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	fIndex = 0;
	fPixelSize = _iSizeY / 1536.0f;
	_fPixelY = fPixelSize;

	for (int i=0; i<1536; i++)
	{
		_iYTableHDS[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

   // SDW 1024x768

	fIndex = 0;
	fPixelSize =  _iSizeX / 1024.0f  ;
	_fPixelX = fPixelSize;

	for (int i=0; i<1024; i++)
	{
		_iXTableSDW[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	fIndex = 0;
	fPixelSize = _iSizeY / 768.0f;
	_fPixelY = fPixelSize;

	for (int i=0; i<768; i++)
	{
		_iYTableSDW[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

   // SDS 1366x768

	fIndex = 0;
	fPixelSize =  _iSizeX / 1366.0f  ;
	_fPixelX = fPixelSize;

	for (int i=0; i<1366; i++)
	{
		_iXTableSDS[i] = (int)fIndex;
		fIndex += fPixelSize;
	}

	fIndex = 0;
	fPixelSize = _iSizeY / 768.0f;
	_fPixelY = fPixelSize;

	for (int i=0; i<768; i++)
	{
		_iYTableSDS[i] = (int)fIndex;
		fIndex += fPixelSize;
	}
}

/**
   Zwraca rozmiar pixela.
   @return rozmiar ekranu / aktualne wymiary zrodlowe
*/

float CScreen::fPixelX(void)
{
   if (_isSDS)
      return (float)_iSizeX/1024.0f;
   
   if (_isSDW)
      return (float)_iSizeX/1366.0f;

   if (_isHDS)
      return (float)_iSizeX/2048.0f;
   
   if (_isHDW)
      return (float)_iSizeX/1920.0f;
}

/**
   Zwraca rozmiar pixela.
   @return rozmiar ekranu / aktualne wymiary zrodlowe
*/

float CScreen::fPixelY(void)
{
   if (_isSDS)
      return (float)_iSizeX/1024.0f;
   
   if (_isSDW)
      return (float)_iSizeX/1366.0f;

   if (_isHDS)
      return (float)_iSizeX/2048.0f;
   
   if (_isHDW)
      return (float)_iSizeX/1920.0f;

}

/**
   Zwraca rzeczywist¹ wspó³rzêdn¹ na ekranie, gdy operujemy na fikcyjnych liczbach.
   @param x gdzie na ekranie chcemy postawiæ pixel
   @return gdzie naprawde postawimy pixel
*/

int CScreen::getX(int x)
{
   if (_isSDS)
      return _iXTableSDS[x];

   if (_isSDW)
      return _iXTableSDW[x];

   if (_isHDS)
      return _iXTableHDS[x];

   if (_isHDW)
      return _iXTableHDW[x];
}

/**
   Zwraca rzeczywist¹ wspó³rzêdn¹ na ekranie, gdy operujemy na fikcyjnych liczbach.
   @param y gdzie na ekranie chcemy postawiæ pixel
   @return gdzie naprawde postawimy pixel
*/

int CScreen::getY(int y)
{
   if (_isSDS)
      return _iYTableSDS[y];

   if (_isSDW)
      return _iYTableSDW[y];

   if (_isHDS)
      return _iYTableHDS[y];

   if (_isHDW)
      return _iYTableHDW[y];
}

/**
   Zwraca nazwe dla danego numeru parametru.
   @param iParam szukany parametr
   @return string z szukan¹ nazw¹
*/
 
char *CScreen::pArg(int iParam)
{
	return _buffer;
}

/**
   Zwraca liczbe calkowita dla danego numeru parametru.
   @param iParam szukany parametr
   @return zawsze 0
*/

int CScreen::iArg(int iParam)
{
	return 0;
}

/**
   Zwraca liczbe rzeczywista dla danego numeru parametru
   @param iParam szukany parametr
   @return zawsze 0
*/

float CScreen::fArg(int iParam)
{
	return 0.f;
}

/**
   Zwroc nazwe pliku dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return nazwa pliku lub wartoœæ w postaci s³ownej
*/

char *CScreen::cObjectFilename(char cName[])	
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->cFilename();
	}
}

/**
   Zwroc parametr rotacji dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return rotacja 
*/

float CScreen::fRotation(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fRotation();
	}
}

/**
   Zwroc parametr inkrementatora rotacji dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return inkrementator rotacji
*/

float CScreen::fRotationI(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fRotation();
	}
}

/**
   Zwroc parametr x dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return x 
*/

float CScreen::fPositionX(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionX();
	}
}

/**
   Zwroc parametr inkrementacji x dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return inkrementator x
*/

float CScreen::fPositionXI(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionXI();
	}
}

/**
   Zwroc parametr y dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return xy
*/

float CScreen::fPositionY(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionY();
	}
}

/**
   Zwroc parametr inkrementacji y dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return inkrementator y
*/

float CScreen::fPositionYI(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fPositionYI();
	}
}

/**
   Zwroc parametr skali x dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return skala x 
*/

float CScreen::fScaleX(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleX();
	}
}

/**
   Zwroc parametr inkrementatora skali x dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return inkrementator skali x 
*/

float CScreen::fScaleXI(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleXI();
	}
}

/**
   Zwroc parametr skali y dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return skala y 
*/

float CScreen::fScaleY(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleY();
	}
}

/**
   Zwroc parametr inkrementator skali y dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return inkrementator skali y 
*/

float CScreen::fScaleYI(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fScaleYI();
	}
}

/**
   Zwroc parametr alfa dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return alfa 
*/

float CScreen::fAlfa(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fAlfa();
	}
}

/**
   Zwroc parametr inkrementatora alfa dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return inkrementator alfa 
*/


float CScreen::fAlfaI(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->fAlfaI();
	}
}

/**
   Zwroc parametr punktu piwotu dla poszukiwanego obiektu.
   @param cName szukany obiekt
   @return true jezeli piwot jest na œrodku obiektu, false je¿eli piwot jest lewym górnym rogiem
*/

bool CScreen::isCenter(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return _pDict[i]->isCenter();
	}
}

/**
   SprawdŸ czy istnieje dany obiekt w s³owniku.
   @param cName szukany obiekt
   @return true je¿eli obiekt znaleziony, false je¿eli nie
*/

bool CScreen::isSpriteObject(char cName[])
{
	for (unsigned int i=0; i<_pDict.size(); i++)
	{
		if (_pDict[i]->isName(cName))
			return true;
	}
	return false;
}
