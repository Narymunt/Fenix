#include "SpriteFont.h"

#pragma warning (disable:4244)

CSpriteFont::CSpriteFont(CScreen *pScreen)
{
	for (int i=0; i<37; i++)
		m_pCharTable[i] = NULL;

	m_pCharTable[0] = new CSprite(pScreen,"FONT_A");
	m_pCharTable[1] = new CSprite(pScreen,"FONT_B");
	m_pCharTable[2] = new CSprite(pScreen,"FONT_C");
	m_pCharTable[3] = new CSprite(pScreen,"FONT_D");
	m_pCharTable[4] = new CSprite(pScreen,"FONT_E");
	m_pCharTable[5] = new CSprite(pScreen,"FONT_F");
	m_pCharTable[6] = new CSprite(pScreen,"FONT_G");
	m_pCharTable[7] = new CSprite(pScreen,"FONT_H");
	m_pCharTable[8] = new CSprite(pScreen,"FONT_I");
	m_pCharTable[9] = new CSprite(pScreen,"FONT_J");
	m_pCharTable[10] = new CSprite(pScreen,"FONT_K");
	m_pCharTable[11] = new CSprite(pScreen,"FONT_L");
	m_pCharTable[12] = new CSprite(pScreen,"FONT_M");
	m_pCharTable[13] = new CSprite(pScreen,"FONT_N");
	m_pCharTable[14] = new CSprite(pScreen,"FONT_O");
	m_pCharTable[15] = new CSprite(pScreen,"FONT_P");
	m_pCharTable[16] = new CSprite(pScreen,"FONT_Q");
	m_pCharTable[17] = new CSprite(pScreen,"FONT_R");
	m_pCharTable[18] = new CSprite(pScreen,"FONT_S");
	m_pCharTable[19] = new CSprite(pScreen,"FONT_T");
	m_pCharTable[20] = new CSprite(pScreen,"FONT_U");
	m_pCharTable[21] = new CSprite(pScreen,"FONT_V");
	m_pCharTable[22] = new CSprite(pScreen,"FONT_W");
	m_pCharTable[23] = new CSprite(pScreen,"FONT_X");
	m_pCharTable[24] = new CSprite(pScreen,"FONT_Y");
	m_pCharTable[25] = new CSprite(pScreen,"FONT_Z");
	m_pCharTable[26] = new CSprite(pScreen,"FONT_COMA");
	m_pCharTable[27] = new CSprite(pScreen,"FONT_0");
	m_pCharTable[28] = new CSprite(pScreen,"FONT_1");
	m_pCharTable[29] = new CSprite(pScreen,"FONT_2");
	m_pCharTable[30] = new CSprite(pScreen,"FONT_3");
	m_pCharTable[31] = new CSprite(pScreen,"FONT_4");
	m_pCharTable[32] = new CSprite(pScreen,"FONT_5");
	m_pCharTable[33] = new CSprite(pScreen,"FONT_6");
	m_pCharTable[34] = new CSprite(pScreen,"FONT_7");
	m_pCharTable[35] = new CSprite(pScreen,"FONT_8");
	m_pCharTable[36] = new CSprite(pScreen,"FONT_9");
}


CSpriteFont::~CSpriteFont()
{
	for (int i=0; i<37; i++)
		SafeDelete(m_pCharTable[i]);
}

