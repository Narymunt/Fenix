#include "Sprite.h"

#pragma warning(disable : 4996)

Sprite::Sprite(char filename[]) : _sprite(NULL)
{
	load(filename);
}

Sprite::Sprite(char filename[], int x, int y) : _sprite(NULL)
{
	position((float)x, (float)y);
	load(filename);
}

Sprite::Sprite(char filename[], int x, int y, float scaleX, float scaleY) : _sprite(NULL)
{
	position((float)x, (float)y);
	scale(scaleX, scaleY);
	load(filename);
}

Sprite::Sprite(char filename[], int x, int y, float scaleX, float scaleY, float rotation) : _sprite(NULL)
{
	position((float)x, (float)y);
	scale(scaleX, scaleY);
	_rotation = rotation;
	load(filename);
}

Sprite::Sprite(char filename[], int x, int y, float a) : _sprite(NULL)
{
	position((float)x, (float)y);
	_a = a;
	load(filename);
}

Sprite::Sprite(char filename[], int x, int y, float scaleX, float scaleY, float a, float rotation) : _sprite(NULL)
{
	position((float)x, (float)y);
	scale(scaleX, scaleY);
	_rotation = rotation;
	_a = a;
	load(filename);
}

Sprite::Sprite(char filename[], float a) : _sprite(NULL)
{
	load(filename);
	_a = a;
}

bool Sprite::load(char filename[])
{
	static SpriteManager spriteManager;

	_sprite = spriteManager.get(filename);		// najpierw sprawdzamy, czy mamy juz taki wskaznik do takiej nazwy pliku, jezeli tak, to pobieramy go i nie tworzymy nowej textury

	if (!_sprite) loadFromZip(filename);
	if (!_sprite) loadFromDatafile(filename);
	if (!_sprite) loadFromFile(filename);
	if (!_sprite) loadFromPAQ(filename);

	if (_sprite) spriteManager.add(filename, _sprite);	// dodajemy, sprawdzamy wewnatrz spriteManagera czy to nie jest duplikat przypadkiem


	if (_sprite != NULL)
	{
		_sizeX = (float)_sprite->w;
		_sizeY = (float)_sprite->h;
		_originalX = _sizeX;
		_originalY = _sizeY;
		
		strcpy(_fileName, filename);	// zachowujemy nazwe na pozniej, bedzie potrzebna przy kasowaniu textury
	}
	else
	{
		printf("ERROR : nie znaleziono pliku %s\n", filename);
	}

	return _sprite ? true : false;
}

void Sprite::loadFromZip(char filename[])
{
	HZIP	hZipFile;
	ZIPENTRY ze;
	int i = 0;
	char	*tempBuffer;		// dla spakowanych / rozpakowanych plikow
	SDL_RWops *rw;

	if ((hZipFile = OpenZip((const TCHAR*)ZIP_FILE, ZIP_PASSWORD)) != NULL)
	{
		FindZipItem(hZipFile, (const TCHAR*)filename, true, &i, &ze); // znajdz plik do wczytania
		tempBuffer = new char[ze.unc_size]; // przydziel w pamieci miejsce na rozpakowane dane
		UnzipItem(hZipFile, i, tempBuffer, ze.unc_size);
		rw = SDL_RWFromMem(tempBuffer, ze.unc_size);
		_sprite = oglFromSurfaceFree(IMG_Load_RW(rw, 1));
		delete[] tempBuffer;
		CloseZip(hZipFile);
	}
}

void Sprite::loadFromDatafile(char filename[])
{
	SDL_RWops *rw;
	Datafile *datafile;

	datafile = new Datafile(filename);       // szukamy ze s³ownika
	
	if (!datafile->_empty)
	{
		rw = SDL_RWFromMem(datafile->_buffer, datafile->_size);
		_sprite = oglFromSurfaceFree(IMG_Load_RW(rw, 1));
	}

	delete datafile;
}

// wczytaj z katalogu data

void Sprite::loadFromFile(char filename[])
{
	char fullname[1024];
	
	sprintf(fullname, "data/%s", filename);
	_sprite = oglFromSurfaceFree(IMG_Load(fullname));
}

// destructor

Sprite::~Sprite()
{
	SpriteManager spriteManager;

	if (_sprite!=NULL)
	{
		if (spriteManager.get(_fileName))
		{
			oglFreeTexture(_sprite);
			spriteManager.set(_fileName, NULL);
			_sprite = NULL;
		}
	}
}

void Sprite::render(int x, int y, float a)
{
	position((float)x,(float)y);
	_a = a;
	render();
}

// render sprite using top left coords

void Sprite::render(void)
{
	_isCenter ? 
		oglCBlit(_sprite, NULL, (int)_x, (int)_y, _r, _g, _b, _a, _scaleX, _scaleY, _rotation) :
		oglBlit(_sprite, NULL, (int)_x, (int)_y, _r, _g, _b, _a, _scaleX, _scaleY, _rotation);
}

// updates parameters after rendering

void Sprite::update(void)
{
	render();

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

void Sprite::update(unsigned long timer)
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



