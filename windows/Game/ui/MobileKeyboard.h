// klawiatura dotykowa na urzadzeniach mobilnych
#pragma once

#include "../Game.h"
#include "../common/GameObject.h"
#include "Mouse.h"
#include "Button.h"
#include "../gfx/Sprite.h"
#include "../gfx/Screen.h"

class MobileKeyboard : public GameObject
{

public:
	
	MobileKeyboard(char cLanguage);				// konstruktor czysci zmienne (NULL)
	virtual ~MobileKeyboard();		// destruktor zwalnia pamiec i urzadzenie

	void open(void);
	void close(void);

	unsigned char  render(unsigned long ulTimer, Mouse *pMouse);					// zwraca numer nacisnietego przycisku

	char	_language;

	char	_state;		// 0 wylaczona i nieaktywna
						// 1 nie aktywna, wysuwa sie
						// 2 aktywna
						// 3 nie aktywna chowa sie

	Button *_a, *_b, *_c, *_d, *_e, *_f, *_g, *_h, *_i, *_j, *_k, *_l, *_m, *_n, *_o;
	Button *_p, *_q, *_r, *_s, *_t, *_u, *_v, *_w, *_x, *_y, *_z, *_0, *_1, *_2, *_3;
	Button *_4, *_5, *_6, *_7, *_8, *_9, *_space, *_delete, *_enter;
		
	unsigned long _timerOpen;
	unsigned long _timerClose;
	

};

