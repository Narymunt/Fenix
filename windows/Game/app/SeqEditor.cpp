#include "SeqEditor.h"

SeqEditor::SeqEditor()
{
	_background = NULL;
	_exitButton = NULL;
	_timerStart = 0;
	_isOpen = false;
}

SeqEditor::~SeqEditor()
{
	close();
}

void SeqEditor::open(Screen* screen)
{
	_background = new Sprite((char*)"grid.jpg");

	_exitButton = new ButtonTTF((char*)"orange.png", (char*) "blue.png", (char*)"green.png",(char*)"exit");
	_exitButton->set(screen->_x[500], screen->_y[500], screen->_x[600], screen->_y[550]);
	_exitButton->alfa(0.5f);

	_isOpen = true;
}

void SeqEditor::close(void)
{
	safeDelete(_background);
	safeDelete(_exitButton);
	_isOpen = false;
}


int SeqEditor::render(unsigned long timer, Mouse* mouse)
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

