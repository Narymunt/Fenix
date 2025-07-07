#include "eLanguage.h"


eLanguage::eLanguage()
{
	m_pBackground = NULL;

	m_ulTimerStart =0;

	for (int i=0; i<19; i++)
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

	m_pFlag[0] = new CButton("data/l_en.png","data/l_en.png","data/l_en.png");
	m_pFlag[0]->SetPosition(64,64-32);
	m_pFlag[0]->SetHotCoords(64,32,64+128,32+128);

	m_pFlag[1] = new CButton("data/l_ru.png","data/l_ru.png","data/l_ru.png");
	m_pFlag[1]->SetPosition(256,64-32);
	m_pFlag[1]->SetHotCoords(256,64-32,256+128,64-32+128);

	m_pFlag[2] = new CButton("data/l_de.png","data/l_de.png","data/l_de.png");
	m_pFlag[2]->SetPosition(448,64-32);
	m_pFlag[2]->SetHotCoords(448,64-32,448+128,64-32+128);

	m_pFlag[3] = new CButton("data/l_fr.png","data/l_fr.png","data/l_fr.png");
	m_pFlag[3]->SetPosition(640,64-32);
	m_pFlag[3]->SetHotCoords(640,64-32,640+128,64-32+128);

	m_pFlag[16] = new CButton("data/l_po.png","data/l_po.png","data/l_po.png");
	m_pFlag[16]->SetPosition(832,64-32);
	m_pFlag[16]->SetHotCoords(832,64-32,832+128,64-32+128);


	//=== druga linia

	m_pFlag[4] = new CButton("data/l_it.png","data/l_it.png","data/l_it.png");
	m_pFlag[4]->SetPosition(64,256-32);
	m_pFlag[4]->SetHotCoords(64,256-32,64+128,256-32+128);

	m_pFlag[5] = new CButton("data/l_es.png","data/l_es.png","data/l_es.png");
	m_pFlag[5]->SetPosition(256,256-32);
	m_pFlag[5]->SetHotCoords(256,256-32,256+128,256-32+128);

	m_pFlag[6] = new CButton("data/l_pl.png","data/l_pl.png","data/l_pl.png");
	m_pFlag[6]->SetPosition(448,256-32);
	m_pFlag[6]->SetHotCoords(448,256-32,448+128,256-32+128);

	m_pFlag[7] = new CButton("data/l_tu.png","data/l_tu.png","data/l_tu.png");
	m_pFlag[7]->SetPosition(640,256-32);
	m_pFlag[7]->SetHotCoords(640,256-32,640+128,256-32+128);

	m_pFlag[17] = new CButton("data/l_se.png","data/l_se.png","data/l_se.png");
	m_pFlag[17]->SetPosition(832,256-32);
	m_pFlag[17]->SetHotCoords(832,256-32,832+128,256-32+128);

	//=== trzecia linia

	m_pFlag[8] = new CButton("data/l_jp.png","data/l_jp.png","data/l_jp.png");
	m_pFlag[8]->SetPosition(64,448-32);
	m_pFlag[8]->SetHotCoords(64,448-32,64+128,448-32+128);

	m_pFlag[9] = new CButton("data/l_ko.png","data/l_ko.png","data/l_ko.png");
	m_pFlag[9]->SetPosition(256,448-32);
	m_pFlag[9]->SetHotCoords(256,448-32,256+128,448-32+128);

	m_pFlag[10] = new CButton("data/l_ch.png","data/l_ch.png","data/l_ch.png");
	m_pFlag[10]->SetPosition(448,448-32);
	m_pFlag[10]->SetHotCoords(448,448-32,448+128,448-32+128);

	m_pFlag[11] = new CButton("data/l_in.png","data/l_in.png","data/l_in.png");
	m_pFlag[11]->SetPosition(640,448-32);
	m_pFlag[11]->SetHotCoords(640,448-32,640+128,448-32+128);

	m_pFlag[18] = new CButton("data/l_no.png","data/l_no.png","data/l_no.png");
	m_pFlag[18]->SetPosition(832,448-32);
	m_pFlag[18]->SetHotCoords(832,448-32,832+128,448-32+128);

	//=== czwarta linia

	m_pFlag[12] = new CButton("data/l_ar.png","data/l_ar.png","data/l_ar.png");
	m_pFlag[12]->SetPosition(64,640-32);
	m_pFlag[12]->SetHotCoords(64,640-32,64+128,640-32+128);

	m_pFlag[13] = new CButton("data/l_is.png","data/l_is.png","data/l_is.png");
	m_pFlag[13]->SetPosition(256,640-32);
	m_pFlag[13]->SetHotCoords(256,640-32,256+128,640-32+128);

	m_pFlag[14] = new CButton("data/l_br.png","data/l_br.png","data/l_br.png");
	m_pFlag[14]->SetPosition(448,640-32);
	m_pFlag[14]->SetHotCoords(448,640-32,448+128,640-32+128);

	m_pFlag[15] = new CButton("data/l_id.png","data/l_id.png","data/l_id.png");
	m_pFlag[15]->SetPosition(640,640-32);
	m_pFlag[15]->SetHotCoords(640,640-32,640+128,640-32+128);

	m_pFlag[19] = new CButton("data/l_dk.png","data/l_dk.png","data/l_dk.png");
	m_pFlag[19]->SetPosition(832,640-32);
	m_pFlag[19]->SetHotCoords(832,640-32,832+128,640-32+128);
	
	m_ucLanguage = 0;
	m_bMouseLock = true;


	_isActive = true;
}


void eLanguage::Close(void)
{
	SafeDelete(m_pBackground);

	for (int i=0; i<19; i++)
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

	if (m_pFlag[0]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_ENGLAND;
	if (m_pFlag[1]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_RUSSIA;
	if (m_pFlag[2]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_GERMANY;
	if (m_pFlag[3]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_FRANCE;
	if (m_pFlag[16]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_PORTUGAL;

	if (m_pFlag[4]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_ITALY;
	if (m_pFlag[5]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_SPAIN;
	if (m_pFlag[6]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_POLAND;
	if (m_pFlag[7]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_TURKEY;
	if (m_pFlag[17]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_SWEDEN;

	if (m_pFlag[8]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_JAPAN;
	if (m_pFlag[9]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_KOREA;
	if (m_pFlag[10]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_CHINA;
	if (m_pFlag[11]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_INDIA;
	if (m_pFlag[18]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_NORWAY;

	if (m_pFlag[12]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_ARABIA;
	if (m_pFlag[13]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_ISRAEL;
	if (m_pFlag[14]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_BRASIL;
	if (m_pFlag[15]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_INDONESIA;
	if (m_pFlag[19]->Render(pMouse)==ON_LEFT) m_ucLanguage = LANG_DENMARK;

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
