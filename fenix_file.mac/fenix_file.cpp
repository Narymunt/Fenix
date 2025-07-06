// fenix_file.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

FILE *plik_conf;	// tutaj jest lista plikow w katalogu	fenix_file.cfg
FILE *plik_out;		// plik wyjsciowy	data.bin
FILE *plik_in;		// pliki wczytywane 
FILE *plik_cpp;		// plik data.h
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

pFile = fopen( filename, "rb" );
fseek( pFile, 0, SEEK_END );
int Size = ftell( pFile );
fclose( pFile );
return Size;
}



int main(int argc, char* argv[])
{
	
	if ((plik_conf = fopen("fenix_file.cfg","rt"))==NULL)
	{
		printf("brak pliku fenix_file.cfg\n");	
		return -1;
	}
	
	plik_out = fopen("data.bin","wb");
	plik_cpp = fopen("data.h","wt");
	plik_map = fopen("data.map","wt");

	fprintf(plik_cpp,"// automatycznie generowane zasoby i offsety na podstawie konwertera\n\n");

	fscanf(plik_conf,"%s\n",&pass);	// wczytaj haslo

	fprintf(plik_cpp,"static char DATA_RESOURCE[]=\"data.bin\";\n");	// nazwa pliku
	fprintf(plik_cpp,"static char DATA_PASSWORD[]=\"%s\";\n",pass);			// haslo do odkodowania
	fprintf(plik_cpp,"static char DATA_MAP[]=\"data.map\";\n\n");
	linia[0]=100;	

	fprintf(plik_out,"SHODAN9");

	ulIndex = 7;

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


			fprintf(plik_cpp,"#define OFFSET_%s %d\n",linia,ulIndex);
			fprintf(plik_cpp,"#define SIZE_%s %d\n\n",linia,iSize);
			

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

	fprintf(plik_map,"<end>");

	fclose(plik_map);
	fclose(plik_cpp);
	fclose(plik_out);
	fclose(plik_conf);


	return 0;
}

