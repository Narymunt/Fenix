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

	_pKey1 = new CButton("data/en_key_11.png","data/en_key_12.png","data/en_key_11.png");
	_pKey2 = new CButton("data/en_key_21.png","data/en_key_22.png","data/en_key_21.png");
	_pKey3 = new CButton("data/en_key_31.png","data/en_key_32.png","data/en_key_31.png");
	_pKey4 = new CButton("data/en_key_41.png","data/en_key_42.png","data/en_key_41.png");
	_pKey5 = new CButton("data/en_key_51.png","data/en_key_52.png","data/en_key_51.png");
	_pKey6 = new CButton("data/en_key_61.png","data/en_key_62.png","data/en_key_61.png");
	_pKey7 = new CButton("data/en_key_71.png","data/en_key_72.png","data/en_key_71.png");
	_pKey8 = new CButton("data/en_key_81.png","data/en_key_82.png","data/en_key_81.png");
	_pKey9 = new CButton("data/en_key_91.png","data/en_key_92.png","data/en_key_91.png");
	_pKey0 = new CButton("data/en_key_01.png","data/en_key_02.png","data/en_key_01.png");


	_pKeyA = new CButton("data/en_key_a1.png","data/en_key_a2.png","data/en_key_a1.png");
	_pKeyB = new CButton("data/en_key_b1.png","data/en_key_b2.png","data/en_key_b1.png");
	_pKeyC = new CButton("data/en_key_c1.png","data/en_key_c2.png","data/en_key_c1.png");
	_pKeyD = new CButton("data/en_key_d1.png","data/en_key_d2.png","data/en_key_d1.png");
	_pKeyE = new CButton("data/en_key_e1.png","data/en_key_e2.png","data/en_key_e1.png");
	_pKeyF = new CButton("data/en_key_f1.png","data/en_key_f2.png","data/en_key_f1.png");
	_pKeyG = new CButton("data/en_key_g1.png","data/en_key_g2.png","data/en_key_g1.png");
	_pKeyH = new CButton("data/en_key_h1.png","data/en_key_h2.png","data/en_key_h1.png");
	_pKeyI = new CButton("data/en_key_i1.png","data/en_key_i2.png","data/en_key_i1.png");
	_pKeyJ = new CButton("data/en_key_j1.png","data/en_key_j2.png","data/en_key_j1.png");
	_pKeyK = new CButton("data/en_key_k1.png","data/en_key_k2.png","data/en_key_k1.png");
	_pKeyL = new CButton("data/en_key_l1.png","data/en_key_l2.png","data/en_key_l1.png");
	_pKeyM = new CButton("data/en_key_m1.png","data/en_key_m2.png","data/en_key_m1.png");
	_pKeyN = new CButton("data/en_key_n1.png","data/en_key_n2.png","data/en_key_n1.png");
	_pKeyO = new CButton("data/en_key_o1.png","data/en_key_o2.png","data/en_key_o1.png");
	_pKeyP = new CButton("data/en_key_p1.png","data/en_key_p2.png","data/en_key_p1.png");
	_pKeyQ = new CButton("data/en_key_q1.png","data/en_key_q2.png","data/en_key_q1.png");
	_pKeyR = new CButton("data/en_key_r1.png","data/en_key_r2.png","data/en_key_r1.png");
	_pKeyS = new CButton("data/en_key_s1.png","data/en_key_s2.png","data/en_key_s1.png");
	_pKeyT = new CButton("data/en_key_t1.png","data/en_key_t2.png","data/en_key_t1.png");
	_pKeyU = new CButton("data/en_key_u1.png","data/en_key_u2.png","data/en_key_u1.png");
	_pKeyV = new CButton("data/en_key_v1.png","data/en_key_v2.png","data/en_key_v1.png");
	_pKeyW = new CButton("data/en_key_w1.png","data/en_key_w2.png","data/en_key_w1.png");
	_pKeyX = new CButton("data/en_key_x1.png","data/en_key_x2.png","data/en_key_x1.png");
	_pKeyY = new CButton("data/en_key_y1.png","data/en_key_y2.png","data/en_key_y1.png");
	_pKeyZ = new CButton("data/en_key_z1.png","data/en_key_z2.png","data/en_key_z1.png");

	_pKeySPACE = new CButton("data/en_key_space1.png","data/en_key_space2.png","data/en_key_space1.png");
	_pKeyDELETE = new CButton("data/en_key_delete1.png","data/en_key_delete2.png","data/en_key_delete1.png");
	_pKeyENTER = new CButton("data/en_key_enter1.png","data/en_key_enter2.png","data/en_key_enter1.png");

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
