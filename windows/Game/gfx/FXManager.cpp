/**
   FXManager.cpp

   Grafiki s¹ zainicjalizowane niezale¿nie od systemu particles, ¿eby nie trzeba by³o dla ka¿dego obiektu trzymaæ osobnego sprite. 
   Dlatego skasowanie obiektu powoduje wpisanie NULL do wskaznika sprite zamiast kasowania go.
   Dopiero skasowanie FXManagera powoduje, ¿e grafiki s¹ kasowane z pamiêci.

   @author Jaros³aw N. Ro¿yñski
   @version 2014-09-04
   
*/

#include "FXManager.h"

/**
   Class construktor
   @param pScreen wskaŸnik do ekranu
   @return none
*/

FXManager::FXManager(Screen *screen) :
_screen(screen)
{
	_image[0] = new Sprite((char*)"m1.png");
	_image[1] = new Sprite((char*)"m2.png");
	_image[2] = new Sprite((char*)"m3.png");
	_image[3] = new Sprite((char*)"m4.png");
	_image[4] = new Sprite((char*)"m5.png");
	_image[5] = new Sprite((char*)"m6.png");
	_image[6] = new Sprite((char*)"m7.png");
	_image[7] = new Sprite((char*)"m8.png");
	_image[8] = new Sprite((char*)"m9.png");
	_image[9] = new Sprite((char*)"ma.png");
	_image[10] = new Sprite((char*)"mb.png");
	_image[11] = new Sprite((char*)"mc.png");
	_image[12] = new Sprite((char*)"md.png");
	_image[13] = new Sprite((char*)"me.png");

}

FXManager::~FXManager()
{
	for (int i = 0; i < 14; i++)
		safeDelete(_image[i]);

	for (unsigned int i = 0; i < _particles.size(); i++)
	{
		if (_timerEnd[i] != 0)
		{
			_particles[i]->_image= NULL; // memory leak ??
			safeDelete(_particles[i]);
			_timerEnd[i] = 0;
		}
	}

	_particles.clear();

	_timerStart.clear();
	_timerEnd.clear();
	_layer.clear();

}

/**
   Dodawanie nowego efektu.

   @param iType rodzaj efektu
   @param x wspó³rzêdna X an ekranie
   @param y wspó³rzêdan Y na ekranie
   @param r kolor R
   @param g kolor G
   @param a kolor B
   @param a przezroczystoœæ
   @timerStart czas startu efektu
   @ulTime d³ugoœæ trwania efektu

   @return none
*/

int FXManager::add(int iType, int x, int y, float r, float g, float b, float a, unsigned long timerStart, unsigned long ulTime)
{
	return add(iType, x, y, r, g, b, a, timerStart, ulTime, 0);
}

/**
   Dodawanie nowego efektu.

   @param iType rodzaj efektu
   @param x wspó³rzêdna X an ekranie
   @param y wspó³rzêdan Y na ekranie
   @param r kolor R
   @param g kolor G
   @param a kolor B
   @param a przezroczystoœæ
   @timerStart czas startu efektu
   @ulTime d³ugoœæ trwania efektu
   @cLayer warstwa na której rysujemy

   @return none
*/

int FXManager::add(int iType, int x, int y, float r, float g, float b, float a, unsigned long timerStart, unsigned long ulTime, char cLayer)
{
	int ret = 0; // zadeklarowana tutaj, poniewaz zmeniamy rozmiary przed zwrotem, oraz lokalnie zwrot bylby poza scope

	switch (iType)
	{
		case FX_SHOW_BOMB:
			_particles.push_back(new Particle2DManager(_image[3], 25,
				x - 8, y - 8, x + 8, y + 8,
				-.003f, -.003f, .003f, .003f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 1000));
	
			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop=false;					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
		break;

		case FX_RAINBOW_EXPLOSION:
			_particles.push_back(new Particle2DManager(_image[3], 50,
				x - 50, y - 50, x + 50, y + 50,
				-.30f, -.30f, .30f, .30f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop= (false);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_DIAMOND_EXPLOSION:
			_particles.push_back(new Particle2DManager(_image[3], 50,
				x - 50, y - 50, x + 50, y + 50,
				-.30f, -.30f, .30f, .30f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (false);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_SMALL_EXPLOSION:
			_particles.push_back(new Particle2DManager(_image[1], 150,
				x-50, y-50, x+50, y+ 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (false);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_BIG_EXPLOSION:
			_particles.push_back(new Particle2DManager(_image[10], 300,
				x - 50, y - 50, x + 50, y + 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.001f, -.005f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (false);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_SMALL_LOOP:
			_particles.push_back(new Particle2DManager(_image[1], 100,
				x - 5, y - 5, x + 5, y + 5,
				-0.25f, -0.25f, 0.25f, 0.25f,
				1.0f, -.0025f, -.0075f,
				0.0f, -.1f, .1f,
				100, 300));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (true);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_BIG_LOOP:
			_particles.push_back(new Particle2DManager(_image[1], 300,
				x - 50, y - 50, x + 50, y + 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.001f, -.005f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (true);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_HINT:
			_particles.push_back(new Particle2DManager(_image[3], 25,
				x - 8, y - 8, x + 8, y + 8,
				-.003f, -.003f, .003f, .003f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (true);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;

		case FX_MENU_BUTTON:
			_particles.push_back(new Particle2DManager(_image[3], 3,
				x - 16, y - 16, x + 32, y + 32,
				-.003f, -.003f, .003f, .003f,
				0.0f, .001f, .005f,
				0.5f, -.05f, .05f,
				100, 5000));

			_particles[_particles.size() - 1]->color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_particles[_particles.size() - 1]->_loop = (true);					// przy eksplozji nie odnawiamy
			_timerStart.push_back(timerStart);
			_timerEnd.push_back(timerStart + ulTime);
			ret = _particles.size() - 1;
			_layer.push_back(cLayer);
			break;
	}
	return ret;
}

/**
   Usuniêcie textury particle o podanym identyfikatorze.
   @param id identyfikator textury
   @return none
*/

void FXManager::remove(int id)
{
	_particles[id]->_image = (NULL); // memory leak ??
	safeDelete(_particles[id]);
	_timerEnd[id] = 0;
}

/**
   Renderowanie wszystkich efektów 
   @param timer aktualny czas
   @return none
*/

void FXManager::render(unsigned long timer)
{
	for (unsigned int i = 0; i < _particles.size(); i++)
	{
		if (timer < _timerEnd[i])
		{
			_particles[i]->render(timer);
		}
		else
		{
			if (_timerEnd[i] != 0)
			{
				_particles[i]->_image = (NULL); // memory leak ??
				safeDelete(_particles[i]);
				_timerEnd[i] = 0;
			}
		}
	}
}

/**
   Renderowanie wszystkich efektów dla wybranej warstwy.
   @param timer aktualny czas
   @param cLayer numer warstwy, któr¹ renderujemy
   @return none
*/

void FXManager::render(unsigned long timer, char cLayer)
{
	for (unsigned int i = 0; i < _particles.size(); i++)
	{
		if (timer < _timerEnd[i])
		{
			if (_layer[i]==cLayer)
			   _particles[i]->render(timer);
		}
		else
		{
			if (_timerEnd[i] != 0)
			{
				_particles[i]->_image = (NULL); // memory leak ??
				safeDelete(_particles[i]);
				_timerEnd[i] = 0;
			}
		}
	}
}

