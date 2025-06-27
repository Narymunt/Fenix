// match3 module 

#pragma once

#include "/Library/Frameworks/SDL_mixer.framework/Headers/SDL_mixer.h"
#include "Animation.h"
#include "Game.h"
#include "GameObject.h"
#include "Mouse.h"
#include "Particle2DManager.h"
#include "Button.h"
#include "Popup.h"
#include "Profile.h"
#include "Screen.h"

#define M3_DELTA	16.0f			// z jaka predkoscia poruszaja sie klocki
#define GEMS_COUNT	11				// ile ikon kamykow

#define GEM_ROCK	7				// kamyk ktory nie uklada sie we wzory
#define GEM_DIAMOND 8				// diament robi blyskawice w pionie i poziomie
#define GEM_RAINBOW 9				// kamyk tenczowy usuwa wszystkie danego typu z planszy
#define	GEM_BOMB	10				// bomba wybucha kamyki dookola

class eIngame : public CGameObject
{
public:
	eIngame();
	~eIngame();

	void					Open(int iLevel, CScreen *pScreen);		// load data 
	void					Close(void);				// unload data 

	int						Render(unsigned long ulTimer,CMouse *pMouse);		// render frame

	bool					isMatch3(unsigned long ulTimer);			// check all combination and generate special gems
	bool					isMatch3Check(void);						// check only for normal gems - used for hint etc. 

	void					Advance(unsigned long ulBonusTime, unsigned long ulBonusExp, unsigned long ulScore);	// add points, exp, time 

	bool					isMoveGems(unsigned long ulTimer);		// update delta x/y 

	void					DrawProgressBar(unsigned long ulTimer);
	char					cToDigit(char cDigit);

	unsigned long			ulGetScore(void);				// return points from this session - used for highscore etc. 
	void					AddScore(long lScore);		// add score

	unsigned char			ucNewTroophy(int i);	// zwraca 1 jezeli odblokowano nowe osiagniecie

private:

	char					m_cBoard[64];	// 8x8 tutaj sa nasze klocki
	bool					m_bBoard[64];	// false = zostaje, true = do skasowania
	
	float					m_fBoardDeltaX[64];		// dla klockow przesuwanych poziomo
	float					m_fBoardDeltaY[64];		// dla klockow przesuwanych pionowo

	char					m_cClickedA, m_cClickedB;	// ktore klocki ze soba przestawiamy

	int						m_iClickedAx, m_iClickedAy;	// zapamietane wspolrzedne
	int						m_iClickedBx, m_iClickedBy;

	char					m_cScaleBoard[64];	// 8x8 informacja o skalowanych klockach, jezeli 255 to nie rysujemy
	float					m_fScaleBoard[64];	// skala klocka
	unsigned long			m_ulScaleTimer[64];	// timer startu
		
	CSprite					*m_pBoard;			// szachownica, podkladka pod kamienie
	unsigned int			_uiBoardOffsetY;	// ile pikseli od gornego rogu ma byc narysowana tablica


	CSprite					*m_pBlack;			// czarne tlo
	CSprite					*m_pBackground;		// tlo

	CSprite					*m_pGem[11];		// obrazki z klockami
	CSprite					*m_pNumber[10];		// cyferki

	CSprite					*m_pTimeBar;		// pokazuje progress czasu
	CSprite					*m_pExpBar;			// doswiadczenie w levelu
	CSprite					*m_pGreyBar;		// szare, zeby bylo wiadomo ile miejsca jest

	unsigned long			m_ulBonusTime;	// dodatkowy czas, ktory pojawia sie, gdy ukladamy klocki
	unsigned long			m_ulBonusExp;	// dodatkowe punkty doswiadczenia

	unsigned long			m_ulTimerStart;	// poczatek
	unsigned long			m_ulPrevTimer;	// zapamietujemy
	unsigned long			m_ulTimer1000;	// zapamietujemy czas 10 sekund temu, jezeli w ciagu 10 sekund nabijemy odpowiednia ilosc punktow to wyskakuje popup

	bool					m_bMouseLock;		// zeby nie lapal tego samego klikniecia na nastepne klatki
	bool					m_bFallLock;		// jezeli klocki spadaja to nie sprawdzamy pionowej kombinacji
	bool					m_bPrevFallLock;	// stan blokady z poprzedniej klatki

	CSprite					*m_pGameOver;		// nakladka na calosc
	bool					m_bGameOver;		// czy koniec gry ?
	long					m_lInGameOver;		// jak dlugo w trybie game over ? 

	CParticle2DManager		*m_pParticleManager;

	CSprite					*m_pHint;			// ramka pokazujaca ktory kamyk przesunac
	
	long					m_lHintTime;		// ile czasu bez ruchu ? 
	bool					m_bHint;			// czy wyswietlamy podpowiedz (po nacisnieciu przycisku)
	int						m_iHintX, m_iHintY;	// wspolrzedne podpowiedzi

	unsigned long			m_ulScore;		// punkty :)
	unsigned long			m_ulScore1000;	// zapamietujemy punkty 10 sekund temu, jezeli w ciagu 10 sekund nabijemy odpowiednia ulosc punktow to wyskakuje popup

	CButton					*m_pButtonMenu;
	CButton					*m_pButtonHint;

	CSprite					*m_pScoreMulti[10];	// mnoznik dla punktow
	unsigned char			m_ucScoreMulti;

	CPopup					*m_pPopup;			// nasz popup manager

	long					m_iCoin[64];	// uzywane do animowania monet wyskakujacych z ulozonych klockow, zawiera timer uruchomienia lub -1 jezeli nie aktywne
	unsigned short			_sCoin[64];	// ile punktow mryga
	CSprite					*_pScore100;	// +100
	CSprite					*_pScore250;	// +250
	CSprite					*_pScore500;	// +500
	CSprite					*_pScore1000;	// +1000

	unsigned char			_ucNewTroophy[21];	// czy zdobyto nowe osiagniecie ?

	unsigned int			_uiMatchCount;	// ile combinacji udalo sie juz ulozyc

	CScreen					*_pScreen;

	CAnimation				*_pGemRock;		// 8
	CAnimation				*_pGemDiamond;	// 9
	CAnimation				*_pGemRainbow;	// 10
	CAnimation				*_pGemBomb;		// 11

	// audio samples 

	Mix_Chunk	*_pMSuper, *_pMRainbow, *_pMDiamond, *_pMLevelUp, *_pMClick, *_pMBomb;

};

