#include "Sprite.h"
#include "Zip.h"
#include "Unzip.h"

#pragma warning(disable : 4996)

CSprite::CSprite(char filename[]) : _sprite(NULL)
{
	init(NULL, filename);
}

CSprite::CSprite(char filename[], int x, int y) : _sprite(NULL)
{
	position((float)x, (float)y);
	init(NULL, filename);
}

CSprite::CSprite(char filename[], int x, int y, float scaleX, float scaleY) : _sprite(NULL)
{
	position((float)x, (float)y);
	scale(scaleX, scaleY);
	init(NULL, filename);
}

CSprite::CSprite(char filename[], int x, int y, float scaleX, float scaleY, float rotation) : _sprite(NULL)
{
	position((float)x, (float)y);
	scale(scaleX, scaleY);
	_rotation = rotation;
	init(NULL, filename);
}

CSprite::CSprite(char filename[], int x, int y, float a) : _sprite(NULL)
{
	position((float)x, (float)y);
	_a = a;
	init(NULL, filename);
}

CSprite::CSprite(char filename[], int x, int y, float scaleX, float scaleY, float a, float rotation) : _sprite(NULL)
{
	position((float)x, (float)y);
	scale(scaleX, scaleY);
	_rotation = rotation;
	_a = a;
	init(NULL, filename);
}

CSprite::CSprite(char filename[], float a) : _sprite(NULL)
{
	init(NULL, filename);
	_a = a;
}

void CSprite::init(CScreen *screen, char filename[])
{

	if (screen != NULL)
	{
		if (screen->_isSDS && !_sprite)
		{
			if (!_sprite) load(filename, "_SDS.png"); if (!_sprite) load(filename, "_SDS.jpg");
			if (!_sprite) load(filename, "_SDW.png"); if (!_sprite) load(filename, "_SDW.jpg");
			if (!_sprite) load(filename, "_HDS.png"); if (!_sprite) load(filename, "_HDS.jpg");
			if (!_sprite) load(filename, "_HDW.png"); if (!_sprite) load(filename, "_HDW.jpg");
		}

		if (screen->_isSDW && !_sprite)
		{
			if (!_sprite) load(filename, "_SDW.png"); if (!_sprite) load(filename, "_SDW.jpg");
			if (!_sprite) load(filename, "_SDS.png"); if (!_sprite) load(filename, "_SDS.jpg");
			if (!_sprite) load(filename, "_HDW.png"); if (!_sprite) load(filename, "_HDW.jpg");
			if (!_sprite) load(filename, "_HDS.png"); if (!_sprite) load(filename, "_HDS.jpg");
		}

		if (screen->_isHDS && !_sprite)
		{
			if (!_sprite) load(filename, "_HDS.png"); if (!_sprite) load(filename, "_HDS.jpg");
			if (!_sprite) load(filename, "_HDW.png"); if (!_sprite) load(filename, "_HDW.jpg");
			if (!_sprite) load(filename, "_SDS.png"); if (!_sprite) load(filename, "_SDS.jpg");
			if (!_sprite) load(filename, "_SDW.png"); if (!_sprite) load(filename, "_SDW.jpg");
		}

		if (screen->_isHDW && !_sprite)
		{
			if (!_sprite) load(filename, "_HDW.png"); if (!_sprite) load(filename, "_HDW.jpg");
			if (!_sprite) load(filename, "_HDS.png"); if (!_sprite) load(filename, "_HDS.jpg");
			if (!_sprite) load(filename, "_SDW.png"); if (!_sprite) load(filename, "_SDW.jpg");
			if (!_sprite) load(filename, "_SDS.png"); if (!_sprite) load(filename, "_SDS.jpg");
		}

	}
	else // pScreen==NULL, podalismy dokladna nazwe pliku
	{
		loadFromZip(filename);		
		if (!_sprite) loadFromDatafile(filename);
		if (!_sprite) loadFromFile(filename);
	}

	// wczytane dane, ustawiamy w³aœciwoœci obiektu

	if (_sprite != NULL)
	{
		_sizeX = (float)_sprite->w;
		_sizeY = (float)_sprite->h;
	}
	else
	{
		printf("ERROR : nie znaleziono pliku %s\n", filename);
	}
}

