#include "Ingame.h"
#pragma warning(disable : 4996)	// sprintf unsafe

CIngame::CIngame() : _black(NULL), _background(NULL), _timerStart(0), _timerPrev(0)
{
	_isOpen = false;
	_isMouseLock = false;
}

// class destructor

CIngame::~CIngame()
{
	close();
}

// load data

void CIngame::open(CScreen *pScreen)
{	
	_timerStart = 0;	// poczatek
	_timerPrev = 0;

//	_black = new CSprite("level05_1920.jpg");
	_background = new CSprite((char*)"level05_1920.jpg");

	_isMouseLock = false;
	
	_screen = pScreen;

	_isOpen = true;	// data loaded
}

// free graphics and music, but keep the required data

void CIngame::close(void)
{
	safeDelete(_black);
	safeDelete(_background);

	_timerStart = 0;	// poczatek

	_isOpen = false;
}

//=== rysuje pojedyncza klatke
//=== TODO: extra klocki dostepne proporcjonalnie do levelu

void CIngame::render(unsigned long timer, CMouse *mouse)
{

	if (_timerStart == 0)		// czy to pierwsza renderowana klatka ?
	{
		_timerStart = timer;

		if (mouse->_isL || mouse->_isR)	// nie przechwytujmy clicku z menu
			_isMouseLock = true;
	}

	_background->render();

	// rysujemy game over

	_timerPrev = timer;		// zapamietaj czas ostatniej klatki
}

