// edytor do scen, do umieszczania obiektów na planszy

#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"
#include "../ui/ButtonTTF.h"

class SceneEditor: public GameObject
{
public:
	SceneEditor();
	~SceneEditor();

	void	open(Screen* pScreen);		// load data
	void	close(void);				// unload 

	int		render(unsigned long timer, Mouse* mouse);		// render frame																					

private:

	Sprite* _background;	
	ButtonTTF* _exitButton;

	unsigned long	_timerStart;	// start

};

