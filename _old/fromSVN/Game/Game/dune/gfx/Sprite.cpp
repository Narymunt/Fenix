/**
   Sprite.cpp

*/

#include "Sprite.h"
#include "../io/Zip.h"
#include "../io/Unzip.h"

#pragma warning(disable : 4996)

/**
   Konstruktor klasy inicjalizuj¹cy ze skryptu.
   @param pScreen wskaŸnik do ekranu
   @param cObjectName nazwa sprite
*/

CSprite::CSprite(CScreen *pScreen, char cObjectName[]) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f)
{
	FILE	*plik;
	char linia[1024],cFullname[1024];
	int x,y;
	HZIP	hZipFile;
	ZIPENTRY ze;
	char	*pTempBuffer;		// dla spakowanych / rozpakowanych plikow
	int		i=0;
	SDL_RWops *rw;
	CDatafile *pDatafile;

	_pSprite = NULL;
	memset(linia,0,1000);	// nie zawsze ta tablica jest czyszczona

	if (pScreen->isSpriteObject(cObjectName))
	{
		// szukamy w datafile, w pliku .zip

		pDatafile = new CDatafile(pScreen->cObjectFilename(cObjectName));       // szukamy ze s³ownika
		rw = SDL_RWFromMem(pDatafile->pBuffer(), pDatafile->ulSize());
		_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
		delete pDatafile;

		if (_pSprite!=NULL)
		{
			_fSizeX = (float) _pSprite->w;
			_fSizeY = (float) _pSprite->h;

			_fPositionX = pScreen->fPositionX(cObjectName);
			_fPositionY = pScreen->fPositionY(cObjectName);
			_fPositionXI = pScreen->fPositionXI(cObjectName);
			_fPositionYI = pScreen->fPositionYI(cObjectName);

			_fScaleX = pScreen->fScaleX(cObjectName);
			_fScaleY = pScreen->fScaleY(cObjectName);
			_fScaleXI = pScreen->fScaleXI(cObjectName);
			_fScaleYI = pScreen->fScaleYI(cObjectName);

			_fRotation = pScreen->fRotation(cObjectName);
			_fRotationI = pScreen->fRotationI(cObjectName);
			
			_a = pScreen->fAlfa(cObjectName);
			_fAlfaI = pScreen->fAlfaI(cObjectName);

			pScreen->isCenter(cObjectName) ? _isCenter = true : _isCenter = false;

			_fSizeX = (float) _pSprite->w;
			_fSizeY = (float) _pSprite->h;

			return;
		}

		// szukamy ze slownika, w katalogu data/

		sprintf(cFullname,"data/%s",pScreen->cObjectFilename(cObjectName));		
		_pSprite = oglFromSurfaceFree(IMG_Load(cFullname));

		if (_pSprite!=NULL)
		{
			_fSizeX = (float) _pSprite->w;
			_fSizeY = (float) _pSprite->h;

			_fPositionX = pScreen->fPositionX(cObjectName);
			_fPositionY = pScreen->fPositionY(cObjectName);
			_fPositionXI = pScreen->fPositionXI(cObjectName);
			_fPositionYI = pScreen->fPositionYI(cObjectName);

			_fScaleX = pScreen->fScaleX(cObjectName);
			_fScaleY = pScreen->fScaleY(cObjectName);
			_fScaleXI = pScreen->fScaleXI(cObjectName);
			_fScaleYI = pScreen->fScaleYI(cObjectName);

			_fRotation = pScreen->fRotation(cObjectName);
			_fRotationI = pScreen->fRotationI(cObjectName);
			
			_a = pScreen->fAlfa(cObjectName);
			_fAlfaI = pScreen->fAlfaI(cObjectName);

			pScreen->isCenter(cObjectName) ? _isCenter = true : _isCenter = false;
		}

      // nie znaleŸliœmy pliku na podstawie klucza podanego do skryptu, szukamy wg. nazwy pliku 

		if (_pSprite==NULL)	// nie wczytalismy sprite z katalogu .dat, sprobojemy z pliku .zip
		{
			if ((hZipFile = OpenZip(MAIN_RESOURCE, MAIN_PASSWORD))!=NULL)
			{
				FindZipItem(hZipFile,pScreen->cObjectFilename(cObjectName),true,&i,&ze); // znajdz plik do wczytania
				pTempBuffer = new char[ze.unc_size]; // przydziel w pamieci miejsce na rozpakowane dane
				UnzipItem(hZipFile,i,pTempBuffer,ze.unc_size);
				rw = SDL_RWFromMem(pTempBuffer, ze.unc_size);
				_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
				delete []pTempBuffer;
				CloseZip(hZipFile);				
			}
		}

		if (_pSprite!=NULL)
		{
			_fSizeX = (float) _pSprite->w;
			_fSizeY = (float) _pSprite->h;

         // tutaj nie znajdzie parametrów, wiêc wiêkszoœæ zostanie ustawiona na 0

			_fPositionX = pScreen->fPositionX(cObjectName);
			_fPositionY = pScreen->fPositionY(cObjectName);
			_fPositionXI = pScreen->fPositionXI(cObjectName);
			_fPositionYI = pScreen->fPositionYI(cObjectName);

			_fScaleX = pScreen->fScaleX(cObjectName);
			_fScaleY = pScreen->fScaleY(cObjectName);
			_fScaleXI = pScreen->fScaleXI(cObjectName);
			_fScaleYI = pScreen->fScaleYI(cObjectName);

			_fRotation = pScreen->fRotation(cObjectName);
			_fRotationI = pScreen->fRotationI(cObjectName);
			
			_a = pScreen->fAlfa(cObjectName);
			_fAlfaI = pScreen->fAlfaI(cObjectName);

			pScreen->isCenter(cObjectName) ? _isCenter = true : _isCenter = false;
		}		
	}	// isSpriteObject

	// nie znaleziono w slowniku ? 

	if (_pSprite==NULL)
	{
		printf(" nie znaleziono w slowniku : %s\n",cObjectName);
	}
	else
	{
		return;
	}

	// szukamy ze skryptu

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
		printf("ERROR: no script file %s\n",SCRIPT_FILE);

	while (strcmp(linia,"<END>") && _pSprite==NULL)
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<SPRITE>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
			UpOnly(linia);

			fscanf(plik,"%d %d\n",&x,&y);	// wczytaj parametry ekranu

			if (!strcmp(linia,cObjectName)) 	// to jest wlasciwy obiekt
			{
				if ( (x==0&&y==0) || (pScreen->iSizeX()==x && pScreen->iSizeY()==y) )
				{
					fscanf(plik,"%s\n",linia);	// wczytaj nazwe pliku

					sprintf(cFullname,"data/%s",linia);

					_pSprite = oglFromSurfaceFree(IMG_Load(cFullname));

					if (!_pSprite)	// nie znaleziono w katalogu data wiec szukamy w paczce zip
					{
						if ((hZipFile = OpenZip(MAIN_RESOURCE, MAIN_PASSWORD))!=NULL)
						{
							FindZipItem(hZipFile,linia,true,&i,&ze); // znajdz plik do wczytania
							pTempBuffer = new char[ze.unc_size]; // przydziel w pamieci miejsce na rozpakowane dane
							UnzipItem(hZipFile,i,pTempBuffer,ze.unc_size);
							rw = SDL_RWFromMem(pTempBuffer, ze.unc_size);
							_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
							delete []pTempBuffer;
							CloseZip(hZipFile);				
						}
					}

					if (!_pSprite)
						printf("ERROR : %s not found !\n",linia);

					_fSizeX = (float) _pSprite->w;
					_fSizeY = (float) _pSprite->h;

					fscanf(plik,"%s\n",linia);	// wczytaj parametr centrowania
					UpOnly(linia);

					!strcmp(linia,"C") ? _isCenter = true : _isCenter = false;

					fscanf(plik,"%f %f %f %f %f %f\n",&_fPositionX, &_fPositionY, &_fScaleX, &_fScaleY, &_fRotation, &_a);
					fscanf(plik,"%f %f %f %f %f %f\n",&_fPositionXI, &_fPositionYI, &_fScaleXI, &_fScaleYI, &_fRotationI, &_fAlfaI);
				} // if x & y
			} // if 
		} // if <sprite>
	} // while <end>

	if (_pSprite==NULL)
		printf("ERROR: object %s screenX %d screenY %d - not found in script file!\n",cObjectName,pScreen->iSizeX(),pScreen->iSizeY());

	fclose(plik);

}

