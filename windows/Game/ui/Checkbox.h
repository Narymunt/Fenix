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
		
	~CCheckbox();

	int	render(unsigned long timer, CMouse *mouse);	// 0 - mysz poza, 1 - clicked, 2 on over
	int	render(int x, int y, unsigned long timer, CMouse *mouse);
		
	void position(int x, int y);
	void position(int x, int y, int x1, int y1, int x2, int y2);
	void setHotCoords(int x1, int y1, int x2, int y2);
		
	void set(bool state, int x, int y);
	void set(bool state,int x, int y, int x1, int y1, int x2, int y2);
		
	bool	_state;	
		
	int		_x, _y;
	int		_x1, _y1, _x2, _y2;
				
private : 
		CSprite	*_onStatic, *_onOver, *_offStatic, *_offOver;
	
	void	init(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b);

	bool	_isMouseLock;

};

