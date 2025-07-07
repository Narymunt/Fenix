// plik z zakodowanymi danymi

#pragma once

#pragma warning(disable : 4996)

#include <windows.h>
#include <stdio.h>
#include "../Game.h"

class CDatafile
{

public:

	CDatafile(unsigned long offset, unsigned long size);
	CDatafile(char filename[]);
	~CDatafile();

	void load(unsigned long offset, unsigned long size);	// wczytaj dane

	unsigned char *_buffer;
	unsigned long _size;
	bool _empty;

};

