#include "Popup.h"


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

CPopup::CPopup(char cFile[])
{

}

CPopup::~CPopup()
{
	Close();
}

void CPopup::Open(CScreen *pScreen)
{
	_pWhiteFlash = new CSprite(pScreen,"GFX_WHITE100_SCREEN");
	_pBlackFlash = new CSprite(pScreen,"GFX_BLACK100_SCREEN");
	_pStart = new  CSprite(pScreen,"START_POPUP");
	_pGood1 = new  CSprite(pScreen,"POPUP1");
	_pGood2 = new  CSprite(pScreen,"POPUP2");
	_pGood3 = new  CSprite(pScreen,"POPUP3");
	_pGood4 = new  CSprite(pScreen,"POPUP4");
	_pGood5 = new  CSprite(pScreen,"POPUP5");
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
	for (int i=0; i<64; i++)
		_bPopupActive[i] = false;
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

