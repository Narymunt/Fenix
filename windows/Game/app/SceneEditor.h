// edytor do scen, do umieszczania obiektów
#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "../gfx/OGL.h"
#include "../ui/Mouse.h"
#include "../ui/Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"
#include "../ui/ButtonTTF.h"

class CSceneEditor: public CGameObject
{
public:
	CSceneEditor();
	~CSceneEditor();

	void	open(CScreen* pScreen);		// load data
	void	close(void);				// unload 

	int		render(unsigned long lTimer, CMouse* pMouse);		// render frame																					

private:

	CSprite* _background;
	
	CButtonTTF* _exitButton;

	unsigned long	_timerStart;	// start

};

