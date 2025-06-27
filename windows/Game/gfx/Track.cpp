#include "track.h"


//=== stworz obiekt

CTrack::CTrack(char cFilename[])
{
	FILE	*plik;	
	char	linia[1024];
	int		iCount;
	int		iStartOffset, iEndOffset, iStart, iEnd;

	
	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		fx_debug("ERROR! Brak pliku demo.ini!\n");
		return ;
	}

	iCount =0;

	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
	UpOnly(linia);

	if (strcmp(linia,"<TRACK>"))	// czy to plik track ? 
	{
		fx_debug("ERROR! Uszkodzony plik track.ini!\n");
		return ;
	}

	// wczytujemy elementy

	while (strcmp(linia,"</TRACK>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
		UpOnly(linia);
		iCount++;		
	}

	iCount--;
	iCount>>=2;

	fclose(plik);

	// teraz parsujemy

	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		fx_debug("ERROR! Brak pliku demo.ini!\n");
		return ;
	}

	fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
	UpOnly(linia);

	// wczytujemy elementy

	for (int i=0; i<iCount; i++)
	{
		fscanf(plik,"%d %d %d %d\n",&iStartOffset, &iStart, &iEnd, &iEndOffset);	// wczytaj linie pliku
		
		m_iOffsetStart.push_back(iStartOffset);
		m_iStart.push_back(iStart);
		m_iEnd.push_back(iEnd);
		m_iOffsetEnd.push_back(iEndOffset);
		
		printf("%d %d %d %d\n",iStartOffset, iStart, iEnd, iEndOffset);	// wczytaj linie pliku
	}

	fclose(plik);

}

//=== usun obiekt === 

CTrack::~CTrack()
{
	m_iOffsetStart.clear();
	m_iStart.clear();
	m_iEnd.clear();
	m_iOffsetEnd.clear();
}

// zamiana literek na duze

void CTrack::UpOnly(char str[])
{
	int i=0;
	char c;
	
	while (str[i])
	{
		c = str[i];
		str[i]= toupper(c);
		i++;
	}
}

int CTrack::iGetSize(void)
{
	return m_iOffsetStart.size();
}

// zwraca maksymalna wartosc startu licznika

int CTrack::iGetStartMax(void)
{
	int iMax;

	iMax = 0;

	for (unsigned int i=0; i<m_iOffsetStart.size(); i++)
	{
		if (m_iStart[i]>iMax) iMax = m_iStart[i];
	}

	return iMax;
}

// zwracanie i ustawianie wartosci

int CTrack::iOffsetStart(int i)
{
	return m_iOffsetStart[i];
}

void CTrack::iOffsetStart(int iIndex, int iValue)
{
	m_iOffsetStart[iIndex] = iValue;
}

int CTrack::iStart(int i)
{
	return m_iStart[i];
}

void CTrack::iStart(int iIndex, int iValue)
{
	m_iStart[iIndex] = iValue;
}

int CTrack::iEnd(int i)
{
	return m_iEnd[i];
}

void CTrack::iEnd((int iIndex, int iValue)
{
	m_iEnd[iIndex] = iValue;
}

int CTrack::iOffsetEnd(int i)
{
	return m_iOffsetEnd[i];
}

void CTrack::iOffsetEnd(int iIndex, int iValue)
{
	m_iOffsetEnd[iIndex] = iValue;
}

// sprawdzamy czy w danym przedziale czasu powinnismy odtwarzac

bool CTrack::isPlaying(int i)
{

	for (unsigned int h1=0; h1<m_iStart.size(); h1++)
	{
		if ( (m_iStart[h1]<=i) && (m_iEnd[h1]>=i) ) return true;
	}

	return false;
}

// zwraca numer klatki jaki powinnismy odtworzyc w tym przedziale czasu
// bez interpolacji, liniowo - musi zgadzać się 1:1

int CTrack::iGetFrame(int i)
{
	int iFrame;

	for (unsigned int h1=0; h1<m_iStart.size(); h1++)
	{
		if ( (m_iStart[h1]<=i) && (m_iEnd[h1]>=i) ) 
		{
			iFrame = (i - m_iStart[h1]) - m_iOffsetStart[h1] + m_iOffsetEnd[h1];
		}
	}

	return iFrame;
}

