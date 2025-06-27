// match3 module 

// isGameOver - czy wyswietlamy plansze game over zatrzymujac cala gre
// isActive - czy dane s� wczytane, regulujemy przez Open/Close
// isFinished - czy gra jest zako�czona i mo�na przej�� do innego stanu gry, ten stan gry mo�e by� te� wywo�any np. przez escape

#pragma once

#include <SDL_mixer.h>
#include "dune/gfx/Animation.h"
#include "Game.h"
#include "dune/GameObject.h"
#include "dune/ui/Mouse.h"
#include "dune/gfx/Particle2DManager.h"
#include "dune/ui/Button.h"
#include "dune/gfx/Popup.h"
#include "dune/io/Profile.h"
#include "dune/gfx/Screen.h"
#include "dune/gfx/FXManager.h"

class CIngame : public CGameObject
{
public:
	CIngame();
	~CIngame();

	void					   Open(CScreen *pScreen);					// load data 
	void					   Close(void);										// unload data 

	void					   Render(unsigned long ulTimer,CMouse *pMouse);		// render frame

	char					   cToDigit(char cDigit);

   inline unsigned long ulScore(void) { return _ulScore; }				         // return points from this session - used for highscore etc. 
   inline void				Score(unsigned long lScore) { _ulScore = lScore; }		// add score

   inline unsigned char	ucNewTroophy(int i) { return _ucNewTroophy[i]; }	   // zwraca 1 jezeli odblokowano nowe osiagniecie

   inline void          isGameOver(bool b) { _isGameOver = b; }
   inline bool          isGameOver(void) { return _isGameOver; }

   inline void          isFinished(bool b) { _isFinished = b; }
   inline bool          isFinished(void) { return _isFinished; }

private:

	CSprite					*_pBlack;											// czarne tlo
	CSprite					*_pBackground;										// tlo

	unsigned long			_ulTimerStart;										// poczatek
   unsigned long        _ulPrevTimer;                             // poprzedni czas wyrenderowania klatki
   unsigned long        _ulTimer1000;                             // czas pobrany 10 sekund temu, s�u�y do sprawdzenia czy odpalamy popup z bonusem

	CParticle2DManager	*_pParticleManager;                       // particle w tle, kt�re widoczne s� ca�y czas
   CFXManager           *_pFXManager;                             // efekty z particlami, kt�re pojawiaj� si� tylko na chwil�

	unsigned long			_ulScore;											// punkty :)
	unsigned long			_ulScore1000;										// zapamietujemy punkty 10 sekund temu, jezeli w ciagu 10 sekund nabijemy odpowiednia ulosc punktow to wyskakuje popup

	CPopup					*_pPopup;											// nasz popup manager

	unsigned char			_ucNewTroophy[21];	                     // czy zdobyto nowe osiagniecie ?

   bool                 _isGameOver;                              // czy jest game over ? to jeszcze nie jest koniec ingame
   bool                 _isFinished;                                  // to jest prawdziwe wyj�cie z ingame, poniewa� game over daje tylko plansz� ko�cow�

};

