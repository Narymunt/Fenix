// fenix_file.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "stdafx.h"
#include "tinydir.h"

FILE *plik_conf;	// tutaj jest lista plikow w katalogu	fenix_file.cfg
FILE *plik_out;		// plik wyjsciowy	data.bin
FILE *plik_in;		// pliki wczytywane 
FILE *plik_map;		// plik data.map ulatwiajacy slownikowanie zasobow

char linia[1024];	// tutaj nazwa aktualnie przerabianego pliku
char pass[8];

unsigned char *buffer_in;		// dane do dolaczenia
unsigned char *buffer_out;

int iZnak;	// do obracania znaku
unsigned char cZnak;

int iIndex;	// ktora literka hasla

int	iSize;

unsigned long ulIndex;

void UpOnly(char str[])
{
	int i=0;
	char c;
	
	while (str[i])
	{
		c = str[i];
		str[i]= toupper(c);
		i++;
	}
}

int filesize( char filename[] )
{
FILE *pFile = NULL;

fopen_s( &pFile, filename, "rb" );
fseek( pFile, 0, SEEK_END );
int Size = ftell( pFile );
fclose( pFile );
return Size;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	if ((plik_conf = fopen("fenix_file.cfg","rt"))==NULL)
	{
		printf("brak pliku fenix_file.cfg\n");	
		return -1;
	}
	
	plik_out = fopen("data.bin","wb");
	plik_map = fopen("data.map","wt");

	fscanf(plik_conf,"%s\n",&pass);	// wczytaj haslo

	linia[0]=100;	

	fprintf(plik_out,"SHODAN9");

	ulIndex = 7;

	tinydir_dir dir;
	int result = tinydir_open_sorted(&dir, "data");

	if (result == -1)
	{
		printf("Nie mo¿na otworzyæ katalogu data\n");
		return 0;
	}

	for (int i = 0; i < dir.n_files; i++)
	{
		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);
		
		if (!file.is_dir)	// katalogow nie konwertujemy
		{
			printf("%s\n", file.name);
			sprintf(linia, "data/%s", file.name);
			iSize = filesize(linia);	// sprawdz rozmiar pliku

			buffer_in = new unsigned char[iSize];
			buffer_out = new unsigned char[iSize];

			plik_in = fopen(linia, "rb");	// wczytaj plik
			fread(buffer_in, iSize, 1, plik_in);

			fprintf(plik_map, "%s %d %d\n", file.name, ulIndex, iSize);

			iIndex = 0;

			UpOnly(linia);

			for (int i = 0; i<1024; i++)
			{
				if (linia[i] == 45 || linia[i] == 46)		// -.
					linia[i] = 95;		// _
			}

			ulIndex += iSize;

			for (int i = 0; i<iSize; i++)	// rotujemy znaki
			{
				buffer_out[i] = buffer_in[i] ^ pass[iIndex];

				iIndex++;

				if (iIndex == 8)
					iIndex = 0;
			}

			fwrite(buffer_out, iSize, 1, plik_out);	// zapisz dane			
			fclose(plik_in);

			delete[] buffer_in;
			delete[] buffer_out;

		} // !isDir

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

/*
	while (strcmp(linia,"<end>"))
	{
		fscanf(plik_conf,"%s\n",&linia);	// wczytaj linie pliku
		printf("PROCESSING: %s\n",linia);

		if (strcmp(linia,"<end>"))	// nazwa pliku jest
		{
			iSize = filesize(linia);
			
			buffer_in = new unsigned char[iSize];
			buffer_out = new unsigned char[iSize];

			plik_in = fopen(linia,"rb");	// wczytaj plik
			fread(buffer_in,iSize,1,plik_in);

			fprintf(plik_map,"%s %d %d\n",linia,ulIndex,iSize);

			iIndex = 0;
			
			UpOnly(linia);

			for (int i=0; i<1024; i++)
			{
				if (linia[i]==45 || linia[i]==46)		// -.
					linia[i] = 95;		// _
			}		

			ulIndex += iSize;

			for (int i=0; i<iSize; i++)	// rotujemy znaki
			{
				buffer_out[i] = buffer_in[i] ^ pass[iIndex];

				iIndex++;
				
				if (iIndex==8) 
					iIndex = 0;
			}

			fwrite(buffer_out,iSize,1,plik_out);	// zapisz dane			
			fclose(plik_in);

			delete [] buffer_in;
			delete [] buffer_out;
		}
	}
*/

	fprintf(plik_map,"<end>");

	fclose(plik_map);
	fclose(plik_out);
	fclose(plik_conf);


	return 0;
}

