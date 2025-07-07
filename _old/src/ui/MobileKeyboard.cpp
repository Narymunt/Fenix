#include "MobileKeyboard.h"

CMobileKeyboard::CMobileKeyboard(char cLanguage) :
	_a(0), _b(0), _c(0), _d(0), _e(0), _f(0), _g(0), _h(0), _i(0), _j(0), _k(0), _l(0), _m(0), _n(0),
	_o(0), _p(0), _q(0), _r(0), _s(0), _t(0), _u(0), _v(0), _w(0), _x(0), _y(0), _z(0),
	_0(0), _1(0), _2(0), _3(0), _4(0), _5(0), _6(0), _7(0), _8(0), _9(0), _space(NULL), _delete(NULL), _enter(NULL),
	_language(cLanguage), _state(0)
{

}

CMobileKeyboard::~CMobileKeyboard()
{
	_state = 0;
	close();
}

void CMobileKeyboard::open(CScreen *pScreen)
{
	_state = 0;
	
	_1 = new CButton(pScreen,"BUTTON_KEY_1");
	_2 = new CButton(pScreen,"BUTTON_KEY_2");
	_3 = new CButton(pScreen,"BUTTON_KEY_3");
	_4 = new CButton(pScreen,"BUTTON_KEY_4");
	_5 = new CButton(pScreen,"BUTTON_KEY_5");
	_6 = new CButton(pScreen,"BUTTON_KEY_6");
	_7 = new CButton(pScreen,"BUTTON_KEY_7");
	_8 = new CButton(pScreen,"BUTTON_KEY_8");
	_9 = new CButton(pScreen,"BUTTON_KEY_9");
	_0 = new CButton(pScreen,"BUTTON_KEY_0");

	_a = new CButton(pScreen,"BUTTON_KEY_A");
	_b = new CButton(pScreen,"BUTTON_KEY_B");
	_c = new CButton(pScreen,"BUTTON_KEY_C");
	_d = new CButton(pScreen,"BUTTON_KEY_D");
	_e = new CButton(pScreen,"BUTTON_KEY_E");
	_f = new CButton(pScreen,"BUTTON_KEY_F");
	_g = new CButton(pScreen,"BUTTON_KEY_G");
	_h = new CButton(pScreen,"BUTTON_KEY_H");
	_i = new CButton(pScreen,"BUTTON_KEY_I");
	_j = new CButton(pScreen,"BUTTON_KEY_J");
	_k = new CButton(pScreen,"BUTTON_KEY_K");
	_l = new CButton(pScreen,"BUTTON_KEY_L");
	_m = new CButton(pScreen,"BUTTON_KEY_M");
	_n = new CButton(pScreen,"BUTTON_KEY_N");
	_o = new CButton(pScreen,"BUTTON_KEY_O");
	_p = new CButton(pScreen,"BUTTON_KEY_P");
	_q = new CButton(pScreen,"BUTTON_KEY_Q");
	_r = new CButton(pScreen,"BUTTON_KEY_R");
	_s = new CButton(pScreen,"BUTTON_KEY_S");
	_t = new CButton(pScreen,"BUTTON_KEY_T");
	_u = new CButton(pScreen,"BUTTON_KEY_U");
	_v = new CButton(pScreen,"BUTTON_KEY_V");
	_w = new CButton(pScreen,"BUTTON_KEY_W");
	_x = new CButton(pScreen,"BUTTON_KEY_X");
	_y = new CButton(pScreen,"BUTTON_KEY_Y");
	_z = new CButton(pScreen,"BUTTON_KEY_Z");

	_space = new CButton(pScreen,"BUTTON_KEY_SPACE");
	_delete = new CButton(pScreen,"BUTTON_KEY_DELETE");
	_enter = new CButton(pScreen,"BUTTON_KEY_ENTER");

	_screen = pScreen;
	_isOpen= true ;
}

