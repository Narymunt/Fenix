#pragma once

#include <stdio.h>
#include <string.h>
#include "../../Game.h"

class CHighScore
{

	public:

	CHighScore();
	~CHighScore();
	
	
		unsigned long 	ulGetScore(unsigned char ucIndex);		// zwraca liczbe puntkow dla danego indeksu
		char 			*cGetName(unsigned char ucIndex);
		
		void			AddScore(char cName[], unsigned long ulScore);			// dodaje punkty do tablicy jezeli potrzebne
	
		bool			bLoad(void);			// wczytanie danych
		bool			bSave(void);			// zapisanie danych
		
	private:
	
		unsigned long	m_ulScoreTable[11];
		char			m_cNameTable[11][100];
				
};

