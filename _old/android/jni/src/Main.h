#pragma once

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// jezyki dla aplikacji

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

//=== zwraca min i max

#define getMin(x,y) ((x) < (y)) ? (x) : (y)
#define getMax(x,y) ((x) > (y)) ? (x) : (y)

//=== aplication state

#define E_PRELOAD			10           // wczytywanie aplikacji
#define E_INTRO				20			 // intro do gry
#define E_MAIN				40           // menu glowne
#define E_KEYPAD			50			 // klawiatura manipulatora
#define E_QUIT				255

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

// ustawianie bit√õw

#define FLAG(theBitIndex) (1 << (theBitIndex))

inline void setBit(unsigned int &theNumber, int theBitIndex, int theValue)
{
	if (theValue != 0)
	{
		theNumber |= FLAG(theBitIndex);
	}
	else
	{
		theNumber &= ~FLAG(theBitIndex);
	}
}

inline bool testBit(unsigned int theNumber, int theBitIndex)
{
	if (theNumber & FLAG(theBitIndex))
	{
		return true;
	}
	else
	{
		return false;
	}
}  

// przelicz proporcjonalnie i zwróc wartosc

inline float fRecalc(float a, float b, float x)
{
	return (float)((b/a)*x);
}
