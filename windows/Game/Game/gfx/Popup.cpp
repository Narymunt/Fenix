/**
   Popup.cpp

   Tylko do wyskakuj¹cych napisów. 
   Trzyma informacje o texturach, ¿eby nie powielaæ sprite dla ka¿dej cz¹stki z osobna.
   Maksymalnie 64 popupy na ekranie.

   @author Jaros³aw Ro¿yñski
   
*/

#include "Popup.h"
#include "../windows/GameSettings.h"
#include "../Game.h"

/**
   Konstruktor klasy.

*/

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

	_isOpen = false;
}

/**
   Destruktor klasy.

*/

CPopup::~CPopup()
{
	Close();
}

/**
   Wczytuje wszystkie potrzebne grafiki ze skryptu.
   
   @param pScreen wskaznik do ekranu
*/

void CPopup::Open(CScreen *pScreen)
{
	CGameSettings *pSetup;
	unsigned char ucLang;

	pSetup = new CGameSettings();
	pSetup->bLoad();

	ucLang = pSetup->cSelectedLanguage();

	delete pSetup;

	_pWhiteFlash = new CSprite(pScreen,"GFX_WHITE50_SCREEN");
	_pBlackFlash = new CSprite(pScreen,"GFX_BLACK100_SCREEN");

	switch (ucLang)
	{
		case (LANG_ARABIA):
			_pStart = new CSprite(pScreen,"AR_POPUP_START");
			_pGood1 = new CSprite(pScreen,"AR_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"AR_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"AR_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"AR_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"AR_POPUP_SUPER");
		break;

		case (LANG_BRASIL):
			_pStart = new CSprite(pScreen,"BR_POPUP_START");
			_pGood1 = new CSprite(pScreen,"BR_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"BR_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"BR_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"BR_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"BR_POPUP_SUPER");
		break;

		case (LANG_CHINA):
			_pStart = new CSprite(pScreen,"CH_POPUP_START");
			_pGood1 = new CSprite(pScreen,"CH_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"CH_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"CH_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"CH_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"CH_POPUP_SUPER");
		break;

		case (LANG_GERMANY):
			_pStart = new CSprite(pScreen,"DE_POPUP_START");
			_pGood1 = new CSprite(pScreen,"DE_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"DE_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"DE_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"DE_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"DE_POPUP_SUPER");
		break;

		case (LANG_DENMARK):
			_pStart = new CSprite(pScreen,"DK_POPUP_START");
			_pGood1 = new CSprite(pScreen,"DK_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"DK_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"DK_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"DK_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"DK_POPUP_SUPER");
		break;

		case (LANG_ENGLAND):
			_pStart = new CSprite(pScreen,"EN_POPUP_START");
			_pGood1 = new CSprite(pScreen,"EN_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"EN_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"EN_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"EN_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"EN_POPUP_SUPER");
		break;
		
		case (LANG_SPAIN):
			_pStart = new CSprite(pScreen,"ES_POPUP_START");
			_pGood1 = new CSprite(pScreen,"ES_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"ES_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"ES_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"ES_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"ES_POPUP_SUPER");
		break;

		case (LANG_FRANCE):
			_pStart = new CSprite(pScreen,"FR_POPUP_START");
			_pGood1 = new CSprite(pScreen,"FR_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"FR_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"FR_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"FR_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"FR_POPUP_SUPER");
		break;

		case (LANG_INDONESIA):
			_pStart = new CSprite(pScreen,"ID_POPUP_START");
			_pGood1 = new CSprite(pScreen,"ID_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"ID_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"ID_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"ID_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"ID_POPUP_SUPER");
		break;

		case (LANG_INDIA):
			_pStart = new CSprite(pScreen,"IN_POPUP_START");
			_pGood1 = new CSprite(pScreen,"IN_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"IN_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"IN_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"IN_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"IN_POPUP_SUPER");
		break;

		case (LANG_ISRAEL):
			_pStart = new CSprite(pScreen,"IS_POPUP_START");
			_pGood1 = new CSprite(pScreen,"IS_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"IS_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"IS_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"IS_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"IS_POPUP_SUPER");
		break;

		case (LANG_ITALY):
			_pStart = new CSprite(pScreen,"IT_POPUP_START");
			_pGood1 = new CSprite(pScreen,"IT_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"IT_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"IT_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"IT_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"IT_POPUP_SUPER");
		break;

		case (LANG_JAPAN):
			_pStart = new CSprite(pScreen,"JP_POPUP_START");
			_pGood1 = new CSprite(pScreen,"JP_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"JP_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"JP_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"JP_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"JP_POPUP_SUPER");
		break;

		case (LANG_KOREA):
			_pStart = new CSprite(pScreen,"KO_POPUP_START");
			_pGood1 = new CSprite(pScreen,"KO_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"KO_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"KO_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"KO_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"KO_POPUP_SUPER");
		break;

		case (LANG_NORWAY):
			_pStart = new CSprite(pScreen,"NO_POPUP_START");
			_pGood1 = new CSprite(pScreen,"NO_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"NO_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"NO_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"NO_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"NO_POPUP_SUPER");
		break;

		case (LANG_POLAND):
			_pStart = new CSprite(pScreen,"PL_POPUP_START");
			_pGood1 = new CSprite(pScreen,"PL_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"PL_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"PL_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"PL_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"PL_POPUP_SUPER");
		break;

		case (LANG_PORTUGAL):
			_pStart = new CSprite(pScreen,"PO_POPUP_START");
			_pGood1 = new CSprite(pScreen,"PO_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"PO_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"PO_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"PO_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"PO_POPUP_SUPER");
		break;

		case (LANG_RUSSIA):
			_pStart = new CSprite(pScreen,"RU_POPUP_START");
			_pGood1 = new CSprite(pScreen,"RU_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"RU_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"RU_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"RU_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"RU_POPUP_SUPER");
		break;

		case (LANG_SWEDEN):
			_pStart = new CSprite(pScreen,"SE_POPUP_START");
			_pGood1 = new CSprite(pScreen,"SE_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"SE_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"SE_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"SE_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"SE_POPUP_SUPER");
		break;

		case (LANG_TURKEY):
			_pStart = new CSprite(pScreen,"TU_POPUP_START");
			_pGood1 = new CSprite(pScreen,"TU_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen,"TU_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen,"TU_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen,"TU_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen,"TU_POPUP_SUPER");
		break;

		default:
			_pStart = new CSprite(pScreen, "EN_POPUP_START");
			_pGood1 = new CSprite(pScreen, "EN_POPUP_EXCELENT");
			_pGood2 = new CSprite(pScreen, "EN_POPUP_GOOD");
			_pGood3 = new CSprite(pScreen, "EN_POPUP_OUTSTANDING");
			_pGood4 = new CSprite(pScreen, "EN_POPUP_PERFECT");
			_pGood5 = new CSprite(pScreen, "EN_POPUP_SUPER");
		break;
	}
   
   _pScreen = pScreen;
	_isOpen = true;
}

