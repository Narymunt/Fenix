#include "HighScore.h"

#pragma warning(disable : 4996)

HighScore::HighScore()
{
	load();
}

HighScore::~HighScore()
{
	save();
}

unsigned long HighScore::getScore(unsigned char ucIndex)		// zwraca liczbe puntkow dla danego indeksu
{
	return _scoreTable[ucIndex];
}

char *HighScore::getName(unsigned char ucIndex)
{
	return _nameTable[ucIndex];
}

void HighScore::addScore(char cName[], unsigned long ulScore)			// dodaje punkty do tablicy jezeli potrzebne
{
	bool bInsert;
	
	bInsert = false;	// jeszcze nie wstawiono

	for (char i=0; i<10; i++)
	{
		if (ulScore >= _scoreTable[i] && !bInsert)
		{
			for (char j=10; j>i; j--)	// scroll punktow na dol
			{
				_scoreTable[j] = _scoreTable[j-1];
				strcpy(_nameTable[j],_nameTable[j-1]);				
			}
			
			_scoreTable[i] = ulScore;	// wpisz nowe punkty
			strcpy(_nameTable[i],cName);

			bInsert = true;
		}
	}

}	

bool HighScore::load(void)			// wczytanie danych
{
	FILE 	*plik;
	
	plik = fopen(HIGHSCORE_FILE,"rt");

	if (!plik)
		return false;
		
	for (char i=0; i<10;i++)
		fscanf(plik,"%s %ld\n",_nameTable[i],&_scoreTable[i]);
		
	fclose(plik);
	
	return true;
}

bool HighScore::save(void)			// zapisanie danych
{
	FILE	*plik;
	
	plik = fopen(HIGHSCORE_FILE,"wt");
	
	if (!plik)
		return false;
	
	for (char i=0; i<10; i++)
		fprintf(plik,"%s %ld\n",_nameTable[i],_scoreTable[i]);
	
	fclose(plik);
	
	return true;	
}