/**
   Konstruktor klasy inicjalizuj¹cy bez skryptu.
   @param cFilename szukany plik w spakowanym archiwum, a potem w katalogu data/ 
*/

CSprite::CSprite(char cFilename[]) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f)
{
	HZIP	hZipFile;
	ZIPENTRY ze;
	char	*pTempBuffer;		// dla spakowanych / rozpakowanych plikow
	int		i=0;
	SDL_RWops *rw;
	CDatafile	*pDatafile;

	_pSprite = NULL;

	// szukamy w datafile, w pliku spakowanym .zip

	pDatafile = new CDatafile(cFilename);
	rw = SDL_RWFromMem(pDatafile->pBuffer(), pDatafile->ulSize());
	_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
	delete pDatafile;

	if (!_pSprite)
	{
		_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));
	}

	if (!_pSprite)	// nie znaleziono w katalogu data wiec szukamy w paczce zip
	{
		if ((hZipFile = OpenZip(MAIN_RESOURCE, MAIN_PASSWORD))!=NULL)
		{
			FindZipItem(hZipFile,cFilename,true,&i,&ze); // znajdz plik do wczytania
			pTempBuffer = new char[ze.unc_size]; // przydziel w pamieci miejsce na rozpakowane dane
			UnzipItem(hZipFile,i,pTempBuffer,ze.unc_size);
			rw = SDL_RWFromMem(pTempBuffer, ze.unc_size);
			_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
			delete []pTempBuffer;
			CloseZip(hZipFile);				
		}
	}

	if (!_pSprite)
		printf("ERROR : %s not found!\n",cFilename);

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = 0.0f;
	_fPositionY = 0.0f;

	// incrementators

	_fRotationI = 0.0f;

	_ulRenderTime = 0;
}

