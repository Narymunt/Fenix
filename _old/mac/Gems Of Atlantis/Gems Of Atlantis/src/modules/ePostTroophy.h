// po ingame - przydzielanie trofeum

// ePostTroophy - wyswietlana informacja o zdobytych trofeach, jezeli takowe zostaly zdobyte
// jezeli nie zosta³o - to nie jest nawet renderowana pierwsza klatka 

// 1 uloz 100 kombinacji
// 2 uloz 1000 kombinacji
// 3 kliknij 100 diamentow
// 4 kliknij 1000 diamentow
// 5 kliknij 100 teczowych kamieni
// 6 kliknij 1000 teczowych kamieni
// 7 kliknij 100 bomb
// 8 kliknij 1000 bomb
// 9 zdobadz 1 miejsce w highscore
// 10 zetknij ze sob¹ dwa teczowe kamienie
// 11 zdobadz 10 000 punktow
// 12 zdobadz 100 000 punktow
// 13 zagraj 100 razy w gre
// 14 zagraj 1000 razy w gre
// 15 zdobadz wszystkie miejsca w high score
// 16 umiesc na jednej planszy 5 diamentow
// 17 umiesc na jednej planszy 5 teczowych kamieni
// 18 uloz 8 klockow w jednej pionowej linii
// 19 uloz 8 klockow w jednej poziomej linii
// 20 ukoncz wszystkie etapy

#pragma once

#include "Game.h"
#include "GameObject.h"
#include "OGL.h"
#include "Mouse.h"
#include "Button.h"
#include "Sprite.h"
#include "Screen.h"
#include "Profile.h"

class ePostTroophy: public CGameObject
{
public:
	ePostTroophy();
	~ePostTroophy();

	void	Open(CScreen *pScreen);		// load data
	bool	reOpen(void);				// porownaj nowe dane ze starymi
	void	Close(void);				// unload 

	int		Render(unsigned long lTimer, CMouse *pMouse);		// render frame																					

	void	ucNewTroophy(int i, char c);	// ustawia znacznik dla nowego trofea, zeby bylo wiadomo co renderowac

private:
	
	CSprite	*_pBackground;		// tlo
	CButton	*_pExitButton;		// wyjscie z helpa

	CSprite	*_pTroophy[21];

	unsigned long	m_ulTimerStart;	// poczatek

	bool		m_bMouseLock;		// blokada przycisku

	bool		_bPreInitialized;	// jezeli nie zostal modul pre-inicjalizowany to przy destruktorze nie zapisujemy pliku
									// chodzi o nie zapisywanie stanu nowych osiagniec w przypadku gdy nigdy nie rozegrano gry

	unsigned char	_ucNewTroophy[21];		// tablica z nowymi trofeami

};

