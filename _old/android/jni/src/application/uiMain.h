// State - stan aplikacji (aktualnie otwarty ekran/okno)

#pragma once

#include "Main.h"
#include "State.h"
#include "../gfx/Screen.h"
#include "../gfx/Button.h"
#include "../control/Touch.h"

#define	uiMain_BUTTON_OK		10
#define uiMain_BUTTON_LIST		20

class uiMain : public CState
{

public:

	uiMain(CScreen *pScreen);
	~uiMain();

	void		Open(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CTouch *pTouch);


protected:

	CButton		*_pButtonList;		// lista urzˆdzeÄ
	CButton		*_pButtonSettings;

};