void CSpriteFont::Print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[])
{
	int iCurrentX;
	char cLetter;

	iCurrentX = iX; 

	for (int i=0; i<strlen(cText); i++)
	{
		cLetter = toupper(cText[i]);

		switch (cLetter)
		{

			case 'A':
				m_pCharTable[0]->Position(iCurrentX, iY);
				m_pCharTable[0]->Scale(fSizeX,fSizeY);
				m_pCharTable[0]->Render();
				iCurrentX += (int)(512 * fSizeX);  
			break;
			
			case 'B':
				m_pCharTable[1]->Position(iCurrentX, iY);
				m_pCharTable[1]->Scale(fSizeX,fSizeY);
				m_pCharTable[1]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'C':
				m_pCharTable[2]->Position(iCurrentX, iY);
				m_pCharTable[2]->Scale(fSizeX,fSizeY);
				m_pCharTable[2]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'D':
				m_pCharTable[3]->Position(iCurrentX, iY);
				m_pCharTable[3]->Scale(fSizeX,fSizeY);
				m_pCharTable[3]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'E':
				m_pCharTable[4]->Position(iCurrentX, iY);
				m_pCharTable[4]->Scale(fSizeX,fSizeY);
				m_pCharTable[4]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'F':
				m_pCharTable[5]->Position(iCurrentX, iY);
				m_pCharTable[5]->Scale(fSizeX,fSizeY);
				m_pCharTable[5]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'G':
				m_pCharTable[6]->Position(iCurrentX, iY);
				m_pCharTable[6]->Scale(fSizeX,fSizeY);
				m_pCharTable[6]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'H':
				m_pCharTable[7]->Position(iCurrentX, iY);
				m_pCharTable[7]->Scale(fSizeX,fSizeY);
				m_pCharTable[7]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'I':
				m_pCharTable[8]->Position(iCurrentX, iY);
				m_pCharTable[8]->Scale(fSizeX,fSizeY);
				m_pCharTable[8]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'J':
				m_pCharTable[9]->Position(iCurrentX, iY);
				m_pCharTable[9]->Scale(fSizeX,fSizeY);
				m_pCharTable[9]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'K':
				m_pCharTable[10]->Position(iCurrentX, iY);
				m_pCharTable[10]->Scale(fSizeX,fSizeY);
				m_pCharTable[10]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'L':
				m_pCharTable[11]->Position(iCurrentX, iY);
				m_pCharTable[11]->Scale(fSizeX,fSizeY);
				m_pCharTable[11]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'M':
				m_pCharTable[12]->Position(iCurrentX, iY);
				m_pCharTable[12]->Scale(fSizeX,fSizeY);
				m_pCharTable[12]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'N':
				m_pCharTable[13]->Position(iCurrentX, iY);
				m_pCharTable[13]->Scale(fSizeX,fSizeY);
				m_pCharTable[13]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'O':
				m_pCharTable[14]->Position(iCurrentX, iY);
				m_pCharTable[14]->Scale(fSizeX,fSizeY);
				m_pCharTable[14]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'P':
				m_pCharTable[15]->Position(iCurrentX, iY);
				m_pCharTable[15]->Scale(fSizeX,fSizeY);
				m_pCharTable[15]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'Q':
				m_pCharTable[16]->Position(iCurrentX, iY);
				m_pCharTable[16]->Scale(fSizeX,fSizeY);
				m_pCharTable[16]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'R':
				m_pCharTable[17]->Position(iCurrentX, iY);
				m_pCharTable[17]->Scale(fSizeX,fSizeY);
				m_pCharTable[17]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'S':
				m_pCharTable[18]->Position(iCurrentX, iY);
				m_pCharTable[18]->Scale(fSizeX,fSizeY);
				m_pCharTable[18]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'T':
				m_pCharTable[19]->Position(iCurrentX, iY);
				m_pCharTable[19]->Scale(fSizeX,fSizeY);
				m_pCharTable[19]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'U':
				m_pCharTable[20]->Position(iCurrentX, iY);
				m_pCharTable[20]->Scale(fSizeX,fSizeY);
				m_pCharTable[20]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'V':
				m_pCharTable[21]->Position(iCurrentX, iY);
				m_pCharTable[21]->Scale(fSizeX,fSizeY);
				m_pCharTable[21]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'W':
				m_pCharTable[22]->Position(iCurrentX, iY);
				m_pCharTable[22]->Scale(fSizeX,fSizeY);
				m_pCharTable[22]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'X':
				m_pCharTable[23]->Position(iCurrentX, iY);
				m_pCharTable[23]->Scale(fSizeX,fSizeY);
				m_pCharTable[23]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'Y':
				m_pCharTable[24]->Position(iCurrentX, iY);
				m_pCharTable[24]->Scale(fSizeX,fSizeY);
				m_pCharTable[24]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'Z':
				m_pCharTable[25]->Position(iCurrentX, iY);
				m_pCharTable[25]->Scale(fSizeX,fSizeY);
				m_pCharTable[25]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '.':
				m_pCharTable[26]->Position(iCurrentX, iY);
				m_pCharTable[26]->Scale(fSizeX,fSizeY);
				m_pCharTable[26]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '0':
				m_pCharTable[27]->Position(iCurrentX, iY);
				m_pCharTable[27]->Scale(fSizeX,fSizeY);
				m_pCharTable[27]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '1':
				m_pCharTable[28]->Position(iCurrentX, iY);
				m_pCharTable[28]->Scale(fSizeX,fSizeY);
				m_pCharTable[28]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '2':
				m_pCharTable[29]->Position(iCurrentX, iY);
				m_pCharTable[29]->Scale(fSizeX,fSizeY);
				m_pCharTable[29]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '3':
				m_pCharTable[30]->Position(iCurrentX, iY);
				m_pCharTable[30]->Scale(fSizeX,fSizeY);
				m_pCharTable[30]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '4':
				m_pCharTable[31]->Position(iCurrentX, iY);
				m_pCharTable[31]->Scale(fSizeX,fSizeY);
				m_pCharTable[31]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '5':
				m_pCharTable[32]->Position(iCurrentX, iY);
				m_pCharTable[32]->Scale(fSizeX,fSizeY);
				m_pCharTable[32]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '6':
				m_pCharTable[33]->Position(iCurrentX, iY);
				m_pCharTable[33]->Scale(fSizeX,fSizeY);
				m_pCharTable[33]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '7':
				m_pCharTable[34]->Position(iCurrentX, iY);
				m_pCharTable[34]->Scale(fSizeX,fSizeY);
				m_pCharTable[34]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '8':
				m_pCharTable[35]->Position(iCurrentX, iY);
				m_pCharTable[35]->Scale(fSizeX,fSizeY);
				m_pCharTable[35]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '9':
				m_pCharTable[36]->Position(iCurrentX, iY);
				m_pCharTable[36]->Scale(fSizeX,fSizeY);
				m_pCharTable[36]->Render();
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case ' ':
				iCurrentX += (int)(512 * fSizeX); 
			break;		
		}
		

	}
}

int CSpriteFont::iSize(float fSizeX, char cText[])	// zwraca ile szerokoœci bêdzie zajmowaæ dany napis
{
	int iCurrentX;
	char cLetter;

	iCurrentX = 0; 

	for (int i=0; i<strlen(cText); i++)
	{
		cLetter = toupper(cText[i]);

		switch (cLetter)
		{

			case 'A':
				iCurrentX += (int)(512 * fSizeX);  
			break;
			
			case 'B':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'C':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'D':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'E':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'F':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'G':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'H':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'I':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'J':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'K':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'L':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'M':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'N':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'O':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'P':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'Q':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'R':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'S':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'T':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'U':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'V':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'W':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'X':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'Y':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case 'Z':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '.':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '0':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '1':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '2':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '3':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '4':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '5':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '6':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '7':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '8':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case '9':
				iCurrentX += (int)(512 * fSizeX); 
			break;

			case ' ':
				iCurrentX += (int)(512 * fSizeX); 
			break;		
		}
	}

	return iCurrentX;
}