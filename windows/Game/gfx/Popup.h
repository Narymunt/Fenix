/**
   Popup.h

   Tylko do wyskakuj¹cych napisów. 
   Trzyma informacje o texturach, ¿eby nie powielaæ sprite dla ka¿dej cz¹stki z osobna.
   Maksymalnie 64 popupy na ekranie.

   @author Jaros³aw Ro¿yñski
   
*/


#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include "../Game.h"
#include "../common/GameObject.h"
#include "Sprite.h"
#include "Screen.h"

#define POPUP_FLASH_BLACK		10
#define POPUP_FLASH_WHITE		20
#define POPUP_FADE_WHITE		30
#define POPUP_FADE_BLACK		40

#define POPUP_INGAME_START		50
#define POPUP_INGAME_GOOD1		60
#define POPUP_INGAME_GOOD2		70
#define POPUP_INGAME_GOOD3		80
#define POPUP_INGAME_GOOD4		90
#define POPUP_INGAME_GOOD5		100

class CPopup: public CGameObject
{
	public:
		CPopup();
		~CPopup();

		void	open(void);				// load 
		void	close(void);						// unload 

		void	add(int type, unsigned long timer);		// add popup to quene 

		void	render(unsigned long timer);		// render active popups

		void	stop(void);								// stop all popups
		void	start(void);							// start all popups

		void	stop(int i);							// stop selected popup
		void	start(int i);

		bool			_isActive[64];			// activity flag 
		int				_type[64];				// type popup
		unsigned long	_timerStart[64];		// popup start timer 
		
		CSprite		*_whiteFlash;			// white screen 
		CSprite		*_blackFlash;			// black screen 

		CSprite		*_start;
		CSprite		*_good1;				// do not look here  ;)
		CSprite		*_good2;
		CSprite		*_good3;
		CSprite		*_good4;
		CSprite		*_good5;		

};
