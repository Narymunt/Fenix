#pragma once

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// jezyki dla aplikacji
// nie moze byc jako enum, poniewaz wartosci zapisywane sa do pliku

#define	LANG_ENGLAND	10
#define LANG_RUSSIA		20
#define	LANG_GERMANY	30
#define LANG_FRANCE		40

#define	LANG_ITALY		50
#define	LANG_SPAIN		60
#define LANG_POLAND		70
#define LANG_TURKEY		80

#define LANG_JAPAN		90
#define LANG_KOREA		100
#define LANG_CHINA		110
#define LANG_INDIA		120

#define LANG_ARABIA		130
#define LANG_ISRAEL		140
#define LANG_BRASIL		150
#define LANG_INDONESIA	160

#define LANG_PORTUGAL	170
#define LANG_SWEDEN		180
#define LANG_NORWAY		190
#define LANG_DENMARK	200

//=== trofea

#define TROOPHY_MATCH_100		0	// 1 uloz 100 kombinacji
#define TROOPHY_MATCH_1000		1	// 2 uloz 1000 kombinacji
#define TROOPHY_DIAMOND_100		2	// 3 kliknij 100 diamentow
#define TROOPHY_DIAMOND_1000	3	// 4 kliknij 1000 diamentow
#define TROOPHY_RAINBOW_100		4	// 5 kliknij 100 teczowych kamieni
#define TROOPHY_RAINBOW_1000	5	// 6 kliknij 1000 teczowych kamieni
#define TROOPHY_BOMB_100		6	// 7 kliknij 100 bomb
#define TROOPHY_BOMB_1000		7	// 8 kliknij 1000 bomb
#define TROOPHY_HIGHSCORE		8	// 9 zdobadz 1 miejsce w highscore
#define TROOPHY_DOUBLE_RAINBOW	9	// 10 zetknij ze sobπ dwa teczowe kamienie
#define TROOPHY_SCORE_10K		10	// 11 zdobadz 10 000 punktow
#define TROOPHY_SCORE_100K		11	// 12 zdobadz 100 000 punktow
#define TROOPHY_GAME_100		12	// 13 zagraj 100 razy w gre
#define TROOPHY_GAME_1000		13	// 14 zagraj 1000 razy w gre
#define TROOPHY_HIGHSCORE_ALL	14	// 15 zdobadz wszystkie miejsca w high score
#define TROOPHY_DIAMOND_5		15	// 16 umiesc na jednej planszy 5 diamentow
#define TROOPHY_RAINBOW_5		16	// 17 umiesc na jednej planszy 5 teczowych kamieni
#define	TROOPHY_VLINE8			17	// 18 uloz 8 klockow w jednej pionowej linii
#define TROOPHY_HLINE8			18	// 19 uloz 8 klockow w jednej poziomej linii
#define TROOPHY_GAME_FINISH		19	// 20 ukoncz wszystkie etapy

//=== zwraca min i max

#define getMin(x,y) ((x) < (y)) ? (x) : (y)
#define getMax(x,y) ((x) > (y)) ? (x) : (y)

//=== konwersja kolorÛw

#define ARGB(a,r,g,b)	((unsigned long(a)<<24) + (unsigned long(r)<<16) + (unsigned long(g)<<8) + unsigned long(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (unsigned long(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (unsigned long(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (unsigned long(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + unsigned long(b))

static char MAIN_VERSION[]="version 0.1";

//=== aplication state

#define E_LANGUAGE			9			 // wybÛr jÍzyka
#define E_PRELOAD			10           // wczytywanie aplikacji
#define E_ADS				20           // banery, reklamy itd.
#define E_INTRO				30           // intro do gry
#define E_MAINMENU			40           // menu g≥Ûwne gry
#define E_SETTINGS			50           // ustawienia gry
#define E_CREDITS			60           // autorzy gry itd.
#define E_PAUSE				70           // pauza w grze
#define E_FREEZE			80           // zamroøenie stanu gry np. w przypadku gdy telefon dzwoni
#define E_PROFILE			90           // ustawianie profilu gracza
#define E_LEVELMENU			100          // wybor etapu w grze
#define E_INGAME			110          // GLOWNY MODU£ GRY
#define E_TROOPHY			120          // ekran z nagrodami
#define E_GAMEOVER			130          // koniec gry
#define E_ENDSCREEN			140          // ekran koÒcowy, kup pe≥nπ wersje itp.
#define E_POSTGAME			150			 // po zakonczeniu gry (game over) - ekran zliczania punktow do profilu
#define E_HELP				160			 // pomoc z instrukcja gry
#define E_POST_TROOPHY		180
#define E_CONGRATULATIONS	200			// zwyciestwo !!! wielki sukces !!!
#define E_QUIT				255

//=== templates for deleting objects

template< class T > void SafeDelete( T*& pVal )
{
    if (pVal != NULL)
    {
        delete pVal;
        pVal = NULL;
    }
}

template< class T > void SafeDeleteArray( T*& pVal )
{
    delete[] pVal;
    pVal = NULL;
}

//=== czy dana liczba jest potÍgπ liczby 2 ?

inline bool isPowerOf2(int n)
{
    if (n < 1)
    {
        return false;
    }
    
    if (n == 1)
    {
        return true;
    }
    
    if (n & (n - 1))
    {
        return false;
    }
    
    return true;
}

