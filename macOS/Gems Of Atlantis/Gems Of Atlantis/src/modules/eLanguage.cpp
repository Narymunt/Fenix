#include "eLanguage.h"
#include "GameSettings.h"

eLanguage::eLanguage()
{
	m_pBackground = NULL;

	m_ulTimerStart =0;

	for (int i=0; i<20; i++)
		m_pFlag[i] = NULL;

	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	_isActive = false;
	m_ucLanguage = 0;

	m_bMouseLock = true;

}


eLanguage::~eLanguage()
{
	Close();
}


void eLanguage::Open(CScreen *pScreen)
{	
	m_pBackground = new CSprite(pScreen,"GFX_LANG_SCREEN");

	float fStepX, fStepY;
	float fSizeX, fSizeY;

	fStepX = (pScreen->iSizeX()-640)/6;
	fStepY = (pScreen->iSizeY()-512)/5;
	fSizeX = 128;
	fSizeY = 128;

	m_pFlag[0] = new CButton(pScreen, "BUTTON_MENU_ENGLISH");
	m_pFlag[0]->SetPosition(fStepX,fStepY);
	m_pFlag[0]->SetHotCoords(fStepX,fStepY,fStepX+fSizeX,fStepY+fSizeY);
	
	m_pFlag[1] = new CButton(pScreen, "BUTTON_MENU_RUSSIA");
	m_pFlag[1]->SetPosition(fStepX*2 + fSizeX, fStepY);
	m_pFlag[1]->SetHotCoords(fStepX*2 + fSizeX, fStepY, fStepX*2 + fSizeX*2, fStepY+fSizeY);
	
	m_pFlag[2] = new CButton(pScreen, "BUTTON_MENU_GERMAN");
	m_pFlag[2]->SetPosition(fStepX*3 + fSizeX*2, fStepY);
	m_pFlag[2]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY, fStepX*3 + fSizeX*3, fStepY+fSizeY);
	
	m_pFlag[3] = new CButton(pScreen, "BUTTON_MENU_FRENCH");
	m_pFlag[3]->SetPosition(fStepX*4 + fSizeX*3, fStepY);
	m_pFlag[3]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY, fStepX*4 + fSizeX*4, fStepY+fSizeY);
	
	m_pFlag[16] = new CButton(pScreen, "BUTTON_MENU_PORTUGAL");
	m_pFlag[16]->SetPosition(fStepX*5 + fSizeX*4, fStepY);
	m_pFlag[16]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY, fStepX*5 + fSizeX*5, fStepY+fSizeY);

	//=== druga linia

	m_pFlag[4] = new CButton(pScreen, "BUTTON_MENU_ITALY");
	m_pFlag[4]->SetPosition(fStepX,fStepY*2+fSizeY);
	m_pFlag[4]->SetHotCoords(fStepX,fStepY*2+fSizeY,fStepX+fSizeX,fStepY*2+fSizeY*2);
	
	m_pFlag[5] = new CButton(pScreen, "BUTTON_MENU_ESPANA");
	m_pFlag[5]->SetPosition(fStepX*2 + fSizeX, fStepY*2+fSizeY);
	m_pFlag[5]->SetHotCoords(fStepX*2 + fSizeX, fStepY*2+fSizeY, fStepX*2 + fSizeX*2, fStepY*2+fSizeY*2);
	
	m_pFlag[6] = new CButton(pScreen, "BUTTON_MENU_POLAND");
	m_pFlag[6]->SetPosition(fStepX*3 + fSizeX*2, fStepY*2+fSizeY);
	m_pFlag[6]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY*2+fSizeY, fStepX*3 + fSizeX*3, fStepY*2+fSizeY*2);
	
	m_pFlag[7] = new CButton(pScreen, "BUTTON_MENU_TURKEY");
	m_pFlag[7]->SetPosition(fStepX*4 + fSizeX*3, fStepY*2+fSizeY);
	m_pFlag[7]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY*2+fSizeY, fStepX*4 + fSizeX*4, fStepY*2+fSizeY*2);
	
	m_pFlag[17] = new CButton(pScreen, "BUTTON_MENU_SWEDEN");
	m_pFlag[17]->SetPosition(fStepX*5 + fSizeX*4, fStepY*2+fSizeY);
	m_pFlag[17]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY*2+fSizeY, fStepX*5 + fSizeX*5, fStepY*2+fSizeY*2);

	//=== trzecia linia

	m_pFlag[8] = new CButton(pScreen, "BUTTON_MENU_JAPAN");
	m_pFlag[8]->SetPosition(fStepX,fStepY*3+fSizeY*2);
	m_pFlag[8]->SetHotCoords(fStepX,fStepY*3+fSizeY*2,fStepX+fSizeX,fStepY*3+fSizeY*3);
	
	m_pFlag[9] = new CButton(pScreen, "BUTTON_MENU_KOREA");
	m_pFlag[9]->SetPosition(fStepX*2 + fSizeX, fStepY*3+fSizeY*2);
	m_pFlag[9]->SetHotCoords(fStepX*2 + fSizeX, fStepY*3+fSizeY*2, fStepX*2 + fSizeX*2, fStepY*3+fSizeY*3);
	
	m_pFlag[10] = new CButton(pScreen, "BUTTON_MENU_CHINA");
	m_pFlag[10]->SetPosition(fStepX*3 + fSizeX*2, fStepY*3+fSizeY*2);
	m_pFlag[10]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY*3+fSizeY*2, fStepX*3 + fSizeX*3, fStepY*3+fSizeY*3);
	
	m_pFlag[11] = new CButton(pScreen, "BUTTON_MENU_INDIA");
	m_pFlag[11]->SetPosition(fStepX*4 + fSizeX*3, fStepY*3+fSizeY*2);
	m_pFlag[11]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY*3+fSizeY*2, fStepX*4 + fSizeX*4, fStepY*3+fSizeY*3);
	
	m_pFlag[18] = new CButton(pScreen, "BUTTON_MENU_NORWAY");
	m_pFlag[18]->SetPosition(fStepX*5 + fSizeX*4, fStepY*3+fSizeY*2);
	m_pFlag[18]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY*3+fSizeY*2, fStepX*5 + fSizeX*5, fStepY*3+fSizeY*3);

	//=== czwarta linia

	m_pFlag[12] = new CButton(pScreen, "BUTTON_MENU_ARABIC");
	m_pFlag[12]->SetPosition(fStepX,fStepY*4+fSizeY*3);
	m_pFlag[12]->SetHotCoords(fStepX,fStepY*4+fSizeY*3,fStepX+fSizeX,fStepY*4+fSizeY*4);
	
	m_pFlag[13] = new CButton(pScreen, "BUTTON_MENU_ISRAEL");
	m_pFlag[13]->SetPosition(fStepX*2 + fSizeX, fStepY*4+fSizeY*3);
	m_pFlag[13]->SetHotCoords(fStepX*2 + fSizeX, fStepY*4+fSizeY*3, fStepX*2 + fSizeX*2, fStepY*4+fSizeY*4);
	
	m_pFlag[14] = new CButton(pScreen, "BUTTON_MENU_BRAZILIAN");
	m_pFlag[14]->SetPosition(fStepX*3 + fSizeX*2, fStepY*4+fSizeY*3);
	m_pFlag[14]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY*4+fSizeY*3, fStepX*3 + fSizeX*3, fStepY*4+fSizeY*4);
	
	m_pFlag[15] = new CButton(pScreen, "BUTTON_MENU_INDONEZJA");
	m_pFlag[15]->SetPosition(fStepX*4 + fSizeX*3, fStepY*4+fSizeY*3);
	m_pFlag[15]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY*4+fSizeY*3, fStepX*4 + fSizeX*4, fStepY*4+fSizeY*4);	
	
	m_pFlag[19] = new CButton(pScreen, "BUTTON_MENU_DENMARK");
	m_pFlag[19]->SetPosition(fStepX*5 + fSizeX*4, fStepY*4+fSizeY*3);
	m_pFlag[19]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY*4+fSizeY*3, fStepX*5 + fSizeX*5, fStepY*4+fSizeY*4);
	
	m_ucLanguage = 0;
	m_bMouseLock = true;


	_isActive = true;
}


