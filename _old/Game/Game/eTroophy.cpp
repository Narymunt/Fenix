#include "eTroophy.h"

#pragma warning(disable : 4996)	// sprintf unsafe
#pragma warning(disable : 4244) // konwersja int do float

eTroophy::eTroophy()
{
	m_pBackground = NULL;
	m_ulTimerStart =0;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
	m_bMouseLock = true;

	for (int i=0; i<21;i++)
	{
		m_pTroophyLocked[i] = NULL;
		m_pTroophyUnlocked[i] = NULL;
	}

	_pFont = NULL;
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

	m_bMouseLock = true;	// blokada myszki, zeby nie przenosic klikniecia z poprzedniej planszy na obecna

	for (int i=0; i<21; i++)
	{
		sprintf(cName,"GFX_ARCH%.2dL",i);
		m_pTroophyLocked[i] = new CSprite(pScreen,cName);

		sprintf(cName,"GFX_ARCH%.2dU",i);
		m_pTroophyUnlocked[i] = new CSprite(pScreen,cName);
	}

	pProfile = new CProfile("Game.cfg");
	pProfile->bLoad();
	
	for (int i=0; i<21; i++)
		m_bTroophyLocked[i] = (bool)pProfile->ucTroophy(i);

	delete pProfile;

	_pFont = new CSpriteFont(pScreen);

	_pScreen = pScreen;

	if (pScreen->iSizeY() == 768)
	{
		_iFontX = 64;
		_iFontY = 700;
		_fFontScale = 0.1f;
	}

	_isActive = true;	// dane wczytane

}


void eTroophy::Close(void)
{
	SafeDelete(m_pBackground);

	for (int i=0; i<21; i++)
	{
		SafeDelete(m_pTroophyLocked[i]);
		SafeDelete(m_pTroophyUnlocked[i]);
	}

	SafeDelete(_pFont);

	_isActive = false;
}


int eTroophy::Render(unsigned long ulTimer, CMouse *pMouse)
{
	float fStepX, fStepY;
	float fSizeX, fSizeY;

	if (_pScreen->iSizeX()<1500)
	{
		fStepX = (_pScreen->iSizeX()-640)/6;
		fStepY = (_pScreen->iSizeY()-512)/5;
		fSizeX = 128;
		fSizeY = 128;
	}
	else
	{
		fStepX = (_pScreen->iSizeX()-1280)/6;
		fStepY = (_pScreen->iSizeY()-1024)/5;
		fSizeX = 256;
		fSizeY = 256;
	}

	if (!pMouse->isLeft())
		m_bMouseLock = false;

	m_pBackground->Render();

	for (int i=0; i<4; i++)
	{
		for (int j=0; j<5; j++)
		{
			if ( (pMouse->fMouseX()>(fStepX+(j*fStepX)+(j*fSizeX))) && (pMouse->fMouseX()<(fStepX+(j*fStepX)+fSizeX+(j*fSizeX))) &&
				 (pMouse->fMouseY()>((i*fStepY)+(i*fSizeY))) && (pMouse->fMouseY()<((i*fStepY)+fSizeY+(i*fSizeY))) )
			{
				if (!m_bTroophyLocked[(i*5)+j])
				{
					m_pTroophyLocked[0]->Position((fSizeX/2)+fStepX+(j*fStepX)+(j*fSizeX),(fSizeY/2)+(i*fStepY)+(i*fSizeY));
					m_pTroophyLocked[0]->fRotation(ulTimer*0.01f);
					m_pTroophyLocked[0]->RenderC();
					m_pTroophyLocked[0]->fRotation(ulTimer*-0.01f);
					m_pTroophyLocked[0]->RenderC();
				}
				else
				{
					m_pTroophyUnlocked[0]->Position((fSizeX/2)+fStepX+(j*fStepX)+(j*fSizeX),(fSizeY/2)+(i*fStepY)+(i*fSizeY));
					m_pTroophyUnlocked[0]->fRotation(ulTimer*0.01f);
					m_pTroophyUnlocked[0]->RenderC();
					m_pTroophyUnlocked[0]->fRotation(ulTimer*-0.01f);
					m_pTroophyUnlocked[0]->RenderC();
				}

				if ((i*5)+j==0)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x100 COMBO");

				if ((i * 5) + j == 1)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x1000 BIG COMBO");

				if ((i * 5) + j == 2)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x100 DIAMONDS COMBO");

				if ((i * 5) + j == 3)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x1000 DIAMONDS COMBO");

				if ((i * 5) + j == 4)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x100 RAINBOW COMBO");

				if ((i * 5) + j == 5)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x1000 RAINBOW COMBO");

				if ((i * 5) + j == 6)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x100 BOMBER COMBO");

				if ((i * 5) + j == 7)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "x1000 BOMBER COMBO");

				if ((i * 5) + j == 8)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "GET 1ST IN HIGHSCORE");

				if ((i * 5) + j == 9)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "DOUBLE RAINBOW COMBO");

				if ((i * 5) + j == 10)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "GET 10K POINTS");

				if ((i * 5) + j == 11)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "GET 100K POINTS");

				if ((i * 5) + j == 12)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "PLAY THE GAME x100");

				if ((i * 5) + j == 13)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "PLAY THE GAME x1000");

				if ((i * 5) + j == 14)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "get all highscore");

				if ((i * 5) + j == 15)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "get 5 diamonds on board");

				if ((i * 5) + j == 16)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "get 5 rainbows on board");

				if ((i * 5) + j == 17)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "8 gems in vertical line");

				if ((i * 5) + j == 18)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "8 gems in line");

				if ((i * 5) + j == 19)
					_pFont->Print(_iFontX, _iFontY, 1, _fFontScale, _fFontScale, "atlantis island");

			}

			if (!m_bTroophyLocked[(i*5)+j])
			{
				m_pTroophyLocked[(i*5)+j+1]->Position(fStepX+(j*fStepX)+(j*fSizeX),(i*fStepY)+(i*fSizeY));
				m_pTroophyLocked[(i*5)+j+1]->Render();
			}
			else
			{
				m_pTroophyUnlocked[(i*5)+j+1]->Position(fStepX+(j*fStepX)+(j*fSizeX),(i*fStepY)+(i*fSizeY));
				m_pTroophyUnlocked[(i*5)+j+1]->Render();
			}	
		}
	}

	if (pMouse->isLeft() && !m_bMouseLock)		
		return 1;

	return 0;
}

//end
