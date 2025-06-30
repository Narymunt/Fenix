/**
   Particle2DManager.h

   Generuje potrzebne cz�stki i zarz�dza nimi. 
   Trzyma informacje o texturach, �eby nie powiela� sprite dla ka�dej cz�stki z osobna.

   @author Jaros�aw Ro�y�ski
   
*/

#include "Particle2DManager.h"
#include <string>
#include <iostream>

/**
   Konstruktor klasy.

   @param cSpriteFilename nazwa pliku z textura
   @param ulCount ile ma by� cz�steczek
   @param fX1 obszar startowy prostokata
   @param fY1 obszar startowy prostokata
   @param fX2 obszar startowy prostokata
   @param fY2 obszar startowy prostokata
   @param fMinIncX minimalna delta wspolrzednych X per tick
   @param fMinIncY minimalna delta wspolrzednych Y per tick
   @param fMaxIncX maxymalna delta wspolrzednych X per tick
   @param fMaxIncY maxymalna delta wspolrzednych Y per tick
   @param fAlpha startowa prze�roczysto��
   @param fMinIncAlpha minimalna delta prze�roczysto�ci per tick
   @param fMaxIncAlpha maxymalna delta prze�roczysto�ci per tick
   @param fMinIncAngle minimalna delta k�ta per tick
   @param fMaxIncAngle maxymalna delta k�ta per tick
   @param ulMinLifeTime minimalna d�ugo�� �ycia cz�stki
   @param ulMaxLifeTime maxymalna d�ugo�� �ycia cz�stki
   @param pScreen wskaznik do ekranu

   @return none
*/

CParticle2DManager::CParticle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                                   double fX1, double fY1, double fX2, double fY2, 
                                   double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                                   double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                                   double fAngle, double fMinIncAngle, double fMaxIncAngle,
                                   unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime, CScreen *pScreen) :
