#include "MobileKeyboard.h"


CMobileKeyboard::CMobileKeyboard(char cLanguage)
{
	_cLanguage = cLanguage;
	_cState = 0;

	_pKeyboardBackground = NULL;

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

	_pKeyboardBackground = new CSprite("data/mobile_keyboard.jpg");

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

	_isActive = true ;

}

void CMobileKeyboard::Close()
{
	SafeDelete(_pKeyboardBackground);

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
	int y1,y2;
	unsigned char cKey;

	cKey = KEY_NONE;

	_pKeyboardBackground->Position(0,384);
	_pKeyboardBackground->Render();

	// pierwszy rzad

	y1 = 384;
	y2 = 384+64;

	_pKey1->SetPosition(32,y1);	 _pKey1->SetHotCoords(32,y1,32+64,y2);   if (_pKey1->Render(pMouse)==ON_LEFT) cKey=KEY_1;
	_pKey2->SetPosition(128,y1); _pKey2->SetHotCoords(128,y1,128+64,y2); if (_pKey2->Render(pMouse)==ON_LEFT) cKey=KEY_2;
	_pKey3->SetPosition(224,y1); _pKey3->SetHotCoords(224,y1,224+64,y2); if (_pKey3->Render(pMouse)==ON_LEFT) cKey=KEY_3;
	_pKey4->SetPosition(320,y1); _pKey4->SetHotCoords(320,y1,320+64,y2); if (_pKey4->Render(pMouse)==ON_LEFT) cKey=KEY_4;
	_pKey5->SetPosition(416,y1); _pKey5->SetHotCoords(416,y1,416+64,y2); if (_pKey5->Render(pMouse)==ON_LEFT) cKey=KEY_5;
	_pKey6->SetPosition(512,y1); _pKey6->SetHotCoords(512,y1,512+64,y2); if (_pKey6->Render(pMouse)==ON_LEFT) cKey=KEY_6;
	_pKey7->SetPosition(608,y1); _pKey7->SetHotCoords(608,y1,608+64,y2); if (_pKey7->Render(pMouse)==ON_LEFT) cKey=KEY_7;
	_pKey8->SetPosition(704,y1); _pKey8->SetHotCoords(704,y1,704+64,y2); if (_pKey8->Render(pMouse)==ON_LEFT) cKey=KEY_8;
	_pKey9->SetPosition(800,y1); _pKey9->SetHotCoords(800,y1,800+64,y2); if (_pKey9->Render(pMouse)==ON_LEFT) cKey=KEY_9;
	_pKey0->SetPosition(896,y1); _pKey0->SetHotCoords(896,y1,896+64,y2); if (_pKey0->Render(pMouse)==ON_LEFT) cKey=KEY_0;

	// drugi rzad

	y1 = 384+64+32;
	y2 = 384+64+64+32;

	_pKeyQ->SetPosition(32,y1);  _pKeyQ->SetHotCoords(32,y1,32+64,y2);   if (_pKeyQ->Render(pMouse)==ON_LEFT) cKey=KEY_Q;
	_pKeyW->SetPosition(128,y1); _pKeyW->SetHotCoords(128,y1,128+64,y2); if (_pKeyW->Render(pMouse)==ON_LEFT) cKey=KEY_W;
	_pKeyE->SetPosition(224,y1); _pKeyE->SetHotCoords(224,y1,224+64,y2); if (_pKeyE->Render(pMouse)==ON_LEFT) cKey=KEY_E;
	_pKeyR->SetPosition(320,y1); _pKeyR->SetHotCoords(320,y1,320+64,y2); if (_pKeyR->Render(pMouse)==ON_LEFT) cKey=KEY_R;
	_pKeyT->SetPosition(416,y1); _pKeyT->SetHotCoords(416,y1,416+64,y2); if (_pKeyT->Render(pMouse)==ON_LEFT) cKey=KEY_T;
	_pKeyY->SetPosition(512,y1); _pKeyY->SetHotCoords(512,y1,512+64,y2); if (_pKeyY->Render(pMouse)==ON_LEFT) cKey=KEY_Y;
	_pKeyU->SetPosition(608,y1); _pKeyU->SetHotCoords(608,y1,608+64,y2); if (_pKeyU->Render(pMouse)==ON_LEFT) cKey=KEY_U;
	_pKeyI->SetPosition(704,y1); _pKeyI->SetHotCoords(704,y1,704+64,y2); if (_pKeyI->Render(pMouse)==ON_LEFT) cKey=KEY_I;
	_pKeyO->SetPosition(800,y1); _pKeyO->SetHotCoords(800,y1,800+64,y2); if (_pKeyO->Render(pMouse)==ON_LEFT) cKey=KEY_O;
	_pKeyP->SetPosition(896,y1); _pKeyP->SetHotCoords(896,y1,896+64,y2); if (_pKeyP->Render(pMouse)==ON_LEFT) cKey=KEY_P;

	// trzeci rzad 

	y1 = 384+64+32+64+32;
	y2 = 384+64+64+32+64+32;

	_pKeyA->SetPosition(32,y1);  _pKeyA->SetHotCoords(32,y1,32+64,y2);   if (_pKeyA->Render(pMouse)==ON_LEFT) cKey=KEY_A;
	_pKeyS->SetPosition(128,y1); _pKeyS->SetHotCoords(128,y1,128+64,y2); if (_pKeyS->Render(pMouse)==ON_LEFT) cKey=KEY_S;
	_pKeyD->SetPosition(224,y1); _pKeyD->SetHotCoords(224,y1,224+64,y2); if (_pKeyD->Render(pMouse)==ON_LEFT) cKey=KEY_D;
	_pKeyF->SetPosition(320,y1); _pKeyF->SetHotCoords(320,y1,320+64,y2); if (_pKeyF->Render(pMouse)==ON_LEFT) cKey=KEY_F;
	_pKeyG->SetPosition(416,y1); _pKeyG->SetHotCoords(416,y1,416+64,y2); if (_pKeyG->Render(pMouse)==ON_LEFT) cKey=KEY_G;
	_pKeyH->SetPosition(512,y1); _pKeyH->SetHotCoords(512,y1,512+64,y2); if (_pKeyH->Render(pMouse)==ON_LEFT) cKey=KEY_H;
	_pKeyJ->SetPosition(608,y1); _pKeyJ->SetHotCoords(608,y1,608+64,y2); if (_pKeyJ->Render(pMouse)==ON_LEFT) cKey=KEY_J;
	_pKeyK->SetPosition(704,y1); _pKeyK->SetHotCoords(704,y1,704+64,y2); if (_pKeyK->Render(pMouse)==ON_LEFT) cKey=KEY_K;
	_pKeyL->SetPosition(800,y1); _pKeyL->SetHotCoords(800,y1,800+64,y2); if (_pKeyL->Render(pMouse)==ON_LEFT) cKey=KEY_L;
	
	// ENTER
	_pKeyENTER->SetPosition(896,y1); _pKeyENTER->SetHotCoords(896,y1,896+64,y2); if (_pKeyENTER->Render(pMouse)==ON_LEFT) cKey=KEY_ENTER;

	// czwarty rzad

	y1 = 384+64+32+64+32+64+32;
	y2 = 384+64+64+32+64+32+64+32;

	_pKeyZ->SetPosition(32,y1);  _pKeyZ->SetHotCoords(32,y1,32+64,y2);   if (_pKeyZ->Render(pMouse)==ON_LEFT) cKey=KEY_Z;
	_pKeyX->SetPosition(128,y1); _pKeyX->SetHotCoords(128,y1,128+64,y2); if (_pKeyX->Render(pMouse)==ON_LEFT) cKey=KEY_X;
	_pKeyC->SetPosition(224,y1); _pKeyC->SetHotCoords(224,y1,224+64,y2); if (_pKeyC->Render(pMouse)==ON_LEFT) cKey=KEY_C;
	_pKeyV->SetPosition(320,y1); _pKeyV->SetHotCoords(320,y1,320+64,y2); if (_pKeyV->Render(pMouse)==ON_LEFT) cKey=KEY_V;
	_pKeyB->SetPosition(416,y1); _pKeyB->SetHotCoords(416,y1,416+64,y2); if (_pKeyB->Render(pMouse)==ON_LEFT) cKey=KEY_B;
	_pKeyN->SetPosition(512,y1); _pKeyN->SetHotCoords(512,y1,512+64,y2); if (_pKeyN->Render(pMouse)==ON_LEFT) cKey=KEY_N;
	_pKeyM->SetPosition(608,y1); _pKeyM->SetHotCoords(608,y1,608+64,y2); if (_pKeyM->Render(pMouse)==ON_LEFT) cKey=KEY_M;

	// DELETE	
	_pKeyDELETE->SetPosition(704,y1); _pKeyDELETE->SetHotCoords(704,y1,704+64,y2); if (_pKeyDELETE->Render(pMouse)==ON_LEFT) cKey=KEY_DELETE;

	// SPACE
//	_pKeySPACE->SetPosition(800,y1); _pKeySPACE->SetHotCoords(800,y1,800+64,y2); if (_pKeySPACE->Render(pMouse)==ON_LEFT) cKey=KEY_SPACE;

	return cKey;
}
