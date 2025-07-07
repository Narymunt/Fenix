#include "MainMenu.h"

//=== onstruktor

CMainMenu::CMainMenu(CScreen *pScreen) :
_pBackground(0), _pTitle(0),
_pBlack(0), _pWhite(0),
_pFont(0), _pParticleManager(0),
_isFirstRun(true),
_taptapText(0),
_lastClick(0),
_fruitCount(0),
_fruit0(0),
_fruit1(0),
_fruit2(0),
_fruit3(0),
_fruit4(0),
_fruit5(0),
_fruit6(0),
_fruit7(0),
_fruit8(0),
_fruit9(0)
{

	CProfile *pProfile;

	_pScreen = pScreen;
	_isActive = false;
	_isMouseLock = true;
	_ulTimerStart = 0;

	for (int i=0; i<18; i++)
		_cEditName[i] = 0;

}

//=== destructor 

CMainMenu::~CMainMenu()
{
	Close();
}

//=== load and prepare data

int CMainMenu::iOpen(void)
{

	CProfile *pProfile;

	if (_pBackground==NULL)
	{
		_pBackground = new CSprite(_pScreen,(char*)"e_mmenu");
		_pBackground->Fullscreen(_pScreen);
	}

	if (_pBlack==NULL)
	{
		_pBlack = new CSprite((char*)"black.png");
		_pBlack->Resize(0, 0, _pScreen->_iSizeX, _pScreen->_iSizeY);
	}

	if (_pWhite==NULL)
	{
		_pWhite = new CSprite((char*)"white.png");
		_pWhite->Fullscreen(_pScreen);
	}

	if (_pParticleManager == NULL)
	{
		_pParticleManager = new CParticle2DManager((char*)"k6.png", 50,
                                               (double)-100,(double)-100,(double)_pScreen->_iSizeX+100,(double)_pScreen->_iSizeY+100,
											   (double)0.01f,(double)0.01f,(double)0.3f,(double)0.3f,
											   (double)0.5f, (double)-.001f,(double).001f,
                                               0.5f, -.5f,.5f,
											   1000,10000);

		_pParticleManager->Color(0.95f, 0.82f, 0.0f, 1.0f);
	}

	if (_taptapText==NULL)
		_taptapText = new CSprite(_pScreen,(char*)"taptap");


	if (_pTitle == NULL)
	{
		_pScreen->_isHD ?
				_pTitle = new CSprite((char*)"title1024.png") :
				_pTitle = new CSprite((char*)"title512.png");

		_pTitle->Position((_pScreen->_iSizeX/2)-(_pTitle->_fSizeX/2),(_pScreen->_iSizeY/2)-(_pTitle->_fSizeY/2));

		return 100;
	}

	if (_pScreen->_isHD)
	{
		_crate0 = new CSprite((char*)"128obj1.png");

		_fruit0 =  new CSprite((char*)"128fruit0.png");
		_fruit1 =  new CSprite((char*)"128fruit1.png");
		_fruit2 =  new CSprite((char*)"128fruit2.png");
		_fruit3 =  new CSprite((char*)"128fruit3.png");
		_fruit4 =  new CSprite((char*)"128fruit4.png");
		_fruit5 =  new CSprite((char*)"128fruit5.png");
		_fruit6 =  new CSprite((char*)"128fruit6.png");
		_fruit7 =  new CSprite((char*)"128fruit7.png");
		_fruit8 =  new CSprite((char*)"128fruit8.png");
		_fruit9 =  new CSprite((char*)"128fruit9.png");
	}

	// budowanie mapy

	for (int i=0; i<300; i++)
	{
		buildMap(rowA[i],i*128,0);

		buildMap(rowX[i],i*128,_pScreen->_iSizeY-384);
		buildMap(rowY[i],i*128,_pScreen->_iSizeY-256);
		buildMap(rowZ[i],i*128,_pScreen->_iSizeY-128);
	}

	_lastClick = 0;
	_isActive = true;
	_isMouseLock = true;
	_ulTimerStart = 0;

	return 101;
}

//=== release data

