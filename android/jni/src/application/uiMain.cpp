#include "uiMain.h"

//=== onstruktor

uiMain::uiMain(CScreen *pScreen)
{
	_pButtonList = 0;
	_pButtonSettings = 0;

	_pScreen = pScreen;
	_isActive = false;
	_isMouseLock = true;
}

//=== destructor 

uiMain::~uiMain()
{
	Close();
}

//=== load and prepare data

void uiMain::Open(void)
{
	int x = fRecalc(1024,128,_pScreen->iSizeX()); //fRecalc(768,128,_pScreen->iSizeX());
	int y = fRecalc(1024,128,_pScreen->iSizeX()); //fRecalc(1024,128,_pScreen->iSizeY());

	_pButtonList = new CButton("lista_img.png","lista_ono.png","lista_onc.png",_pScreen->iXD()-x, _pScreen->iYB()-y);
	_pButtonList->SetHotCoords(_pScreen->iXD()-x, _pScreen->iYB()-y, _pScreen->iXD()+x, _pScreen->iYB()+y);
	_pButtonList->Resize(_pScreen->iXD()-x, _pScreen->iYB()-y, _pScreen->iXD()+x, _pScreen->iYB()+y);

	_pButtonSettings = new CButton("buttonSettings_img.png","buttonSettings_ono.png","buttonSettings_onc.png",_pScreen->iXB()-x, _pScreen->iYB()-y);
	_pButtonSettings->SetHotCoords(_pScreen->iXB()-x, _pScreen->iYB()-y, _pScreen->iXB()+x, _pScreen->iYB()+y);
	_pButtonSettings->Resize(_pScreen->iXB()-x, _pScreen->iYB()-y, _pScreen->iXB()+x, _pScreen->iYB()+y);

	_isActive = true;
	_isMouseLock = true;
}

//=== release data

void uiMain::Close(void)
{
	SafeDelete(_pButtonList);
	SafeDelete(_pButtonSettings);

	_isActive = false;
	_isMouseLock = true;
}

// rysuj ekran

int uiMain::iRender(unsigned long ulTimer, CTouch *pTouch)
{
	int iReturn = -1;

	if (!_isActive)
		Open();

	if (!pTouch->isTouch())
		_isMouseLock = false;

//	if (_pButtonOK->Render(pTouch) && ! _isMouseLock)
//			return	uiMain_BUTTON_OK;

	if (_pButtonList->Render(pTouch)==ON_LEFT && !_isMouseLock)
		iReturn = uiMain_BUTTON_LIST;

	_pButtonSettings->Render(pTouch);

	return iReturn;
}
