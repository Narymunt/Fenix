// plik z zakodowanymi danymi

#pragma once

#pragma warning(disable : 4996)

#include <windows.h>
#include <stdio.h>
#include "../Game.h"

class Datafile
{

public:

	Datafile(unsigned long offset, unsigned long size);
	Datafile(char filename[]);
	~Datafile();

	void load(unsigned long offset, unsigned long size);	// wczytaj dane

	unsigned char *_buffer;
	unsigned long _size;
	bool _empty;
};

