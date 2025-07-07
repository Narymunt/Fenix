// main class

#include "eLevelMenu.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eLevelMenu::eLevelMenu() :
_pExitButton(NULL), _pBackground(NULL), _ucCurrentLevel(1)
{
    _isActive = false;
}

eLevelMenu::~eLevelMenu()
{
    Close();
}

void eLevelMenu::Open(CScreen *pScreen)
{
    CProfile *pUserProfile;
    
    _iOS = pScreen->iOS();

    _pBackground = new CSprite((char*)"e_levelmenu",_iOS);

    _pLevel[0] = new CButton((char*)"level01_click.png",(char*)"level01_over.png",(char*)"level01.png",0,0,128,128);
    _pLevel[1] = new CButton((char*)"level02_click.png",(char*)"level02_over.png",(char*)"level02.png",0,0,128,128);
    _pLevel[2] = new CButton((char*)"level03_click.png",(char*)"level03_over.png",(char*)"level03.png",0,0,128,128);
    _pLevel[3] = new CButton((char*)"level04_click.png",(char*)"level04_over.png",(char*)"level04.png",0,0,128,128);
    _pLevel[4] = new CButton((char*)"level05_click.png",(char*)"level05_over.png",(char*)"level05.png",0,0,128,128);
    _pLevel[5] = new CButton((char*)"level06_click.png",(char*)"level06_over.png",(char*)"level06.png",0,0,128,128);
    _pLevel[6] = new CButton((char*)"level07_click.png",(char*)"level07_over.png",(char*)"level07.png",0,0,128,128);
    
    if (_iOS == IPAD_HD)
    {
        _pExitButton = new CButton((char*)"menu_over256.png",(char*)"menu_click256.png",(char*)"menu_static256.png",0,0,256,256);
        _pExitButton->SetPosition(1050-128,1170);
        _pExitButton->SetHotCoords(1050-128,1170,1050+128,1170+256);
        
        _pLevel[0]->SetPosition(520,900); // ameryka poludniowa
        _pLevel[0]->SetHotCoords(520,900,520+128,900+128);
        
        _pLevel[1]->SetPosition(350,400); // ameryka polnocna
        _pLevel[1]->SetHotCoords(350,400,350+128,400+128);
        
        _pLevel[2]->SetPosition(900,350); // europa
        _pLevel[2]->SetHotCoords(900,350,900+128,350+128);
        
        _pLevel[3]->SetPosition(1500,500); // azja
        _pLevel[3]->SetHotCoords(1500,500,1500+128,500+128);
        
        _pLevel[4]->SetPosition(1650,850); // australia
        _pLevel[4]->SetHotCoords(1650,850,1650+128,850+128);
        
        _pLevel[5]->SetPosition(1000,700); // afryka
        _pLevel[5]->SetHotCoords(1000,700,1000+128,700+128);
        
        _pLevel[6]->SetPosition(650,550); // atlantyda
        _pLevel[6]->SetHotCoords(650,550,650+128,550+128);
        
    }
    else if (_iOS == IPAD)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(512-64,580);
        _pExitButton->SetHotCoords(512-64,580,512+64,580+128);
        
        _pLevel[0]->SetPosition(240,450); // ameryka poludniowa
        _pLevel[0]->SetHotCoords(240,450,240+128,450+128);
        
        _pLevel[1]->SetPosition(150,170); // ameryka polnocna
        _pLevel[1]->SetHotCoords(150,170,150+128,170+128);
        
        _pLevel[2]->SetPosition(410,130); // europa
        _pLevel[2]->SetHotCoords(410,130,410+128,130+128);
        
        _pLevel[3]->SetPosition(750,200); // azja
        _pLevel[3]->SetHotCoords(750,200,750+128,200+128);
        
        _pLevel[4]->SetPosition(800,400); // australia
        _pLevel[4]->SetHotCoords(800,400,800+128,400+128);
        
        _pLevel[5]->SetPosition(450,350); // afryka
        _pLevel[5]->SetHotCoords(450,350,450+128,350+128);
        
        _pLevel[6]->SetPosition(300,250); // atlantyda
        _pLevel[6]->SetHotCoords(300,250,300+128,250+128);
    }
    else if (_iOS == IPHONE4)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(480-64,480);
        _pExitButton->SetHotCoords(480-64,480,480+64,480+128);
        
        _pLevel[0]->SetPosition(270,350); // ameryka poludniowa
        _pLevel[0]->SetHotCoords(270,350,270+128,350+128);
        
        _pLevel[1]->SetPosition(200,130); // ameryka polnocna
        _pLevel[1]->SetHotCoords(200,130,200+128,130+128);
        
        _pLevel[2]->SetPosition(410,100); // europa
        _pLevel[2]->SetHotCoords(410,100,410+128,100+128);
        
        _pLevel[3]->SetPosition(600,150); // azja
        _pLevel[3]->SetHotCoords(600,150,600+128,150+128);
        
        _pLevel[4]->SetPosition(700,350); // australia
        _pLevel[4]->SetHotCoords(700,350,700+128,350+128);
        
        _pLevel[5]->SetPosition(420,300);
        _pLevel[5]->SetHotCoords(420,300,420+128,300+128);
        
        _pLevel[6]->SetPosition(320,200);
        _pLevel[6]->SetHotCoords(320,200,320+128,200+128);
        
    }
    else if (_iOS == IPHONE5)
    {
        _pExitButton = new CButton((char*)"menu_over.png",(char*)"menu_click.png",(char*)"menu_static.png",0,0,128,128);
        _pExitButton->SetPosition(568-64,480);
        _pExitButton->SetHotCoords(568-64,480,568+64,480+128);

        _pLevel[0]->SetPosition(290,350); // ameryka poludniowa
        _pLevel[0]->SetHotCoords(290,350,290+128,350+128);
        
        _pLevel[1]->SetPosition(220,130); // ameryka polnocna
        _pLevel[1]->SetHotCoords(220,130,220+128,130+128);
        
        _pLevel[2]->SetPosition(470,100); // europa
        _pLevel[2]->SetHotCoords(470,100,470+128,100+128);
        
        _pLevel[3]->SetPosition(750,150); // azja
        _pLevel[3]->SetHotCoords(750,150,750+128,150+128);
        
        _pLevel[4]->SetPosition(800,350); // australia
        _pLevel[4]->SetHotCoords(800,350,800+128,350+128);
        
        _pLevel[5]->SetPosition(520,300); // afryka
        _pLevel[5]->SetHotCoords(520,300,520+128,300+128);
        
        _pLevel[6]->SetPosition(360,200); // atlantyda
        _pLevel[6]->SetHotCoords(360,200,360+128,200+128);
    
    }
    
    // pobierz informacje o aktualnie dostępnych etapach
    
	pUserProfile = new CProfile();
	pUserProfile->bLoad();
    
	_ulMap = pUserProfile->ulMap();
    
	delete pUserProfile;
    
    _ulTimerStart = 0;
    _isActive = true;
    _isMouseLock = true;
}

void eLevelMenu::Close(void)
{
    SafeDelete(_pBackground);
    SafeDelete(_pExitButton);
    
    for (int i=0; i<7; i++)
        SafeDelete(_pLevel[i]);
    
    _isActive = false;
    _isMouseLock = true;
}

int eLevelMenu::Render(CTouch *pTouch, unsigned long ulTimer)
{
    int iReturn=0;
    
    if (!pTouch->isPressed())
        _isMouseLock = false;
    
	if (_ulTimerStart == 0)
		_ulTimerStart = ulTimer;

    _pBackground->Render();

	for (int i=0; i<7; i++)
	{
		if (i<=_ulMap)	// czy ten etap jest dostepny
		{
			if (_pLevel[i]->Render(pTouch)==ON_LEFT && !_isMouseLock)
			{
				_ucCurrentLevel = i+1;
                
				if (!_isMouseLock)
					iReturn = i+1;
			}
		}
	}
    
    if (_pExitButton->Render(pTouch)==ON_LEFT && !_isMouseLock)
    {
        return -1;
    }   
    
    return iReturn;   // nie rob nic
}

