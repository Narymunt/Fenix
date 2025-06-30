#include "SceneEditor.h"

SceneEditor::SceneEditor()
{
	_background = NULL;
	_exitButton = NULL;
	_timerStart = 0;
	_isOpen = false;
}

SceneEditor::~SceneEditor()
{
	close();
}

void SceneEditor::open(Screen* screen)
{
	_background = new Sprite((char*)"grid.jpg");

//	_exitButton = new ButtonTTF((char*)"orange.png", (char*) "blue.png", (char*)"green.png",(char*)"tutaj JAKI� exit");
	_exitButton = new ButtonTTF((char*)"green_0.png", (char*)"green_1.png", (char*)"green.png", (char*)"some text");
	_exitButton->set(screen->_x[500], screen->_y[500], screen->_x[600], screen->_y[550]);
	_exitButton->alfa(1.f);

	_isOpen = true;
}

void SceneEditor::close(void)
{
	safeDelete(_background);
	safeDelete(_exitButton);
	_isOpen = false;
}


int SceneEditor::render(unsigned long timer, Mouse* mouse)
{
	if (!mouse->_isL)
		_isMouseLock = false;

	if (_timerStart == 0)
		_timerStart = timer;

	oglClear();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_background->position(i * 256, j * 256);
			_background->render();
		}
	}

	return (_exitButton->render(mouse) == ON_LEFT && !_isMouseLock) ? 1 : 0;
}

