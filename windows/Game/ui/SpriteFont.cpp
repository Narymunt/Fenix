#include "SpriteFont.h"

#pragma warning (disable:4244)

SpriteFont::SpriteFont(Screen *pScreen)
{
	for (int i=0; i<37; i++)
		_charTable[i] = NULL;

	_charTable[0] = new Sprite((char*)"FONT_A");
	_charTable[1] = new Sprite((char*)"FONT_B");
	_charTable[2] = new Sprite((char*)"FONT_C");
	_charTable[3] = new Sprite((char*)"FONT_D");
	_charTable[4] = new Sprite((char*)"FONT_E");
	_charTable[5] = new Sprite((char*)"FONT_F");
	_charTable[6] = new Sprite((char*)"FONT_G");
	_charTable[7] = new Sprite((char*)"FONT_H");
	_charTable[8] = new Sprite((char*)"FONT_I");
	_charTable[9] = new Sprite((char*)"FONT_J");
	_charTable[10] = new Sprite((char*)"FONT_K");
	_charTable[11] = new Sprite((char*)"FONT_L");
	_charTable[12] = new Sprite((char*)"FONT_M");
	_charTable[13] = new Sprite((char*)"FONT_N");
	_charTable[14] = new Sprite((char*)"FONT_O");
	_charTable[15] = new Sprite((char*)"FONT_P");
	_charTable[16] = new Sprite((char*)"FONT_Q");
	_charTable[17] = new Sprite((char*)"FONT_R");
	_charTable[18] = new Sprite((char*)"FONT_S");
	_charTable[19] = new Sprite((char*)"FONT_T");
	_charTable[20] = new Sprite((char*)"FONT_U");
	_charTable[21] = new Sprite((char*)"FONT_V");
	_charTable[22] = new Sprite((char*)"FONT_W");
	_charTable[23] = new Sprite((char*)"FONT_X");
	_charTable[24] = new Sprite((char*)"FONT_Y");
	_charTable[25] = new Sprite((char*)"FONT_Z");
	_charTable[26] = new Sprite((char*)"FONT_COMA");
	_charTable[27] = new Sprite((char*)"FONT_0");
	_charTable[28] = new Sprite((char*)"FONT_1");
	_charTable[29] = new Sprite((char*)"FONT_2");
	_charTable[30] = new Sprite((char*)"FONT_3");
	_charTable[31] = new Sprite((char*)"FONT_4");
	_charTable[32] = new Sprite((char*)"FONT_5");
	_charTable[33] = new Sprite((char*)"FONT_6");
	_charTable[34] = new Sprite((char*)"FONT_7");
	_charTable[35] = new Sprite((char*)"FONT_8");
	_charTable[36] = new Sprite((char*)"FONT_9");
}


SpriteFont::~SpriteFont()
{
	for (int i=0; i<37; i++)
		safeDelete(_charTable[i]);
}

