#include "MobileKeyboard.h"


CMobileKeyboard::CMobileKeyboard(char cLanguage)
{
	_cLanguage = cLanguage;
	_cState = 0;

	_pKey1 = _pKey2 = _pKey3 = _pKey4 = _pKey5 = _pKey6 = _pKey7 = _pKey8 = _pKey9 = _pKey0 = NULL;

	_pKeyA = _pKeyB = _pKeyC = _pKeyD = _pKeyE = _pKeyF = _pKeyG = _pKeyH = _pKeyI = _pKeyJ = NULL;
	_pKeyK = _pKeyL = _pKeyM = _pKeyN = _pKeyO = _pKeyP = _pKeyQ = _pKeyR = _pKeyS = _pKeyT = NULL;
	_pKeyU = _pKeyV = _pKeyW = _pKeyX = _pKeyY = _pKeyZ = NULL;

	_pKeySPACE = NULL;
	_pKeyDELETE = NULL;
	_pKeyENTER = NULL;

}

CMobileKeyboard::~CMobileKeyboard()
{
	_cState = 0;
	Close();
}

void CMobileKeyboard::Open(CScreen *pScreen)
{
	_cState = 0;
	
	_pKey1 = new CButton(pScreen,"BUTTON_KEY_1");
	_pKey2 = new CButton(pScreen,"BUTTON_KEY_2");
	_pKey3 = new CButton(pScreen,"BUTTON_KEY_3");
	_pKey4 = new CButton(pScreen,"BUTTON_KEY_4");
	_pKey5 = new CButton(pScreen,"BUTTON_KEY_5");
	_pKey6 = new CButton(pScreen,"BUTTON_KEY_6");
	_pKey7 = new CButton(pScreen,"BUTTON_KEY_7");
	_pKey8 = new CButton(pScreen,"BUTTON_KEY_8");
	_pKey9 = new CButton(pScreen,"BUTTON_KEY_9");
	_pKey0 = new CButton(pScreen,"BUTTON_KEY_0");

	_pKeyA = new CButton(pScreen,"BUTTON_KEY_A");
	_pKeyB = new CButton(pScreen,"BUTTON_KEY_B");
	_pKeyC = new CButton(pScreen,"BUTTON_KEY_C");
	_pKeyD = new CButton(pScreen,"BUTTON_KEY_D");
	_pKeyE = new CButton(pScreen,"BUTTON_KEY_E");
	_pKeyF = new CButton(pScreen,"BUTTON_KEY_F");
	_pKeyG = new CButton(pScreen,"BUTTON_KEY_G");
	_pKeyH = new CButton(pScreen,"BUTTON_KEY_H");
	_pKeyI = new CButton(pScreen,"BUTTON_KEY_I");
	_pKeyJ = new CButton(pScreen,"BUTTON_KEY_J");
	_pKeyK = new CButton(pScreen,"BUTTON_KEY_K");
	_pKeyL = new CButton(pScreen,"BUTTON_KEY_L");
	_pKeyM = new CButton(pScreen,"BUTTON_KEY_M");
	_pKeyN = new CButton(pScreen,"BUTTON_KEY_N");
	_pKeyO = new CButton(pScreen,"BUTTON_KEY_O");
	_pKeyP = new CButton(pScreen,"BUTTON_KEY_P");
	_pKeyQ = new CButton(pScreen,"BUTTON_KEY_Q");
	_pKeyR = new CButton(pScreen,"BUTTON_KEY_R");
	_pKeyS = new CButton(pScreen,"BUTTON_KEY_S");
	_pKeyT = new CButton(pScreen,"BUTTON_KEY_T");
	_pKeyU = new CButton(pScreen,"BUTTON_KEY_U");
	_pKeyV = new CButton(pScreen,"BUTTON_KEY_V");
	_pKeyW = new CButton(pScreen,"BUTTON_KEY_W");
	_pKeyX = new CButton(pScreen,"BUTTON_KEY_X");
	_pKeyY = new CButton(pScreen,"BUTTON_KEY_Y");
	_pKeyZ = new CButton(pScreen,"BUTTON_KEY_Z");

	_pKeySPACE = new CButton(pScreen,"BUTTON_KEY_SPACE");
	_pKeyDELETE = new CButton(pScreen,"BUTTON_KEY_DELETE");
	_pKeyENTER = new CButton(pScreen,"BUTTON_KEY_ENTER");

	_pScreen = pScreen;
	_isActive = true ;

}

