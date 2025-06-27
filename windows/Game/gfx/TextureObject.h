#pragma once
#pragma warning(disable : 4996)

#include <SDL.h>
#include <SDL_image.h>
#include "OGL.h"
#include "Screen.h"

// zapamietuje wskazniki do tworzonych obiektow
// jezeli obiekt istnieje, nie tworzymy nowego

using namespace std;

class TextureObject
{

public:

	TextureObject(char filename[], oglTexture *object)
	{
		_object = object;
		strcpy(textureName, filename);
	}

	~TextureObject() {};

	// jezeli to jest podana nazwa pliku to zwraca wskaznik, w przeciwnym razie zwraca null

	oglTexture* get(char filename[])
	{
		return (strcmp(filename, textureName)) ?
			NULL : _object;
	}

	void set(oglTexture* object)
	{
		_object = object;
	}

	void set(char filename[], oglTexture* object)
	{
		_object = object;
		strcpy(textureName, filename);
	}

private:

	oglTexture* _object;
	char textureName[256];

};

 