_r(1), _g(1), _b(1), _a(1),
_ulCount(ulCount),
_x1(fX1), _y1(fY1), _x2(fX2), _y2(fY2),
_dMinIncX(fMinIncX), _dMaxIncX(fMaxIncX),
_dMinIncY(fMinIncY), _dMaxIncY(fMaxIncY),
_dAlpha(fAlpha), _dMinIncAlpha(fMinIncAlpha), _dMaxIncAlpha(fMaxIncAlpha),
_dAngle(fAngle), _dMinIncAngle(fMinIncAngle), _dMaxIncAngle(fMaxIncAngle),
_ulMinLifeTime(ulMinLifeTime), _ulMaxLifeTime(ulMaxLifeTime)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;           
    
    for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = Randomdouble(_x1, _x2);
        fY = Randomdouble(_y1, _y2);

        fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
        fIncY = Randomdouble(_dMinIncY, _dMaxIncY);
    
        fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
        fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);
    
        ulLifeTime = _ulMinLifeTime + ((unsigned long)rand()%(_ulMaxLifeTime-_ulMinLifeTime));
    
        _pParticles.push_back(new CParticle2D(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
    
    _pImage = new CSprite(cSpriteFilename);	
}

/**
   Konstruktor klasy.

   @param pImage wskaznik do istniej�cego ju� sprite
   @param ulCount ile ma by� cz�steczek
   @param fX1 obszar startowy prostokata
   @param fY1 obszar startowy prostokata
   @param fX2 obszar startowy prostokata
   @param fY2 obszar startowy prostokata
   @param fMinIncX minimalna delta wspolrzednych X per tick
   @param fMinIncY minimalna delta wspolrzednych Y per tick
   @param fMaxIncX maxymalna delta wspolrzednych X per tick
   @param fMaxIncY maxymalna delta wspolrzednych Y per tick
   @param fAlpha startowa prze�roczysto��
   @param fMinIncAlpha minimalna delta prze�roczysto�ci per tick
   @param fMaxIncAlpha maxymalna delta prze�roczysto�ci per tick
   @param fMinIncAngle minimalna delta k�ta per tick
   @param fMaxIncAngle maxymalna delta k�ta per tick
   @param ulMinLifeTime minimalna d�ugo�� �ycia cz�stki
   @param ulMaxLifeTime maxymalna d�ugo�� �ycia cz�stki
   
   @return none
*/

CParticle2DManager::CParticle2DManager(CSprite *pImage, unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) :
_r(1), _g(1), _b(1), _a(1),
_ulCount(ulCount),
_x1(fX1), _y1(fY1), _x2(fX2), _y2(fY2),
_dMinIncX(fMinIncX), _dMaxIncX(fMaxIncX),
_dMinIncY(fMinIncY), _dMaxIncY(fMaxIncY),
_dAlpha(fAlpha), _dMinIncAlpha(fMinIncAlpha), _dMaxIncAlpha(fMaxIncAlpha),
_dAngle(fAngle), _dMinIncAngle(fMinIncAngle), _dMaxIncAngle(fMaxIncAngle),
_ulMinLifeTime(ulMinLifeTime), _ulMaxLifeTime(ulMaxLifeTime)
{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = Randomdouble(_x1, _x2);
		fY = Randomdouble(_y1, _y2);

		fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
		fIncY = Randomdouble(_dMinIncY, _dMaxIncY);

		fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
		fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);

		ulLifeTime = _ulMinLifeTime + ((unsigned long)rand() % (_ulMaxLifeTime - _ulMinLifeTime));

		_pParticles.push_back(new CParticle2D(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

	_pImage = pImage;	// przekazujemy wskaznik przez referencje

}

/**
   Ustawienie nowych parametr�w

   @param pImage wskaznik do istniejacego juz sprite
   @param ulCount ile ma by� cz�steczek
   @param fX1 obszar startowy prostokata
   @param fY1 obszar startowy prostokata
   @param fX2 obszar startowy prostokata
   @param fY2 obszar startowy prostokata
   @param fMinIncX minimalna delta wspolrzednych X per tick
   @param fMinIncY minimalna delta wspolrzednych Y per tick
   @param fMaxIncX maxymalna delta wspolrzednych X per tick
   @param fMaxIncY maxymalna delta wspolrzednych Y per tick
   @param fAlpha startowa prze�roczysto��
   @param fMinIncAlpha minimalna delta prze�roczysto�ci per tick
   @param fMaxIncAlpha maxymalna delta prze�roczysto�ci per tick
   @param fMinIncAngle minimalna delta k�ta per tick
   @param fMaxIncAngle maxymalna delta k�ta per tick
   @param ulMinLifeTime minimalna d�ugo�� �ycia cz�stki
   @param ulMaxLifeTime maxymalna d�ugo�� �ycia cz�stki

   @return none
*/

void CParticle2DManager::Reset(CSprite *pImage, unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) 

{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	_ulCount = ulCount;

	_x1 = fX1; _y1 = fY1; _x2 = fX2; _y2 = fY2;

	_dMinIncX = fMinIncX; _dMinIncY = fMinIncY;
	_dMaxIncX = fMaxIncX; _dMaxIncY = fMaxIncY;

	_dAlpha = fAlpha; _dMinIncAlpha = fMinIncAlpha; _dMaxIncAlpha = fMaxIncAlpha;
	_dAngle = fAngle; _dMinIncAngle = fMinIncAngle; _dMaxIncAngle = fMaxIncAngle;

	_ulMinLifeTime = ulMinLifeTime;
	_ulMaxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = Randomdouble(_x1, _x2);
		fY = Randomdouble(_y1, _y2);

		fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
		fIncY = Randomdouble(_dMinIncY, _dMaxIncY);

		fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
		fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);

		ulLifeTime = _ulMinLifeTime + ((unsigned long)rand() % (_ulMaxLifeTime - _ulMinLifeTime));

		_pParticles.push_back(new CParticle2D(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

	_pImage = pImage;

}

/**
   Zmieniamy wszystkie parametry poza wskaznikiem na sprite.
   Obarz pozostaje ten sam.

   @param ulCount ile ma by� cz�steczek
   @param fX1 obszar startowy prostokata
   @param fY1 obszar startowy prostokata
   @param fX2 obszar startowy prostokata
   @param fY2 obszar startowy prostokata
   @param fMinIncX minimalna delta wspolrzednych X per tick
   @param fMinIncY minimalna delta wspolrzednych Y per tick
   @param fMaxIncX maxymalna delta wspolrzednych X per tick
   @param fMaxIncY maxymalna delta wspolrzednych Y per tick
   @param fAlpha startowa prze�roczysto��
   @param fMinIncAlpha minimalna delta prze�roczysto�ci per tick
   @param fMaxIncAlpha maxymalna delta prze�roczysto�ci per tick
   @param fMinIncAngle minimalna delta k�ta per tick
   @param fMaxIncAngle maxymalna delta k�ta per tick
   @param ulMinLifeTime minimalna d�ugo�� �ycia cz�stki
   @param ulMaxLifeTime maxymalna d�ugo�� �ycia cz�stki

   @return none
*/

void CParticle2DManager::Reset(unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime)
{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	_ulCount = ulCount;

	_x1 = fX1; _y1 = fY1; _x2 = fX2; _y2 = fY2;

	_dMinIncX = fMinIncX; _dMinIncY = fMinIncY;
	_dMaxIncX = fMaxIncX; _dMaxIncY = fMaxIncY;

	_dAlpha = fAlpha; _dMinIncAlpha = fMinIncAlpha; _dMaxIncAlpha = fMaxIncAlpha;
	_dAngle = fAngle; _dMinIncAngle = fMinIncAngle; _dMaxIncAngle = fMaxIncAngle;

	_ulMinLifeTime = ulMinLifeTime;
	_ulMaxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = Randomdouble(_x1, _x2);
		fY = Randomdouble(_y1, _y2);

		fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
		fIncY = Randomdouble(_dMinIncY, _dMaxIncY);

		fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
		fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);

		ulLifeTime = _ulMinLifeTime + ((unsigned long)rand() % (_ulMaxLifeTime - _ulMinLifeTime));

		_pParticles.push_back(new CParticle2D(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

}

/**
   Wygenerowanie nowych pozycji dla wszystkich cz�stek.

   @param ulCount mo�liwe jest nadanie nowej liczby cz�stek

   @return none
*/

void CParticle2DManager::Restart(unsigned long ulCount)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

	_pParticles.clear();

	for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = Randomdouble(_x1, _x2);
        fY = Randomdouble(_y1, _y2);

        fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
        fIncY = Randomdouble(_dMinIncY, _dMaxIncY);
    
        fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
        fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);
    
        ulLifeTime = _ulMinLifeTime + ((unsigned long)rand()%(_ulMaxLifeTime-_ulMinLifeTime));
    
        _pParticles.push_back(new CParticle2D(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
}

/**
   Wygenerowanie nowych pozycji dla wszystkich cz�stek.

   @param none

   @return none
*/

void CParticle2DManager::Restart(void)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

	_pParticles.clear();

	for (unsigned long i=0; i<_ulCount; i++)
    {    
  
        fX = Randomdouble(_x1, _x2);
        fY = Randomdouble(_y1, _y2);

        fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
        fIncY = Randomdouble(_dMinIncY, _dMaxIncY);
    
        fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
        fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);
    
        ulLifeTime = _ulMinLifeTime + ((unsigned long)rand()%(_ulMaxLifeTime-_ulMinLifeTime));
    
        _pParticles.push_back(new CParticle2D(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
}

/**
   Destruktor klasy.

   @param none

   @return none
*/

CParticle2DManager::~CParticle2DManager()
{
	for (unsigned int i=0; i<_pParticles.size(); i++)
		delete _pParticles[i];

	_pParticles.clear();
    SafeDelete(_pImage);
}

/**
   Wygenerowanie nowej cz�steczki, je�eli min�� czas jej �ycia.

   @param ulIndex numer czastki

   @return none
*/

void CParticle2DManager::Regenerate(unsigned long ulIndex)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

    fX = Randomdouble(_x1, _x2);
    fY = Randomdouble(_y1, _y2);
    
    fIncX = Randomdouble(_dMinIncX, _dMaxIncX);
    fIncY = Randomdouble(_dMinIncY, _dMaxIncY);
    
    fIncAlpha = Randomdouble(_dMinIncAlpha, _dMaxIncAlpha);
    fIncAngle = Randomdouble(_dMinIncAngle, _dMaxIncAngle);
    
    ulLifeTime = _ulMinLifeTime + ((unsigned long)rand()%(_ulMaxLifeTime-_ulMinLifeTime));
    
    _pParticles[ulIndex]->Regenerate(fX, fY, _dAlpha, _dAngle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime); 
    
}

/**
   Wyrenderowanie wszystkich cz�stek.

   @param ulTimer aktualny czas

   @return none
*/

int CParticle2DManager::Render(unsigned long ulTimer)
{   
	if (_pImage == NULL)
		return 0;

	for (unsigned long i=0; i<_pParticles.size(); i++)
    {
        if (_pParticles[i]->Update(ulTimer))
        {            
            _pImage->Position((float)_pParticles[i]->x(),(float)_pParticles[i]->y());
			   _pImage->fRotation((float)_pParticles[i]->dAngle());
			   _pImage->fAlfa((float)_pParticles[i]->dAlpha());	
			   _pImage->Color(_r, _g, _b);
			   _pImage->RenderC();                             
        }
        else 
        {	
			if (_isLoop)
				Regenerate(i);        
        }
    }    
        
    return 0;   
}

/**
   Ustawienie wsp�rz�dnych prostok�ta emitera.

   @param x1 wsp�rz�dne prostok�ta emitera na ekranie
   @param y2 wsp�rz�dne prostok�ta emitera na ekranie
   @param x2 wsp�rz�dne prostok�ta emitera na ekranie
   @param y2 wsp�rz�dne prostok�ta emitera na ekranie

   @return none
*/

void CParticle2DManager::SetXY(double x1, double y1, double x2, double y2)
{
	_x1 = x1;	_x2 = x2; 
	_y1 = y1;	_y2 = y2;
}

/**
   Ustawienie inkrementator�w emitera.

   @param minX minimalny zakres inkrementator�w emitera
   @param minY minimalny zakres inkrementator�w emitera
   @param maxX maksymalny zakres inkrementator�w emitera
   @param maxY maksymalny zakres inkrementator�w emitera

   @return none
*/

void CParticle2DManager::SetInc(double minX, double minY, double maxX, double maxY)
{
	_dMinIncX = minX; 	_dMinIncY = minY;
	_dMaxIncX = maxX;	   _dMaxIncY = maxY;
}

/**
   Ustawienie inkrementator�w alfy oraz aktualnej warto�ci.

   @param alpha startowa warto�� alfy
   @param min minimalny zakres inkrementatora alfy
   @param max maksymalny zakres inkrementatora alfy

   @return none
*/

void CParticle2DManager::SetAlpha(double alpha, double min, double max)
{
	_dAlpha = alpha;
	_dMinIncAlpha = min;
	_dMaxIncAlpha = max;
}

/**
   Ustawienie inkrementator�w k�ta oraz aktualnej warto�ci.

   @param angle startowa warto�� k�ta
   @param min minimalny zakres inkrementatora k�ta
   @param max maksymalny zakres inkrementatora k�ta

   @return none
*/

void CParticle2DManager::SetAngle(double angle, double min, double max)
{
	_dAngle = angle;
	_dMinIncAngle = min;
	_dMaxIncAngle = max;
}

/**
   Wygenerowanie losowej liczby double w a < ? < b

   @param a minimalna warto��
   @param b maksymalna warto��

   @return losowa liczba w podanym przedziale
*/

double CParticle2DManager::Randomdouble(double a, double b)
{
    return ((b-a)*((double)rand()/RAND_MAX))+a;
}

/**
   Ustawienie og�lnego modyfikatora koloru tekstury.

   @param r red - czerwony
   @param g green - zielony
   @param b blue - niebieski
   @param a alfa - prze�roczysto��
*/

void CParticle2DManager::Color(float r, float g, float b, float a)
{
	_r = r; 
	_g = g; 
	_b = b; 
	_a = a;
	_pImage->Color(r, g, b, a);
}

/**
   Ustawienie og�lnego modyfikatora koloru tekstury.

   @param r red - czerwony
   @param g green - zielony
   @param b blue - niebieski
*/

void CParticle2DManager::Color(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;
	_pImage->Color(r, g, b);
}
