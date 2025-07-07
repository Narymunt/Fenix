// profile graczy

#pragma warning (disable:4996)

#include "Profile.h"

Profile::Profile(char cFilename[])
{
	strcpy(_cFilename,cFilename);	// zapamietaj nazwe pliku

	for (int i=0; i<8; i++)
	{
		_ulTotalScore[i] = 0;
		_ulScore[i] = 0;
		_ulMap[i] = 0;
		_ulLevel[i] = 0;

		sprintf(_cName[i],"_____");
	}

	_ucCurrentProfile = 0;
}

Profile::~Profile()
{

}

void Profile::setName(char cNewName[])
{
	strcpy(_cName[_ucCurrentProfile],cNewName);	// zapamietaj nazwe gracza
}

char *Profile::getName(void)
{
	return _cName[_ucCurrentProfile];
}

void Profile::setTotalScore(unsigned long ulScore)
{
	_ulTotalScore[_ucCurrentProfile] = ulScore;
}

void Profile::addTotalScore(unsigned long ulScore)
{
	_ulTotalScore[_ucCurrentProfile] += ulScore;
}

unsigned long Profile::getTotalScore(void)
{
	return _ulTotalScore[_ucCurrentProfile];
}

void Profile::setScore(unsigned long ulScore)
{
	_ulScore[_ucCurrentProfile] = ulScore;
}

void Profile::addScore(unsigned long ulScore)
{
	_ulScore[_ucCurrentProfile] += ulScore;
}

unsigned long Profile::getScore(void)
{
	return _ulScore[_ucCurrentProfile];
}

void Profile::setLevel(unsigned long ulLevel)
{
	_ulLevel[_ucCurrentProfile] = ulLevel;
}

void Profile::addLevel(unsigned long ulLevel)
{
	_ulLevel[_ucCurrentProfile] += ulLevel;
}

unsigned long Profile::getLevel(void)
{
	if (_ulTotalScore[_ucCurrentProfile] < 10000)
		_ulLevel[_ucCurrentProfile] = 1; 

	if (_ulTotalScore[_ucCurrentProfile] >=10000 && _ulTotalScore[_ucCurrentProfile] < 30000)
		_ulLevel[_ucCurrentProfile] = 2;

	if (_ulTotalScore[_ucCurrentProfile] >=30000 && _ulTotalScore[_ucCurrentProfile] < 60000)
		_ulLevel[_ucCurrentProfile] = 3;

	if (_ulTotalScore[_ucCurrentProfile] >=60000 && _ulTotalScore[_ucCurrentProfile] < 100000)
		_ulLevel[_ucCurrentProfile] = 4;

	if (_ulTotalScore[_ucCurrentProfile] >=100000 && _ulTotalScore[_ucCurrentProfile] < 150000)
		_ulLevel[_ucCurrentProfile] = 5;

	if (_ulTotalScore[_ucCurrentProfile] >=150000 && _ulTotalScore[_ucCurrentProfile] < 210000)
		_ulLevel[_ucCurrentProfile] = 6;

	if (_ulTotalScore[_ucCurrentProfile] >=210000 && _ulTotalScore[_ucCurrentProfile] < 280000)
		_ulLevel[_ucCurrentProfile] = 7;

	if (_ulTotalScore[_ucCurrentProfile] >=280000 && _ulTotalScore[_ucCurrentProfile] < 360000)
		_ulLevel[_ucCurrentProfile] = 8;

	if (_ulTotalScore[_ucCurrentProfile] >=360000 && _ulTotalScore[_ucCurrentProfile] < 450000)
		_ulLevel[_ucCurrentProfile] = 9;

	if (_ulTotalScore[_ucCurrentProfile] >=450000 && _ulTotalScore[_ucCurrentProfile] < 550000)
		_ulLevel[_ucCurrentProfile] = 10;

	if (_ulTotalScore[_ucCurrentProfile] >=550000 && _ulTotalScore[_ucCurrentProfile] < 660000)
		_ulLevel[_ucCurrentProfile] = 11;

	if (_ulTotalScore[_ucCurrentProfile] >=660000 && _ulTotalScore[_ucCurrentProfile] < 780000)
		_ulLevel[_ucCurrentProfile] = 12;

	if (_ulTotalScore[_ucCurrentProfile] >=780000 && _ulTotalScore[_ucCurrentProfile] < 910000)
		_ulLevel[_ucCurrentProfile] = 13;

	if (_ulTotalScore[_ucCurrentProfile] >=910000 && _ulTotalScore[_ucCurrentProfile] < 1050000)
		_ulLevel[_ucCurrentProfile] = 14;

	if (_ulTotalScore[_ucCurrentProfile] >=1050000 && _ulTotalScore[_ucCurrentProfile] < 1200000)
		_ulLevel[_ucCurrentProfile] = 15;

	if (_ulTotalScore[_ucCurrentProfile] >=1200000 && _ulTotalScore[_ucCurrentProfile] < 1360000)
		_ulLevel[_ucCurrentProfile] = 16;

	if (_ulTotalScore[_ucCurrentProfile] >=1360000 && _ulTotalScore[_ucCurrentProfile] < 1530000)
		_ulLevel[_ucCurrentProfile] = 17;

	if (_ulTotalScore[_ucCurrentProfile] >=1530000 && _ulTotalScore[_ucCurrentProfile] < 1720000)
		_ulLevel[_ucCurrentProfile] = 18;

	if (_ulTotalScore[_ucCurrentProfile] >=1720000 && _ulTotalScore[_ucCurrentProfile] < 1910000)
		_ulLevel[_ucCurrentProfile] = 19;

	if (_ulTotalScore[_ucCurrentProfile] >=1910000 )
		_ulLevel[_ucCurrentProfile] = 20;

	return _ulLevel[_ucCurrentProfile];
}


