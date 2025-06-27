#include "ePreload.h"

ePreload::ePreload()
{
	m_pBlack = NULL;
	m_pLogoBF = NULL;
	m_pLogoShodan9 = NULL;

	m_ulTimerStart = 0;	// poczatek

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
}


ePreload::~ePreload()
{
	Close();
}


void ePreload::Open(CScreen *pScreen)
{	
	m_pBlack = new CSprite(pScreen,"GFX_BLACK100_SCREEN");
	m_pLogoBF = new CSprite(pScreen,"GFX_ADS1_SCREEN");
	m_pLogoShodan9 = new CSprite(pScreen,"GFX_ADS2_SCREEN");

	_isActive = true;
}


void ePreload::Close(void)
{
	SafeDelete(m_pBlack);
	SafeDelete(m_pLogoBF);
	SafeDelete(m_pLogoShodan9);
	
	_isActive = false;
}


int ePreload::Render(unsigned long ulTimer, CMouse *pMouse)
{
	if (m_ulTimerStart == 0)
		m_ulTimerStart = ulTimer;

	if ((ulTimer - m_ulTimerStart)<500)
		m_pLogoBF->Render();

	if ((ulTimer - m_ulTimerStart)>499)
		m_pLogoShodan9->Render();
	
	if ((ulTimer - m_ulTimerStart)>1200)
		return 1;
/*
	if ((lTimer - m_ulTimerStart)<255)
	{
		m_pBlack->SetModulate(255-(lTimer - m_ulTimerStart),255-(lTimer - m_ulTimerStart),255-(lTimer - m_ulTimerStart),255-(lTimer - m_ulTimerStart));
		m_pBlack->Render();
	}

	if ((lTimer - m_ulTimerStart)>499 && (lTimer - m_ulTimerStart)<754)
	{
		m_pBlack->SetModulate(255-(lTimer - m_ulTimerStart-499),255-(lTimer - m_ulTimerStart-499),255-(lTimer - m_ulTimerStart-499),255-(lTimer - m_ulTimerStart-499));
		m_pBlack->Render();
	}
*/
	return 0;
}


//end
