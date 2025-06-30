// klawiatura manipulatora

#pragma once

#include "Main.h"
#include "State.h"
#include "../gfx/Screen.h"
#include "../gfx/Button.h"
#include "../control/Touch.h"

#define KEYPAD_0		0
#define KEYPAD_1		1
#define KEYPAD_2		2
#define KEYPAD_3		3
#define KEYPAD_4		4
#define KEYPAD_5 		5
#define KEYPAD_6		6
#define KEYPAD_7		7
#define KEYPAD_8		8
#define KEYPAD_9		9
#define KEYPAD_STAR 	10
#define KEYPAD_HASH 	11
#define KEYPAD_UP		12
#define KEYPAD_DOWN 	13
#define KEYPAD_LEFT 	14
#define KEYPAD_RIGHT	15

class uiKeypad : public CState
{

public:

	uiKeypad(CScreen *pScreen);
	~uiKeypad();

	void		Open(void);			// load
	void		Close(void);		// unload

	int			iRender(unsigned long ulTimer, CTouch *pTouch);

	inline bool isLedAlarm(void) { return _isLedAlarm; }
	inline void isLedAlarm(bool b) { _isLedAlarm = b; }

	inline bool isLedArm(void) { return _isLedArm; }
	inline void isLedArm(bool b) { _isLedArm = b; }

	inline bool isLedGroupA(void) { return _isLedGroupA; }
	inline void isLedGroupA(bool b) { _isLedGroupA = b; }

	inline bool isLedGroupB(void) { return _isLedGroupB; }
	inline void isLedGroupB(bool b) { _isLedGroupB = b; }

	inline bool	isLedService(void) { return _isLedService; }
	inline void isLedService(bool b) { _isLedService = b; }

	inline bool isLedTrouble(void) { return _isLedTrouble; }
	inline void isLedTrouble(bool b) { _isLedTrouble = b; }

protected:

	CSprite		*_pBackground;

	bool		_isLedAlarm, _isLedArm, _isLedGroupA, _isLedGroupB;
	bool		_isLedService, _isLedTrouble;

	CSprite		*_pLedAlarmOn, *_pLedAlarmOff;		// dzwonek symbolizujacy czy alarm jest wlaczony
	CSprite		*_pLedArmOn, *_pLedArmOff;			// oczko symbolizujace uzbrojenie alarmu
	CSprite		*_pLedGroupAOn, *_pLedGroupAOff;	// grupa
	CSprite		*_pLedGroupBOn, *_pLedGroupBOff;
	CSprite		*_pLedServiceOn, *_pLedServiceOff;	// tryb serwisowy
	CSprite		*_pLedTroubleOn, *_pLedTroubleOff;	// sygnalizacja awarii

	CSprite		*_pDisplay;							// mini ekran na ktorym pojawiaja sie komunikaty
	CSprite		*_pLogo;							// logo satel pod wyswietlaczem

	CButton		*_pButtonKey[16];					// przyciski od klawiatury


};