float Profile::getProgress(void)
{

	float fProgress;

	if (_ulTotalScore[_ucCurrentProfile] < 10000)
	{
		_ulLevel[_ucCurrentProfile] = 1; 
		fProgress = (float)(_ulTotalScore[_ucCurrentProfile] / 10000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=10000 && _ulTotalScore[_ucCurrentProfile] < 30000)
	{
		_ulLevel[_ucCurrentProfile] = 2;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-10000) / 20000.0f ) * 100.0f;
	}
	
	if (_ulTotalScore[_ucCurrentProfile] >=30000 && _ulTotalScore[_ucCurrentProfile] < 60000)
	{
		_ulLevel[_ucCurrentProfile] = 3;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-30000) / 30000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=60000 && _ulTotalScore[_ucCurrentProfile] < 100000)
	{
		_ulLevel[_ucCurrentProfile] = 4;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-60000) / 40000.0f) * 100.0f;		
	}

	if (_ulTotalScore[_ucCurrentProfile] >=100000 && _ulTotalScore[_ucCurrentProfile] < 150000)
	{
		_ulLevel[_ucCurrentProfile] = 5;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-100000) / 50000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=150000 && _ulTotalScore[_ucCurrentProfile] < 210000)
	{
		_ulLevel[_ucCurrentProfile] = 6;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-150000) / 60000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=210000 && _ulTotalScore[_ucCurrentProfile] < 280000)
	{
		_ulLevel[_ucCurrentProfile] = 7;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-210000) / 70000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=280000 && _ulTotalScore[_ucCurrentProfile] < 360000)
	{
		_ulLevel[_ucCurrentProfile] = 8;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-280000) / 80000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=360000 && _ulTotalScore[_ucCurrentProfile] < 450000)
	{
		_ulLevel[_ucCurrentProfile] = 9;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-360000) / 90000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=450000 && _ulTotalScore[_ucCurrentProfile] < 550000)
	{
		_ulLevel[_ucCurrentProfile] = 10;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-450000) / 100000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=550000 && _ulTotalScore[_ucCurrentProfile] < 660000)
	{
		_ulLevel[_ucCurrentProfile] = 11;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-550000) / 110000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=660000 && _ulTotalScore[_ucCurrentProfile] < 780000)
	{
		_ulLevel[_ucCurrentProfile] = 12;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-660000) / 120000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=780000 && _ulTotalScore[_ucCurrentProfile] < 910000)
	{
		_ulLevel[_ucCurrentProfile] = 13;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-780000) / 130000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=910000 && _ulTotalScore[_ucCurrentProfile] < 1050000)
	{
		_ulLevel[_ucCurrentProfile] = 14;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-910000) / 140000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=1050000 && _ulTotalScore[_ucCurrentProfile] < 1200000)
	{
		_ulLevel[_ucCurrentProfile] = 15;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-1050000) / 150000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=1200000 && _ulTotalScore[_ucCurrentProfile] < 1360000)
	{
		_ulLevel[_ucCurrentProfile] = 16;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-1200000) / 160000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=1360000 && _ulTotalScore[_ucCurrentProfile] < 1530000)
	{
		_ulLevel[_ucCurrentProfile] = 17;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-1360000) / 170000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=1530000 && _ulTotalScore[_ucCurrentProfile] < 1720000)
	{
		_ulLevel[_ucCurrentProfile] = 18;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-1530000) / 180000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=1720000 && _ulTotalScore[_ucCurrentProfile] < 1910000)
	{
		_ulLevel[_ucCurrentProfile] = 19;
		fProgress = (float)( (_ulTotalScore[_ucCurrentProfile]-1720000) / 190000.0f) * 100.0f;
	}

	if (_ulTotalScore[_ucCurrentProfile] >=1910000 )
	{
		_ulLevel[_ucCurrentProfile] = 20;
		fProgress = 100.0f;
	}

	return fProgress;
}