void SpriteFont::print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[])
{
	int iCurrentX;
	char cLetter;

	iCurrentX = iX; 

	for (unsigned int i=0; i<strlen(cText); i++)
	{
		cLetter = toupper(cText[i]);

		switch (cLetter)
		{

			case 'A':
				_charTable[0]->position(iCurrentX, iY);
				_charTable[0]->scale(fSizeX,fSizeY);
				_charTable[0]->render();
				iCurrentX += (int)(400 * fSizeX);  
			break;
			
			case 'B':
				_charTable[1]->position(iCurrentX, iY);
				_charTable[1]->scale(fSizeX,fSizeY);
				_charTable[1]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'C':
				_charTable[2]->position(iCurrentX, iY);
				_charTable[2]->scale(fSizeX,fSizeY);
				_charTable[2]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'D':
				_charTable[3]->position(iCurrentX, iY);
				_charTable[3]->scale(fSizeX,fSizeY);
				_charTable[3]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'E':
				_charTable[4]->position(iCurrentX, iY);
				_charTable[4]->scale(fSizeX,fSizeY);
				_charTable[4]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'F':
				_charTable[5]->position(iCurrentX, iY);
				_charTable[5]->scale(fSizeX,fSizeY);
				_charTable[5]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'G':
				_charTable[6]->position(iCurrentX, iY);
				_charTable[6]->scale(fSizeX,fSizeY);
				_charTable[6]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'H':
				_charTable[7]->position(iCurrentX, iY);
				_charTable[7]->scale(fSizeX,fSizeY);
				_charTable[7]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'I':
				_charTable[8]->position(iCurrentX, iY);
				_charTable[8]->scale(fSizeX,fSizeY);
				_charTable[8]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'J':
				_charTable[9]->position(iCurrentX, iY);
				_charTable[9]->scale(fSizeX,fSizeY);
				_charTable[9]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'K':
				_charTable[10]->position(iCurrentX, iY);
				_charTable[10]->scale(fSizeX,fSizeY);
				_charTable[10]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'L':
				_charTable[11]->position(iCurrentX, iY);
				_charTable[11]->scale(fSizeX,fSizeY);
				_charTable[11]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'M':
				_charTable[12]->position(iCurrentX, iY);
				_charTable[12]->scale(fSizeX,fSizeY);
				_charTable[12]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'N':
				_charTable[13]->position(iCurrentX, iY);
				_charTable[13]->scale(fSizeX,fSizeY);
				_charTable[13]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'O':
				_charTable[14]->position(iCurrentX, iY);
				_charTable[14]->scale(fSizeX,fSizeY);
				_charTable[14]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'P':
				_charTable[15]->position(iCurrentX, iY);
				_charTable[15]->scale(fSizeX,fSizeY);
				_charTable[15]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Q':
				_charTable[16]->position(iCurrentX, iY);
				_charTable[16]->scale(fSizeX,fSizeY);
				_charTable[16]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'R':
				_charTable[17]->position(iCurrentX, iY);
				_charTable[17]->scale(fSizeX,fSizeY);
				_charTable[17]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'S':
				_charTable[18]->position(iCurrentX, iY);
				_charTable[18]->scale(fSizeX,fSizeY);
				_charTable[18]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'T':
				_charTable[19]->position(iCurrentX, iY);
				_charTable[19]->scale(fSizeX,fSizeY);
				_charTable[19]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'U':
				_charTable[20]->position(iCurrentX, iY);
				_charTable[20]->scale(fSizeX,fSizeY);
				_charTable[20]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'V':
				_charTable[21]->position(iCurrentX, iY);
				_charTable[21]->scale(fSizeX,fSizeY);
				_charTable[21]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'W':
				_charTable[22]->position(iCurrentX, iY);
				_charTable[22]->scale(fSizeX,fSizeY);
				_charTable[22]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'X':
				_charTable[23]->position(iCurrentX, iY);
				_charTable[23]->scale(fSizeX,fSizeY);
				_charTable[23]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Y':
				_charTable[24]->position(iCurrentX, iY);
				_charTable[24]->scale(fSizeX,fSizeY);
				_charTable[24]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Z':
				_charTable[25]->position(iCurrentX, iY);
				_charTable[25]->scale(fSizeX,fSizeY);
				_charTable[25]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '.':
				_charTable[26]->position(iCurrentX, iY);
				_charTable[26]->scale(fSizeX,fSizeY);
				_charTable[26]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '0':
				_charTable[27]->position(iCurrentX, iY);
				_charTable[27]->scale(fSizeX,fSizeY);
				_charTable[27]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '1':
				_charTable[28]->position(iCurrentX, iY);
				_charTable[28]->scale(fSizeX,fSizeY);
				_charTable[28]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '2':
				_charTable[29]->position(iCurrentX, iY);
				_charTable[29]->scale(fSizeX,fSizeY);
				_charTable[29]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '3':
				_charTable[30]->position(iCurrentX, iY);
				_charTable[30]->scale(fSizeX,fSizeY);
				_charTable[30]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '4':
				_charTable[31]->position(iCurrentX, iY);
				_charTable[31]->scale(fSizeX,fSizeY);
				_charTable[31]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '5':
				_charTable[32]->position(iCurrentX, iY);
				_charTable[32]->scale(fSizeX,fSizeY);
				_charTable[32]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '6':
				_charTable[33]->position(iCurrentX, iY);
				_charTable[33]->scale(fSizeX,fSizeY);
				_charTable[33]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '7':
				_charTable[34]->position(iCurrentX, iY);
				_charTable[34]->scale(fSizeX,fSizeY);
				_charTable[34]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '8':
				_charTable[35]->position(iCurrentX, iY);
				_charTable[35]->scale(fSizeX,fSizeY);
				_charTable[35]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '9':
				_charTable[36]->position(iCurrentX, iY);
				_charTable[36]->scale(fSizeX,fSizeY);
				_charTable[36]->render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case ' ':
				iCurrentX += (int)(400 * fSizeX); 
			break;		
		}
	}
}

int SpriteFont::size(float fSizeX, char cText[])	// zwraca ile szerokoœci bêdzie zajmowaæ dany napis
{
	int iCurrentX;
	char cLetter;

	iCurrentX = 0; 

	for (unsigned int i=0; i<strlen(cText); i++)
	{
		cLetter = toupper(cText[i]);

		switch (cLetter)
		{

			case 'A':
				iCurrentX += (int)(400 * fSizeX);  
			break;
			
			case 'B':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'C':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'D':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'E':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'F':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'G':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'H':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'I':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'J':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'K':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'L':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'M':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'N':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'O':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'P':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Q':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'R':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'S':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'T':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'U':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'V':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'W':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'X':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Y':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Z':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '.':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '0':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '1':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '2':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '3':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '4':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '5':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '6':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '7':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '8':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '9':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case ' ':
				iCurrentX += (int)(400 * fSizeX); 
			break;		
		}
	}

	return iCurrentX;
}