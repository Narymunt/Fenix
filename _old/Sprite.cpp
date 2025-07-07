#include "Sprite.h"

// init sprite in top left corner

CSprite::CSprite(char cFilename[])
{
	_pSprite = NULL;

	_pSprite = oglFromSurfaceFree(IMG_Load(cFilename));

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
}

// destructor

CSprite::~CSprite()
{
	oglFreeTexture(_pSprite);
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

	_fSizeX += _fSizeXI;
	_fSizeY += _fSizeYI;

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

	_fSizeX += _fSizeXI;
	_fSizeY += _fSizeYI;

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