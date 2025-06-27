#include "HighScore.h"

#pragma warning(disable : 4996)

CHighScore::CHighScore()
{
	bLoad();
}

CHighScore::~CHighScore()
{
	bSave();
}

unsigned long CHighScore::ulGetScore(unsigned char ucIndex)		// zwraca liczbe puntkow dla danego indeksu
{
	return m_ulScoreTable[ucIndex];
}

char *CHighScore::cGetName(unsigned char ucIndex)
{
	return m_cNameTable[ucIndex];
}

void CHighScore::AddScore(char cName[], unsigned long ulScore)			// dodaje punkty do tablicy jezeli potrzebne
{
	bool bInsert;
	
	bInsert = false;	// jeszcze nie wstawiono

	for (char i=0; i<10; i++)
	{
		if (ulScore >= m_ulScoreTable[i] && !bInsert)
		{
			for (char j=10; j>i; j--)	// scroll punktow na dol
			{
				m_ulScoreTable[j] = m_ulScoreTable[j-1];
				strcpy(m_cNameTable[j],m_cNameTable[j-1]);				
			}
			
			m_ulScoreTable[i] = ulScore;	// wpisz nowe punkty
			strcpy(m_cNameTable[i],cName);

			bInsert = true;
		}
	}

}	

bool CHighScore::bLoad(void)			// wczytanie danych
{
	FILE 	*plik;
	
	plik = fopen(HIGHSCORE_FILE,"rt");

	if (!plik)
		return false;
		
	for (char i=0; i<10;i++)
		fscanf(plik,"%s %ld\n",m_cNameTable[i],&m_ulScoreTable[i]);
		
	fclose(plik);
	
	return true;
}

bool CHighScore::bSave(void)			// zapisanie danych
{
	FILE	*plik;
	
	plik = fopen(HIGHSCORE_FILE,"wt");
	
	if (!plik)
		return false;
	
	for (char i=0; i<10; i++)
		fprintf(plik,"%s %ld\n",m_cNameTable[i],m_ulScoreTable[i]);
	
	fclose(plik);
	
	return true;	
}