/**
   Konstruktor klasy inicjalizuj¹cy ze skryptu.
   @param cFilename nazwa szukanego obiektu
   @param pScreen wskaŸnik do ekranu
*/

CSprite::CSprite(char cFilename[], CScreen *pScreen) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f)
{
	HZIP	hZipFile;
	ZIPENTRY ze;
	char	*pTempBuffer;		// dla spakowanych / rozpakowanych plikow
	int		i=0;
	SDL_RWops *rw;
	CDatafile	*pDatafile;

	_pSprite = NULL;

	// szukamy w datafile

	pDatafile = new CDatafile(cFilename);
	rw = SDL_RWFromMem(pDatafile->pBuffer(), pDatafile->ulSize());
	_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
	delete pDatafile;

	// nie udalo sie - sproboj z katalogu data/

	if (!_pSprite)
	{
		_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));
	}

	if (!_pSprite)	// nie znaleziono w katalogu data wiec szukamy w paczce zip
	{
		if ((hZipFile = OpenZip(MAIN_RESOURCE, MAIN_PASSWORD))!=NULL)
		{
			FindZipItem(hZipFile,cFilename,true,&i,&ze); // znajdz plik do wczytania
			pTempBuffer = new char[ze.unc_size]; // przydziel w pamieci miejsce na rozpakowane dane
			UnzipItem(hZipFile,i,pTempBuffer,ze.unc_size);
			rw = SDL_RWFromMem(pTempBuffer, ze.unc_size);
			_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));
			delete []pTempBuffer;
			CloseZip(hZipFile);				
		}
	}

	if (!_pSprite)
		printf("ERROR : %s not found!\n",cFilename);

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = 0.0f;
	_fPositionY = 0.0f;

	// incrementators

	_fRotationI = 0.0f;

	_ulRenderTime = 0;
}

/**
   Konstruktor klasy inicjalizuj¹cy bez skryptu.
   @param cFilename nazwa pliku
   @param iX wspó³rzêdna x na ekranie
   @param iY wspó³rzêdna y na ekranie
*/

CSprite::CSprite(char cFilename[], int iX, int iY) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_ulRenderTime = 0;
}

/**
   Konstruktor klasy inicjalizuj¹cy bez skryptu.
   @param cFilename nazwa pliku
   @param iX wspó³rzêdna x na ekranie
   @param iY wspó³rzêdna y na ekranie
   @param fX skala X
   @param fY skala Y
*/

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = fX;
	_fScaleY = fY;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_ulRenderTime = 0;
}

/**
   Konstruktor klasy inicjalizuj¹cy bez skryptu.
   @param cFilename nazwa pliku
   @param iX wspó³rzêdna x na ekranie
   @param iY wspó³rzêdna y na ekranie
   @param fX skala X
   @param fY skala Y
   @param fRot rotacja
*/

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = fRot;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = fX;
	_fScaleY = fY;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_ulRenderTime = 0;
}

// init sprite x,y,alfa

CSprite::CSprite(char cFilename[], int iX, int iY, float fAlfa) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(fAlfa)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_ulRenderTime = 0;
}

