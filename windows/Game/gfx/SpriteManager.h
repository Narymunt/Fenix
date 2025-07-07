#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "OGL.h"
#include "Screen.h"
#include "TextureObject.h"

// zapamietuje wskazniki do tworzonych obiektow
// jezeli obiekt istnieje, nie tworzymy nowego

// SINGLETON

using namespace std;

class SpriteManager
{

public:

	SpriteManager() { };

	~SpriteManager() 
	{
		for (unsigned int i = 0; i < _texturePool.size(); i++)
			delete _texturePool[i];

		_texturePool.clear();
	};

	oglTexture* get(char filename[]);
	void add(char filename[], oglTexture* sprite);
	void set(char filename[], oglTexture* sprite);

private:

	vector <TextureObject*> _texturePool;

};

 