void eLanguage::Close(void)
{	
	CGameSettings *pSetup;

	// na wyjscie z tego modulu zapisz wybrany jezyk w pliku

	pSetup = new CGameSettings();
	pSetup->bLoad();

	pSetup->cSelectedLanguage(m_ucLanguage);

	pSetup->bSave();

	delete pSetup;

	// skasuj zasoby

	SafeDelete(m_pBackground);

	for (int i=0; i<20; i++)
		SafeDelete(m_pFlag[i]);
	
	_isActive = false;
}


int eLanguage::Render(unsigned long ulTimer, CMouse *pMouse)
{
	if (m_ulTimerStart == 0)
		m_ulTimerStart = ulTimer;

	if (!pMouse->isLeft())
		m_bMouseLock = false;

	m_pBackground->Render();		

	if (m_pFlag[0]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_ENGLAND;
	if (m_pFlag[1]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_RUSSIA;
	if (m_pFlag[2]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_GERMANY;
	if (m_pFlag[3]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_FRANCE;
	if (m_pFlag[16]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_PORTUGAL;

	if (m_pFlag[4]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_ITALY;
	if (m_pFlag[5]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_SPAIN;
	if (m_pFlag[6]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_POLAND;
	if (m_pFlag[7]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_TURKEY;
	if (m_pFlag[17]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_SWEDEN;

	if (m_pFlag[8]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_JAPAN;
	if (m_pFlag[9]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_KOREA;
	if (m_pFlag[10]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_CHINA;
	if (m_pFlag[11]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_INDIA;
	if (m_pFlag[18]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_NORWAY;

	if (m_pFlag[12]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_ARABIA;
	if (m_pFlag[13]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_ISRAEL;
	if (m_pFlag[14]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_BRASIL;
	if (m_pFlag[15]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_INDONESIA;
	if (m_pFlag[19]->Render(pMouse)==ON_LEFT && !m_bMouseLock) m_ucLanguage = LANG_DENMARK;

	if (!m_bMouseLock)
		return (int)m_ucLanguage;

	return 0;

}

void eLanguage::ucLanguage(unsigned char ucLang)
{
	m_ucLanguage = ucLang;
}

unsigned char eLanguage::ucLanguage(void)
{
	return m_ucLanguage;
}

//end