void CMobileKeyboard::Close()
{
//	SafeDelete(_pKeyboardBackground);

	SafeDelete(_pKey1); SafeDelete(_pKey2); SafeDelete(_pKey3);
	SafeDelete(_pKey4); SafeDelete(_pKey5); SafeDelete(_pKey6);
	SafeDelete(_pKey7); SafeDelete(_pKey8); SafeDelete(_pKey9);
	SafeDelete(_pKey0);

	SafeDelete(_pKeyA);	SafeDelete(_pKeyB);	SafeDelete(_pKeyC);
	SafeDelete(_pKeyD);	SafeDelete(_pKeyE);	SafeDelete(_pKeyF);
	SafeDelete(_pKeyG);	SafeDelete(_pKeyH);	SafeDelete(_pKeyI);
	SafeDelete(_pKeyJ);	SafeDelete(_pKeyK);	SafeDelete(_pKeyL);
	SafeDelete(_pKeyM);	SafeDelete(_pKeyN);	SafeDelete(_pKeyO);
	SafeDelete(_pKeyP);	SafeDelete(_pKeyQ);	SafeDelete(_pKeyR);
	SafeDelete(_pKeyS);	SafeDelete(_pKeyT);	SafeDelete(_pKeyU);
	SafeDelete(_pKeyV);	SafeDelete(_pKeyW);	SafeDelete(_pKeyX);
	SafeDelete(_pKeyY);	SafeDelete(_pKeyZ);	

	SafeDelete(_pKeySPACE);
	SafeDelete(_pKeyDELETE);
	SafeDelete(_pKeyENTER);

	_isActive = false;
}

