// klawiatura dotykowa na urzadzeniach mobilnych
#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "Mouse.h"
#include "Button.h"

#ifdef _WIN32
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"
#endif

#ifdef __ANDROID__
#include "../android/Sprite.h"
#include "../android/Screen.h"
#endif

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#include "../ios/Sprite.h"
#include "../ios/Screen.h"
#elif TARGET_OS_IPHONE
// iOS device
#include "../ios/Sprite.h"
#include "../ios/Screen.h"
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#include "../osx/Sprite.h"
#include "../osx/Screen.h"
#else
#   error "Unknown Apple platform"
#endif
#endif

class CMobileKeyboard : public CGameObject
{

public:
	
	CMobileKeyboard(char cLanguage);				// konstruktor czysci zmienne (NULL)
	virtual ~CMobileKeyboard();		// destruktor zwalnia pamiec i urzadzenie

	void open(void);
	void close(void);

	unsigned char  render(unsigned long ulTimer, CMouse *pMouse);					// zwraca numer nacisnietego przycisku

private :

	char	_language;

	char	_state;		// 0 wylaczona i nieaktywna
						// 1 nie aktywna, wysuwa sie
						// 2 aktywna
						// 3 nie aktywna chowa sie

	CButton *_a, *_b, *_c, *_d, *_e, *_f, *_g, *_h, *_i, *_j, *_k, *_l, *_m, *_n, *_o;
	CButton *_p, *_q, *_r, *_s, *_t, *_u, *_v, *_w, *_x, *_y, *_z, *_0, *_1, *_2, *_3;
	CButton *_4, *_5, *_6, *_7, *_8, *_9, *_space, *_delete, *_enter;
		
	unsigned long _timerOpen;
	unsigned long _timerClose;
	

};

