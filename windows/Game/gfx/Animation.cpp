#include "Animation.h"
#pragma warning(disable : 4996)	// sprintf unsafe

CAnimation::CAnimation() :
_frameCount(0)
{
	_isOpen = false;
}

CAnimation::CAnimation(char cFile[], int iFrameCount, char cExt[]) :
   _frameCount(iFrameCount)
{
	strcpy(_file,cFile);	// zapamietujemy nazwe pliku i rozszerzenie, numery dodajemy np. img001,img002
	strcpy(_ext,cExt);
}

CAnimation::~CAnimation()
{
	close();
}

// Wczytanie danych na podstawie wcze�niej ustawionych parametr�w

void CAnimation::open(void)
{
	char buffer[1024];	// tutaj wygenerujemy nazwe pliku

	for (int i=0; i<_frameCount; i++)
	{
		if (_frameCount>99) // jezeli klatek jest minimum 100 to stosujemy 3-cyfrowa numeracje
		{
			if (i<10)
				sprintf(buffer,"%s00%d.%s",_file,i,_ext);

			if (i>9 && i <100)
				sprintf(buffer,"%s0%d.%s",_file,i,_ext);

			if (i>99)
				sprintf_s(buffer,"%s%d.%s",_file,i,_ext);
		}

		if (_frameCount<100) // jezeli klatek jest minimum 100 to stosujemy 3-cyfrowa numeracje
		{
			if (i<10)
				sprintf(buffer,"%s0%d.%s",_file,i,_ext);

			if (i>9 && i <100)
				sprintf(buffer,"%s%d.%s",_file,i,_ext);
		}
		_sprite.push_back(new CSprite(buffer));
	}
	_isOpen = true;
}

// Zwolnij wszystkie dane. 

void CAnimation::close(void)
{
	for (unsigned int i=0; i<_sprite.size(); i++)
		delete _sprite[i];

	_sprite.clear();
	_isOpen = false;
}

// Dodajemy klatk� na koniec kolejki

void CAnimation::add(char cFilename[])
{
	_sprite.push_back(new CSprite(cFilename));
}

// Renderuj klatk� o podanym numerze

void CAnimation::render(int i)
{
	if (i>=0 && i < _frameCount)
		_sprite[i]->render();
}

/**
   Renderuj klatk� o podanym numerze
   
   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie

   @return none
*/

void CAnimation::render(int i, int x, int y)
{
	if (i>=0 && i<_frameCount)
	{
		_sprite[i]->position((float)x,(float)y);
		_sprite[i]->render();
	}
}

/**
   Renderuj klatk� o podanym numerze
   
   @param iFrame numer klatki 
   @param iY wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param alfa przezroczystosc w skali 0-255

   @return none
*/

void CAnimation::render(int i, int x, int y, unsigned char a)
{
	if (i>=0 && i<_frameCount)
	{
		_sprite[i]->_a = a;
		_sprite[i]->position((float)x,(float)y);
		_sprite[i]->render();
	}
}

/**
   Renderuj klatk� o podanym numerze
   
   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param fScaleX skala X
   @param fScaleY skala Y

   @return none
*/

void CAnimation::render(int i, int x, int y, float sx, float sy)
{
	if (i>=0 && i<_frameCount)
	{
		_sprite[i]->position((float)x,(float)y);
		_sprite[i]->scale(sx,sy);
		_sprite[i]->render();
	}
}

/**
   Renderuj klatk� o podanym numerze

   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param fScaleX skala X
   @param fScaleY skala Y
   @param fRotation k�t obrotu

   @return none
*/


void CAnimation::render(int i, int x, int y, float sx, float sy, float r)
{
	if (i>=0 && i<_frameCount)
	{
		_sprite[i]->position((float)x,(float)y);
		_sprite[i]->scale(sx, sy);
		_sprite[i]->_rotation = r;
		_sprite[i]->render();
	}
}

/**
   Renderuj klatk� o podanym numerze

   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param fScaleX skala X
   @param fScaleY skala Y
   @param fRotation k�t obrotu
   @param fRotationX punkt obrotu X
   @param fRotationY punkt obrotu Y

   @return none
*/


void CAnimation::render(int i, int x, int y, float sx, float sy, float r, float rx, float ry)
{
	if (i>=0 && i<_frameCount)
	{
		_sprite[i]->position((float)x,(float)y);
		_sprite[i]->scale(sx, sy);
		_sprite[i]->pivot(rx, ry);
		_sprite[i]->_rotation = r;
		_sprite[i]->render();
	}
}

