/**
   Particle2DManager.h
   Generuje potrzebne cz�stki i zarz�dza nimi. 
   Trzyma informacje o texturach, �eby nie powiela� sprite dla ka�dej cz�stki z osobna.
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

Particle2DManager::Particle2DManager(char cSpriteFilename[], unsigned long ulCount, 
                                   double fX1, double fY1, double fX2, double fY2, 
                                   double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
                                   double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
                                   double fAngle, double fMinIncAngle, double fMaxIncAngle,
                                   unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime, Screen *pScreen) :
_r(1), _g(1), _b(1), _a(1),
_count(ulCount),
_x1(fX1), _y1(fY1), _x2(fX2), _y2(fY2),
_minIncX(fMinIncX), _maxIncX(fMaxIncX),
_minIncY(fMinIncY), _maxIncY(fMaxIncY),
_alpha(fAlpha), _minIncAlpha(fMinIncAlpha), _maxIncAlpha(fMaxIncAlpha),
_angle(fAngle), _minIncAngle(fMinIncAngle), _maxIncAngle(fMaxIncAngle),
_minLifeTime(ulMinLifeTime), _maxLifeTime(ulMaxLifeTime)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;           
    
    for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = randomDouble(_x1, _x2);
        fY = randomDouble(_y1, _y2);

        fIncX = randomDouble(_minIncX, _maxIncX);
        fIncY = randomDouble(_minIncY, _maxIncY);
    
        fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
        fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);
    
        ulLifeTime = _minLifeTime + ((unsigned long)rand()%(_maxLifeTime-_minLifeTime));
    
        _particles.push_back(new Particle2D(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
    
    _image = new Sprite(cSpriteFilename);	
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

Particle2DManager::Particle2DManager(Sprite *pImage, unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) :
_r(1), _g(1), _b(1), _a(1),
_count(ulCount),
_x1(fX1), _y1(fY1), _x2(fX2), _y2(fY2),
_minIncX(fMinIncX), _maxIncX(fMaxIncX),
_minIncY(fMinIncY), _maxIncY(fMaxIncY),
_alpha(fAlpha), _minIncAlpha(fMinIncAlpha), _maxIncAlpha(fMaxIncAlpha),
_angle(fAngle), _minIncAngle(fMinIncAngle), _maxIncAngle(fMaxIncAngle),
_minLifeTime(ulMinLifeTime), _maxLifeTime(ulMaxLifeTime)
{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = randomDouble(_x1, _x2);
		fY = randomDouble(_y1, _y2);

		fIncX = randomDouble(_minIncX, _maxIncX);
		fIncY = randomDouble(_minIncY, _maxIncY);

		fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
		fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);

		ulLifeTime = _minLifeTime + ((unsigned long)rand() % (_maxLifeTime - _minLifeTime));

		_particles.push_back(new Particle2D(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

	_image = pImage;	// przekazujemy wskaznik przez referencje

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

void Particle2DManager::reset(Sprite *pImage, unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime) 

{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	_count = ulCount;

	_x1 = fX1; _y1 = fY1; _x2 = fX2; _y2 = fY2;

	_minIncX = fMinIncX; _minIncY = fMinIncY;
	_maxIncX = fMaxIncX; _maxIncY = fMaxIncY;

	_alpha = fAlpha; _minIncAlpha = fMinIncAlpha; _maxIncAlpha = fMaxIncAlpha;
	_angle = fAngle; _minIncAngle = fMinIncAngle; _maxIncAngle = fMaxIncAngle;

	_minLifeTime = ulMinLifeTime;
	_maxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = randomDouble(_x1, _x2);
		fY = randomDouble(_y1, _y2);

		fIncX = randomDouble(_minIncX, _maxIncX);
		fIncY = randomDouble(_minIncY, _maxIncY);

		fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
		fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);

		ulLifeTime = _minLifeTime + ((unsigned long)rand() % (_maxLifeTime - _minLifeTime));

		_particles.push_back(new Particle2D(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}

	_image = pImage;

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

void Particle2DManager::reset(unsigned long ulCount,
	double fX1, double fY1, double fX2, double fY2,
	double fMinIncX, double fMinIncY, double fMaxIncX, double fMaxIncY,
	double fAlpha, double fMinIncAlpha, double fMaxIncAlpha,
	double fAngle, double fMinIncAngle, double fMaxIncAngle,
	unsigned long ulMinLifeTime, unsigned long ulMaxLifeTime)
{
	double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
	unsigned long ulLifeTime;

	_count = ulCount;

	_x1 = fX1; _y1 = fY1; _x2 = fX2; _y2 = fY2;

	_minIncX = fMinIncX; _minIncY = fMinIncY;
	_maxIncX = fMaxIncX; _maxIncY = fMaxIncY;

	_alpha = fAlpha; _minIncAlpha = fMinIncAlpha; _maxIncAlpha = fMaxIncAlpha;
	_angle = fAngle; _minIncAngle = fMinIncAngle; _maxIncAngle = fMaxIncAngle;

	_minLifeTime = ulMinLifeTime;
	_maxLifeTime = ulMaxLifeTime;

	for (unsigned long i = 0; i<ulCount; i++)
	{

		fX = randomDouble(_x1, _x2);
		fY = randomDouble(_y1, _y2);

		fIncX = randomDouble(_minIncX, _maxIncX);
		fIncY = randomDouble(_minIncY, _maxIncY);

		fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
		fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);

		ulLifeTime = _minLifeTime + ((unsigned long)rand() % (_maxLifeTime - _minLifeTime));

		_particles.push_back(new Particle2D(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
	}
}

/**
   Wygenerowanie nowych pozycji dla wszystkich cz�stek.
   @param ulCount mo�liwe jest nadanie nowej liczby cz�stek
   @return none
*/