unsigned char CMobileKeyboard::cRender(unsigned long ulTimer, CMouse *pMouse)
{
	int y1,y2, x1, iStepX, iSize;
	unsigned char cKey;

	cKey = KEY_NONE;

	// pierwszy rzad

	if (_pScreen->iSizeX() == 1024)
	{
		iSize = 64;
		y1 = 384; y2 = 384 + iSize;
		x1 = 32; iStepX = 96;
	}
	else if (_pScreen->iSizeX() == 1366)
	{
		iSize = 64;
		y1 = 384; y2 = 384 + iSize;
		x1 = 64; iStepX = 128;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		iSize = 128;
		y1 = 384; y2 = 384 + iSize + 64;
		x1 = 32; iStepX = 128+64;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		iSize = 128;
		y1 = 700; y2 = 700 + iSize;
		x1 = 64; iStepX = 256;
	}

	_pKey1->setPosition(x1 + (iStepX * 0), y1);	_pKey1->setHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_pKey1->Render(pMouse) == ON_LEFT) cKey = KEY_1;
	_pKey2->setPosition(x1 + (iStepX * 1), y1); _pKey2->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKey2->Render(pMouse) == ON_LEFT) cKey = KEY_2;
	_pKey3->setPosition(x1 + (iStepX * 2), y1); _pKey3->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKey3->Render(pMouse) == ON_LEFT) cKey = KEY_3;
	_pKey4->setPosition(x1 + (iStepX * 3), y1); _pKey4->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKey4->Render(pMouse) == ON_LEFT) cKey = KEY_4;
	_pKey5->setPosition(x1 + (iStepX * 4), y1); _pKey5->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKey5->Render(pMouse) == ON_LEFT) cKey = KEY_5;
	_pKey6->setPosition(x1 + (iStepX * 5), y1); _pKey6->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKey6->Render(pMouse) == ON_LEFT) cKey = KEY_6;
	_pKey7->setPosition(x1 + (iStepX * 6), y1); _pKey7->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKey7->Render(pMouse) == ON_LEFT) cKey = KEY_7;
	_pKey8->setPosition(x1 + (iStepX * 7), y1); _pKey8->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKey8->Render(pMouse) == ON_LEFT) cKey = KEY_8;
	_pKey9->setPosition(x1 + (iStepX * 8), y1); _pKey9->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKey9->Render(pMouse) == ON_LEFT) cKey = KEY_9;
	_pKey0->setPosition(x1 + (iStepX * 9), y1); _pKey0->setHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_pKey0->Render(pMouse) == ON_LEFT) cKey = KEY_0;
	
	// drugi rzad

	if (_pScreen->iSizeX() == 1024)
	{
		iSize = 64;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 1366)
	{
		iSize = 64;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		iSize = 128;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		iSize = 128;
		y1 = 700 + iSize + 32;
		y2 = 700 + iSize + iSize + 32;
	}

	_pKeyQ->setPosition(x1 + (iStepX * 0), y1); _pKeyQ->setHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_pKeyQ->Render(pMouse) == ON_LEFT) cKey = KEY_Q;
	_pKeyW->setPosition(x1 + (iStepX * 1), y1); _pKeyW->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKeyW->Render(pMouse) == ON_LEFT) cKey = KEY_W;
	_pKeyE->setPosition(x1 + (iStepX * 2), y1); _pKeyE->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKeyE->Render(pMouse) == ON_LEFT) cKey = KEY_E;
	_pKeyR->setPosition(x1 + (iStepX * 3), y1); _pKeyR->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKeyR->Render(pMouse) == ON_LEFT) cKey = KEY_R;
	_pKeyT->setPosition(x1 + (iStepX * 4), y1); _pKeyT->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKeyT->Render(pMouse) == ON_LEFT) cKey = KEY_T;
	_pKeyY->setPosition(x1 + (iStepX * 5), y1); _pKeyY->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKeyY->Render(pMouse) == ON_LEFT) cKey = KEY_Y;
	_pKeyU->setPosition(x1 + (iStepX * 6), y1); _pKeyU->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKeyU->Render(pMouse) == ON_LEFT) cKey = KEY_U;
	_pKeyI->setPosition(x1 + (iStepX * 7), y1); _pKeyI->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKeyI->Render(pMouse) == ON_LEFT) cKey = KEY_I;
	_pKeyO->setPosition(x1 + (iStepX * 8), y1); _pKeyO->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKeyO->Render(pMouse) == ON_LEFT) cKey = KEY_O;
	_pKeyP->setPosition(x1 + (iStepX * 9), y1); _pKeyP->setHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_pKeyP->Render(pMouse) == ON_LEFT) cKey = KEY_P;

	// trzeci rzad 

	if (_pScreen->iSizeX() == 1024)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 1366)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		iSize = 128;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		iSize = 128;
		y1 = 700 + iSize + 32 + iSize + 32;
		y2 = 700 + iSize + iSize + 32 + iSize + 32;
	}

	_pKeyA->setPosition(x1 + (iStepX * 0), y1); _pKeyA->setHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_pKeyA->Render(pMouse) == ON_LEFT) cKey = KEY_A;
	_pKeyS->setPosition(x1 + (iStepX * 1), y1); _pKeyS->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKeyS->Render(pMouse) == ON_LEFT) cKey = KEY_S;
	_pKeyD->setPosition(x1 + (iStepX * 2), y1); _pKeyD->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKeyD->Render(pMouse) == ON_LEFT) cKey = KEY_D;
	_pKeyF->setPosition(x1 + (iStepX * 3), y1); _pKeyF->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKeyF->Render(pMouse) == ON_LEFT) cKey = KEY_F;
	_pKeyG->setPosition(x1 + (iStepX * 4), y1); _pKeyG->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKeyG->Render(pMouse) == ON_LEFT) cKey = KEY_G;
	_pKeyH->setPosition(x1 + (iStepX * 5), y1); _pKeyH->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKeyH->Render(pMouse) == ON_LEFT) cKey = KEY_H;
	_pKeyJ->setPosition(x1 + (iStepX * 6), y1); _pKeyJ->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKeyJ->Render(pMouse) == ON_LEFT) cKey = KEY_J;
	_pKeyK->setPosition(x1 + (iStepX * 7), y1); _pKeyK->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKeyK->Render(pMouse) == ON_LEFT) cKey = KEY_K;
	_pKeyL->setPosition(x1 + (iStepX * 8), y1); _pKeyL->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKeyL->Render(pMouse) == ON_LEFT) cKey = KEY_L;
	_pKeyENTER->setPosition(x1 + (iStepX * 9), y1); _pKeyENTER->setHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_pKeyENTER->Render(pMouse) == ON_LEFT) cKey = KEY_ENTER;

	// czwarty rzad

	if (_pScreen->iSizeX() == 1024)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 1366)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 1920)
	{
		iSize = 128;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}
	else if (_pScreen->iSizeX() == 2560)
	{
		iSize = 128;
		y1 = 700 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 700 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}

	_pKeyZ->setPosition(x1 + (iStepX * 1), y1); _pKeyZ->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKeyZ->Render(pMouse) == ON_LEFT) cKey = KEY_Z;
	_pKeyX->setPosition(x1 + (iStepX * 2), y1); _pKeyX->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKeyX->Render(pMouse) == ON_LEFT) cKey = KEY_X;
	_pKeyC->setPosition(x1 + (iStepX * 3), y1); _pKeyC->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKeyC->Render(pMouse) == ON_LEFT) cKey = KEY_C;
	_pKeyV->setPosition(x1 + (iStepX * 4), y1); _pKeyV->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKeyV->Render(pMouse) == ON_LEFT) cKey = KEY_V;
	_pKeyB->setPosition(x1 + (iStepX * 5), y1); _pKeyB->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKeyB->Render(pMouse) == ON_LEFT) cKey = KEY_B;
	_pKeyN->setPosition(x1 + (iStepX * 6), y1); _pKeyN->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKeyN->Render(pMouse) == ON_LEFT) cKey = KEY_N;
	_pKeyM->setPosition(x1 + (iStepX * 7), y1); _pKeyM->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKeyM->Render(pMouse) == ON_LEFT) cKey = KEY_M;
	_pKeyDELETE->setPosition(x1 + (iStepX * 8), y1); _pKeyDELETE->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKeyDELETE->Render(pMouse) == ON_LEFT) cKey = KEY_DELETE;

	return cKey;
}
