#include "eMainMenu.h"


eMainMenu::eMainMenu()
{
	_pBackground = NULL;
	_pBlack = NULL;
	
	_pButtonStart = NULL;
	_pButtonQuit = NULL;

	_ulTimerStart = 0;

	_isActive = false;

	_pParticleManager = NULL;
}


eMainMenu::~eMainMenu()
{
	Close();
}


void eMainMenu::Open(CScreen *pScreen)
{	
	_pBackground = new CSprite("data/e_mmenu.jpg");
	_pBackground->Resize(0,0,pScreen->toX(1920), pScreen->toY(1080));

	_pBlack = new CSprite("data/fc1.png");
	_pBlack->Resize(0,0,pScreen->toX(1920), pScreen->toY(1080));

	_pButtonStart = new CButton("data/pl_startc.png","data/pl_starto.png","data/pl_start.png",pScreen->toX(990-200),pScreen->toY(100), pScreen->toX(990+200),pScreen->toY(300));
	_pButtonQuit = new CButton("data/pl_exitc.png","data/pl_exito.png","data/pl_exit.png",pScreen->toX(990-200), pScreen->toY(600), pScreen->toX(990+200), pScreen->toY(800));

	_pParticleManager = new CParticle2DManager((char*)"data/particle.png", 250, 
                                               -100,-100,pScreen->toX(1920),pScreen->toY(1080),
                                               0.01f,0.01f,0.3f,0.3f,
                                               0.5f, -.001f,.001f,
                                               0.5f, -5.0f,5.0f,
                                               1000,10000,pScreen);


	_isActive = true;
}


void eMainMenu::Close(void)
{
	SafeDelete(_pBackground);
	
	SafeDelete(_pBlack);
	
	SafeDelete(_pButtonStart);
	SafeDelete(_pButtonQuit);
	
	SafeDelete(_pParticleManager);

	_isActive = false;
}


int eMainMenu::Render(unsigned long ulTimer, CMouse *pMouse)
{
	int iReturn=0;

	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

	_pBackground->Render();
	
	_pParticleManager->Render(ulTimer);

	if (_pButtonStart->Render(pMouse)==ON_LEFT) iReturn = 1 ;
	if (_pButtonQuit->Render(pMouse)==ON_LEFT) iReturn = 2;

	if ((ulTimer - _ulTimerStart)<5000)	// black fade out
	{
		_pBlack->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart)/5000));
		_pBlack->Render();
	}
	

	return iReturn;
}



//end
