// edytor do animacji szkieletowych i sprite, 

#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"
#include "../ui/ButtonTTF.h"

class SkeletalEditor: public GameObject
{
public:
	SkeletalEditor();
	~SkeletalEditor();

	void	open(Screen* pScreen);		// load data
	void	close(void);				// unload 

	int		render(unsigned long timer, Mouse* mouse);		// render frame																					

	Sprite* _background;	
	ButtonTTF* _exitButton;

	unsigned long	_timerStart;	// start

};

