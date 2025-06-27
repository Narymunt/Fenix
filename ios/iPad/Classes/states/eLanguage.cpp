// main class

#include "eLanguage.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eLanguage::eLanguage(int iOS) :
_iOS(iOS), _pBackground(0), _ulTimerStart(0)
{
    isActive(false);
    
    for (int i=0; i<20; i++)
		_pFlag[i] = NULL;
}

eLanguage::~eLanguage()
{
    Close();
    isActive(false);
}

void eLanguage::Open(void)
{
	float fStepX, fStepY;
	float fSizeX, fSizeY;

    int iSizeX, iSizeY;
    
    _pBackground = new CSprite((char*)"e_lang",_iOS);

    switch (_iOS)
    {
        case IPHONE4:
            iSizeX = 960; iSizeY = 640;
        break;
            
        case IPHONE5:
            iSizeX = 1136; iSizeY = 640;
        break;
            
        case IPAD:
            iSizeX = 1024; iSizeY = 768;
        break;
            
        case IPAD_HD:
            iSizeX = 2048; iSizeY = 1536;
        break;
    }
    
	fStepX = (iSizeX-640)/6;
	fStepY = (iSizeY-512)/5;
	fSizeX = 128;
	fSizeY = 128;
    
    _pFlag[0] = new CButton((char*)"l_en_click128.png",(char*)"l_en_over128.png",(char*)"l_en128.png",0,0,128,128);
    _pFlag[0]->SetPosition(fStepX,fStepY);
    _pFlag[0]->SetHotCoords(fStepX,fStepY,fStepX+fSizeX,fStepY+fSizeY);

    _pFlag[1] = new CButton((char*)"l_ru_click128.png",(char*)"l_ru_over128.png",(char*)"l_ru128.png",0,0,128,128);
	_pFlag[1]->SetPosition(fStepX*2 + fSizeX, fStepY);
	_pFlag[1]->SetHotCoords(fStepX*2 + fSizeX, fStepY, fStepX*2 + fSizeX*2, fStepY+fSizeY);
	
    _pFlag[2] = new CButton((char*)"l_de_click128.png",(char*)"l_de_over128.png",(char*)"l_de128.png",0,0,128,128);
	_pFlag[2]->SetPosition(fStepX*3 + fSizeX*2, fStepY);
	_pFlag[2]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY, fStepX*3 + fSizeX*3, fStepY+fSizeY);
	
    _pFlag[3] = new CButton((char*)"l_fr_click128.png",(char*)"l_fr_over128.png",(char*)"l_fr128.png",0,0,128,128);
	_pFlag[3]->SetPosition(fStepX*4 + fSizeX*3, fStepY);
	_pFlag[3]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY, fStepX*4 + fSizeX*4, fStepY+fSizeY);

    _pFlag[16] = new CButton((char*)"l_po_click128.png",(char*)"l_po_over128.png",(char*)"l_po128.png",0,0,128,128);
	_pFlag[16]->SetPosition(fStepX*5 + fSizeX*4, fStepY);
	_pFlag[16]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY, fStepX*5 + fSizeX*5, fStepY+fSizeY);
    
	//=== druga linia

    _pFlag[4] = new CButton((char*)"l_it_click128.png",(char*)"l_it_over128.png",(char*)"l_it128.png",0,0,128,128);
	_pFlag[4]->SetPosition(fStepX,fStepY*2+fSizeY);
	_pFlag[4]->SetHotCoords(fStepX,fStepY*2+fSizeY,fStepX+fSizeX,fStepY*2+fSizeY*2);
	
    _pFlag[5] = new CButton((char*)"l_es_click128.png",(char*)"l_es_over128.png",(char*)"l_es128.png",0,0,128,128);
	_pFlag[5]->SetPosition(fStepX*2 + fSizeX, fStepY*2+fSizeY);
	_pFlag[5]->SetHotCoords(fStepX*2 + fSizeX, fStepY*2+fSizeY, fStepX*2 + fSizeX*2, fStepY*2+fSizeY*2);
	
    _pFlag[6] = new CButton((char*)"l_pl_click128.png",(char*)"l_pl_over128.png",(char*)"l_pl128.png",0,0,128,128);
	_pFlag[6]->SetPosition(fStepX*3 + fSizeX*2, fStepY*2+fSizeY);
	_pFlag[6]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY*2+fSizeY, fStepX*3 + fSizeX*3, fStepY*2+fSizeY*2);
	
    _pFlag[7] = new CButton((char*)"l_tu_click128.png",(char*)"l_tu_over128.png",(char*)"l_tu128.png",0,0,128,128);
	_pFlag[7]->SetPosition(fStepX*4 + fSizeX*3, fStepY*2+fSizeY);
	_pFlag[7]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY*2+fSizeY, fStepX*4 + fSizeX*4, fStepY*2+fSizeY*2);
	
    _pFlag[17] = new CButton((char*)"l_se_click128.png",(char*)"l_se_over128.png",(char*)"l_se128.png",0,0,128,128);
	_pFlag[17]->SetPosition(fStepX*5 + fSizeX*4, fStepY*2+fSizeY);
	_pFlag[17]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY*2+fSizeY, fStepX*5 + fSizeX*5, fStepY*2+fSizeY*2);
    
	//=== trzecia linia

    _pFlag[8] = new CButton((char*)"l_jp_click128.png",(char*)"l_jp_over128.png",(char*)"l_jp128.png",0,0,128,128);
	_pFlag[8]->SetPosition(fStepX,fStepY*3+fSizeY*2);
	_pFlag[8]->SetHotCoords(fStepX,fStepY*3+fSizeY*2,fStepX+fSizeX,fStepY*3+fSizeY*3);
	
    _pFlag[9] = new CButton((char*)"l_ko_click128.png",(char*)"l_ko_over128.png",(char*)"l_ko128.png",0,0,128,128);
	_pFlag[9]->SetPosition(fStepX*2 + fSizeX, fStepY*3+fSizeY*2);
	_pFlag[9]->SetHotCoords(fStepX*2 + fSizeX, fStepY*3+fSizeY*2, fStepX*2 + fSizeX*2, fStepY*3+fSizeY*3);
	
    _pFlag[10] = new CButton((char*)"l_ch_click128.png",(char*)"l_ch_over128.png",(char*)"l_ch128.png",0,0,128,128);
	_pFlag[10]->SetPosition(fStepX*3 + fSizeX*2, fStepY*3+fSizeY*2);
	_pFlag[10]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY*3+fSizeY*2, fStepX*3 + fSizeX*3, fStepY*3+fSizeY*3);
	
    _pFlag[11] = new CButton((char*)"l_in_click128.png",(char*)"l_in_over128.png",(char*)"l_in128.png",0,0,128,128);
	_pFlag[11]->SetPosition(fStepX*4 + fSizeX*3, fStepY*3+fSizeY*2);
	_pFlag[11]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY*3+fSizeY*2, fStepX*4 + fSizeX*4, fStepY*3+fSizeY*3);
	
    _pFlag[18] = new CButton((char*)"l_no_click128.png",(char*)"l_no_over128.png",(char*)"l_no128.png",0,0,128,128);
	_pFlag[18]->SetPosition(fStepX*5 + fSizeX*4, fStepY*3+fSizeY*2);
	_pFlag[18]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY*3+fSizeY*2, fStepX*5 + fSizeX*5, fStepY*3+fSizeY*3);
    
	//=== czwarta linia

    _pFlag[12] = new CButton((char*)"l_ar_click128.png",(char*)"l_ar_over128.png",(char*)"l_ar128.png",0,0,128,128);
	_pFlag[12]->SetPosition(fStepX,fStepY*4+fSizeY*3);
	_pFlag[12]->SetHotCoords(fStepX,fStepY*4+fSizeY*3,fStepX+fSizeX,fStepY*4+fSizeY*4);
	
    _pFlag[13] = new CButton((char*)"l_is_click128.png",(char*)"l_is_over128.png",(char*)"l_is128.png",0,0,128,128);
	_pFlag[13]->SetPosition(fStepX*2 + fSizeX, fStepY*4+fSizeY*3);
	_pFlag[13]->SetHotCoords(fStepX*2 + fSizeX, fStepY*4+fSizeY*3, fStepX*2 + fSizeX*2, fStepY*4+fSizeY*4);
	
    _pFlag[14] = new CButton((char*)"l_br_click128.png",(char*)"l_br_over128.png",(char*)"l_br128.png",0,0,128,128);
	_pFlag[14]->SetPosition(fStepX*3 + fSizeX*2, fStepY*4+fSizeY*3);
	_pFlag[14]->SetHotCoords(fStepX*3 + fSizeX*2, fStepY*4+fSizeY*3, fStepX*3 + fSizeX*3, fStepY*4+fSizeY*4);
	
    _pFlag[15] = new CButton((char*)"l_id_click128.png",(char*)"l_id_over128.png",(char*)"l_id128.png",0,0,128,128);
	_pFlag[15]->SetPosition(fStepX*4 + fSizeX*3, fStepY*4+fSizeY*3);
	_pFlag[15]->SetHotCoords(fStepX*4 + fSizeX*3, fStepY*4+fSizeY*3, fStepX*4 + fSizeX*4, fStepY*4+fSizeY*4);
	
    _pFlag[19] = new CButton((char*)"l_dk_click128.png",(char*)"l_dk_over128.png",(char*)"l_dk128.png",0,0,128,128);
	_pFlag[19]->SetPosition(fStepX*5 + fSizeX*4, fStepY*4+fSizeY*3);
	_pFlag[19]->SetHotCoords(fStepX*5 + fSizeX*4, fStepY*4+fSizeY*3, fStepX*5 + fSizeX*5, fStepY*4+fSizeY*4);

    _ucLanguage = 0;
    _isMouseLock = true;
    
    isActive(true);
}