// zapis profilu

bool Profile::save(void)
{
	FILE	*plik;

	if ((plik=fopen(_cFilename,"wb"))==NULL)
	{
		return false;
	}
	else
	{
		fprintf(plik,"%d\n",_ucCurrentProfile);

		for (int i=0; i<8; i++)
		{
			fprintf(plik,"%s\n%d\n%d\n%d\n%d\n", _cName[i], _ulTotalScore[i], _ulScore[i], _ulMap[i], _ulLevel[i]);

			for (int j=0; j<21;j++)
				fprintf(plik,"%d\n",_ucTroophy[i][j]);
		}
	}
	
	fclose(plik);

	return true;
}

bool Profile::load(void)
{
	FILE	*plik;

	plik = NULL;

	if ((plik=fopen(_cFilename,"rt"))==NULL)
	{
		return false;
	}
	else
	{
		fscanf(plik,"%d\n",&_ucCurrentProfile);

		for (int i=0; i!=8; i++)
		{
			fscanf(plik,"%s\n%d\n%d\n%d\n%d\n", _cName[i], &_ulTotalScore[i], &_ulScore[i], &_ulMap[i], &_ulLevel[i]);

			for (int j=0; j!=21; j++)
				fscanf(plik,"%d\n",&_ucTroophy[i][j]);
		}
	}

	fclose(plik);

	// poprawka dla etapu, jezeli ktos ma etap 0 lub > 10 to zamieniamy na 1

	for (int i=0; i<8; i++)
	{
		if (_ulLevel[i]>9 || _ulLevel[i]<1)
			_ulLevel[i] = 1;
	}

	return true;
}

void Profile::troophy(int iIndex, unsigned char ucValue)
{
	_ucTroophy[_ucCurrentProfile][iIndex] = ucValue;
}

unsigned char Profile::troophy(int iIndex)
{
	return _ucTroophy[_ucCurrentProfile][iIndex];
}

//=== mapa oznacza poziom / miejsce na mapie, ktore wybieramy w eLevelMenu

void Profile::map(unsigned long ul)
{
	_ulMap[_ucCurrentProfile] = ul;
}

unsigned long Profile::map(void)
{
	return _ulMap[_ucCurrentProfile];
}

void Profile::currentProfile(unsigned char uProfile)	// ktory profil jest aktualnie u¿ywany
{
	_ucCurrentProfile = uProfile;
}

unsigned char Profile::currentProfile(void)
{
	return _ucCurrentProfile;
}

int Profile::nameSize(void)
{
	return strlen(_cName[_ucCurrentProfile]);
}

