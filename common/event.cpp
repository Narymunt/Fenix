#include "event.h"
#include "debug.h"

// stworzenie obiektu i ustawienie wskaznikow

CEvent::CEvent()
{
	m_pEventName = (unsigned char*) malloc (256);

	m_uiFrameCount = 0;

	m_pPositionX = NULL;
	m_pPositionY = NULL;

	m_pScaleX = NULL;
	m_pScaleY = NULL;

	m_pRotation = NULL;
	
	m_pRotationX = NULL;
	m_pRotationY = NULL;
	
	m_pFrame = NULL;
}

// usuniecie obiektu i wyzerowanie wskaznikow

CEvent::~CEvent()
{
	if (m_pFrame!=NULL)
	{
		delete m_pFrame;
		m_pFrame = NULL;
	}
	
	if (m_pScaleX!=NULL)
	{
		delete m_pScaleX;
		m_pScaleX = NULL;
	}

	if (m_pScaleY!=NULL)
	{
		delete m_pScaleY;
		m_pScaleY = NULL;
	}

	if (m_pPositionX!=NULL)
	{
		delete m_pPositionX;
		m_pPositionX = NULL;
	}

	if (m_pPositionY!=NULL)
	{
		delete m_pPositionY;
		m_pPositionY = NULL;
	}

	if (m_pRotation!=NULL)
	{
		delete m_pRotation;
		m_pRotation= NULL;
	}
	
	if (m_pRotationX!=NULL)
	{
		delete m_pRotationX;
		m_pRotationX = NULL;
	}

	if (m_pRotationY!=NULL)
	{
		delete m_pRotationY;
		m_pRotationY = NULL;
	}
}

CEvent::CEvent(char cFilename[])
{
	FILE	*plik;
	char	linia[1024];
	int		iCount;

	m_pEventName = (unsigned char*) malloc (256);

	m_pPositionX = NULL;
	m_pPositionY = NULL;

	m_pScaleX = NULL;
	m_pScaleY = NULL;

	m_pRotation = NULL;
	
	m_pRotationX = NULL;
	m_pRotationY = NULL;
	
	m_pFrame = NULL;


	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		fx_debug("ERROR! Brak pliku eventu graficznego!\n");
		return ;
	}

	iCount = 0; 
	
	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
	UpOnly(linia);

	if (strcmp(linia,"<EVENT>"))	// czy to plik track ? 
	{
		fx_debug("ERROR! Uszkodzony plik event!\n");
		return ;
	}

	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - nazwa zdarzenia
	UpOnly(linia);
	strcpy((char*)m_pEventName, linia);

	// wczytujemy elementy

	while (strcmp(linia,"</EVENT>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
		UpOnly(linia);
		iCount++;		
	}

	iCount--;
	iCount>>=3;		// dzielimy przez 8 - tyle parametrów jest w jednej linii

	m_uiFrameCount = iCount;
	
	fclose(plik);

	// teraz wczytujemy
	
	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		fx_debug("ERROR! Brak pliku eventu graficznego!\n");
		return ;
	}
	
	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - <EVENT>
	UpOnly(linia);
	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - nazwa zdarzenia
	UpOnly(linia);

	// alokacja pamieci na tablice

	m_pFrame = (unsigned int*) malloc(1+m_uiFrameCount*sizeof(unsigned int));
	
	m_pScaleX = (float*) malloc(1+m_uiFrameCount*sizeof(float));
	m_pScaleY = (float*) malloc(1+m_uiFrameCount*sizeof(float));
	
	m_pPositionX= (int*) malloc(1+m_uiFrameCount*sizeof(int));
	m_pPositionY= (int*) malloc(1+m_uiFrameCount*sizeof(int));

	m_pRotation = (float*) malloc(1+m_uiFrameCount*sizeof(float));
	
	m_pRotationX= (int*) malloc(1+m_uiFrameCount*sizeof(int));
	m_pRotationY= (int*) malloc(1+m_uiFrameCount*sizeof(int));
	
	// [numer klatki] [scale_x] [scale_y] [x] [y] [rotacja] [rotacja_x] [rotacja_y]
	// [uint] [float] [float] [int] [int] [float] [int] [int]
	
	for (int i=0; i<iCount; i++)
	{
		fscanf(plik,"%d %f %f %d %d %f %d %d\n",
		&m_pFrame[i],
		&m_pScaleX[i], &m_pScaleY[i],
		&m_pPositionX[i], &m_pPositionY[i],
		&m_pRotation[i],
		&m_pRotationX[i], &m_pRotationY[i]);	// wczytaj linie pliku
	}

	fclose(plik);
	
}

