#include "Sprite.h"

#pragma warning(disable : 4996)

// init ze skryptu

CSprite::CSprite(CScreen *pScreen, char cObjectName[])
{
	FILE	*plik;
	char linia[1024],cFullname[1024];
	int x,y;
	char	*pTempBuffer;		// dla spakowanych / rozpakowanych plikow
	int		i=0;
	SDL_RWops *rw;
	CDatafile *pDatafile;

	_pSprite = NULL;
	memset(linia,0,1000);	// nie zawsze ta tablica jest czyszczona

	if (pScreen->isSpriteObject(cObjectName))
	{
		// szukamy w datafile

		pDatafile = new CDatafile(pScreen->cObjectFilename(cObjectName));
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
			
			_fAlfa = pScreen->fAlfa(cObjectName);
			_fAlfaI = pScreen->fAlfaI(cObjectName);

			pScreen->isCenter(cObjectName) ? _isCenter = true : _isCenter = false;

			_fSizeX = (float) _pSprite->w;
			_fSizeY = (float) _pSprite->h;

			return;
		}


		// szukamy ze slownika, najpierw w katalogu data

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
			
			_fAlfa = pScreen->fAlfa(cObjectName);
			_fAlfaI = pScreen->fAlfaI(cObjectName);

			pScreen->isCenter(cObjectName) ? _isCenter = true : _isCenter = false;
		}

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
			
			_fAlfa = pScreen->fAlfa(cObjectName);
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

					if (!_pSprite)
						printf("ERROR : %s not found !\n",linia);

					_fSizeX = (float) _pSprite->w;
					_fSizeY = (float) _pSprite->h;

					fscanf(plik,"%s\n",linia);	// wczytaj parametr centrowania
					UpOnly(linia);

					!strcmp(linia,"C") ? _isCenter = true : _isCenter = false;

					fscanf(plik,"%f %f %f %f %f %f\n",&_fPositionX, &_fPositionY, &_fScaleX, &_fScaleY, &_fRotation, &_fAlfa);
					fscanf(plik,"%f %f %f %f %f %f\n",&_fPositionXI, &_fPositionYI, &_fScaleXI, &_fScaleYI, &_fRotationI, &_fAlfaI);
				} // if x & y
			} // if 
		} // if <sprite>
	} // while <end>

	if (_pSprite==NULL)
		printf("ERROR: object %s screenX %d screenY %d - not found in script file!\n",cObjectName,pScreen->iSizeX(),pScreen->iSizeY());

	fclose(plik);

}

// init sprite in top left corner

CSprite::CSprite(char cFilename[])
{
	char	*pTempBuffer;		// dla spakowanych / rozpakowanych plikow
	int		i=0;
	SDL_RWops *rw;
	CDatafile	*pDatafile;
    SDL_Surface *surface;
    GLint nOfColors;
    GLenum texture_format;
	
    _pSprite = NULL;

	// szukamy w datafile

	pDatafile = new CDatafile(cFilename);
	rw = SDL_RWFromMem(pDatafile->pBuffer(), pDatafile->ulSize());
    
    surface = IMG_Load_RW(rw,1);
    
    // get the number of channels in the SDL surface
    nOfColors = surface->format->BytesPerPixel;
    
    if (nOfColors == 4)     // contains an alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
        texture_format = GL_BGRA;
    } else if (nOfColors == 3)     // no alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        //else
        //texture_format = GL_BGR;
    } else {
        printf("warning: the image is not truecolor..  this will probably break\n");
        // this error should not go unhandled
    }

	_pSprite = oglFromSurfaceFree(surface);
    
//	_pSprite = oglFromSurfaceFree(IMG_Load_RW(rw,1));

	delete pDatafile;

	if (!_pSprite)
	{
		_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));
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

	_fAlfa = 1.0f;

	// incrementators

	_fRotationI = 0.0f;

	_ulRenderTime = 0;
}

// wczytaj bezposrednio plik bez podawania nazwy obiektu

CSprite::CSprite(char cFilename[], CScreen *pScreen)
{
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

	if (!_pSprite)
		printf("ERROR : %s not found!\n",cFilename);

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = 0.0f;
	_fPositionY = 0.0f;

	_fAlfa = 1.0f;

	// incrementators

	_fRotationI = 0.0f;

	_ulRenderTime = 0;
}


// init sprite at given x,y

CSprite::CSprite(char cFilename[], int iX, int iY)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_fAlfa = 1.0f;

	_ulRenderTime = 0;
}

// init sprite at given x,y,scalex, scaley

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = fX;
	_fScaleY = fY;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_fAlfa = 1.0f;

	_ulRenderTime = 0;
}

