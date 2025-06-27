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
	_pExitButton->SetPosition(128,64-32);
	_pExitButton->SetHotCoords(128,32,128+128,32+128);

	for (int i=0; i<21; i++)
	{
		sprintf(cName,"GFX_ARCH%.2dU",i);
		_pTroophy[i] = new CSprite(pScreen,cName);
		_ucNewTroophy[i] = 0;
	}

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna

	m_ulTimerStart = 0;

	_bPreInitialized = false;

	_isActive = true;
}

bool ePostTroophy::reOpen(void)
{
	CProfile *pProfile;
	bool bReturn;

	pProfile = new CProfile(USERS_FILE);
	pProfile->bLoad();

	bReturn = false;

	for (int i=0; i<21; i++)
	{
		if (pProfile->ucTroophy(i)!=0)
			_ucNewTroophy[i]=0;

		if (_ucNewTroophy[i]!=0)
			bReturn = true; 
	}

	delete pProfile;

	_bPreInitialized = true;

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

	
	_isActive = false;
}


int ePostTroophy::Render(unsigned long ulTimer, CMouse *pMouse)
{
	if (!pMouse->isLeft())
		m_bMouseLock = false;

	if (m_ulTimerStart==0)
		m_ulTimerStart = ulTimer;

	_pBackground->Render();

	for (int i=0; i<21; i++)
	{
		if (_ucNewTroophy[i]!=0)
		{
			_pTroophy[i]->Position(i*50,400);
			_pTroophy[i]->Render();
		}
	}

	if (_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}

//=== ustaw znacznik 

void ePostTroophy::ucNewTroophy(int i, char c)
{
	_ucNewTroophy[i] = c;
}

//end
