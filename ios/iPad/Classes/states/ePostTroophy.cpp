#include "ePostTroophy.h"

ePostTroophy::ePostTroophy()
{
	_pBackground = NULL;
	m_ulTimerStart =0;
	_pExitButton = NULL;

	for (int i=0; i<21; i++)
	{
		_pTroophy[i] = NULL;
		_ucNewTroophy[i] = 0;
	}

	// ustaw znacznik, ze dane nie sa jeszcze wczytane

	_bPreInitialized = false;
	m_bMouseLock = true;

	_pTween = new CTween(1.0f, 3.0f, (int)1000);

    _pTroophySFX = new CSound((char*)"troophy.wav");
    
	_isActive = false;

}

ePostTroophy::~ePostTroophy()
{
	Close();
}

void ePostTroophy::Open(CScreen *pScreen)
{	
	char cName[100];

	memset(cName,0,100);

    _pScreen = pScreen;
    _iOS = pScreen->iOS();
    
	_pBackground = new CSprite((char*)"e_posttroophy",pScreen->iOS());

    if (_iOS == IPAD_HD)
    {
        _pExitButton = new CButton((char*)"menu_over256.png",(char*)"menu_click256.png",(char*)"menu_static256.png",0,0,256,256);
        _pExitButton->SetPosition(1024-128,1150);
        _pExitButton->SetHotCoords(1024-128,1150,1024+128,1150+256);
    }
    else if (_iOS == IPAD)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(512-64,580);
        _pExitButton->SetHotCoords(512-64,580,512+64,580+128);
    }
    else if (_iOS == IPHONE4)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(480-64,480);
        _pExitButton->SetHotCoords(480-64,480,480+64,480+128);
    }
    else if (_iOS == IPHONE5)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(568-64,480);
        _pExitButton->SetHotCoords(568-64,480,568+64,480+128);
    }
    
    _pTroophy[0] = new CSprite((char*)"a00_u2.png");
        
    for (int i=1; i<21; i++)
    {
        sprintf(cName,"a%.2d_on_static_256.png",i);
        _pTroophy[i] = new CSprite(cName);
    }

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna

	m_ulTimerStart = 0;

	_bPreInitialized = false;
	_pScreen = pScreen;
	_isActive = true;
}

bool ePostTroophy::reOpen(void)
{
	CProfile *pProfile;
	bool bReturn;

	pProfile = new CProfile();
	pProfile->bLoad();

	bReturn = false;

	// tablica _ucNewTroophy jest ustawiana z zewn¹trz w Game.cpp

	for (int i=0; i<21; i++)
	{
		if (pProfile->ucTroophy(i)!=0)
			_ucNewTroophy[i]=0;

		if (_ucNewTroophy[i]!=0)
			bReturn = true; 
	}

	delete pProfile;

	_bPreInitialized = true;
	
	_iIndex = -1;

	for (int i = 0; i < 21; i++)										// znajdz pierwszy element nie zerowy w tablicy
	{
		if (_ucNewTroophy[i] && _iIndex == -1)
			_iIndex = i;
	}

	return bReturn;		
}


void ePostTroophy::Close(void)
{
	CProfile *pProfile;

	SafeDelete(_pBackground);
	SafeDelete(_pExitButton);

	for (int i=0; i<21; i++)
		SafeDelete(_pTroophy[i]);

	// zapisz zmiany w profilu

	if (_bPreInitialized)
	{

		pProfile = new CProfile();
		pProfile->bLoad();
	
		for (int i=0; i<21; i++)		// zapisujemy zmiany w profilu, na stale odblokowujemy zdobyte osiagniecie
		{
			if (_ucNewTroophy[i]!=0)
			{
				if (pProfile->ucTroophy(i)==0)
					pProfile->ucTroophy(i,1);	// ustawiamy na 1
			}
		}

		pProfile->bSave();
		delete pProfile;
	}

	SafeDelete(_pTween);
    SafeDelete(_pTroophySFX);
    
	_isActive = false;
}


int ePostTroophy::Render(unsigned long ulTimer, CTouch *pTouch)
{
	int iTween;

	if (m_ulTimerStart == 0)
	{
		m_ulTimerStart = ulTimer;
		_pTroophySFX->Play();
	}

	if (!pTouch->isPressed())
		m_bMouseLock = false;
    
	iTween = (ulTimer - m_ulTimerStart) / 2;

	_pTroophy[0]->Position(_pScreen->iSizeX() / 2, _pScreen->iSizeY() / 2);

	_pBackground->Render();

	_pTroophy[0]->fRotation(ulTimer / 9);
	_pTroophy[0]->RenderC();

	_pTroophy[_iIndex+1]->Position(_pScreen->iSizeX()/2,_pScreen->iSizeY()/2);
	_pTroophy[_iIndex+1]->RenderC();

	if (_pExitButton->Render(pTouch) == ON_LEFT && !m_bMouseLock && ((ulTimer-m_ulTimerStart)>1000))				// szukamy nastepnego elementu w nowych trofeach
	{
		int iPrev = _iIndex;
        
        m_bMouseLock = true;
        pTouch->Reset();
        _pExitButton->isPressed(false);
        
		for (int i = iPrev+1; i < 21; i++)										// znajdz pierwszy element nie zerowy w tablicy
		{
			if (_ucNewTroophy[i] && _iIndex == iPrev)
				_iIndex = i;
		}

		if (iPrev == _iIndex)
		{
			return 1;
		}
		else
		{
			m_ulTimerStart = 0;
//			Mix_PlayChannel(-1, _pTroophySFX, 0);
		}
	}
	
	return 0;
}

//=== ustaw znacznik 

void ePostTroophy::ucNewTroophy(int i, char c)
{
	_ucNewTroophy[i] = c;
}

//end
