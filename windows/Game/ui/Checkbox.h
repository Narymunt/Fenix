#pragma once

#include <stdio.h>
#include <string.h>
#include "../Game.h"
#include "../gfx/Sprite.h"
#include "../ui/Mouse.h"
#include "../gfx/Screen.h"

class Checkbox
{
public:

	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[]);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], bool b);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, bool b);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x1, int y1, int x2, int y2, bool b);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2);
	Checkbox(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b);
		
	~Checkbox();

	int	render(unsigned long timer, Mouse *mouse);	// 0 - mysz poza, 1 - clicked, 2 on over
	int	render(int x, int y, unsigned long timer, Mouse *mouse);
		
	void position(int x, int y);
	void position(int x, int y, int x1, int y1, int x2, int y2);
	void setHotCoords(int x1, int y1, int x2, int y2);
		
	void set(bool state, int x, int y);
	void set(bool state,int x, int y, int x1, int y1, int x2, int y2);
		
	bool	_state;	
		
	int		_x, _y;
	int		_x1, _y1, _x2, _y2;
				
	Sprite	*_onStatic, *_onOver, *_offStatic, *_offOver;
	
	void	init(char onStatic[], char onOver[], char offStatic[], char offOver[], int x, int y, int x1, int y1, int x2, int y2, bool b);

	bool	_isMouseLock;

};

