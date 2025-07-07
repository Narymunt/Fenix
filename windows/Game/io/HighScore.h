#pragma once

#include <stdio.h>
#include <string.h>
#include "../Game.h"

class HighScore
{

public:
	HighScore();
	~HighScore();
	
	unsigned long 	getScore(unsigned char ucIndex);		// zwraca liczbe puntkow dla danego indeksu
	char 			*getName(unsigned char ucIndex);
		
	void			addScore(char cName[], unsigned long ulScore);			// dodaje punkty do tablicy jezeli potrzebne
	
	bool			load(void);			// wczytanie danych
	bool			save(void);			// zapisanie danych
		
	unsigned long	_scoreTable[11];
	char			_nameTable[11][100];
				
};

