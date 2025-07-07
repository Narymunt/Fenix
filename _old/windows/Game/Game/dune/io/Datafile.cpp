// profile graczy

#include "Datafile.h"

CDatafile::CDatafile(unsigned long ulOffset, unsigned long ulSize)
{
	Load(ulOffset,ulSize);
}

CDatafile::CDatafile(char cFilename[])	// dane o offsecie itd biezemy z pliku data.map
{
	char linia[1024];
	unsigned long ulOffset;
	unsigned long ulSize;

	FILE *plik;

	plik = fopen(DATA_MAP,"rt");

	linia[0]=linia[1]=linia[2]=0;
	ulOffset = ulSize = 0;

	while (strcmp(linia,"<end>") && strcmp(linia,cFilename))
	{
		if (strcmp(linia,"<end>"))
		fscanf(plik,"%s %d %d\n",linia,&ulOffset,&ulSize);
	}

	fclose(plik);

	if (ulOffset!=0)
		Load(ulOffset,ulSize);
}

CDatafile::~CDatafile()
{
	delete []_pBuffer;
}

void CDatafile::Load(unsigned long ulOffset, unsigned long ulSize)
{
	FILE *plik;
	static int index;

	_ulSize = ulSize;

	_pBuffer = new unsigned char[ulSize];	// alokujemy bufer

	plik = fopen(DATA_RESOURCE,"rb");
	fseek(plik,ulOffset,SEEK_SET);
	fread(_pBuffer,1,ulSize,plik);
	fclose(plik);

	// odwracanie znakow

	index = 0;

	for (unsigned int i=0; i<ulSize; i++)
	{
		_pBuffer[i] = _pBuffer[i] ^ DATA_PASSWORD[index];

		index++;

		if (index==8)
			index = 0;
	}
}

unsigned char *CDatafile::pBuffer(void)
{
	return _pBuffer;
}

unsigned long CDatafile::ulSize(void)
{
	return _ulSize;
}