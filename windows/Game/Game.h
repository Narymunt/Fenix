// main config file

#pragma once

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// jezyki dla aplikacji

enum eLanguage
{
   ENGLAND, RUSSIA, GERMANY, FRANCE, ITALY,	SPAIN,		
   POLAND, TURKEY, JAPAN, KOREA, CHINA, INDIA,
   ARABIA, ISRAEL, BRASIL, INDONESIA, PORTUGAL,
   SWEDEN, NORWAY, DENMARK
};

//=== trofea

// 1 uloz 100 kombinacji
// 2 uloz 1000 kombinacji
// 3 kliknij 100 diamentow
// 4 kliknij 1000 diamentow
// 5 kliknij 100 teczowych kamieni
// 6 kliknij 1000 teczowych kamieni
// 7 kliknij 100 bomb
// 8 kliknij 1000 bomb
// 9 zdobadz 1 miejsce w highscore
// 10 zetknij ze sob¹ dwa teczowe kamienie
// 11 zdobadz 10 000 punktow
// 12 zdobadz 100 000 punktow
// 13 zagraj 100 razy w gre
// 14 zagraj 1000 razy w gre
// 15 zdobadz wszystkie miejsca w high score
// 16 umiesc na jednej planszy 5 diamentow
// 17 umiesc na jednej planszy 5 teczowych kamieni
// 18 uloz 8 klockow w jednej pionowej linii
// 19 uloz 8 klockow w jednej poziomej linii
// 20 ukoncz wszystkie etapy

enum eTroophy
{
	TROOPHY_MATCH_100,
	TROOPHY_MATCH_1000,
	TROOPHY_DIAMOND_100,
	TROOPHY_DIAMOND_1000,
	TROOPHY_RAINBOW_100,
	TROOPHY_RAINBOW_1000,
	TROOPHY_BOMB_100,
	TROOPHY_BOMB_1000,
	TROOPHY_HIGHSCORE,
	TROOPHY_DOUBLE_RAINBOW,
	TROOPHY_SCORE_10K,
	TROOPHY_SCORE_100K,
	TROOPHY_GAME_100,
	TROOPHY_GAME_1000,
	TROOPHY_HIGHSCORE_ALL,
	TROOPHY_DIAMOND_5,
	TROOPHY_RAINBOW_5,
	TROOPHY_VLINE8,
	TROOPHY_HLINE8,
	TROOPHY_GAME_FINISH
};

//=== zwraca min i max

#define _min(x,y) ((x) < (y)) ? (x) : (y)
#define _max(x,y) ((x) > (y)) ? (x) : (y)

//=== definicje PI

#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f
#define M_PI_4	0.785398163397448309616f
#define M_1_PI	0.318309886183790671538f
#define M_2_PI	0.636619772367581343076f

//=== konwersja kolorów

#define ARGB(a,r,g,b)	((unsigned long(a)<<24) + (unsigned long(r)<<16) + (unsigned long(g)<<8) + unsigned long(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (unsigned long(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (unsigned long(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (unsigned long(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + unsigned long(b))

//=== has³o do plików .zip

static char ZIP_FILE[]="Game.bin";
static char	ZIP_PASSWORD[]="pass";

//=== tu trzymamy najlepsze punktu

static char HIGHSCORE_FILE[]="highscore.bin";

//=== tutaj trzymamy dane o graczach

static char USERS_FILE[]="Game.cfg";

//=== plik ze zlaczonymi danymi

static char DATA_FILE[]="Game.dat";
static char DATA_PASSWORD[]="!shodan9";
static char DATA_MAP[]="Game.map";

//=== do uzupelnienia

#define CIRCLE_FULL	360.0f

//=== plik konfiguracyjny

static char SETTINGS_FILE[]="settings.cfg";

//=== aplication state

