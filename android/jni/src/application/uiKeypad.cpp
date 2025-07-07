#include "uiKeypad.h"

//=== onstruktor

uiKeypad::uiKeypad(CScreen *pScreen) :
_pLedAlarmOn(0), _pLedAlarmOff(0), _pLedArmOn(0), _pLedArmOff(0),
_pLedGroupAOn(0), _pLedGroupAOff(0), _pLedGroupBOn(0), _pLedGroupBOff(0),
_pLedServiceOn(0), _pLedServiceOff(0), _pLedTroubleOn(0), _pLedTroubleOff(0),
_pLogo(0), _pDisplay(0), _pBackground(0),
_isLedAlarm(false), _isLedArm(false), _isLedGroupA(false), _isLedGroupB(false),
_isLedService(false), _isLedTrouble(false)
{
	_pScreen = pScreen;
	_isActive = false;
	_isMouseLock = true;

	for (int i=0; i<16; i++)
		_pButtonKey[i] = 0;
}

//=== destructor 

uiKeypad::~uiKeypad()
{
	Close();
}

//=== load and prepare data

void uiKeypad::Open(void)
{
	float fStepX = (float)(_pScreen->iSizeX()/6);
	float fStepY = (float)(_pScreen->iSizeY()/10);
	float x1,y1,x2,y2;

	char cBufferImg[100], cBufferOver[100], cBufferClick[100];

	_pBackground = new CSprite("black.png");
	_pBackground->Resize(0,0,_pScreen->iSizeX(), _pScreen->iSizeY());

	// mini ekran

	_pDisplay = new CSprite("display.png");
	_pDisplay->Resize(fStepX*0.25f, fStepY*2, fStepX*5.75f, fStepY*4);

	_pLogo = new CSprite("DisplayLogo.png");
	_pLogo->Resize(fStepX*1.0f, fStepY*4, fStepX*5.0f, fStepY*5);

	// sygnalizacja alarmu

	_pLedAlarmOn = new CSprite("ledAlarmOn.png");
	_pLedAlarmOn->Position(fStepX*0.25,fStepY*1);

	_pLedAlarmOff = new CSprite("ledAlarmOff.png");
	_pLedAlarmOff->Position(fStepX*0.25,fStepY*1);

	// sygnalizacja awarii

	_pLedTroubleOn = new CSprite("ledTroubleOn.png");
	_pLedTroubleOn->Position(fStepX*1.25f,fStepY*1);

	_pLedTroubleOff = new CSprite("ledTroubleOff.png");
	_pLedTroubleOff->Position(fStepX*1.25f,fStepY*1);

	// sygnalizacja trybu serwisowego

	_pLedServiceOn = new CSprite("ledServiceOn.png");
	_pLedServiceOn->Position(fStepX*2.25f,fStepY*1);

	_pLedServiceOff = new CSprite("ledServiceOff.png");
	_pLedServiceOff->Position(fStepX*2.25f,fStepY*1);

	// sygnalizacja uzbrojenia

	_pLedArmOn = new CSprite("ledArmOn.png");
	_pLedArmOn->Position(fStepX*3.25f,fStepY*1);

	_pLedArmOff = new CSprite("ledArmOff.png");
	_pLedArmOff->Position(fStepX*3.25f,fStepY*1);

	// sygnalizacja grupy A

	_pLedGroupAOn = new CSprite("ledGroupAOn.png");
	_pLedGroupAOn->Position(fStepX*4.25f,fStepY*1);

	_pLedGroupAOff = new CSprite("ledGroupAOff.png");
	_pLedGroupAOff->Position(fStepX*4.25f,fStepY*1);

	// sygnalizacja grupy B

	_pLedGroupBOn = new CSprite("ledGroupBOn.png");
	_pLedGroupBOn->Position(fStepX*5.25f,fStepY*1);

	_pLedGroupBOff = new CSprite("ledGroupBOff.png");
	_pLedGroupBOff->Position(fStepX*5.25f,fStepY*1);

	// klawiatura

	for (int i=0; i<10; i++)
	{
		sprintf(cBufferImg,"ic_%d.png",i);
		sprintf(cBufferOver,"ic_%d_pressed.png",i);
		sprintf(cBufferClick,"ic_%d_pressed.png",i);

		_pButtonKey[i] = new CButton(cBufferImg, cBufferOver, cBufferClick);
	}

	fStepX = (float)(_pScreen->iSizeX()/4);

	// 1 2 3 ^

	x1 = fStepX * 0.25f;
	y1 = fStepY * 5;

	x2 = fStepX * 1.25f - 1;
	y2 = fStepY * 6 -1 ;

	_pButtonKey[1]->Position(x1, y1);
	_pButtonKey[1]->SetHotCoords(x1, y1, x2, y2);

	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[2]->Position(x1,y1);
	_pButtonKey[2]->SetHotCoords(x1,y1,x2,y2);

	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[3]->Position(x1,y1);
	_pButtonKey[3]->SetHotCoords(x1,y1,x2,y2);

	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[12] = new CButton("ic_up.png","ic_up_pressed.png","ic_up_pressed.png");
	_pButtonKey[12]->Position(x1,y1);
	_pButtonKey[12]->SetHotCoords(x1,y1,x2,y2);

	// 4 5 6 <

	x1 = fStepX * 0.25f;
	y1 = fStepY * 6;

	x2 = fStepX * 1.25f - 1;
	y2 = fStepY * 7 -1 ;

	_pButtonKey[4]->Position(x1,y1);
	_pButtonKey[4]->SetHotCoords(x1,y1,x2,y2);

	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[5]->Position(x1,y1);
	_pButtonKey[5]->SetHotCoords(x1,y1,x2,y2);

	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[6]->Position(x1,y1);
	_pButtonKey[6]->SetHotCoords(x1,y1,x2,y2);

	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[13] = new CButton("ic_left.png","ic_left_pressed.png","ic_left_pressed.png");
	_pButtonKey[13]->Position(x1,y1);
	_pButtonKey[13]->SetHotCoords(x1,y1,x2,y2);

	// 7 8 9 >

	x1 = fStepX * 0.25f;
	y1 = fStepY * 7;

	x2 = fStepX * 1.25f - 1;
	y2 = fStepY * 8 -1 ;

	_pButtonKey[7]->Position(x1,y1);
	_pButtonKey[7]->SetHotCoords(x1,y1,x2,y2);
	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[8]->Position(x1,y1);
	_pButtonKey[8]->SetHotCoords(x1,y1,x2,y2);
	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[9]->Position(x1,y1);
	_pButtonKey[9]->SetHotCoords(x1,y1,x2,y2);
	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[14] = new CButton("ic_right.png", "ic_right_pressed.png", "ic_right_pressed.png");
	_pButtonKey[14]->Position(x1,y1);
	_pButtonKey[14]->SetHotCoords(x1,y1,x2,y2);

	// * 0 # \/

	x1 = fStepX * 0.25f;
	y1 = fStepY * 8;

	x2 = fStepX * 1.25f - 1;
	y2 = fStepY * 9 -1 ;

	_pButtonKey[10] = new CButton("ic_star.png","ic_star_pressed.png","ic_star_pressed.png");
	_pButtonKey[10]->Position(x1,y1);
	_pButtonKey[10]->SetHotCoords(x1,y1,x2,y2);
	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[0]->Position(x1,y1);
	_pButtonKey[0]->SetHotCoords(x1,y1,x2,y2);
	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[11] = new CButton("ic_hash.png","ic_hash_pressed.png","ic_hash_pressed.png");
	_pButtonKey[11]->Position(x1,y1);
	_pButtonKey[11]->SetHotCoords(x1,y1,x2,y2);
	x1 += fStepX;
	x2 += fStepX;

	_pButtonKey[15] = new CButton("ic_down.png", "ic_down_pressed.png", "ic_down_pressed.png");
	_pButtonKey[15]->Position(x1,y1);
	_pButtonKey[15]->SetHotCoords(x1,y1,x2,y2);

	_isActive = true;
	_isMouseLock = true;
}

