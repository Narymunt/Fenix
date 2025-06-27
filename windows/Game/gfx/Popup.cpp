/**
   Popup.cpp

   Tylko do wyskakuj¹cych napisów. 
   Trzyma informacje o texturach, ¿eby nie powielaæ sprite dla ka¿dej cz¹stki z osobna.
   Maksymalnie 64 popupy na ekranie.

   @author Jaros³aw Ro¿yñski
   
*/

#include "Popup.h"
#include "../common/GameSettings.h"
#include "../Game.h"

CPopup::CPopup() 
{
	_whiteFlash = NULL;
	_blackFlash = NULL;

	stop();	// set false to all popups

	_start = NULL;

	_good1 = NULL;
	_good2 = NULL;
	_good3 = NULL;
	_good4 = NULL;
	_good5 = NULL;

	_isOpen = false;
}

CPopup::~CPopup()
{
	close();
}

/**
   Wczytuje wszystkie potrzebne grafiki ze skryptu.   
   @param pScreen wskaznik do ekranu
*/

void CPopup::open(void)
{
	CGameSettings *pSetup;
	unsigned char ucLang;

	pSetup = new CGameSettings();
	pSetup->load();

	ucLang = pSetup->_language;

	delete pSetup;

	_whiteFlash = new CSprite((char*)"GFX_WHITE50_SCREEN");
	_blackFlash = new CSprite((char*)"GFX_BLACK100_SCREEN");

	switch (ucLang)
	{
		case (ARABIA):
			_start = new CSprite((char*)"AR_POPUP_START");
			_good1 = new CSprite((char*)"AR_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"AR_POPUP_GOOD");
			_good3 = new CSprite((char*)"AR_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"AR_POPUP_PERFECT");
			_good5 = new CSprite((char*)"AR_POPUP_SUPER");
		break;

		case (BRASIL):
			_start = new CSprite((char*)"BR_POPUP_START");
			_good1 = new CSprite((char*)"BR_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"BR_POPUP_GOOD");
			_good3 = new CSprite((char*)"BR_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"BR_POPUP_PERFECT");
			_good5 = new CSprite((char*)"BR_POPUP_SUPER");
		break;

		case (CHINA):
			_start = new CSprite((char*)"CH_POPUP_START");
			_good1 = new CSprite((char*)"CH_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"CH_POPUP_GOOD");
			_good3 = new CSprite((char*)"CH_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"CH_POPUP_PERFECT");
			_good5 = new CSprite((char*)"CH_POPUP_SUPER");
		break;

		case (GERMANY):
			_start = new CSprite((char*)"DE_POPUP_START");
			_good1 = new CSprite((char*)"DE_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"DE_POPUP_GOOD");
			_good3 = new CSprite((char*)"DE_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"DE_POPUP_PERFECT");
			_good5 = new CSprite((char*)"DE_POPUP_SUPER");
		break;

		case (DENMARK):
			_start = new CSprite((char*)"DK_POPUP_START");
			_good1 = new CSprite((char*)"DK_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"DK_POPUP_GOOD");
			_good3 = new CSprite((char*)"DK_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"DK_POPUP_PERFECT");
			_good5 = new CSprite((char*)"DK_POPUP_SUPER");
		break;

		case (ENGLAND):
			_start = new CSprite((char*)"EN_POPUP_START");
			_good1 = new CSprite((char*)"EN_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"EN_POPUP_GOOD");
			_good3 = new CSprite((char*)"EN_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"EN_POPUP_PERFECT");
			_good5 = new CSprite((char*)"EN_POPUP_SUPER");
		break;
		
		case (SPAIN):
			_start = new CSprite((char*)"ES_POPUP_START");
			_good1 = new CSprite((char*)"ES_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"ES_POPUP_GOOD");
			_good3 = new CSprite((char*)"ES_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"ES_POPUP_PERFECT");
			_good5 = new CSprite((char*)"ES_POPUP_SUPER");
		break;

		case (FRANCE):
			_start = new CSprite((char*)"FR_POPUP_START");
			_good1 = new CSprite((char*)"FR_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"FR_POPUP_GOOD");
			_good3 = new CSprite((char*)"FR_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"FR_POPUP_PERFECT");
			_good5 = new CSprite((char*)"FR_POPUP_SUPER");
		break;

		case (INDONESIA):
			_start = new CSprite((char*)"ID_POPUP_START");
			_good1 = new CSprite((char*)"ID_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"ID_POPUP_GOOD");
			_good3 = new CSprite((char*)"ID_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"ID_POPUP_PERFECT");
			_good5 = new CSprite((char*)"ID_POPUP_SUPER");
		break;

		case (INDIA):
			_start = new CSprite((char*)"IN_POPUP_START");
			_good1 = new CSprite((char*)"IN_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"IN_POPUP_GOOD");
			_good3 = new CSprite((char*)"IN_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"IN_POPUP_PERFECT");
			_good5 = new CSprite((char*)"IN_POPUP_SUPER");
		break;

		case (ISRAEL):
			_start = new CSprite((char*)"IS_POPUP_START");
			_good1 = new CSprite((char*)"IS_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"IS_POPUP_GOOD");
			_good3 = new CSprite((char*)"IS_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"IS_POPUP_PERFECT");
			_good5 = new CSprite((char*)"IS_POPUP_SUPER");
		break;

		case (ITALY):
			_start = new CSprite((char*)"IT_POPUP_START");
			_good1 = new CSprite((char*)"IT_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"IT_POPUP_GOOD");
			_good3 = new CSprite((char*)"IT_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"IT_POPUP_PERFECT");
			_good5 = new CSprite((char*)"IT_POPUP_SUPER");
		break;

		case (JAPAN):
			_start = new CSprite((char*)"JP_POPUP_START");
			_good1 = new CSprite((char*)"JP_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"JP_POPUP_GOOD");
			_good3 = new CSprite((char*)"JP_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"JP_POPUP_PERFECT");
			_good5 = new CSprite((char*)"JP_POPUP_SUPER");
		break;

		case (KOREA):
			_start = new CSprite((char*)"KO_POPUP_START");
			_good1 = new CSprite((char*)"KO_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"KO_POPUP_GOOD");
			_good3 = new CSprite((char*)"KO_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"KO_POPUP_PERFECT");
			_good5 = new CSprite((char*)"KO_POPUP_SUPER");
		break;

		case (NORWAY):
			_start = new CSprite((char*)"NO_POPUP_START");
			_good1 = new CSprite((char*)"NO_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"NO_POPUP_GOOD");
			_good3 = new CSprite((char*)"NO_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"NO_POPUP_PERFECT");
			_good5 = new CSprite((char*)"NO_POPUP_SUPER");
		break;

		case (POLAND):
			_start = new CSprite((char*)"PL_POPUP_START");
			_good1 = new CSprite((char*)"PL_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"PL_POPUP_GOOD");
			_good3 = new CSprite((char*)"PL_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"PL_POPUP_PERFECT");
			_good5 = new CSprite((char*)"PL_POPUP_SUPER");
		break;

		case (PORTUGAL):
			_start = new CSprite((char*)"PO_POPUP_START");
			_good1 = new CSprite((char*)"PO_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"PO_POPUP_GOOD");
			_good3 = new CSprite((char*)"PO_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"PO_POPUP_PERFECT");
			_good5 = new CSprite((char*)"PO_POPUP_SUPER");
		break;

		case (RUSSIA):
			_start = new CSprite((char*)"RU_POPUP_START");
			_good1 = new CSprite((char*)"RU_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"RU_POPUP_GOOD");
			_good3 = new CSprite((char*)"RU_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"RU_POPUP_PERFECT");
			_good5 = new CSprite((char*)"RU_POPUP_SUPER");
		break;

		case (SWEDEN):
			_start = new CSprite((char*)"SE_POPUP_START");
			_good1 = new CSprite((char*)"SE_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"SE_POPUP_GOOD");
			_good3 = new CSprite((char*)"SE_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"SE_POPUP_PERFECT");
			_good5 = new CSprite((char*)"SE_POPUP_SUPER");
		break;

		case (TURKEY):
			_start = new CSprite((char*)"TU_POPUP_START");
			_good1 = new CSprite((char*)"TU_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"TU_POPUP_GOOD");
			_good3 = new CSprite((char*)"TU_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"TU_POPUP_PERFECT");
			_good5 = new CSprite((char*)"TU_POPUP_SUPER");
		break;

		default:
			_start = new CSprite((char*)"EN_POPUP_START");
			_good1 = new CSprite((char*)"EN_POPUP_EXCELENT");
			_good2 = new CSprite((char*)"EN_POPUP_GOOD");
			_good3 = new CSprite((char*)"EN_POPUP_OUTSTANDING");
			_good4 = new CSprite((char*)"EN_POPUP_PERFECT");
			_good5 = new CSprite((char*)"EN_POPUP_SUPER");
		break;
	}
   
	_isOpen = true;
}

/**
   Zwalnia wszystkie wczytane grafiki.
*/

void CPopup::close(void)
{
	safeDelete(_whiteFlash);
	safeDelete(_blackFlash);

	safeDelete(_start);

	safeDelete(_good1);
	safeDelete(_good2);
	safeDelete(_good3);
	safeDelete(_good4);
	safeDelete(_good5);

	_isOpen = false;
}

/**
   Dodanie nowego popup do kolejki.
   
   @param iPopupType rodzaj popupu z listy
   @param ulTimer czas wystartowania popupu
*/

void CPopup::add(int type, unsigned long timer)
{
	int index=-1;

	for (int i=0; i<64; i++)	
	{
		if (_isActive[i]==false && index==-1)
			index = i;
	}

	if (index!=-1)
	{
		_isActive[index] = true;
		_timerStart[index] = timer;
		_type[index] = type;
	}
}

/**
   Narysuj wszystkie aktywne popupy.
   @param ulTimer aktualny czas
*/

void CPopup::render(unsigned long timer)
{
	for (int i=0; i<64; i++)
	{
		if (_isActive[i])
		{
			switch(_type[i])
			{
				case POPUP_FLASH_BLACK:
					if (timer - _timerStart[i] < 500)
					{
						_blackFlash->_a = (1.0f - ((float)(timer - _timerStart[i])/500));
						_blackFlash->render();
					}
					else
					{					
						_isActive[i] = false;
					}
				break;

				case POPUP_FLASH_WHITE:
					if (timer - _timerStart[i] < 500)
					{
						_whiteFlash->_a = (1.0f - ((float)(timer - _timerStart[i])/500));
						_whiteFlash->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_FADE_BLACK:
					if (timer - _timerStart[i] < 500)
					{
						_blackFlash->_a = (1.0f - ((float)(timer - _timerStart[i])/500));
						_blackFlash->render();
					}
					else
					{
						_isActive[i] = false;
					}

				break;

				case POPUP_FADE_WHITE:
					if (timer - _timerStart[i] < 500)
					{
						_whiteFlash->_a = (1.0f - ((float)(timer - _timerStart[i])/500));
						_whiteFlash->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_INGAME_START:
					if (timer - _timerStart[i] < 200)
					{
						_start->_a = (1.0f - ((float)(timer - _timerStart[i])/200));
						_start->scale(1.0f + ((float)(timer - _timerStart[i])/200),1.0f);
						_start->_isCenter = true;
						_start->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD1:
					if (timer - _timerStart[i] < 200)
					{
						_good1->_a = (1.0f - ((float)(timer - _timerStart[i])/200));
						_good1->scale(1.0f + ((float)(timer - _timerStart[i])/200),1.0f);
						_start->_isCenter = true;
						_good1->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD2:
					if (timer - _timerStart[i] < 200)
					{
						_good2->_a = (1.0f - ((float)(timer - _timerStart[i])/200));
						_good2->scale(1.0f, 1.0f + ((float)(timer - _timerStart[i])/200));
						_good2->_isCenter = true;
						_good2->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD3:
					if (timer - _timerStart[i] < 200)
					{
						_good3->_a = (1.0f - ((float)(timer - _timerStart[i])/200));
						_good3->scale(1.0f + ((float)(timer - _timerStart[i])/200), 1.0f - ((float)(timer - _timerStart[i]) / 200));
						_good3->_isCenter = true;
						_good3->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD4:
					if (timer - _timerStart[i] < 200)
					{
						_good4->_a = (1.0f - ((float)(timer - _timerStart[i])/200));
						_good4->scale(1.0f - ((float)(timer - _timerStart[i])/200), 1.0f + ((float)(timer - _timerStart[i]) / 200));
						_good4->_isCenter = true;
						_good4->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;

				case POPUP_INGAME_GOOD5:
					if (timer - _timerStart[i] < 200)
					{
						_good5->_a = (1.0f - ((float)(timer - _timerStart[i])/200));
						_good5->scale(1.0f - ((float)(timer - _timerStart[i])/200), 1.0f - ((float)(timer - _timerStart[i]) / 200));
						_good5->_isCenter = true;
						_good5->render();
					}
					else
					{
						_isActive[i] = false;
					}
				break;
			}
		}
	}
}


/**
   Zatrzymaj i wyzeruj wszystkie popupy.
*/

void CPopup::stop(void)
{
	for (int i = 0; i < 64; i++)
	{
		_isActive[i] = false;
		_type[i] = 0;
		_timerStart[i] = 0;
	}
}

/**
   Uruchom wszystkie popupy.
*/

void CPopup::start(void)
{
	for (int i=0; i<64; i++)
		_isActive[i] = true;
}

/**
   Zatrzymaj konkretny popup.
   @param i indeks popupu
*/


void CPopup::stop(int i)
{
	_isActive[i] = false;
}

/**
   Zatrzymaj konkretny popup.
   @param i indeks popupu
*/

void CPopup::start(int i)
{
	_isActive[i] = true;
}

