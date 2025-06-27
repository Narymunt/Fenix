#include "AnimationTrack.h"

// stworzenie obiektu i ustawienie wskaznikow

AnimationTrack::AnimationTrack()
{
	_eventName = (unsigned char*) malloc (256);

	_frameCount = 0;

	_positionX = NULL;
	_positionY = NULL;

	_scaleX = NULL;
	_scaleY = NULL;

	_rotation = NULL;
	
	_rotationX = NULL;
	_rotationY = NULL;
	
	_frame = NULL;
}

// usuniecie obiektu i wyzerowanie wskaznikow

AnimationTrack::~AnimationTrack()
{
	if (_frame!=NULL)
	{
		delete _frame;
		_frame = NULL;
	}
	
	if (_scaleX!=NULL)
	{
		delete _scaleX;
		_scaleX = NULL;
	}

	if (_scaleY!=NULL)
	{
		delete _scaleY;
		_scaleY = NULL;
	}

	if (_positionX!=NULL)
	{
		delete _positionX;
		_positionX = NULL;
	}

	if (_positionY!=NULL)
	{
		delete _positionY;
		_positionY = NULL;
	}

	if (_rotation!=NULL)
	{
		delete _rotation;
		_rotation= NULL;
	}
	
	if (_rotationX!=NULL)
	{
		delete _rotationX;
		_rotationX = NULL;
	}

	if (_rotationY!=NULL)
	{
		delete _rotationY;
		_rotationY = NULL;
	}
}

AnimationTrack::AnimationTrack(char cFilename[])
{
	FILE	*plik;
	char	linia[1024];
	int		iCount;

	_eventName = (unsigned char*) malloc (256);

	_positionX = NULL;
	_positionY = NULL;

	_scaleX = NULL;
	_scaleY = NULL;

	_rotation = NULL;
	
	_rotationX = NULL;
	_rotationY = NULL;
	
	_frame = NULL;


	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		printf("ERROR! Brak pliku eventu graficznego!\n");
		return ;
	}

	iCount = 0; 
	
	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
	upOnly(linia);

	if (strcmp(linia,"<EVENT>"))	// czy to plik track ? 
	{
		printf("ERROR! Uszkodzony plik event!\n");
		return ;
	}

	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - nazwa zdarzenia
	upOnly(linia);
	strcpy((char*)_eventName, linia);

	// wczytujemy elementy

	while (strcmp(linia,"</EVENT>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
		upOnly(linia);
		iCount++;		
	}

	iCount--;
	iCount>>=3;		// dzielimy przez 8 - tyle parametrów jest w jednej linii

	_frameCount = iCount;
	
	fclose(plik);

	// teraz wczytujemy
	
	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		printf("ERROR! Brak pliku eventu graficznego!\n");
		return ;
	}
	
	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - <EVENT>
	upOnly(linia);
	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku - nazwa zdarzenia
	upOnly(linia);

	// alokacja pamieci na tablice

	_frame = (unsigned int*) malloc(1+_frameCount*sizeof(unsigned int));
	
	_scaleX = (float*) malloc(1+_frameCount*sizeof(float));
	_scaleY = (float*) malloc(1+_frameCount*sizeof(float));
	
	_positionX= (int*) malloc(1+_frameCount*sizeof(int));
	_positionY= (int*) malloc(1+_frameCount*sizeof(int));

	_rotation = (float*) malloc(1+_frameCount*sizeof(float));
	
	_rotationX= (int*) malloc(1+_frameCount*sizeof(int));
	_rotationY= (int*) malloc(1+_frameCount*sizeof(int));
	
	// [numer klatki] [scale_x] [scale_y] [x] [y] [rotacja] [rotacja_x] [rotacja_y]
	// [uint] [float] [float] [int] [int] [float] [int] [int]
	
	for (int i=0; i<iCount; i++)
	{
		fscanf(plik,"%d %f %f %d %d %f %d %d\n",
		&_frame[i],
		&_scaleX[i], &_scaleY[i],
		&_positionX[i], &_positionY[i],
		&_rotation[i],
		&_rotationX[i], &_rotationY[i]);	// wczytaj linie pliku
	}

	fclose(plik);
	
}

// zwraca wskaznik na nazwe zdarzenia

unsigned char *AnimationTrack::trackName(void)
{
	return _eventName;
}

void AnimationTrack::trackName(char cName[])
{
	strcpy((char*)_eventName,cName);
}

//=== ustaw liczbe klatek w zdarzeniu

void AnimationTrack::frameCount(unsigned int uiCount)
{
	_frameCount = uiCount;
}

//=== pobierz liczbe klatek w zdarzeniu

unsigned int AnimationTrack::frameCount(void)
{
	return _frameCount;
}

//=== pobierz wspolrzedne X

int AnimationTrack::positionX(unsigned int uiIndex)
{
	return _positionX[uiIndex];
}

//=== ustaw wspolrzedne X

void AnimationTrack::positionX(unsigned int uiIndex, int iValue)
{
	_positionX[uiIndex]=iValue;
}

//=== pobierz wspolrzedne Y

int AnimationTrack::positionY(unsigned int uiIndex)
{
	return _positionY[uiIndex];
}

//=== ustaw wspolrzedne Y

void AnimationTrack::positionY(unsigned int uiIndex, int iValue)
{
	_positionY[uiIndex]=iValue;
}

//=== pobierz nr klatki z listy

unsigned int AnimationTrack::frame(unsigned int uiIndex)
{
	return _frame[uiIndex];
}

//=== ustaw nr klatki na liscie

void AnimationTrack::frame(unsigned int uiIndex, unsigned int uiValue)
{
	_frame[uiIndex]=uiValue;
}

bool AnimationTrack::isName(char cName[])
{
	return !strcmp(cName,(char*)_eventName);
}

float AnimationTrack::rotation(unsigned int uiIndex)
{
	return _rotation[uiIndex];
}

void AnimationTrack::rotation(unsigned int uiIndex, float fValue)
{
	_rotation[uiIndex] = fValue;
}
	
float AnimationTrack::scaleX(unsigned int uiIndex)
{
	return _scaleX[uiIndex];
}
	
void AnimationTrack::scaleX(unsigned int uiIndex, float fValue)
{
	_scaleX[uiIndex] = fValue;
}
	
float AnimationTrack::scaleY(unsigned int uiIndex)
{
	return _scaleY[uiIndex];
}

void AnimationTrack::scaleY(unsigned int uiIndex, float fValue)
{
	_scaleY[uiIndex] = fValue;
}

unsigned int AnimationTrack::rotationX(unsigned int uiIndex)		// zwraca numer klatki dla zadanego indeksu
{
	return _rotationX[uiIndex];
}

void AnimationTrack::rotationX(unsigned int uiIndex, unsigned int uiValue)
{
	_rotationX[uiIndex] = uiValue;
}
	
unsigned int AnimationTrack::rotationY(unsigned int uiIndex)		// zwraca numer klatki dla zadanego indeksu
{
	return _rotationY[uiIndex];
}

void AnimationTrack::rotationY(unsigned int uiIndex, unsigned int uiValue)
{
	_rotationY[uiIndex] = uiValue;
}

void AnimationTrack::upOnly(char str[])
{
	int i=0; char c;
	
	while (str[i])
	{
		c = str[i];
		str[i]= toupper(c);
		i++;
	}
}

