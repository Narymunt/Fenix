/**
   Animation.cpp

   @author Jaros³aw N. Ro¿yñski
   @version 2014-08-27
   
*/

#include "Animation.h"

#pragma warning(disable : 4996)	// sprintf unsafe

/**
   Class construktor

   @param cFile plik skryptu z którego inicjalizujemy

   @return none
*/

CAnimation::CAnimation(char cFile[]) :
   _iFrameCount(0)
{
	
}

/**
   Class construktor, nie wczytujemy jeszcze danych
   
   @param cFile plik skryptu z którego inicjalizujemy
   @param iFrameCount ile klatek wczytaæ
   @param cExt rozszerzenie pliku np. "png"

   @return none
*/

CAnimation::CAnimation(char cFile[], int iFrameCount, char cExt[]) :
   _iFrameCount(iFrameCount)
{
	strcpy(_cFile,cFile);	// zapamietujemy nazwe pliku i rozszerzenie
	strcpy(_cExt,cExt);
}

/**
   Class construktor, wczytujemy wszystkie dane ze skryptu
   
   @param pScreen wskaŸnik do ekranu
   @param cObjectName nazwa obiektu w skrypcie

   @return none
*/

CAnimation::CAnimation(CScreen *pScreen, char cObjectName[]) 
{
	FILE	*plik;
	char	linia[1024];
	int	x,y;	

	memset(linia,0,900);

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
	   printf("ERROR: no script file %s\n",SCRIPT_FILE);

	while (strcmp(linia,"<END>"))
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<ANIMATION>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
			UpOnly(linia);

			fscanf(plik,"%d %d\n",&x,&y);	// wczytaj parametry ekranu

			if (!strcmp(linia,cObjectName) && pScreen->iSizeX()==x && pScreen->iSizeY()==y)	// to jest wlasciwy obiekt
			{
				fscanf(plik,"%s\n",&_cFile);	// wczytaj nazwe pliku
				fscanf(plik,"%d\n",&_iFrameCount);	// liczba klatek
				fscanf(plik,"%s\n",&_cExt);	// rozszerzenie
			}  
		} // if animation
	} // while <end>

	fclose(plik);

	Open(pScreen);	// tutaj wczytujemy dane
}

/**
   Destruktor, kasujemy dane i zamykamy status
   
   @param pScreen wskaŸnik do ekranu
   @param cObjectName nazwa obiektu w skrypcie

   @return none
*/

CAnimation::~CAnimation()
{
	Close();
}

/**
   Wczytanie danych na podstawie wczeœniej ustawionych parametrów
   
   @param pScreen wskaŸnik do ekranu

   @return none
*/

void CAnimation::Open(CScreen *pScreen)
{
	char cBuffer[256];	// tutaj wygenerujemy nazwe pliku

	for (int i=0; i<_iFrameCount; i++)
	{
		if (_iFrameCount>99) // jezeli klatek jest minimum 100 to stosujemy 3-cyfrowa numeracje
		{
			if (i<10)
				sprintf(cBuffer,"%s00%d.%s",_cFile,i,_cExt);

			if (i>9 && i <100)
				sprintf(cBuffer,"%s0%d.%s",_cFile,i,_cExt);

			if (i>99)
				sprintf_s(cBuffer,"%s%d.%s",_cFile,i,_cExt);
		}

		if (_iFrameCount<100) // jezeli klatek jest minimum 100 to stosujemy 3-cyfrowa numeracje
		{
			if (i<10)
				sprintf(cBuffer,"%s0%d.%s",_cFile,i,_cExt);

			if (i>9 && i <100)
				sprintf(cBuffer,"%s%d.%s",_cFile,i,_cExt);
		}
		m_pSprite.push_back(new CSprite(cBuffer, pScreen));
	}
	_isActive = true;
}

/**
   Zwolnij wszystkie dane. 

   @return none
*/

void CAnimation::Close(void)
{
	for (unsigned int i=0; i<m_pSprite.size(); i++)
		delete m_pSprite[i];

	m_pSprite.clear();

	_isActive = false;
}

/**
   Dodajemy klatkê na koniec kolejki
   
   @param cFilename nazwa pliku graficznego

   @return none
*/

void CAnimation::Add(char cFilename[])
{
	m_pSprite.push_back(new CSprite(cFilename));
}

/**
   Renderuj klatkê o podanym numerze
   
   @param iFrame numer klatki 

   @return none
*/

void CAnimation::Render(int iFrame)
{
	if (iFrame>=0 && iFrame < _iFrameCount)
		m_pSprite[iFrame]->Render();
}

/**
   Renderuj klatkê o podanym numerze
   
   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie

   @return none
*/

void CAnimation::Render(int iFrame, int iX, int iY)
{
	if (iFrame>=0 && iFrame<_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Render();
	}
}

/**
   Renderuj klatkê o podanym numerze
   
   @param iFrame numer klatki 
   @param iY wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param alfa przezroczystosc w skali 0-255

   @return none
*/

void CAnimation::Render(int iFrame, int iX, int iY, unsigned char alfa)
{
	if (iFrame>=0 && iFrame<_iFrameCount)
	{
		m_pSprite[iFrame]->fAlfa(alfa);
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Render();
	}
}

/**
   Renderuj klatkê o podanym numerze
   
   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param fScaleX skala X
   @param fScaleY skala Y

   @return none
*/


void CAnimation::Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY)
{
	if (iFrame>=0 && iFrame<_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Scale(fScaleX, fScaleY);
		m_pSprite[iFrame]->Render();
	}
}

/**
   Renderuj klatkê o podanym numerze

   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param fScaleX skala X
   @param fScaleY skala Y
   @param fRotation k¹t obrotu

   @return none
*/


void CAnimation::Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation)
{
	if (iFrame>=0 && iFrame<_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Scale(fScaleX, fScaleY);
		m_pSprite[iFrame]->fRotation(fRotation);
		m_pSprite[iFrame]->Render();
	}
}

/**
   Renderuj klatkê o podanym numerze

   @param iFrame numer klatki 
   @param iX wspolrzedna X na ekranie
   @param iY wspolrzedna Y na ekranie
   @param fScaleX skala X
   @param fScaleY skala Y
   @param fRotation k¹t obrotu
   @param fRotationX punkt obrotu X
   @param fRotationY punkt obrotu Y

   @return none
*/


void CAnimation::Render(int iFrame, int iX, int iY, float fScaleX, float fScaleY, float fRotation, float fRotationX, float fRotationY)
{
	if (iFrame>=0 && iFrame<_iFrameCount)
	{
		m_pSprite[iFrame]->Position((float)iX,(float)iY);
		m_pSprite[iFrame]->Scale(fScaleX, fScaleY);
		m_pSprite[iFrame]->fRotation(fRotation);
		m_pSprite[iFrame]->RenderC();
	}
}

