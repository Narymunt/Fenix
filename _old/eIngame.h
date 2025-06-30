// match3 module 

#pragma once

#include <SDL_mixer.h>
#include "main.h"
#include "GameObject.h"
#include "Mouse.h"
#include "Particle2DManager.h"
#include "Button.h"
#include "Popup.h"

#define GEMS_COUNT	11				// how many gem type 

#define GEM_ROCK	7				// that gem does not match to any pattern
#define GEM_DIAMOND 8				// clean all gems in horizontal and vertical line 
#define GEM_RAINBOW 9				// remove all gems of the same color 
#define	GEM_BOMB	10				// explode gems around 

#define BOARD_X1	700
#define BOARD_Y1	28
#define	BOARD_X2	700+1024
#define BOARD_Y2	28+1024

#define	DEFAULT_SCREENX		1920
#define DEFAULT_SCREENY		1080

#define BAR_SIZEX	600
#define BAR_X		32
#define BAR_Y1		850
#define BAR_Y2		950

#define ITEM_SIZE	128

#define	CLICK_DELTA	64				// how sensitive is mouse when clicked on gems

class eIngame : public CGameObject
{
public:
	eIngame();
	~eIngame();

	void	Open(CScreen *pScreen);		// load data 
	void	Close(void);				// unload data 

	int		Render(unsigned long ulTimer,CMouse *pMouse);		// render frame

	bool	isMatch3(unsigned long ulTimer);			// check all combination and generate special gems
	bool	isMatch3Check(void);						// check only for normal gems - used for hint etc. 

	void	Advance(unsigned long ulBonusTime, unsigned long ulBonusExp, unsigned long ulScore);	// add points, exp, time 

	bool	isMoveGems(unsigned long ulTimer);		// update delta x/y 

	void	DrawProgressBar(unsigned long ulTimer);
	char	cToDigit(char cDigit);

	unsigned long ulGetScore(void);				// return points from this session - used for highscore etc. 
	void	AddScore(unsigned long lScore);		// add score

private:

	float	_fM3Delta;

	char	_cBoard[64];				// 8x8 
	bool	_bBoard[64];				// false = stay, true = delete 
	
	float	_fBoardDeltaX[64];			// delta from default position 
	float	_fBoardDeltaY[64];			

	char	_cClickedA, _cClickedB;		// clicked gems

	int		_iClickedAx, _iClickedAy;	// clicked gems positions 
	int		_iClickedBx, _iClickedBy;

	char	_cReplacedA, _cReplacedB;			// clicked, unmatched gems
	float	_idA_lastDeltaX, _idA_lastDeltaY;	// delta for unmatched, swaped gems
	float	_idB_lastDeltaX, _idB_lastDeltaY;	

	char	_cScaleBoard[64];			// 8x8 scaled board 
	float	_fScaleBoard[64];			// underlayer scale
	unsigned long _ulScaleTimer[64];	// timer start
		
	CSprite	*_pBoard;					// board image

	CSprite	*_pBlack;					// black fade
	CSprite	*_pBackground;				// background fade

	CSprite	*_pGem[11];					// gems bitmaps 
	CSprite	*_pNumber[10];				// numbers

	CSprite	*_pTimeBar;					// time progress bar 
	CSprite	*_pExpBar;					// experience progress bar 
	CSprite	*_pGreyBar;					// background of progress bars 

	unsigned long	_ulBonusTime;		// extra time 
	unsigned long	_ulBonusExp;		// extra experience

	unsigned long	_ulTimerStart;		// game start 
	unsigned long	_ulPrevTimer;		// time passed between frames
	unsigned long	_ulTimer1000;		// time 10 seconds ago 


	bool		_bMouseLock;			// mouse lock to transfer click 
	bool		_bFallLock;				// lock when gems are falling 
	bool		_bPrevFallLock;			// previous frame lock 

	CSprite		*_pGameOver;			// game over bitmap
	bool		_bGameOver;				// game over state
	long		_lInGameOver;			// game over state timer

	CParticle2DManager	*_pParticleManager;

	CSprite	*_pHint;					// hint frame
	
	long		_lHintTime;				// time since last move 
	bool		_bHint;					// czy wyswietlamy podpowiedz (po nacisnieciu przycisku)
	int			_iHintX, _iHintY;		// wspolrzedne podpowiedzi

	unsigned long	_ulScore;			// points  :)
	unsigned long	_ulScore1000;		// points 10 seconds ago 

	CButton		*_pButtonMenu;
	CButton		*_pButtonHint;

	CSprite	*_pScoreMulti[10];			// score mul icon 
	unsigned char	_ucScoreMulti;

	CPopup		*_pPopup;				//  popup manager

	CScreen		*_pScreen;				// reference

	// audio samples 

	Mix_Chunk	*_pMSuper, *_pMRainbow, *_pMDiamond, *_pMLevelUp, *_pMClick, *_pMBomb;

};