// zwraca wskaznik na nazwe zdarzenia

unsigned char *CEvent::ucEventName(void)
{
	return m_pEventName;
}

void CEvent::ucEventName(char cName[])
{
	strcpy((char*)m_pEventName,cName);
}

//=== ustaw liczbe klatek w zdarzeniu

void CEvent::uiFrameCount(unsigned int uiCount)
{
	m_uiFrameCount = uiCount;
}

//=== pobierz liczbe klatek w zdarzeniu

unsigned int CEvent::uiFrameCount(void)
{
	return m_uiFrameCount;
}

//=== pobierz wspolrzedne X

int CEvent::iPositionX(unsigned int uiIndex)
{
	return m_pPositionX[uiIndex];
}

//=== ustaw wspolrzedne X

void CEvent::iPositionX(unsigned int uiIndex, int iValue)
{
	m_pPositionX[uiIndex]=iValue;
}

//=== pobierz wspolrzedne Y

int CEvent::iPositionY(unsigned int uiIndex)
{
	return m_pPositionY[uiIndex];
}

//=== ustaw wspolrzedne Y

void CEvent::iPositionY(unsigned int uiIndex, int iValue)
{
	m_pPositionY[uiIndex]=iValue;
}

//=== pobierz nr klatki z listy

unsigned int CEvent::uiFrame(unsigned int uiIndex)
{
	return m_pFrame[uiIndex];
}

//=== ustaw nr klatki na liscie

void CEvent::uiFrame(unsigned int uiIndex, unsigned int uiValue)
{
	m_pFrame[uiIndex]=uiValue;
}

bool CEvent::isName(char cName[])
{
	return !strcmp(cName,(char*)m_pEventName);
}

float CEvent::fRotation(unsigned int uiIndex)
{
	return m_pRotation[uiIndex];
}

void CEvent::fRotation(unsigned int uiIndex, float fValue)
{
	m_pRotation[uiIndex] = fValue;
}
	
float CEvent::fScaleX(unsigned int uiIndex)
{
	return m_pScaleX[uiIndex];
}
	
void CEvent::fScaleX(unsigned int uiIndex, float fValue)
{
	m_pScaleX[uiIndex] = fValue;
}
	
float CEvent::fScaleY(unsigned int uiIndex)
{
	return m_pScaleY[uiIndex];
}

void CEvent::fScaleY(unsigned int uiIndex, float fValue)
{
	m_pScaleY[uiIndex] = fValue;
}

unsigned int CEvent::iRotationX(unsigned int uiIndex)		// zwraca numer klatki dla zadanego indeksu
{
	return m_pRotationX[uiIndex];
}

void CEvent::iRotationX(unsigned int uiIndex, unsigned int uiValue)
{
	m_pRotationX[uiIndex] = uiValue;
}
	
unsigned int CEvent::iRotationY(unsigned int uiIndex)		// zwraca numer klatki dla zadanego indeksu
{
	return m_pRotationY[uiIndex];
}

void CEvent::iRotationY(unsigned int uiIndex, unsigned int uiValue)
{
	m_pRotationY[uiIndex] = uiValue;
}

void CEvent::UpOnly(char str[]){	int i=0; char c;		while (str[i])	{		c = str[i];		str[i]= toupper(c);		i++;	}}
