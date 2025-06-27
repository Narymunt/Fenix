// event to zdarzenie animacyjne
// jest to wewnetrzna czesc ANIMO
// w pliku animo sa klatki oraz zdarzenia czyli numery klatek do kolejki
// <event>
// [nazwa_zdarzenia]
// [numer klatki] [scale_x] [scale_y] [x] [y] [rotacja] [rotacja_x] [rotacja_y]
// [uint] [float] [float] [int] [int] [float] [int] [int]
// 1
// 2
// 3
// 3
// 2
// </event>

#pragma once 

#include <windows.h>
#include <string.h>
#include <stdio.h>


class CEvent  
{
public:
	
	// wczytaj z pliku serie animacji

	CEvent();
	CEvent(char cFilename[]);
	~CEvent();

	void ucEventName(char cName[]);
	unsigned char *ucEventName(void);
	
	bool isName(char cName[]);
	
	void uiFrameCount(unsigned int iCount);
	unsigned int uiFrameCount(void);
	
	int	iPositionX(unsigned int uiIndex);
	void iPositionX(unsigned int uiIndex, int iValue);
	
	int	iPositionY(unsigned int uiIndex);
	void iPositionY(unsigned int uiIndex, int iValue);
	
	void iPositionXY(unsigned int uiIndex, int iX, int iY);

	unsigned int uiFrame(unsigned int uiIndex);		// zwraca numer klatki dla zadanego indeksu
	void uiFrame(unsigned int uiIndex, unsigned int uiValue);

	float fRotation(unsigned int uiIndex);
	void fRotation(unsigned int uiIndex, float fValue);
	
	float fScaleX(unsigned int uiIndex);
	void fScaleX(unsigned int uiIndex, float fValue);
	
	float fScaleY(unsigned int uiIndex);
	void fScaleY(unsigned int uiIndex, float fValue);

	unsigned int iRotationX(unsigned int uiIndex);		// zwraca numer klatki dla zadanego indeksu
	void iRotationX(unsigned int uiIndex, unsigned int uiValue);
	
	unsigned int iRotationY(unsigned int uiIndex);		// zwraca numer klatki dla zadanego indeksu
	void iRotationY(unsigned int uiIndex, unsigned int uiValue);

	void UpOnly(char str[]);
	
private:
	
	unsigned char	*m_pEventName;		// 256 bajtow

	unsigned int	m_uiFrameCount;		// ile klatek w tym zdarzeniu

	unsigned int	*m_pFrame;
	
	float			*m_pScaleX;
	float			*m_pScaleY;	
	
	int 			*m_pPositionX;
	int				*m_pPositionY;
	
	float			*m_pRotation;
	
	int				*m_pRotationX;
	int				*m_pRotationY;

};

