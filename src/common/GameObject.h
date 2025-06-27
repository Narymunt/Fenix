#pragma once

#ifdef _WIN32
#include "../gfx/Screen.h"
#endif

#ifdef __ANDROID__
#include "../android/Screen.h"
#endif

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#include "../ios/Screen.h"
#elif TARGET_OS_IPHONE
// iOS device
#include "../ios/Screen.h"
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#include "../osx/Screen.h"
#else
#   error "Unknown Apple platform"
#endif
#endif

class CGameObject
{

public:

	CGameObject();												// tutaj _pScreen jest NULL
	CGameObject(CScreen *screen);								// tutaj zapamiêtujemy wskaŸnik pScreen
	~CGameObject();

	virtual void		open(void);								// wczytaj dane 
	virtual void		close(void);							// zwolnij dane

	bool				_isOpen;								// czy modu³ jest aktywny ? czy dane zostaly wczytane ?
	bool				_isMouseLock;							// czy myszka jest zablokowana po poprzednim ekranie ? 

	CScreen				*_screen;								// zapamietujemy w niektorych metodach

};