// init sprite at given x,y,scalex, scaley, rotation

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fRot)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = fRot;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = fX;
	_fScaleY = fY;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_fAlfa = 1.0f;

	_ulRenderTime = 0;
}

// init sprite x,y,alfa

CSprite::CSprite(char cFilename[], int iX, int iY, float fAlfa)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_fAlfa = fAlfa;

	_ulRenderTime = 0;
}

// init sprite

CSprite::CSprite(char cFilename[], int iX, int iY, float fX, float fY, float fAlfa, float fRot)
{
	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = fRot;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = fX;
	_fScaleY = fY;

	_fPositionX = (float) iX;
	_fPositionY = (float) iY;

	_fAlfa = fAlfa;

	_ulRenderTime = 0;
}

// init sprite with alfa at top left corner

CSprite::CSprite(char cFilename[], float fAlfa)
{

	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

	_fRotation = 0.0f;
	
	_fSizeX = (float) _pSprite->w;
	_fSizeY = (float) _pSprite->h;

	_fScaleX = 1.0f;
	_fScaleY = 1.0f;

	_fPositionX = 0.0f;
	_fPositionY = 0.0f;

	_fAlfa = fAlfa;

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
	Position(x,y);
	fAlfa(a);
	Render();
}

// render sprite using top left coords

void CSprite::Render(void)
{
	oglBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _fAlfa, _fScaleX, _fScaleY, _fRotation);
}

// render sprite using middle of texture coords

void CSprite::RenderC(void)
{
	oglCBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _fAlfa, _fScaleX, _fScaleY, _fRotation);
}

// updates parameters after rendering

void CSprite::Update(void)
{
	oglBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _fAlfa, _fScaleX, _fScaleY, _fRotation);

	_fRotation += _fRotationI;

	_fScaleX += _fScaleXI;
	_fScaleY += _fScaleYI;

	_fPositionX += _fPositionXI;
	_fPositionY += _fPositionYI;

	_fAlfa += _fAlfaI;
}

// updates parameters after rendering, center coords

void CSprite::UpdateC(void)
{
	oglCBlit(_pSprite, NULL, (int)_fPositionX, (int)_fPositionY, _fAlfa, _fScaleX, _fScaleY, _fRotation);

	_fRotation += _fRotationI;

	_fScaleX += _fScaleXI;
	_fScaleY += _fScaleYI;

	_fPositionX += _fPositionXI;
	_fPositionY += _fPositionYI;

	_fAlfa += _fAlfaI;
}
	
// set & get rotation

void CSprite::AddRotation(float fRot)
{
	_fRotation += fRot;
}

void CSprite::fRotation(float fRot)
{
	_fRotation = fRot;
}
	
float CSprite::fRotation(void)
{
	return _fRotation;
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

float CSprite::fPositionX(void)
{
	return _fPositionX;
}

void CSprite::fPositionX(float fX)
{
	_fPositionX = fX;
}

void CSprite::AddPositionX(float fX)
{
	_fPositionX += fX;
}

float CSprite::fPositionY(void)
{
	return _fPositionY;
}

void CSprite::fPositionY(float fY)
{
	_fPositionY = fY;
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

		_fAlfa += (float)(_fAlfaI * _ulDeltaTime);

		_isCenter ? RenderC() : Render();
	}

	_ulRenderTime = ulTimer;	// zapamietaj kiedy narysowalismy klatke
}


void CSprite::fScaleX(float fX)
{
	_fScaleX = fX;
	_fSizeX = _pSprite->w * _fScaleX;
}

float CSprite::fScaleX(void)
{
	return _fScaleX;
}

void CSprite::fScaleY(float fY)
{
	_fScaleY = fY;
	_fSizeY = _pSprite->h * _fScaleY;
}

float CSprite::fScaleY(void)
{
	return _fScaleY;
}

// set & get alfa

void CSprite::fAlfa(float f)
{
	_fAlfa = f;
}

float CSprite::fAlfa(void)
{
	return _fAlfa;
}


void CSprite::AddAlfa(float f)
{
	_fAlfa += f;

	if (_fAlfa>1.0f) 
		_fAlfa = 1.0f;

	if (_fAlfa<0.0f)
		_fAlfa = 0.0f;
}

void CSprite::Resize(int x1, int y1, int x2, int y2)
{
	Position((float)x1, (float)y1);
	Scale( (float)(x2-x1)/(float)(_pSprite->w), (float)(y2-y1)/(float)(_pSprite->h) );
}

float CSprite::fSizeX(void)
{
	return _fSizeX;
}

float CSprite::fSizeY(void)
{
	return _fSizeY;
}

