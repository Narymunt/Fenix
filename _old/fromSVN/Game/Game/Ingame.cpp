#include "Ingame.h"

#pragma warning(disable : 4996)	// sprintf unsafe

// class constructor

CIngame::CIngame() :
_pFXManager(NULL), 
_pBlack(NULL),
_pBackground(NULL),
_ulTimerStart(0),
_ulPrevTimer(0),
_ulTimer1000(0),
_pParticleManager(NULL),
_ulScore(NULL),
_ulScore1000(NULL),
_pPopup(NULL),
_isGameOver(false),
_isFinished(false)
{
	
	_isActive = false;

	_isMouseLock = false;

   for (unsigned int i=0; i<21; i++)
      _ucNewTroophy[i] = 0;

}

// class destructor

CIngame::~CIngame()
{
	Close();
}

// load data

void CIngame::Open(CScreen *pScreen)
{	
	_ulScore = 0;			// iloœæ punktów

	_ulTimer1000 = 0;		// czas 10 sek temu
	_ulScore1000 = 0;		// punkty 10 sek temu
	_ulTimerStart = 0;	// poczatek
	_ulPrevTimer = 0;

	_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");
   _pBackground = new CSprite(pScreen,"LEVEL01_SCREEN");

	_pFXManager = new CFXManager(pScreen);

	// popup manager

	_pPopup = new CPopup();
	_pPopup->Open(pScreen);

	_isMouseLock = false;

	_isGameOver = false;
   _isFinished = false;

	for (int i=0; i<20; i++)		/// zerujemy tablice nowych osiagniec
		_ucNewTroophy[i] = 0;
	
	_pScreen = pScreen;

	_isActive = true;	// data loaded

}

// free graphics and music, but keep the required data

void CIngame::Close(void)
{
	SafeDelete(_pFXManager);

	SafeDelete(_pBlack);
	SafeDelete(_pBackground);

	SafeDelete(_pParticleManager);
   SafeDelete(_pPopup);

	_ulTimerStart = 0;	// poczatek

	_isActive = false;
}

// zwraca liczbe przy konwersji znaku z tablicy
// convert char digit to int and return as char :)

char CIngame::cToDigit(char cDigit)
{
	return char((int)cDigit-'0');
}

//=== rysuje pojedyncza klatke
//=== TODO: extra klocki dostepne proporcjonalnie do levelu

void CIngame::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int 	iReturn,h3;

	iReturn = 0;

	if (_ulTimerStart == 0)		// czy to pierwsza renderowana klatka ?
	{
		_ulTimerStart = ulTimer;

		if (pMouse->isLeft() || pMouse->isRight())	// nie przechwytujmy clicku z menu
			_isMouseLock = true;

		_pPopup->Add(POPUP_INGAME_START,ulTimer);

	}

	_pBackground->Render();
	_pParticleManager->Render(ulTimer);

	_pFXManager->Render(ulTimer, FX_LAYER_0);

	// rysujemy licznik punktow

	h3=0;

	// dodatkowe particle - hint

	_pFXManager->Render(ulTimer, FX_LAYER_5);

	// rysujemy game over

	_ulPrevTimer = ulTimer;		// zapamietaj czas ostatniej klatki

	// renderujemy popup jezeli jakis jest

	if (!_isGameOver)
		_pPopup->Render(ulTimer);

}

//end