//=== release data

void uiKeypad::Close(void)
{
	SafeDelete(_pBackground);

	SafeDelete(_pDisplay);
	SafeDelete(_pLogo);

	SafeDelete(_pLedAlarmOn); SafeDelete(_pLedAlarmOff);
	SafeDelete(_pLedArmOn); SafeDelete(_pLedArmOff);
	SafeDelete(_pLedGroupAOn); SafeDelete(_pLedGroupAOff);
	SafeDelete(_pLedGroupBOn); SafeDelete(_pLedGroupBOff);
	SafeDelete(_pLedServiceOn); SafeDelete(_pLedServiceOff);
	SafeDelete(_pLedTroubleOn); SafeDelete(_pLedTroubleOff);

	for (int i=0; i<16; i++)
		SafeDelete(_pButtonKey[i]);

	_isActive = false;
	_isMouseLock = true;
}

// rysuj ekran

int uiKeypad::iRender(unsigned long ulTimer, CTouch *pTouch)
{
	int iReturn = -1;

	if (!_isActive)
		Open();

	if (!pTouch->isTouch())
		_isMouseLock = false;

	_pBackground->Render();
	_pDisplay->Render();
	_pLogo->Render();

	_isLedAlarm ? _pLedAlarmOn->Render() : _pLedAlarmOff->Render();
	_isLedArm ? _pLedArmOn->Render() : _pLedArmOff->Render();
	_isLedGroupA ? _pLedGroupAOn->Render() : _pLedGroupAOff->Render();
	_isLedGroupB ? _pLedGroupBOn->Render() : _pLedGroupBOff->Render();
	_isLedService ? _pLedServiceOn->Render() : _pLedServiceOff->Render();
	_isLedTrouble ? _pLedTroubleOn->Render() : _pLedTroubleOff->Render();

	for (int i=0; i<16; i++)
	{
		if (_pButtonKey[i]->Render(pTouch)==ON_LEFT && !_isMouseLock)
			iReturn = i;
	}

	//	if (_pButtonOK->Render(pTouch) && ! _isMouseLock)
	//			return	uiMain_BUTTON_OK;

	return iReturn;
}
