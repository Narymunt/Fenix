#include "SpriteManager.h"

#pragma warning(disable : 4996)


oglTexture* SpriteManager::get(char filename[])
{
	oglTexture* ret = NULL;

	for (unsigned int i = 0; i < _texturePool.size(); i++)
	{
		if (!ret)
			ret = _texturePool[i]->get(filename);
	}
	
	return ret;
}

void SpriteManager::add(char filename[], oglTexture* sprite)
{
	if (!get(filename))
		_texturePool.push_back(new TextureObject(filename, sprite));
}

void SpriteManager::set(char filename[], oglTexture* sprite)
{
	for (unsigned int i = 0; i < _texturePool.size(); i++)
	{
		if (_texturePool[i]->get(filename))
			_texturePool[i]->set(filename, sprite);
	}

}