void CMainMenu::Close(void)
{
	SafeDelete(_pBackground);
	SafeDelete(_pTitle);

	SafeDelete(_pBlack);
	SafeDelete(_pWhite);

	SafeDelete(_pFont);
	SafeDelete(_pParticleManager);
	SafeDelete(_taptapText);

	SafeDelete(_crate0);

	SafeDelete(_fruit0);
	SafeDelete(_fruit1);
	SafeDelete(_fruit2);
	SafeDelete(_fruit3);
	SafeDelete(_fruit4);
	SafeDelete(_fruit5);
	SafeDelete(_fruit6);
	SafeDelete(_fruit7);
	SafeDelete(_fruit8);
	SafeDelete(_fruit9);

	_isActive = false;
	_isMouseLock = true;
}


// rysuj ekran

int CMainMenu::iRender(unsigned long ulTimer, CTouch *pTouch)
{

	int iReturn = 0;
	int iDelta;

	if (!_isActive)
		Open();

	if (!pTouch->_isTouch)
		_isMouseLock = false;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	iDelta = ulTimer - _ulTimerStart;

	_pBackground->Render();

	_pParticleManager->Render(ulTimer);

	renderMap();

	if ((ulTimer%1000)<500)
		_taptapText->Render();

	if (pTouch->_isTouch && !_isMouseLock)
	{
		if (ulTimer-_lastClick>10 && ulTimer-_lastClick<2000)
			iReturn = 1;

		_lastClick = ulTimer;
		_isMouseLock = true;
	}

	_pTitle->Render();												// logo gry


	return iReturn;

}


void CMainMenu::renderMap()
{
	// renderowanie planszy

	for (int i=0;i<300; i++)
	{
		switch(_lane[i]->type)
		{
			case CRATE0:
				_crate0->Position(_lane[i]->x, _lane[i]->y);
				_crate0->Render();
			break;

			case FRUIT0:
				_fruit0->Position(_lane[i]->x, _lane[i]->y);
				_fruit0->Render();
			break;

			case FRUIT1:
				_fruit1->Position(_lane[i]->x, _lane[i]->y);
				_fruit1->Render();
			break;

			case FRUIT2:
				_fruit2->Position(_lane[i]->x, _lane[i]->y);
				_fruit2->Render();
			break;

			case FRUIT3:
				_fruit3->Position(_lane[i]->x, _lane[i]->y);
				_fruit3->Render();
			break;

			case FRUIT4:
				_fruit4->Position(_lane[i]->x, _lane[i]->y);
				_fruit4->Render();
			break;

			case FRUIT5:
				_fruit5->Position(_lane[i]->x, _lane[i]->y);
				_fruit5->Render();
			break;

			case FRUIT6:
				_fruit6->Position(_lane[i]->x, _lane[i]->y);
				_fruit6->Render();
			break;

			case FRUIT7:
				_fruit7->Position(_lane[i]->x, _lane[i]->y);
				_fruit7->Render();
			break;

			case FRUIT8:
				_fruit8->Position(_lane[i]->x, _lane[i]->y);
				_fruit8->Render();
			break;

			case FRUIT9:
				_fruit9->Position(_lane[i]->x, _lane[i]->y);
				_fruit9->Render();
			break;
		}
	}

	// przesuwanie planszy

	for (int i=0;i<300; i++)
	{
		switch(_lane[i]->type)
		{
			case CRATE0:
				_lane[i]->x--;
			break;

			default:
				_lane[i]->x--;
			break;

		}
	}
}

void CMainMenu::buildMap(int item, int x, int y)
{
	switch (item)
	{
		case '#':
			_lane.push_back(new CObject(x,y,CRATE0));
		break;

		case '$':
			if (_fruitCount==0)
				_lane.push_back(new CObject(x,y,FRUIT0));

			if (_fruitCount==1)
				_lane.push_back(new CObject(x,y,FRUIT1));

			if (_fruitCount==2)
				_lane.push_back(new CObject(x,y,FRUIT2));

			if (_fruitCount==3)
				_lane.push_back(new CObject(x,y,FRUIT3));

			if (_fruitCount==4)
				_lane.push_back(new CObject(x,y,FRUIT4));

			if (_fruitCount==5)
				_lane.push_back(new CObject(x,y,FRUIT5));

			if (_fruitCount==6)
				_lane.push_back(new CObject(x,y,FRUIT6));

			if (_fruitCount==7)
				_lane.push_back(new CObject(x,y,FRUIT7));

			if (_fruitCount==8)
				_lane.push_back(new CObject(x,y,FRUIT8));

			if (_fruitCount==9)
				_lane.push_back(new CObject(x,y,FRUIT9));

			_fruitCount++;

			if (_fruitCount==10)
				_fruitCount=0;
		break;
	}

}