void eLanguage::Close(void)
{
	
	CGameSettings *pSetup;
    
	// na wyjscie z tego modulu zapisz wybrany jezyk w pliku
    
	pSetup = new CGameSettings();
	pSetup->bLoad();
    
	pSetup->cSelectedLanguage(_ucLanguage);
    
	pSetup->bSave();
    
	delete pSetup;
    SafeDelete(_pBackground);

    for (int i=0; i<20; i++)
        SafeDelete(_pFlag[i]);
    
    isActive(false);
}

int eLanguage::Render(CTouch *pTouch, unsigned long ulTimer)
{

    if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;
    
	if (!pTouch->isPressed())
		_isMouseLock = false;

    _pBackground->Render();

	if (_pFlag[0]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_ENGLAND;
	if (_pFlag[1]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_RUSSIA;
	if (_pFlag[2]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_GERMANY;
	if (_pFlag[3]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_FRANCE;
	if (_pFlag[16]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_PORTUGAL;
    
	if (_pFlag[4]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_ITALY;
	if (_pFlag[5]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_SPAIN;
	if (_pFlag[6]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_POLAND;
	if (_pFlag[7]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_TURKEY;
	if (_pFlag[17]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_SWEDEN;
    
	if (_pFlag[8]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_JAPAN;
	if (_pFlag[9]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_KOREA;
	if (_pFlag[10]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_CHINA;
	if (_pFlag[11]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_INDIA;
	if (_pFlag[18]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_NORWAY;
    
	if (_pFlag[12]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_ARABIA;
	if (_pFlag[13]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_ISRAEL;
	if (_pFlag[14]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_BRASIL;
	if (_pFlag[15]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_INDONESIA;
	if (_pFlag[19]->Render(pTouch)==ON_LEFT && !_isMouseLock) _ucLanguage = LANG_DENMARK;
    
	if (!_isMouseLock)
		return (int)_ucLanguage;
    
	return 0;
    
    
/*
    if (pTouch->isPressed())
    {
        printf("[TOUCH]: x %d y %d PRESSED\n", pTouch->iGetX(), pTouch->iGetY());
    }
    else
    {
        printf("[TOUCH]: x %d y %d \n", pTouch->iGetX(), pTouch->iGetY());
    }
*/
}

