// AnimationTrack to odtwarzanie animacji po trasie, z dodatkowymi modyfikatorami
// AnimationTrack jest niezale¿ny od animacji, ¿eby mo¿na by³o ten sam event wykonaæ na ró¿nych kolejkach sprite
// w pliku AnimationEvent sa klatki oraz zdarzenia czyli numery klatek do kolejki
// <AnimationTrack>
// [nazwa_zdarzenia]
// [numer klatki] [scale_x] [scale_y] [x] [y] [rotacja] [rotacja_x] [rotacja_y]
// [uint] [float] [float] [int] [int] [float] [int] [int]
// 1
// 2
// 3
// 3
// 2
// </AnimationTrack>

#pragma once 
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <string.h>
#include <stdio.h>

class AnimationTrack
{
public:
	
	// wczytaj z pliku serie animacji

	AnimationTrack();
	AnimationTrack(char cFilename[]);
	~AnimationTrack();

	void trackName(char cName[]);
	unsigned char *trackName(void);
	
	bool isName(char cName[]);
	
	void frameCount(unsigned int iCount);
	unsigned int frameCount(void);
	
	int	positionX(unsigned int uiIndex);
	void positionX(unsigned int uiIndex, int iValue);
	
	int	positionY(unsigned int uiIndex);
	void positionY(unsigned int uiIndex, int iValue);
	
	void positionXY(unsigned int uiIndex, int iX, int iY);

	unsigned int frame(unsigned int uiIndex);		// zwraca numer klatki dla zadanego indeksu
	void frame(unsigned int uiIndex, unsigned int uiValue);

	float rotation(unsigned int uiIndex);
	void rotation(unsigned int uiIndex, float fValue);
	
	float scaleX(unsigned int uiIndex);
	void scaleX(unsigned int uiIndex, float fValue);
	
	float scaleY(unsigned int uiIndex);
	void scaleY(unsigned int uiIndex, float fValue);

	unsigned int rotationX(unsigned int uiIndex);		// zwraca numer klatki dla zadanego indeksu
	void rotationX(unsigned int uiIndex, unsigned int uiValue);
	
	unsigned int rotationY(unsigned int uiIndex);		// zwraca numer klatki dla zadanego indeksu
	void rotationY(unsigned int uiIndex, unsigned int uiValue);

	void upOnly(char str[]);
	
	unsigned char	*_eventName;		// 256 bajtow

	unsigned int	_frameCount;		// ile klatek w tym zdarzeniu
	unsigned int	*_frame;
	
	float			*_scaleX;
	float			*_scaleY;	
	
	int 			*_positionX;
	int				*_positionY;
	
	float			*_rotation;
	
	int				*_rotationX;		// pivot point
	int				*_rotationY;

};

