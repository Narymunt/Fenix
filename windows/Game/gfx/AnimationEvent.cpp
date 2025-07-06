#pragma warning(disable : 4996)	// sprintf unsafe

#include "AnimationEvent.h"

AnimationEvent::AnimationEvent() 
{
	_isOpen = false;
}

AnimationEvent::AnimationEvent(char file[]) 
{
	strcpy(_file,file);	// zapamietujemy nazwe pliku i rozszerzenie, numery dodajemy np. img001,img002
}

AnimationEvent::~AnimationEvent()
{
	close();
}

// Wczytanie danych na podstawie wcze�niej ustawionych parametr�w

void AnimationEvent::open(void)
{
	char buffer[1024];	// tutaj wygenerujemy nazwe pliku

	_isOpen = true;
}

// Zwolnij wszystkie dane. 

void AnimationEvent::close(void)
{
	_isOpen = false;
}

// Dodajemy klatk� na koniec kolejki

void AnimationEvent::add(char cFilename[])
{

}

// Renderuj klatk� o podanym numerze

void AnimationEvent::render(unsigned long timer)
{

}

