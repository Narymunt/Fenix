#include "Popup.h"
#include "GameSettings.h"

CPopup::CPopup()
{
	_pWhiteFlash = NULL;
	_pBlackFlash = NULL;

	Stop();	// set false to all popups

	_pStart = NULL;

	_pGood1 = NULL;
	_pGood2 = NULL;
	_pGood3 = NULL;
	_pGood4 = NULL;
	_pGood5 = NULL;

	_isActive = false;
}

CPopup::~CPopup()
{
	Close();
}

void CPopup::Open(CScreen *pScreen)
{
	CGameSettings *pSetup;
	unsigned char ucLang;

	pSetup = new CGameSettings();
	pSetup->bLoad();

	ucLang = pSetup->cSelectedLanguage();

	delete pSetup;
    
	_pWhiteFlash = new CSprite((char*)"white100",pScreen->iOS());
	_pBlackFlash = new CSprite((char*)"black100",pScreen->iOS());

    if (pScreen->iOS()!=IPAD_HD)
    {
        switch (ucLang)
        {
            case (LANG_ARABIA):
                _pStart = new CSprite((char*)"ar_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"ar_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"ar_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"ar_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"ar_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"ar_popup_super_1024.png");
                break;

            case (LANG_BRASIL):
                _pStart = new CSprite((char*)"br_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"br_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"br_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"br_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"br_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"br_popup_super_1024.png");
                break;

            case (LANG_CHINA):
                _pStart = new CSprite((char*)"ch_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"ch_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"ch_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"ch_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"ch_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"ch_popup_super_1024.png");
                break;

            case (LANG_GERMANY):
                _pStart = new CSprite((char*)"de_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"de_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"de_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"de_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"de_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"de_popup_super_1024.png");
                break;

            case (LANG_DENMARK):
                _pStart = new CSprite((char*)"dk_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"dk_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"dk_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"dk_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"dk_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"dk_popup_super_1024.png");
                break;

            case (LANG_ENGLAND):
                _pStart = new CSprite((char*)"en_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"en_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"en_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"en_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"en_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"en_popup_super_1024.png");
                break;
		
            case (LANG_SPAIN):
                _pStart = new CSprite((char*)"es_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"es_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"es_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"es_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"es_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"es_popup_super_1024.png");
                break;

            case (LANG_FRANCE):
                _pStart = new CSprite((char*)"fr_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"fr_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"fr_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"fr_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"fr_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"fr_popup_super_1024.png");
                break;

            case (LANG_INDONESIA):
                _pStart = new CSprite((char*)"id_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"id_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"id_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"id_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"id_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"id_popup_super_1024.png");
                break;

            case (LANG_INDIA):
                _pStart = new CSprite((char*)"in_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"in_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"in_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"in_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"in_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"in_popup_super_1024.png");
                break;

            case (LANG_ISRAEL):
                _pStart = new CSprite((char*)"is_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"is_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"is_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"is_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"is_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"is_popup_super_1024.png");
                break;

            case (LANG_ITALY):
                _pStart = new CSprite((char*)"it_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"it_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"it_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"it_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"it_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"it_popup_super_1024.png");
                break;

            case (LANG_JAPAN):
                _pStart = new CSprite((char*)"jp_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"jp_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"jp_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"jp_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"jp_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"jp_popup_super_1024.png");
                break;

            case (LANG_KOREA):
                _pStart = new CSprite((char*)"ko_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"ko_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"ko_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"ko_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"ko_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"ko_popup_super_1024.png");
                break;

            case (LANG_NORWAY):
                _pStart = new CSprite((char*)"no_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"no_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"no_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"no_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"no_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"no_popup_super_1024.png");
                break;

            case (LANG_POLAND):
                _pStart = new CSprite((char*)"pl_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"pl_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"pl_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"pl_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"pl_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"pl_popup_super_1024.png");
                break;

            case (LANG_PORTUGAL):
                _pStart = new CSprite((char*)"po_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"po_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"po_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"po_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"po_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"po_popup_super_1024.png");
                break;

            case (LANG_RUSSIA):
                _pStart = new CSprite((char*)"ru_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"ru_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"ru_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"ru_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"ru_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"ru_popup_super_1024.png");
                break;

            case (LANG_SWEDEN):
                _pStart = new CSprite((char*)"se_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"se_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"se_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"se_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"se_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"se_popup_super_1024.png");
                break;

            case (LANG_TURKEY):
                _pStart = new CSprite((char*)"tu_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"tu_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"tu_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"tu_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"tu_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"tu_popup_super_1024.png");
                break;

            default:
                _pStart = new CSprite((char*)"en_popup_start_1024.png");
                _pGood1 = new CSprite((char*)"en_popup_excelent_1024.png");
                _pGood2 = new CSprite((char*)"en_popup_good_1024.png");
                _pGood3 = new CSprite((char*)"en_popup_outstanding_1024.png");
                _pGood4 = new CSprite((char*)"en_popup_perfect_1024.png");
                _pGood5 = new CSprite((char*)"en_popup_super_1024.png");
                break;
        }
    }
    else
    {
        switch (ucLang)
        {
            case (LANG_ARABIA):
                _pStart = new CSprite((char*)"ar_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"ar_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"ar_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"ar_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"ar_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"ar_popup_super",pScreen->iOS());
                break;
                
            case (LANG_BRASIL):
                _pStart = new CSprite((char*)"br_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"br_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"br_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"br_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"br_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"br_popup_super",pScreen->iOS());
                break;
                
            case (LANG_CHINA):
                _pStart = new CSprite((char*)"ch_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"ch_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"ch_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"ch_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"ch_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"ch_popup_super",pScreen->iOS());
                break;
                
            case (LANG_GERMANY):
                _pStart = new CSprite((char*)"de_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"de_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"de_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"de_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"de_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"de_popup_super",pScreen->iOS());
                break;
                
            case (LANG_DENMARK):
                _pStart = new CSprite((char*)"dk_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"dk_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"dk_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"dk_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"dk_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"dk_popup_super",pScreen->iOS());
                break;
                
            case (LANG_ENGLAND):
                _pStart = new CSprite((char*)"en_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"en_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"en_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"en_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"en_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"en_popup_super",pScreen->iOS());
                break;
                
            case (LANG_SPAIN):
                _pStart = new CSprite((char*)"es_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"es_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"es_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"es_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"es_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"es_popup_super",pScreen->iOS());
                break;
                
            case (LANG_FRANCE):
                _pStart = new CSprite((char*)"fr_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"fr_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"fr_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"fr_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"fr_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"fr_popup_super",pScreen->iOS());
                break;
                
            case (LANG_INDONESIA):
                _pStart = new CSprite((char*)"id_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"id_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"id_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"id_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"id_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"id_popup_super",pScreen->iOS());
                break;
                
            case (LANG_INDIA):
                _pStart = new CSprite((char*)"in_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"in_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"in_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"in_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"in_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"in_popup_super",pScreen->iOS());
                break;
                
            case (LANG_ISRAEL):
                _pStart = new CSprite((char*)"is_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"is_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"is_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"is_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"is_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"is_popup_super",pScreen->iOS());
                break;
                
            case (LANG_ITALY):
                _pStart = new CSprite((char*)"it_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"it_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"it_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"it_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"it_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"it_popup_super",pScreen->iOS());
                break;
                
            case (LANG_JAPAN):
                _pStart = new CSprite((char*)"jp_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"jp_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"jp_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"jp_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"jp_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"jp_popup_super",pScreen->iOS());
                break;
                
            case (LANG_KOREA):
                _pStart = new CSprite((char*)"ko_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"ko_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"ko_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"ko_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"ko_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"ko_popup_super",pScreen->iOS());
                break;
                
            case (LANG_NORWAY):
                _pStart = new CSprite((char*)"no_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"no_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"no_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"no_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"no_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"no_popup_super",pScreen->iOS());
                break;
                
            case (LANG_POLAND):
                _pStart = new CSprite((char*)"pl_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"pl_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"pl_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"pl_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"pl_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"pl_popup_super",pScreen->iOS());
                break;
                
            case (LANG_PORTUGAL):
                _pStart = new CSprite((char*)"po_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"po_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"po_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"po_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"po_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"po_popup_super",pScreen->iOS());
                break;
                
            case (LANG_RUSSIA):
                _pStart = new CSprite((char*)"ru_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"ru_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"ru_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"ru_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"ru_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"ru_popup_super",pScreen->iOS());
                break;
                
            case (LANG_SWEDEN):
                _pStart = new CSprite((char*)"se_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"se_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"se_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"se_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"se_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"se_popup_super",pScreen->iOS());
                break;
                
            case (LANG_TURKEY):
                _pStart = new CSprite((char*)"tu_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"tu_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"tu_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"tu_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"tu_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"tu_popup_super",pScreen->iOS());
                break;

            default:
                _pStart = new CSprite((char*)"en_popup_start",pScreen->iOS());
                _pGood1 = new CSprite((char*)"en_popup_excelent",pScreen->iOS());
                _pGood2 = new CSprite((char*)"en_popup_good",pScreen->iOS());
                _pGood3 = new CSprite((char*)"en_popup_outstanding",pScreen->iOS());
                _pGood4 = new CSprite((char*)"en_popup_perfect",pScreen->iOS());
                _pGood5 = new CSprite((char*)"en_popup_super",pScreen->iOS());
                break;
                
        }
        
    }
    
    
    if (pScreen->iOS()==IPHONE4)
    {
        _pStart->SetPosition(-32,-64);
        _pGood1->SetPosition(-32,-64);
        _pGood2->SetPosition(-32,-64);
        _pGood3->SetPosition(-32,-64);
        _pGood4->SetPosition(-32,-64);
        _pGood5->SetPosition(-32,-64);
    }
    else if (pScreen->iOS()==IPHONE5)
    {
        _pStart->SetPosition(56,-64);
        _pGood1->SetPosition(56,-64);
        _pGood2->SetPosition(56,-64);
        _pGood3->SetPosition(56,-64);
        _pGood4->SetPosition(56,-64);
        _pGood5->SetPosition(56,-64);
    }
    
    _pScreen = pScreen;
	_isActive = true;
}

void CPopup::Close(void)
{
	SafeDelete(_pWhiteFlash);
	SafeDelete(_pBlackFlash);

	SafeDelete(_pStart);

	SafeDelete(_pGood1);
	SafeDelete(_pGood2);
	SafeDelete(_pGood3);
	SafeDelete(_pGood4);
	SafeDelete(_pGood5);

	_isActive = false;
}

void CPopup::Add(int iPopupType, unsigned long ulTimer)
{
	int iIndex;

	iIndex = -1;	// look for available spot 

	for (int i=0; i<64; i++)	
	{
		if (_bPopupActive[i]==false && iIndex==-1)
			iIndex = i;
	}

	if (iIndex!=-1)
	{
		_bPopupActive[iIndex] = true;
		_ulTimerStart[iIndex] = ulTimer;
		_iType[iIndex] = iPopupType;
	}

}

void CPopup::Render(unsigned long ulTimer)
{
	for (int i=0; i<64; i++)
	{
		if (_bPopupActive[i])
		{
			switch(_iType[i])
			{
				case POPUP_FLASH_BLACK:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pBlackFlash->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pBlackFlash->Render();
					}
					else
					{					
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_FLASH_WHITE:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pWhiteFlash->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pWhiteFlash->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_FADE_BLACK:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pBlackFlash->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pBlackFlash->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}

				break;

				case POPUP_FADE_WHITE:
					if (ulTimer - _ulTimerStart[i] < 500)
					{
						_pWhiteFlash->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/500));
						_pWhiteFlash->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_START:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pStart->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
//						_pStart->SetScale(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pStart->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD1:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood1->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
//						_pGood1->SetScale(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
//                        _pGood1->SetPosition(_pScreen->iSizeX()/2 - _pGood1->fSizeX()/2,_pScreen->iSizeY()/2 - _pGood1->fSizeY()/2);
//                        _pGood1->SetPosition(_pScreen->iSizeX()/2, _pScreen->iSizeY()/2);
						_pGood1->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD2:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood2->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
//						_pGood2->SetScale(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
//                        _pGood2->SetPosition(_pScreen->iSizeX()/2 - _pGood2->fSizeX()/2,_pScreen->iSizeY()/2 - _pGood2->fSizeY()/2);
//                        _pGood2->SetPosition(_pScreen->iSizeX()/2, _pScreen->iSizeY()/2);
						_pGood2->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD3:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood3->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
//						_pGood3->SetScale(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
//                        _pGood3->SetPosition(_pScreen->iSizeX()/2 - _pGood3->fSizeX()/2,_pScreen->iSizeY()/2 - _pGood3->fSizeY()/2);
//                        _pGood3->SetPosition(_pScreen->iSizeX()/2, _pScreen->iSizeY()/2);
						_pGood3->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD4:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood4->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
//						_pGood4->SetScale(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
//                        _pGood4->SetPosition(_pScreen->iSizeX()/2 - _pGood4->fSizeX()/2,_pScreen->iSizeY()/2 - _pGood4->fSizeY()/2);
//                        _pGood4->SetPosition(_pScreen->iSizeX()/2, _pScreen->iSizeY()/2);
						_pGood4->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD5:
					if (ulTimer - _ulTimerStart[i] < 200)
					{
						_pGood5->fAlfa(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
//						_pGood5->SetScale(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
//                        _pGood5->SetPosition(_pScreen->iSizeX()/2 - _pGood5->fSizeX()/2,_pScreen->iSizeY()/2 - _pGood5->fSizeY()/2);
//                        _pGood5->SetPosition(_pScreen->iSizeX()/2, _pScreen->iSizeY()/2);
						_pGood5->Render();
					}
					else
					{
						_bPopupActive[i] = false;
					}
				break;
			}
		}
	}
}

bool CPopup::isActive(int i)
{
	return _bPopupActive[i];
}

void CPopup::isActive(int i, bool b)
{
	_bPopupActive[i] = b;
}

void CPopup::Stop(void)
{
	for (int i = 0; i < 64; i++)
	{
		_bPopupActive[i] = false;
		_iType[i] = 0;
		_ulTimerStart[i] = 0;
	}
}

void CPopup::Start(void)
{
	for (int i=0; i<64; i++)
		_bPopupActive[i] = true;
}

void CPopup::Stop(int i)
{
	_bPopupActive[i] = false;
}

void CPopup::Start(int i)
{
	_bPopupActive[i] = true;
}