void Particle2DManager::restart(unsigned long ulCount)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

	_particles.clear();

	for (unsigned long i=0; i<ulCount; i++)
    {    
  
        fX = randomDouble(_x1, _x2);
        fY = randomDouble(_y1, _y2);

        fIncX = randomDouble(_minIncX, _maxIncX);
        fIncY = randomDouble(_minIncY, _maxIncY);
    
        fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
        fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);
    
        ulLifeTime = _minLifeTime + ((unsigned long)rand()%(_maxLifeTime-_minLifeTime));
    
        _particles.push_back(new Particle2D(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
}

/**
   Wygenerowanie nowych pozycji dla wszystkich cz�stek.

   @param none

   @return none
*/

void Particle2DManager::restart(void)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

	_particles.clear();

	for (unsigned long i=0; i<_count; i++)
    {    
  
        fX = randomDouble(_x1, _x2);
        fY = randomDouble(_y1, _y2);

        fIncX = randomDouble(_minIncX, _maxIncX);
        fIncY = randomDouble(_minIncY, _maxIncY);
    
        fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
        fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);
    
        ulLifeTime = _minLifeTime + ((unsigned long)rand()%(_maxLifeTime-_minLifeTime));
    
        _particles.push_back(new Particle2D(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime));
    }        
}

/**
   Destruktor klasy.

   @param none

   @return none
*/

Particle2DManager::~Particle2DManager()
{
	for (unsigned int i=0; i<_particles.size(); i++)
		delete _particles[i];

	_particles.clear();
    safeDelete(_image);
}

/**
   Wygenerowanie nowej cz�steczki, je�eli min�� czas jej �ycia.

   @param ulIndex numer czastki

   @return none
*/

void Particle2DManager::regenerate(unsigned long ulIndex)
{
    double fX, fY, fIncX, fIncY, fIncAlpha, fIncAngle;
    unsigned long ulLifeTime;

    fX = randomDouble(_x1, _x2);
    fY = randomDouble(_y1, _y2);
    
    fIncX = randomDouble(_minIncX, _maxIncX);
    fIncY = randomDouble(_minIncY, _maxIncY);
    
    fIncAlpha = randomDouble(_minIncAlpha, _maxIncAlpha);
    fIncAngle = randomDouble(_minIncAngle, _maxIncAngle);
    
    ulLifeTime = _minLifeTime + ((unsigned long)rand()%(_maxLifeTime-_minLifeTime));
    
    _particles[ulIndex]->regenerate(fX, fY, _alpha, _angle, fIncX, fIncY, fIncAlpha, fIncAngle, ulLifeTime); 
}

/**
   Wyrenderowanie wszystkich cz�stek.

   @param ulTimer aktualny czas
   @return none
*/

int Particle2DManager::render(unsigned long ulTimer)
{   
	if (_image == NULL)
		return 0;

	for (unsigned long i=0; i<_particles.size(); i++)
    {
        if (_particles[i]->update(ulTimer))
        {            
            _image->position((float)_particles[i]->x(),(float)_particles[i]->y());
            _image->_r = (float)_particles[i]->_dAngle;
		   _image->_a = (float)_particles[i]->_dAlpha;	
		   _image->color(_r, _g, _b,_a);
		   _image->render();                             
        }
        else 
        {	
			if (_loop)
				regenerate(i);        
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

void Particle2DManager::setXY(double x1, double y1, double x2, double y2)
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

void Particle2DManager::setInc(double minX, double minY, double maxX, double maxY)
{
	_minIncX = minX; _minIncY = minY;
	_maxIncX = maxX; _maxIncY = maxY;
}

/**
   Ustawienie inkrementator�w alfy oraz aktualnej warto�ci.

   @param alpha startowa warto�� alfy
   @param min minimalny zakres inkrementatora alfy
   @param max maksymalny zakres inkrementatora alfy

   @return none
*/

void Particle2DManager::alpha(double alpha, double min, double max)
{
	_alpha = alpha;
	_minIncAlpha = min;
	_maxIncAlpha = max;
}

/**
   Ustawienie inkrementator�w k�ta oraz aktualnej warto�ci.

   @param angle startowa warto�� k�ta
   @param min minimalny zakres inkrementatora k�ta
   @param max maksymalny zakres inkrementatora k�ta

   @return none
*/

void Particle2DManager::angle(double angle, double min, double max)
{
	_angle = angle;
	_minIncAngle = min;
	_maxIncAngle = max;
}

/**
   Wygenerowanie losowej liczby double w a < ? < b

   @param a minimalna warto��
   @param b maksymalna warto��

   @return losowa liczba w podanym przedziale
*/

double Particle2DManager::randomDouble(double a, double b)
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

void Particle2DManager::color(float r, float g, float b, float a)
{
	_r = r; 
	_g = g; 
	_b = b; 
	_a = a;
	_image->color(r, g, b, a);
}

/**
   Ustawienie og�lnego modyfikatora koloru tekstury.

   @param r red - czerwony
   @param g green - zielony
   @param b blue - niebieski
*/

void Particle2DManager::color(float r, float g, float b)
{
	_r = r;
	_g = g;
	_b = b;
	_image->color(r, g, b);
}