// E_LANGUAGE wybór jêzyka
// E_PRELOAD wczytywanie aplikacji
// E_ADS banery, reklamy itd.
// E_INTRO intro do gry
// E_MAINMENU  menu g³ówne gry
// E_SETTINGS ustawienia gry
// E_CREDITS autorzy gry itd. 
// E_PAUSE pauza w grze
// E_FREEZE zamro¿enie stanu gry np. w przypadku gdy telefon dzwoni
// E_PROFILE ustawianie profilu gracza
// E_LEVELMENU wybor etapu w grze
// E_INGAME GLOWNY MODU£ GRY
// E_TROOPHY ekran z nagrodami
// E_GAMEOVER koniec gry
// E_ENDSCREEN ekran koñcowy, kup pe³n¹ wersje itp.
// E_POSTGAME po zakonczeniu gry (game over) - ekran zliczania punktow do profilu
// E_HELP pomoc z instrukcja gry
// E_POST_TROOPHY	pomocniczy
// E_CONGRATULATIONS	zwyciestwo !!! wielki sukces !!!
// E_CONFIRM_QUIT potwierdz wyjscie z gry
// E_QUIT wyjscie z gry = koniec aplikacji

enum appState
{
   LANGUAGE,
   PRELOAD,
   ADS,
   INTRO,
   MAINMENU,
   SETTINGS,
   CREDITS, 
   PAUSE,
   FREEZE,
   PROFILE,
   LEVELMENU,
   INGAME,
   TROOPHY,
   GAMEOVER,
   ENDSCREEN,
   POSTGAME,
   HELP,
   POST_TROOPHY,
   CONGRATULATIONS,
   CONFIRM_QUIT,
   
   ANIMATIONS_EDITOR,
   SCENE_EDITOR,
   PARTICLE_EDITOR,

   QUIT			
};

//=== klawiatura

static	unsigned char	KEYPRESSED;

#define KEY_NONE		0

#define KEY_A			1
#define KEY_B			2
#define KEY_C			3
#define KEY_D			4
#define KEY_E			5
#define KEY_F			6
#define KEY_G			7
#define KEY_H			8
#define KEY_I			9
#define KEY_J			10
#define KEY_K			11
#define KEY_L			12
#define KEY_M			13
#define KEY_N			14
#define KEY_O			15
#define KEY_P			16
#define KEY_Q			17
#define KEY_R			18
#define KEY_S			19
#define KEY_T			20
#define KEY_U			21
#define KEY_V			22
#define KEY_W			23
#define KEY_X			24
#define KEY_Y			25
#define KEY_Z			26

#define KEY_0			100
#define KEY_1			101
#define KEY_2			102
#define KEY_3			103
#define KEY_4			104
#define KEY_5			105
#define KEY_6			106
#define KEY_7			107
#define KEY_8			108
#define KEY_9			109

#define KEY_COMA		180
#define KEY_ENTER		190
#define KEY_SPACE		200
#define KEY_DELETE		210
#define KEY_ESC			255


//=== templates for deleting objects

template< class T > void safeDelete( T*& pVal )
{
    if (pVal != NULL)
	{
		delete pVal;
		pVal = NULL;
	}
}
    
template< class T > void safeDeleteArray( T*& pVal )
{
    delete[] pVal;
    pVal = NULL;
}

//=== zmiana wszystkich malych liter na duze w stringu

void upStr(char str[]);

//=== czy dana liczba jest potêg¹ liczby 2 ?

inline bool isPowerOf2(int n)
{
    if (n < 1)
        return false;

    if (n == 1)
        return true;

    if (n & (n - 1))
        return false;

    return true;
}

//=== zaokraglona konwersja float do int

inline int FloatRoundToInt(float theFloatValue)
{
	return theFloatValue > 0.0f ? (int)(theFloatValue + 0.5f): (int)(theFloatValue - 0.5f);
}

inline float DegToRad(float theAngle)
{
	return theAngle * (CIRCLE_FULL / 360.0f); // konwersja katow z deg do rad 
}

//=== konwersja katow z rad do deg

inline float RadToDeg(float theAngle)
{
	return theAngle * (360.0f / CIRCLE_FULL);
}

// ustawianie bitów

#define FLAG(theBitIndex) (1 << (theBitIndex))

inline void setBit(unsigned int &theNumber, int theBitIndex, int theValue)
{
	theValue != 0 ? theNumber |= FLAG(theBitIndex) : theNumber &= ~FLAG(theBitIndex);
}

inline bool testBit(unsigned int theNumber, int theBitIndex)
{
	return (theNumber & FLAG(theBitIndex)) ? true : false;
}  
