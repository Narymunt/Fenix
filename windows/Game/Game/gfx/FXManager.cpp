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

CFXManager::CFXManager(CScreen *pScreen) :
_pScreen(pScreen)
{
	_pImage[0] = new CSprite("m1.png");
	_pImage[1] = new CSprite("m2.png");
	_pImage[2] = new CSprite("m3.png");
	_pImage[3] = new CSprite("m4.png");
	_pImage[4] = new CSprite("m5.png");
	_pImage[5] = new CSprite("m6.png");
	_pImage[6] = new CSprite("m7.png");
	_pImage[7] = new CSprite("m8.png");
	_pImage[8] = new CSprite("m9.png");
	_pImage[9] = new CSprite("ma.png");
	_pImage[10] = new CSprite("mb.png");
	_pImage[11] = new CSprite("mc.png");
	_pImage[12] = new CSprite("md.png");
	_pImage[13] = new CSprite("me.png");

}

/**
   Desktruktor klasy.

   @param none

   @return none
*/


CFXManager::~CFXManager()
{
	for (int i = 0; i < 14; i++)
		SafeDelete(_pImage[i]);

	for (unsigned int i = 0; i < _pParticles.size(); i++)
	{
		if (_ulTimerEnd[i] != 0)
		{
			_pParticles[i]->pImage(NULL);
			SafeDelete(_pParticles[i]);
			_ulTimerEnd[i] = 0;
		}
	}

	_pParticles.clear();

	_ulTimerStart.clear();
	_ulTimerEnd.clear();
	_cLayer.clear();

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
   @ulTimerStart czas startu efektu
   @ulTime d³ugoœæ trwania efektu

   @return none
*/

int CFXManager::Add(int iType, int x, int y, float r, float g, float b, float a, unsigned long ulTimerStart, unsigned long ulTime)
{
	return Add(iType, x, y, r, g, b, a, ulTimerStart, ulTime, 0);
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
   @ulTimerStart czas startu efektu
   @ulTime d³ugoœæ trwania efektu
   @cLayer warstwa na której rysujemy

   @return none
*/

int CFXManager::Add(int iType, int x, int y, float r, float g, float b, float a, unsigned long ulTimerStart, unsigned long ulTime, char cLayer)
{
	int iReturn = 0;

	switch (iType)
	{
		case FX_SHOW_BOMB:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 25,
				x - 8, y - 8, x + 8, y + 8,
				-.003f, -.003f, .003f, .003f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 1000));
	
			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
		break;

		case FX_RAINBOW_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 50,
				x - 50, y - 50, x + 50, y + 50,
				-.30f, -.30f, .30f, .30f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_DIAMOND_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 50,
				x - 50, y - 50, x + 50, y + 50,
				-.30f, -.30f, .30f, .30f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_SMALL_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[1], 150,
				x-50, y-50, x+50, y+ 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_BIG_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[10], 300,
				x - 50, y - 50, x + 50, y + 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.001f, -.005f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_SMALL_LOOP:
			_pParticles.push_back(new CParticle2DManager(_pImage[1], 100,
				x - 5, y - 5, x + 5, y + 5,
				-0.25f, -0.25f, 0.25f, 0.25f,
				1.0f, -.0025f, -.0075f,
				0.0f, -.1f, .1f,
				100, 300));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_BIG_LOOP:
			_pParticles.push_back(new CParticle2DManager(_pImage[1], 300,
				x - 50, y - 50, x + 50, y + 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.001f, -.005f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_HINT:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 25,
				x - 8, y - 8, x + 8, y + 8,
				-.003f, -.003f, .003f, .003f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_MENU_BUTTON:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 3,
				x - 16, y - 16, x + 32, y + 32,
				-.003f, -.003f, .003f, .003f,
				0.0f, .001f, .005f,
				0.5f, -.05f, .05f,
				100, 5000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;


	}

	return iReturn;
}

/**
   Usuniêcie textury particle o podanym identyfikatorze.

   @param id identyfikator textury

   @return none
*/


void CFXManager::Remove(int id)
{
	_pParticles[id]->pImage(NULL);
	SafeDelete(_pParticles[id]);
	_ulTimerEnd[id] = 0;
}

/**
   Renderowanie wszystkich efektów 

   @param ulTimer aktualny czas

   @return none
*/

void CFXManager::Render(unsigned long ulTimer)
{
	for (unsigned int i = 0; i < _pParticles.size(); i++)
	{
		if (ulTimer < _ulTimerEnd[i])
		{
			_pParticles[i]->Render(ulTimer);
		}
		else
		{
			if (_ulTimerEnd[i] != 0)
			{
				_pParticles[i]->pImage(NULL);
				SafeDelete(_pParticles[i]);
				_ulTimerEnd[i] = 0;
			}
		}
	}
}

/**
   Renderowanie wszystkich efektów dla wybranej warstwy.

   @param ulTimer aktualny czas
   @param cLayer numer warstwy, któr¹ renderujemy

   @return none
*/

void CFXManager::Render(unsigned long ulTimer, char cLayer)
{
	for (unsigned int i = 0; i < _pParticles.size(); i++)
	{
		if (ulTimer < _ulTimerEnd[i])
		{
			if (_cLayer[i]==cLayer)
			   _pParticles[i]->Render(ulTimer);
		}
		else
		{
			if (_ulTimerEnd[i] != 0)
			{
				_pParticles[i]->pImage(NULL);
				SafeDelete(_pParticles[i]);
				_ulTimerEnd[i] = 0;
			}
		}
	}
}