// init sprite

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(fAlfa)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = fRot;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = fX;
	_fScaleY = fY;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_ulRenderTime = 0;
}

// init sprite with alfa at top left corner

CSprite::CSprite(char cFilename[], float fAlfa) :
_r(1.0f), _g(1.0f), _b(1.0f), _a(fAlfa)
{

	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = 0.0f;
	_fPositionY = 0.0f;

	_ulRenderTime = 0;
}

// destructor

CSprite::~CSprite()
{
	if (_pSprite!=NULL)
	{
		oglFreeTexture(_pSprite);
		_pSprite = NULL;
	}
}

void CSprite::Render(int x, int y, float a)
{
	Position((float)x,(float)y);
	fAlfa(a);
	Render();
}

// render sprite using top left coords

void CSprite::Render(void)
{
	oglBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _r, _g, _b, _a, _fScaleX, _fScaleY, _fRotation);
}

// render sprite using middle of texture coords

void CSprite::RenderC(void)
{
	oglCBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _r, _g, _b, _a, _fScaleX, _fScaleY, _fRotation);
}

// updates parameters after rendering

void CSprite::Update(void)
{
	oglBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _r, _g, _b, _a, _fScaleX, _fScaleY, _fRotation);

	_fRotation += _fRotationI;

	_fScaleX += _fScaleXI;
	_fScaleY += _fScaleYI;

	_fPositionX += _fPositionXI;
	_fPositionY += _fPositionYI;

	_a += _fAlfaI;
}

// updates parameters after rendering, center coords

void CSprite::UpdateC(void)
{
	oglCBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _r, _g, _b, _a, _fScaleX, _fScaleY, _fRotation);

	_fRotation += _fRotationI;

	_fScaleX += _fScaleXI;
	_fScaleY += _fScaleYI;

	_fPositionX += _fPositionXI;
	_fPositionY += _fPositionYI;

	_a += _fAlfaI;
}
	
// set & get rotation

void CSprite::AddRotation(float fRot)
{
	_fRotation += fRot;
}

// set & get position

void CSprite::Position(float fX, float fY)
{
	_fPositionX = fX;
	_fPositionY = fY;
}

void CSprite::AddPosition(float fX, float fY)
{
	_fPositionX += fX; 
	_fPositionY += fY;
}

void CSprite::AddPositionX(float fX)
{
	_fPositionX += fX;
}

void CSprite::AddPositionY(float fY)
{
	_fPositionY += fY;
}

// set & get scale, update size

void CSprite::Scale(float fX, float fY)
{
	_fScaleX = fX;
	_fScaleY = fY;

	_fSizeX = _pSprite->w * _fScaleX;
	_fSizeY = _pSprite->h * _fScaleY;
}

// aktualizuj parametry i rysuj 

void CSprite::Render(unsigned long ulTimer)
{
	if (_ulRenderTime==0)	// pierwsze rysowanie 
	{
		_isCenter ? UpdateC() : Update();
	}
	else
	{
		_ulDeltaTime = ulTimer - _ulRenderTime;

		_fRotation += (float)(_fRotationI * _ulDeltaTime);

		_fScaleX += (float)(_fScaleXI * _ulDeltaTime);
		_fScaleY += (float)(_fScaleYI * _ulDeltaTime);

		_fPositionX += (float)(_fPositionXI * _ulDeltaTime);
		_fPositionY += (float)(_fPositionYI * _ulDeltaTime);

		_a += (float)(_fAlfaI * _ulDeltaTime);

		_isCenter ? RenderC() : Render();
	}

	_ulRenderTime = ulTimer;	// zapamietaj kiedy narysowalismy klatke
}


void CSprite::fScaleX(float fX)
{
	_fScaleX = fX;
	_fSizeX = _pSprite->w * _fScaleX;
}

void CSprite::fScaleY(float fY)
{
	_fScaleY = fY;
	_fSizeY = _pSprite->h * _fScaleY;
}


void CSprite::AddAlfa(float f)
{
	_a += f;

	if (_a>1.0f) 
		_a = 1.0f;

	if (_a<0.0f)
		_a = 0.0f;
}

void CSprite::Resize(int x1, int y1, int x2, int y2)
{
	Position((float)x1, (float)y1);
	Scale( (float)(x2-x1)/(float)(_pSprite->w), (float)(y2-y1)/(float)(_pSprite->h) );
}

void CSprite::Color(float r, float g, float b, float a)
{
	_r = r; 
	_g = g; 
	_b = b; 
	_a = a;
}

void CSprite::Color(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;
}