void CMobileKeyboard::close()
{
	SafeDelete(_1); SafeDelete(_2); SafeDelete(_3);
	SafeDelete(_4); SafeDelete(_5); SafeDelete(_6);
	SafeDelete(_7); SafeDelete(_8); SafeDelete(_9);
	SafeDelete(_0);

	SafeDelete(_a);	SafeDelete(_b);	SafeDelete(_c);
	SafeDelete(_d);	SafeDelete(_e);	SafeDelete(_f);
	SafeDelete(_g);	SafeDelete(_h);	SafeDelete(_i);
	SafeDelete(_j);	SafeDelete(_k);	SafeDelete(_l);
	SafeDelete(_m);	SafeDelete(_n);	SafeDelete(_o);
	SafeDelete(_p);	SafeDelete(_q);	SafeDelete(_r);
	SafeDelete(_s);	SafeDelete(_t);	SafeDelete(_u);
	SafeDelete(_v);	SafeDelete(_w);	SafeDelete(_x);
	SafeDelete(_y);	SafeDelete(_z);	

	SafeDelete(_space);
	SafeDelete(_delete);
	SafeDelete(_enter);

	_isOpen = false;
}

unsigned char CMobileKeyboard::render(unsigned long ulTimer, CMouse *pMouse)
{
	int y1,y2, x1, iStepX, iSize;
	unsigned char cKey;

	cKey = KEY_NONE;

	// pierwszy rzad

	if (_screen->_isSDS)
	{
		iSize = 64;
		y1 = 384; y2 = 384 + iSize;
		x1 = 32; iStepX = 96;
	}
	else if (_screen->_isSDW)
	{
		iSize = 64;
		y1 = 384; y2 = 384 + iSize;
		x1 = 64; iStepX = 128;
	}
	else if (_screen->_isHDW)
	{
		iSize = 128;
		y1 = 384; y2 = 384 + iSize + 64;
		x1 = 32; iStepX = 128+64;
	}
	else if (_screen->_isHDS)
	{
		iSize = 128;
		y1 = 700; y2 = 700 + iSize;
		x1 = 64; iStepX = 256;
	}

	_1->position(x1 + (iStepX * 0), y1); _1->setHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_1->render(pMouse) == ON_LEFT) cKey = KEY_1;
	_2->position(x1 + (iStepX * 1), y1); _2->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_2->render(pMouse) == ON_LEFT) cKey = KEY_2;
	_3->position(x1 + (iStepX * 2), y1); _3->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_3->render(pMouse) == ON_LEFT) cKey = KEY_3;
	_4->position(x1 + (iStepX * 3), y1); _4->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_4->render(pMouse) == ON_LEFT) cKey = KEY_4;
	_5->position(x1 + (iStepX * 4), y1); _5->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_5->render(pMouse) == ON_LEFT) cKey = KEY_5;
	_6->position(x1 + (iStepX * 5), y1); _6->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_6->render(pMouse) == ON_LEFT) cKey = KEY_6;
	_7->position(x1 + (iStepX * 6), y1); _7->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_7->render(pMouse) == ON_LEFT) cKey = KEY_7;
	_8->position(x1 + (iStepX * 7), y1); _8->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_8->render(pMouse) == ON_LEFT) cKey = KEY_8;
	_9->position(x1 + (iStepX * 8), y1); _9->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_9->render(pMouse) == ON_LEFT) cKey = KEY_9;
	_0->position(x1 + (iStepX * 9), y1); _0->setHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_0->render(pMouse) == ON_LEFT) cKey = KEY_0;
	
	// drugi rzad

	if (_screen->_isSDS)
	{
		iSize = 64;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
	}
	else if (_screen->_isSDW )
	{
		iSize = 64;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
	}
	else if (_screen->_isHDW)
	{
		iSize = 128;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
	}
	else if (_screen->_isHDS)
	{
		iSize = 128;
		y1 = 700 + iSize + 32;
		y2 = 700 + iSize + iSize + 32;
	}

	_q->position(x1 + (iStepX * 0), y1); _q->setHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_q->render(pMouse) == ON_LEFT) cKey = KEY_Q;
	_w->position(x1 + (iStepX * 1), y1); _w->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_w->render(pMouse) == ON_LEFT) cKey = KEY_W;
	_e->position(x1 + (iStepX * 2), y1); _e->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_e->render(pMouse) == ON_LEFT) cKey = KEY_E;
	_r->position(x1 + (iStepX * 3), y1); _r->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_r->render(pMouse) == ON_LEFT) cKey = KEY_R;
	_t->position(x1 + (iStepX * 4), y1); _t->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_t->render(pMouse) == ON_LEFT) cKey = KEY_T;
	_y->position(x1 + (iStepX * 5), y1); _y->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_y->render(pMouse) == ON_LEFT) cKey = KEY_Y;
	_u->position(x1 + (iStepX * 6), y1); _u->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_u->render(pMouse) == ON_LEFT) cKey = KEY_U;
	_i->position(x1 + (iStepX * 7), y1); _i->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_i->render(pMouse) == ON_LEFT) cKey = KEY_I;
	_o->position(x1 + (iStepX * 8), y1); _o->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_o->render(pMouse) == ON_LEFT) cKey = KEY_O;
	_p->position(x1 + (iStepX * 9), y1); _p->setHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_p->render(pMouse) == ON_LEFT) cKey = KEY_P;

	// trzeci rzad 

	if (_screen->_isSDS)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
	}
	else if (_screen->_isSDW)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
	}
	else if (_screen->_isHDW)
	{
		iSize = 128;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
	}
	else if (_screen->_isHDS)
	{
		iSize = 128;
		y1 = 700 + iSize + 32 + iSize + 32;
		y2 = 700 + iSize + iSize + 32 + iSize + 32;
	}

	_a->position(x1 + (iStepX * 0), y1); _a->setHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_a->render(pMouse) == ON_LEFT) cKey = KEY_A;
	_s->position(x1 + (iStepX * 1), y1); _s->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_s->render(pMouse) == ON_LEFT) cKey = KEY_S;
	_d->position(x1 + (iStepX * 2), y1); _d->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_d->render(pMouse) == ON_LEFT) cKey = KEY_D;
	_f->position(x1 + (iStepX * 3), y1); _f->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_f->render(pMouse) == ON_LEFT) cKey = KEY_F;
	_g->position(x1 + (iStepX * 4), y1); _g->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_g->render(pMouse) == ON_LEFT) cKey = KEY_G;
	_h->position(x1 + (iStepX * 5), y1); _h->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_h->render(pMouse) == ON_LEFT) cKey = KEY_H;
	_j->position(x1 + (iStepX * 6), y1); _j->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_j->render(pMouse) == ON_LEFT) cKey = KEY_J;
	_k->position(x1 + (iStepX * 7), y1); _k->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_k->render(pMouse) == ON_LEFT) cKey = KEY_K;
	_l->position(x1 + (iStepX * 8), y1); _l->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_l->render(pMouse) == ON_LEFT) cKey = KEY_L;
	_enter->position(x1 + (iStepX * 9), y1); _enter->setHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_enter->render(pMouse) == ON_LEFT) cKey = KEY_ENTER;

	// czwarty rzad

	if (_screen->_isSDS)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}
	else if (_screen->_isSDW)
	{
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}
	else if (_screen->_isHDW)
	{
		iSize = 128;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}
	else if (_screen->_isHDS)
	{
		iSize = 128;
		y1 = 700 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 700 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
	}

	_z->position(x1 + (iStepX * 1), y1); _z->setHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_z->render(pMouse) == ON_LEFT) cKey = KEY_Z;
	_x->position(x1 + (iStepX * 2), y1); _x->setHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_x->render(pMouse) == ON_LEFT) cKey = KEY_X;
	_c->position(x1 + (iStepX * 3), y1); _c->setHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_c->render(pMouse) == ON_LEFT) cKey = KEY_C;
	_v->position(x1 + (iStepX * 4), y1); _v->setHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_v->render(pMouse) == ON_LEFT) cKey = KEY_V;
	_b->position(x1 + (iStepX * 5), y1); _b->setHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_b->render(pMouse) == ON_LEFT) cKey = KEY_B;
	_n->position(x1 + (iStepX * 6), y1); _n->setHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_n->render(pMouse) == ON_LEFT) cKey = KEY_N;
	_m->position(x1 + (iStepX * 7), y1); _m->setHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_m->render(pMouse) == ON_LEFT) cKey = KEY_M;
	_delete->position(x1 + (iStepX * 8), y1); _delete->setHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_delete->render(pMouse) == ON_LEFT) cKey = KEY_DELETE;

	return cKey;
}
