// checkbox - kontrolka do zaznaczania/odznaczania

#pragma once

#include <stdio.h>
#include <string.h>
#include "../Game.h"
#include "../gfx/Sprite.h"
#include "../ui/Mouse.h"
#include "../gfx/Screen.h"

class CCheckbox
{

	public:

		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[]);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], bool b);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, bool b);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2, bool b);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2);
		CCheckbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b);

		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[]);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], bool b);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, bool b);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2, bool b);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2);
		CCheckbox(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b);
		
		~CCheckbox();

		int		render(unsigned long ulTimer,CMouse *pMouse);	// 0 - mysz poza, 1 - clicked, 2 on over
		int		render(int iX, int iY, unsigned long ulTimer,CMouse *pMouse);
		
		void	set(int iX, int iY);
		void	set(int iX1, int iY1, int iX2, int iY2);
		void	set(int iX, int iY, int iX1, int iY1, int iX2, int iY2);
		
		void	set(int iX, int iY, bool b);
		void	set(int iX1, int iY1, int iX2, int iY2, bool b);
		void	set(int iX, int iY, int iX1, int iY1, int iX2, int iY2, bool b);
		
		bool	_isSet;	
		
		int		_x, _y;
		int		_x1, _y1, _x2, _y2;
				
private : 
		CSprite	*_onStatic, *_onOver, *_offStatic, *_offOver;
	
		void	init(CScreen *screen, char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b);

		bool	_isMouseLock;

};

