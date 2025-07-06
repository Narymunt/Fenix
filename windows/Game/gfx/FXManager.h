#pragma once

#include <windows.h>
#include <stdio.h>
#include <vector>
#include "../Game.h"
#include "Particle2DManager.h"
#include "Screen.h"
#include "Sprite.h"

#define  FX_SMALL_EXPLOSION		10
#define  FX_BIG_EXPLOSION		100

#define  FX_SMALL_LOOP			200
#define	 FX_BIG_LOOP			300

#define  FX_HINT				400

#define  FX_SHOW_BOMB			500
#define  FX_DIAMOND_EXPLOSION	600
#define  FX_RAINBOW_EXPLOSION	800

#define  FX_MENU_BUTTON			700

#define  FX_LAYER_0				0
#define  FX_LAYER_1				1
#define  FX_LAYER_2				2
#define  FX_LAYER_3				3
#define  FX_LAYER_4				4
#define  FX_LAYER_5				5
#define  FX_LAYER_6				6
#define  FX_LAYER_7				7
#define  FX_LAYER_8				8
#define  FX_LAYER_9				9

class FXManager
{

public:

	FXManager(Screen *pScreen);
	~FXManager();

	int add(int type, int x, int y, float r, float g, float b, float a, unsigned long timerStart, unsigned long time);
	int add(int type, int x, int y, float r, float g, float b, float a, unsigned long timerStart, unsigned long time, char layer);

	void remove(int id);

	void render(unsigned long timer);
	void render(unsigned long timer, char layer);

	Screen		*_screen;

	vector <unsigned long>_timerStart; // kiedy efekt ma siê zacz¹æ
	vector <unsigned long>_timerEnd; // kiedy efekt ma siê skoñczyæ

	vector <Particle2DManager*> _particles; // nasze generatory particli

	vector <char>_layer; // warstwy, ¿eby mo¿na by³o ³atwiej kontrolowaæ to co ma siê wyœwietlaæ pod tablic¹ i nad tablic¹

	Sprite *_image[14];

};

