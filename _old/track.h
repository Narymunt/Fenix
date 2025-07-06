// track zawiera ustawienia czasu
// offset start end offset
// struktura : 
// <track>
// 0 20 50 100
// </track>
// oznacza : 
// graj w czasie od 0 do 100 klatki 20 do 50 
// lub
// rysuj animację od pixela 0 do 100 klatki 20 do 50
//
// zapis punktów to tylko klatki kluczowe, nie zawierają interpolacji

#pragma once

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "debug.h"

using namespace std;

class CTrack 
{
public:

	CTrack(char cFilename[]);
	~CTrack();

	void		UpOnly(char str[]);		// zamiana wszystkich literek lancucha na duze

	int			iGetSize(void);			// zwraca liczbe elementow
	int			iGetStartMax(void);		// pobierz maksymalny mozliwy czas rozpoczecia odtwarzania

	int			iOffsetStart(int i);	// zwraca wartosci dla elementow
	void		iOffsetStart(int iIndex, int iValue);
	
	int			iStart(int i);
	void		iStart(int iIndex, int iValue);
	
	int			iEnd(int i);
	void		iEnd(int iIndex, int iValue);
	
	int			iOffsetEnd(int i);
	void		iOffsetEnd(int iIndex, int iValue);
	
	bool		isPlaying(int i);		// czy powinnismy teraz grac w tej klatce
	int			iGetFrame(int i);		// pobierz wlasciwa klatke dla danego czasu

private:

	vector <int>	m_iOffsetStart;	// offsety poczatkowe
	vector <int>	m_iStart;		// czas startowy
	vector <int>	m_iEnd;			// czas koncowy
	vector <int>	m_iOffsetEnd;	// offset koncowy
};

#endif 
