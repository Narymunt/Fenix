#pragma once

#include <stdio.h>
#include "zip.h"
#include "unzip.h"

class CZipImageTGA
{

public : 

	CZipImageTGA(char cZipFile[], char cPassword[], char cFilename[]);	
	~CZipImageTGA();

	int	iSizeX(void);
	int	iSizeY(void);
	int	iBpp(void);

	unsigned char cPixelR(int x, int y);
	unsigned char cPixelG(int x, int y);
	unsigned char cPixelB(int x, int y);
	unsigned char cPixelA(int x, int y);

	void cPixelR(int x, int y, unsigned char color);
	void cPixelG(int x, int y, unsigned char color);
	void cPixelB(int x, int y, unsigned char color);
	void cPixelA(int x, int y, unsigned char color);
	
	unsigned char cData(int iOffset);
	void cData(int iOffset, unsigned char color);

protected :

	char	*m_pData;
	unsigned char	m_pHeader[18];
	int		m_iSizeX, m_iSizeY, m_iBpp;

};

#endif