void CSprite::load(char filename[], char ext[])
{
	char fullname[1024];
	memset(fullname, 0, 1024);

	sprintf(fullname, "%s%s", filename, ext);

	if (!_sprite) loadFromZip(fullname);
	if (!_sprite) loadFromDatafile(fullname);
	if (!_sprite) loadFromFile(fullname);
}

void CSprite::loadFromZip(char filename[])
{
	HZIP	hZipFile;
	ZIPENTRY ze;
	int i = 0;
	char	*tempBuffer;		// dla spakowanych / rozpakowanych plikow
	SDL_RWops *rw;

	if ((hZipFile = OpenZip(ZIP_FILE, ZIP_PASSWORD)) != NULL)
	{
		FindZipItem(hZipFile, filename, true, &i, &ze); // znajdz plik do wczytania
		tempBuffer = new char[ze.unc_size]; // przydziel w pamieci miejsce na rozpakowane dane
		UnzipItem(hZipFile, i, tempBuffer, ze.unc_size);
		rw = SDL_RWFromMem(tempBuffer, ze.unc_size);
		_sprite = oglFromSurfaceFree(IMG_Load_RW(rw, 1));
		delete[] tempBuffer;
		CloseZip(hZipFile);
	}
}

void CSprite::loadFromDatafile(char filename[])
{
	SDL_RWops *rw;
	CDatafile *datafile;

	datafile = new CDatafile(filename);       // szukamy ze s³ownika
	rw = SDL_RWFromMem(datafile->_buffer, datafile->_size);
	_sprite = oglFromSurfaceFree(IMG_Load_RW(rw, 1));

	delete datafile;
}

// wczytaj z katalogu data

void CSprite::loadFromFile(char filename[])
{
	char fullname[1024];
	
	sprintf(fullname, "data/%s", filename);
	_sprite = oglFromSurfaceFree(IMG_Load(fullname));
}

// destructor

CSprite::~CSprite()
{
	if (_sprite!=NULL)
	{
		oglFreeTexture(_sprite);
		_sprite = NULL;
	}
}

void CSprite::render(int x, int y, float a)
{
	position((float)x,(float)y);
	_a = a;
	render();
}

// render sprite using top left coords

void CSprite::render(void)
{
	if (_isCenter)
	{
		oglCBlit(_sprite, NULL, (int)_x, (int)_y, _r, _g, _b, _a, _scaleX, _scaleY, _rotation);
	}
	else
	{
		oglBlit(_sprite, NULL, (int)_x, (int)_y, _r, _g, _b, _a, _scaleX, _scaleY, _rotation);
	}
}

// updates parameters after rendering

void CSprite::update(void)
{
	if (_isCenter)
	{
		oglCBlit(_sprite, NULL, (int)_x, (int)_y, _r, _g, _b, _a, _scaleX, _scaleY, _rotation);
	}
	else
	{
		oglBlit(_sprite, NULL, (int)_x, (int)_y, _r, _g, _b, _a, _scaleX, _scaleY, _rotation);
	}

	_rotation += _rotationI;

	_scaleX += _scaleXI;
	_scaleY += _scaleYI;

	_x += _xI;
	_y += _yI;

	_r += _rI;
	_g += _gI;
	_b += _bI;
	_a += _aI;
}

// aktualizuj parametry i rysuj 

void CSprite::update(unsigned long timer)
{
	if (_renderTime==0)	// pierwsze rysowanie 
	{
		update();
	}
	else
	{
		_deltaTime = timer- _renderTime;

		_rotation += (float)(_rotationI * _deltaTime);

		_scaleX += (float)(_scaleXI * _deltaTime);
		_scaleY += (float)(_scaleYI * _deltaTime);

		_x += (float)(_xI * _deltaTime);
		_y += (float)(_yI * _deltaTime);

		_r += (float)(_rI * _deltaTime);
		_g += (float)(_gI * _deltaTime);
		_b += (float)(_bI * _deltaTime);
		_a += (float)(_aI * _deltaTime);

		render();
	}

	_renderTime = timer;	// zapamietaj kiedy narysowalismy klatke
}



