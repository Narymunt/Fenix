// profile - profil gracza 
// zawiera w srodku profile dla 8 uzytkownikow / graczy

#pragma once

#include <windows.h>
#include <stdio.h>

class Profile  
{

public:

	Profile(char cFilename[]);
	~Profile();

	void	setName(char cNewName[]);
	char	*getName(void);
	int		nameSize(void);


	void	setTotalScore(unsigned long ulScore);
	void	addTotalScore(unsigned long ulScore);
	unsigned long getTotalScore(void);

	void	setScore(unsigned long ulScore);
	void	addScore(unsigned long ulScore);
	unsigned long getScore(void);

	void	setLevel(unsigned long ulLevel);
	void	addLevel(unsigned long ulLevel);
	unsigned long getLevel(void);

	void	map(unsigned long ul);	
	unsigned long map(void);

	bool	save(void);		// save profile
	bool	load(void);

	float	getProgress(void);	// zwraca procentowo ile jeszcze nam brakuje do konca levelu

	void	troophy(int iIndex, unsigned char ucValue);
	unsigned char troophy(int iIndex); 

	void	currentProfile(unsigned char ucProfile);	// ktory profil jest aktualnie u¿ywany
	unsigned char currentProfile(void);

	char	_cFilename[1024];	// nazwa pliku z danymi profilu
	char	_cName[8][100];	// nazwa profilu

	unsigned char	_ucCurrentProfile;	

	unsigned long	_ulTotalScore[8];	// suma wszystkich zebranych punktow
	unsigned long	_ulScore[8];		// aktualna suma punktow
	unsigned long	_ulMap[8];			// ktore mapy sa dostepne, numer oznacza mapa1, mapa2 itd. 
	unsigned long	_ulLevel[8];		// aktualny poziom w danym levelu, dla kazdego gracza/profilu, ktore sa dostepne

	unsigned char	_ucTroophy[9][21];	// zdobyte osiagniecia

};

