// profile graczy

#include "Datafile.h"

CDatafile::CDatafile(unsigned long offset, unsigned long size) :
_buffer(NULL), _size(0), _empty(true)
{
	load(offset,size);
}

CDatafile::CDatafile(char filename[]) :	// dane o offsecie itd biezemy z pliku data.map
_buffer(NULL), _size(0), _empty(true)
{
	char linia[1024];
	unsigned long offset;
	unsigned long size;

	FILE *plik = NULL;

	plik = fopen(DATA_MAP,"rt");
	
	if (plik == NULL)
		printf("[ERROR]: nie mozna znalezc pliku %s\n", DATA_MAP);

	linia[0]=linia[1]=linia[2]=0;
	offset = size = 0;

	while (strcmp(linia,"<end>") && strcmp(linia,filename))
	{
		if (strcmp(linia,"<end>"))
			fscanf(plik,"%s %d %d\n",linia,&offset,&size);
	}

	fclose(plik);

	if (offset != 0)
		load(offset, size);

}

CDatafile::~CDatafile()
{
	delete []_buffer;
}

void CDatafile::load(unsigned long offset, unsigned long size)
{
	FILE *plik = NULL;
	static int index;


	_buffer = new unsigned char[size];	// alokujemy bufer

	plik = fopen(DATA_FILE,"rb");

	if (plik == NULL)
	{
		printf("[ERROR]: nie mozna znalezc pliku %s\n", DATA_MAP);
		return;
	}

	fseek(plik,offset,SEEK_SET);
	fread(_buffer,1,size,plik);
	fclose(plik);

	_size = size;
	_empty = false;

	// odwracanie znakow

	index = 0;

	for (unsigned int i=0; i<size; i++)
	{
		_buffer[i] = _buffer[i] ^ DATA_PASSWORD[index];

		index++;

		if (index==8)
			index = 0;
	}
}
