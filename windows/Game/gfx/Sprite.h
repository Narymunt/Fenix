#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "OGL.h"
#include "Screen.h"
#include "../io/Datafile.h"
#include "../gfx/SpriteObject.h"
#include "../io/Zip.h"
#include "../io/Unzip.h"

class CSprite  : public CSpriteObject
{

public:
	
	// bezwzgledna nazwa pliku np. "obiekt.jpg"

	CSprite(char filename[]);
	CSprite(char filename[], int x, int y);
	CSprite(char filename[], int x, int y, float scaleX, float scaleY);
	CSprite(char filename[], int x, int y, float scaleX, float scaleY, float rotation);
	CSprite(char filename[], int x, int y, float a);
	CSprite(char filename[], int x, int y, float scaleX, float scaleY, float a, float rotation);
	CSprite(char filename[], float a);

	bool	load(char filename[]);	// pomocnicza dla funkcji ponizej 

	void	loadFromZip(char filename[]);			// wczytaj z pliku ZIP_FILE (haslo)
	void	loadFromDatafile(char filename[]);	// wczytaj z pliku DATA_FILE (haslo)
	void	loadFromFile(char filename[]);		// wczytaj z katalogu data/
	void	loadFromPAQ(char filename[]) {};

	~CSprite();

	void	render(int x, int y, float a);
	void	render(void);						// use top left coords

	void	update(void);						// update factors and render
	void	update(unsigned long timer);		// tutaj wszystkie parapetry sa aktualizowane na podstawie timera

private:

	oglTexture			*_sprite;

};

 