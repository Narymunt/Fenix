#pragma once

#include <stdlib.h>
#include <stdio.h>

void fx_debug(char cInfo[])
{
	FILE *plik;
	
	plik = fopen("debug.log","at");
	fprintf(plik,cInfo);
	
	fclose(plik);
}