/**
   Zwalnia wszystkie wczytane grafiki.

*/

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

	_isOpen = false;
}

/**
   Dodanie nowego popup do kolejki.
   
   @param iPopupType rodzaj popupu z listy
   @param ulTimer czas wystartowania popupu
*/

void CPopup::Add(int iPopupType, unsigned long ulTimer)
{
	int iIndex=-1;

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

/**
   Narysuj wszystkie aktywne popupy.

   @param ulTimer aktualny czas
*/

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
						_pStart->fScaleX(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pStart->RenderC();
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
						_pGood1->fScaleX(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood1->RenderC();
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
						_pGood2->fScaleY(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood2->RenderC();
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
						_pGood3->fScaleX(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood3->fScaleY(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood3->RenderC();
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
						_pGood4->fScaleX(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood4->fScaleY(1.0f + ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood4->RenderC();
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
						_pGood3->fScaleX(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood3->fScaleY(1.0f - ((float)(ulTimer - _ulTimerStart[i])/200));
						_pGood5->RenderC();
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

/**
   Sprawdzenie czy popup jest aktywny.

   @param i indeks popupu
   @return true je¿eli aktywny, false je¿eli nie
*/

bool CPopup::isActive(int i)
{
	return _bPopupActive[i];
}

/**
   Ustawienie flagi aktywnoœci dla popupu.

   @param i index popupu
   @param b ustawienie flagi
*/

void CPopup::isActive(int i, bool b)
{
	_bPopupActive[i] = b;
}

/**
   Zatrzymaj i wyzeruj wszystkie popupy.

*/

void CPopup::Stop(void)
{
	for (int i = 0; i < 64; i++)
	{
		_bPopupActive[i] = false;
		_iType[i] = 0;
		_ulTimerStart[i] = 0;
	}
}

/**
   Uruchom wszystkie popupy.

*/


void CPopup::Start(void)
{
	for (int i=0; i<64; i++)
		_bPopupActive[i] = true;
}

/**
   Zatrzymaj konkretny popup.

   @param i indeks popupu
*/


void CPopup::Stop(int i)
{
	_bPopupActive[i] = false;
}

/**
   Zatrzymaj konkretny popup.

   @param i indeks popupu
*/

void CPopup::Start(int i)
{
	_bPopupActive[i] = true;
}

