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

	_pTroophySFX = Mix_LoadWAV("data/troophy.ogg");

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

	_pBackground = new CSprite(pScreen,"POSTTROOPHY_SCREEN");

	_pExitButton = new CButton(pScreen,"BUTTON_MENU");
	
	if (pScreen->iSizeX() < 1500)
	{
		_pExitButton->SetPosition((pScreen->iSizeX() / 2) - 64, pScreen->iSizeY() - 150);
		_pExitButton->SetHotCoords((pScreen->iSizeX() / 2) - 64, pScreen->iSizeY() - 150, (pScreen->iSizeX() / 2) + 64, pScreen->iSizeY());
	}
	else
	{
		_pExitButton->SetPosition((pScreen->iSizeX() / 2) - 128, pScreen->iSizeY() - 256 -150);
		_pExitButton->SetHotCoords((pScreen->iSizeX() / 2) - 128, pScreen->iSizeY() - 256 - 150, (pScreen->iSizeX() / 2) -150, pScreen->iSizeY());
	}

	for (int i=0; i<21; i++)
	{
		sprintf(cName,"GFX_ARCH%.2dU",i);
		_pTroophy[i] = new CSprite(pScreen, cName);
		_ucNewTroophy[i] = 0;
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

	pProfile = new CProfile(USERS_FILE);
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

		pProfile = new CProfile(USERS_FILE);
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

	if (_pTroophySFX != NULL)
	{
		Mix_FreeChunk(_pTroophySFX);
		_pTroophySFX = NULL;
	}

	_isActive = false;
}


int ePostTroophy::Render(unsigned long ulTimer, CMouse *pMouse)
{
	float fScale;
	int iTween;

	if (!pMouse->isLeft())
		m_bMouseLock = false;

	if (m_ulTimerStart == 0)
	{
		m_ulTimerStart = ulTimer;
		Mix_PlayChannel(-1, _pTroophySFX, 0);
	}

	iTween = (ulTimer - m_ulTimerStart) / 2;

	_pTroophy[0]->Position(_pScreen->iSizeX() / 2, _pScreen->iSizeY() / 2);

	if (iTween<1000)
	{
		fScale = _pTween->fCirc(iTween * 0.001f);
		_pTroophy[0]->Scale(_pTween->fBounce(iTween*0.001f), _pTween->fBounce(iTween*0.001f));
	}
	else
	{
		fScale = _pTween->fCirc(1.0f);
		_pTroophy[0]->Scale(_pTween->fBounce(1.0f), _pTween->fBounce(1.0f));
	}

	_pBackground->Render();

	_pTroophy[0]->fRotation(ulTimer / 9);
	_pTroophy[0]->RenderC();
	
	_pTroophy[0]->fRotation(m_ulTimerStart - ulTimer / 7);
	_pTroophy[0]->RenderC();

	_pTroophy[_iIndex]->Position(_pScreen->iSizeX()/2,_pScreen->iSizeY()/2);
	_pTroophy[_iIndex]->Scale(fScale, fScale);
	_pTroophy[_iIndex]->RenderC();

	if (_pExitButton->Render(pMouse) == ON_LEFT && !m_bMouseLock)				// szukamy nastepnego elementu w nowych trofeach
	{
		int iPrev = _iIndex;

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
			Mix_PlayChannel(-1, _pTroophySFX, 0);
			m_bMouseLock = true;
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
