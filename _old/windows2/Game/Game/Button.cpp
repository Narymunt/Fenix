#include "Button.h"

#pragma warning(disable:4996)

// tworzy przycisk na podstawie wszystkich parametrow ze skryptow

CButton::CButton(CScreen *pScreen, char cName[])
{
	FILE	*plik;
	char linia[1024];
	bool isLoad = false;
	int x,y,x1,y1,x2,y2;

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
		printf("ERROR: no script file %s\n",SCRIPT_FILE);

	while (strcmp(linia,"<END>"))
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<BUTTON>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
			UpOnly(linia);

			if (!strcmp(linia,cName))	// to ten przycisk ? 
			{
				fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - static sprite
				UpOnly(linia);
				_pImage = new CSprite(pScreen,linia);

				fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - on over sprite
				UpOnly(linia);
				_pOnButton = new CSprite(pScreen,linia);

				fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - on over sprite
				UpOnly(linia);
				_pClicked = new CSprite(pScreen,linia);

				fscanf(plik,"%d %d %d %d %d %d\n",&x,&y,&x1,&y1,&x2,&y2);	// 1024x768

				if (pScreen->iSizeX()!=x || pScreen->iSizeY()!=y)
					fscanf(plik,"%d %d %d %d %d %d\n",&x,&y,&x1,&y1,&x2,&y2);	// 1366x768

				if (pScreen->iSizeX()!=x || pScreen->iSizeY()!=y)
					fscanf(plik,"%d %d %d %d %d %d\n",&x,&y,&x1,&y1,&x2,&y2);	// 1920x1080

				if (pScreen->iSizeX()!=x || pScreen->iSizeY()!=y)
					fscanf(plik,"%d %d %d %d %d %d\n",&x,&y,&x1,&y1,&x2,&y2);	// 2048x1536

				SetHotCoords(x1,y1,x2,y2);

				isLoad = true;
			} // if !strcmp
		} // if button
	} // while end

	if (!isLoad)
		printf("ERROR: unable to find button %d in script!\n",cName);

	fclose(plik);

}

// create 3 bitmap based button

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[])
{
	_pClicked = new CSprite(clicked_name);
	_pOnButton = new CSprite(onButton_name);
	_pImage = new CSprite(m_pImage_name);

	// bez hotx i hoty

	_lXStart = 0;
	_lYStart = 0;
	_lXEnd = 0; 
	_lYEnd = 0;

}

// create and rescale

CButton::CButton(char clicked_name[], char onButton_name[], char m_pImage_name[], int x1, int y1, int x2, int y2)
{
	_pClicked = new CSprite(clicked_name);
	_pClicked->Resize(x1, y1, x2, y2);
	
	_pOnButton = new CSprite(onButton_name);
	_pOnButton->Resize(x1, y1, x2, y2);
	
	_pImage = new CSprite(m_pImage_name);
	_pImage->Resize(x1, y1, x2, y2);

	// bez hotx i hoty

	_lXStart = x1;
	_lYStart = y1;
	_lXEnd = x2; 
	_lYEnd = y2;

}

// destructor, release graphics 

CButton::~CButton()
{
	SafeDelete(_pClicked);
	SafeDelete(_pImage);
	SafeDelete(_pOnButton);
}

// check mouse state and draw 

int CButton::Render(CMouse *pMouse)
{

	// check hot coords 

	if ((pMouse->fMouseX()>_lXStart)&&(pMouse->fMouseX()<_lXEnd)&&(pMouse->fMouseY()>_lYStart)&&(pMouse->fMouseY()<_lYEnd))
	{
		if (pMouse->isRight())
		{
			_pClicked->Render();	
			return ON_RIGHT;
		}

		if (pMouse->isLeft())
		{
			_pClicked->Render();
			return ON_LEFT;
		}
		
		if (pMouse->isCenter())
		{
			_pClicked->Render();
			return ON_CENTER;
		}

		_pOnButton->Render();
		return ON_OVER;
	}

	_pImage->Render();
	return 0;

}

// setup button position 

void CButton::SetPosition(long lX, long lY)
{
	_pClicked->Position((float)lX,(float)lY);
	_pImage->Position((float)lX,(float)lY);
	_pOnButton->Position((float)lX,(float)lY);
}

// set hot coords for button

void CButton::SetHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd)
{
	_lXStart = lXStart;
	_lYStart = lYStart;
	_lXEnd = lXEnd;
	_lYEnd = lYEnd;

	_pClicked->Position((float)lXStart,(float)lYStart);
	_pImage->Position((float)lXStart,(float)lYStart);
	_pOnButton->Position((float)lXStart,(float)lYStart);

}

//=== end ===