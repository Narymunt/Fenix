// MainMenu - glowne menu gry

#pragma once

#include <vector>
#include "Main.h"
#include "State.h"
#include "../gfx/Screen.h"
#include "../gfx/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/SpriteFont.h"
#include "../gfx/Particle2DManager.h"
#include "../gfx/FXManager.h"
#include "../control/Touch.h"
#include "../system/Profile.h"

#define CRATE0 1	// #

#define CRATE1 2	// < poczatek platformy
#define CRATE2 3	// - œrodek platformy
#define CRATE3 4	// > zamkniêcie platformy

#define CRATE4 5	// [ otwarcie
#define CRATE5 6 	// =
#define CRATE6 7 	// ]


#define FRUIT0 20 	// $
#define FRUIT1 21
#define FRUIT2 22
#define FRUIT3 23
#define FRUIT4 24
#define FRUIT5 25
#define FRUIT6 26
#define FRUIT7 27
#define FRUIT8 28
#define FRUIT9 29

#define ENEMY0 50	// statyczny
#define ENEMY1 51	// lewo prawo powoli


#define	EXIT_LEVEL	255

const char rowA[]="# ## ### #### ##### #### ### ## # ################## ########################## ##################### ###################### #################### ############################### ######################### ####################### ## # ################ ################### ############ ### #############";

const char rowX[]="     ###                                         $#                                    ##                  $#                     $$        ##       $     ###                  ##         ###    $     ##  #    $ # ###  $  ###             $    #$            $     ##          #        $         $     #";
const char rowY[]="  $    $   #   $     $   $        $   #      $   ##    $   $    $    #     $           #$              $   ###       $    $$             $ ## $$            $         $$$     # $   $       $    ##   #     $$  ##  $$$           #$   $   $   $ ##   $       $ #  $#       $$ $   $  #$ # #  $   $  # $   #";
const char rowZ[]="# ## ### ## # # # # ### ## # ## ##  #### ## ### ### ##### ### #### ## #### ## #### ## ### # ## ### # ####################### #################### ############################### ######################### ####################### ## # ################ ################### ############ ### #############";

class CObject
{
public:

	CObject(int a, int b, int c)
	{
		x=a; y=b; type =c;
	}

	int 	x,y, type;

};

class CMainMenu : public CState
{

public:

	CMainMenu(CScreen *pScreen);
	~CMainMenu();

	int 		iOpen(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CTouch *pTouch);

	void 		renderMap();
	void 		buildMap(int item, int x, int y);

protected:

	unsigned long		_lastClick;

	char				_cEditName[18];				// nowa nazwa gracza

	bool				_isFirstRun;				// czy to pierwsze uruchomienie ?

	CSprite				*_pBackground;				// tlo z logiem gry
	CSprite				*_pTitle;					// tytu¸ gry

	CSprite				*_pBlack;					// czarny ekran
	CSprite				*_pWhite;					// bialy ekran

	CSprite				*_taptapText;				// migajacy napis taptap

	// elementy do planszy

	CSprite				*_crate0;

	CSprite				*_fruit0;
	CSprite				*_fruit1;
	CSprite				*_fruit2;
	CSprite				*_fruit3;
	CSprite				*_fruit4;
	CSprite				*_fruit5;
	CSprite				*_fruit6;
	CSprite				*_fruit7;
	CSprite				*_fruit8;
	CSprite				*_fruit9;

	char				_fruitCount;

    vector <CObject*>   _lane;

	CSpriteFont			*_pFont;

	char				_cUserName[8][20];
	unsigned char		_ucCurrentProfile;

	CParticle2DManager	*_pParticleManager;

};

