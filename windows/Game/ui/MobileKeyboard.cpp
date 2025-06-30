#include "MobileKeyboard.h"

MobileKeyboard::MobileKeyboard(char cLanguage) :
	_a(0), _b(0), _c(0), _d(0), _e(0), _f(0), _g(0), _h(0), _i(0), _j(0), _k(0), _l(0), _m(0), _n(0),
	_o(0), _p(0), _q(0), _r(0), _s(0), _t(0), _u(0), _v(0), _w(0), _x(0), _y(0), _z(0),
	_0(0), _1(0), _2(0), _3(0), _4(0), _5(0), _6(0), _7(0), _8(0), _9(0), _space(NULL), _delete(NULL), _enter(NULL),
	_language(cLanguage), _state(0)
{

}

MobileKeyboard::~MobileKeyboard()
{
	_state = 0;
	close();
}

void MobileKeyboard::open(void)
{
	_state = 0;
	
	_1 = new Button((char*)"BUTTON_KEY_1", (char*)"BUTTON_KEY_1");
	_2 = new Button((char*)"BUTTON_KEY_2", (char*)"BUTTON_KEY_1");
	_3 = new Button((char*)"BUTTON_KEY_3", (char*)"BUTTON_KEY_1");
	_4 = new Button((char*)"BUTTON_KEY_4", (char*)"BUTTON_KEY_1");
	_5 = new Button((char*)"BUTTON_KEY_5", (char*)"BUTTON_KEY_1");
	_6 = new Button((char*)"BUTTON_KEY_6", (char*)"BUTTON_KEY_1");
	_7 = new Button((char*)"BUTTON_KEY_7", (char*)"BUTTON_KEY_1");
	_8 = new Button((char*)"BUTTON_KEY_8", (char*)"BUTTON_KEY_1");
	_9 = new Button((char*)"BUTTON_KEY_9", (char*)"BUTTON_KEY_1");
	_0 = new Button((char*)"BUTTON_KEY_0", (char*)"BUTTON_KEY_1");

	_a = new Button((char*)"BUTTON_KEY_A", (char*)"BUTTON_KEY_1");
	_b = new Button((char*)"BUTTON_KEY_B", (char*)"BUTTON_KEY_1");
	_c = new Button((char*)"BUTTON_KEY_C", (char*)"BUTTON_KEY_1");
	_d = new Button((char*)"BUTTON_KEY_D", (char*)"BUTTON_KEY_1");
	_e = new Button((char*)"BUTTON_KEY_E", (char*)"BUTTON_KEY_1");
	_f = new Button((char*)"BUTTON_KEY_F", (char*)"BUTTON_KEY_1");
	_g = new Button((char*)"BUTTON_KEY_G", (char*)"BUTTON_KEY_1");
	_h = new Button((char*)"BUTTON_KEY_H", (char*)"BUTTON_KEY_1");
	_i = new Button((char*)"BUTTON_KEY_I", (char*)"BUTTON_KEY_1");
	_j = new Button((char*)"BUTTON_KEY_J", (char*)"BUTTON_KEY_1");
	_k = new Button((char*)"BUTTON_KEY_K", (char*)"BUTTON_KEY_1");
	_l = new Button((char*)"BUTTON_KEY_L", (char*)"BUTTON_KEY_1");
	_m = new Button((char*)"BUTTON_KEY_M", (char*)"BUTTON_KEY_1");
	_n = new Button((char*)"BUTTON_KEY_N", (char*)"BUTTON_KEY_1");
	_o = new Button((char*)"BUTTON_KEY_O", (char*)"BUTTON_KEY_1");
	_p = new Button((char*)"BUTTON_KEY_P", (char*)"BUTTON_KEY_1");
	_q = new Button((char*)"BUTTON_KEY_Q", (char*)"BUTTON_KEY_1");
	_r = new Button((char*)"BUTTON_KEY_R", (char*)"BUTTON_KEY_1");
	_s = new Button((char*)"BUTTON_KEY_S", (char*)"BUTTON_KEY_1");
	_t = new Button((char*)"BUTTON_KEY_T", (char*)"BUTTON_KEY_1");
	_u = new Button((char*)"BUTTON_KEY_U", (char*)"BUTTON_KEY_1");
	_v = new Button((char*)"BUTTON_KEY_V", (char*)"BUTTON_KEY_1");
	_w = new Button((char*)"BUTTON_KEY_W", (char*)"BUTTON_KEY_1");
	_x = new Button((char*)"BUTTON_KEY_X", (char*)"BUTTON_KEY_1");
	_y = new Button((char*)"BUTTON_KEY_Y", (char*)"BUTTON_KEY_1");
	_z = new Button((char*)"BUTTON_KEY_Z", (char*)"BUTTON_KEY_1");

	_space = new Button((char*)"BUTTON_KEY_SPACE", (char*)"BUTTON_KEY_1");
	_delete = new Button((char*)"BUTTON_KEY_DELETE", (char*)"BUTTON_KEY_1");
	_enter = new Button((char*)"BUTTON_KEY_ENTER", (char*)"BUTTON_KEY_1");

	_isOpen= true ;
}

void MobileKeyboard::close()
{
	safeDelete(_1); safeDelete(_2); safeDelete(_3);
	safeDelete(_4); safeDelete(_5); safeDelete(_6);
	safeDelete(_7); safeDelete(_8); safeDelete(_9);
	safeDelete(_0);

	safeDelete(_a);	safeDelete(_b);	safeDelete(_c);
	safeDelete(_d);	safeDelete(_e);	safeDelete(_f);
	safeDelete(_g);	safeDelete(_h);	safeDelete(_i);
	safeDelete(_j);	safeDelete(_k);	safeDelete(_l);
	safeDelete(_m);	safeDelete(_n);	safeDelete(_o);
	safeDelete(_p);	safeDelete(_q);	safeDelete(_r);
	safeDelete(_s);	safeDelete(_t);	safeDelete(_u);
	safeDelete(_v);	safeDelete(_w);	safeDelete(_x);
	safeDelete(_y);	safeDelete(_z);	

	safeDelete(_space);
	safeDelete(_delete);
	safeDelete(_enter);

	_isOpen = false;
}

unsigned char MobileKeyboard::render(unsigned long ulTimer, Mouse *pMouse)
{
	int y1,y2, x1, iStepX, iSize;
	unsigned char cKey;

	cKey = KEY_NONE;

	// pierwszy rzad - tylko 1920x1080 HDW

	iSize = 128;
	y1 = 384; y2 = 384 + iSize + 64;
	x1 = 32; iStepX = 128+64;

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
	
	// drugi rzad - tylko HDW 1920x1080

	iSize = 128;
	y1 = 384 + iSize + 32;
	y2 = 384 + iSize + iSize + 32;

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

	// trzeci rzad  - tylko HDW 1920x1080

	iSize = 128;
	y1 = 384 + iSize + 32 + iSize + 32;
	y2 = 384 + iSize + iSize + 32 + iSize + 32;

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

	// czwarty rzad - tylko HDW 1920x1080

	iSize = 128;
	y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
	y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;

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
