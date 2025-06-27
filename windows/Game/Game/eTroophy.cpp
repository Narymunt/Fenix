#include "eTroophy.h"

#pragma warning(disable : 4996)	// sprintf unsafe
#pragma warning(disable : 4244) // konwersja int do float

eTroophy::eTroophy()
{
	m_pBackground = NULL;
	m_ulTimerStart =0;
	m_pExitButton = NULL;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
	m_bMouseLock = true;

	for (int i=0; i<21;i++)
	{
		m_pTroophyLocked[i] = NULL;
		m_pTroophyUnlocked[i] = NULL;
	}

}


eTroophy::~eTroophy()
{
	Close();
}


void eTroophy::Open(CScreen *pScreen)
{	
	char cName[100];
	CProfile *pProfile;

	memset(cName,0,100);	// wyzeruj tablice na wszelki wypadek

	m_pBackground = new CSprite(pScreen,"TROOPHY_SCREEN");

	m_pExitButton = new CButton("data/x1.png","data/x2.png","data/x3.png");
	m_pExitButton->SetPosition(128,64-32);
	m_pExitButton->SetHotCoords(128,32,128+128,32+128);

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna

	for (int i=0; i<21; i++)
	{
		sprintf(cName,"data/a%.2d_l.png",i);
		m_pTroophyLocked[i] = new CSprite(cName);

		sprintf(cName,"data/a%.2d_u.png",i);
		m_pTroophyUnlocked[i] = new CSprite(cName);
	}

	pProfile = new CProfile("Game.cfg");
	pProfile->bLoad();
	
	for (int i=0; i<21; i++)
		m_bTroophyLocked[i] = (bool)pProfile->ucTroophy(i);

	delete pProfile;

	_isActive = true;	// dane wczytane

}


void eTroophy::Close(void)
{
	SafeDelete(m_pBackground);
	SafeDelete(m_pExitButton);

	for (int i=0; i<21; i++)
	{
		SafeDelete(m_pTroophyLocked[i]);
		SafeDelete(m_pTroophyUnlocked[i]);
	}

	_isActive = false;
}


int eTroophy::Render(unsigned long ulTimer, CMouse *pMouse)
{
	if (!pMouse->isLeft())
		m_bMouseLock = false;

	m_pBackground->Render();

	for (int i=0; i<4; i++)
	{
		for (int j=0; j<5; j++)
		{
			if ( (pMouse->fMouseX()>(64+(j*192))) && (pMouse->fMouseX()<(128+64+(j*192))) &&
				 (pMouse->fMouseY()>(128+(i*128))) && (pMouse->fMouseY()<(128+128+(i*128))) )
			{
				if (m_bTroophyLocked[(i*5)+j])
				{
					m_pTroophyLocked[0]->Position(64+(j*192),128+(i*128));
					m_pTroophyLocked[0]->Render();
				}
				else
				{
					m_pTroophyUnlocked[0]->Position(64+(j*192),128+(i*128));
					m_pTroophyUnlocked[0]->Render();
				}
			}

			if (!m_bTroophyLocked[(i*5)+j])
			{
				m_pTroophyLocked[(i*5)+j+1]->Position(64+(j*192),128+(i*128));
				m_pTroophyLocked[(i*5)+j+1]->Render();
			}
			else
			{
				m_pTroophyUnlocked[(i*5)+j+1]->Position(64+(j*192),128+(i*128));
				m_pTroophyUnlocked[(i*5)+j+1]->Render();
			}

		}
	}

	if (m_pExitButton->Render(pMouse)==ON_LEFT && !m_bMouseLock)		
		return 1;

	return 0;
}


//end
