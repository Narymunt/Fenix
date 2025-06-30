#pragma once
#include "sound.h"

class AudioBank
{
public : 
	
	AudioBank(char file[]) : isLoaded(false),size(0) {};
	~AudioBank();

	void load() {};
	void play() {};	// odtwarza wszystkie po kolei
	
	void playRandom(unsigned int i) {}; // odtw�rz x razy losowe d�wi�ki, ka�dy kolejny losowy
	
	// odtw�rz x razy losowe d�wi�ki, ale ka�dy tylko raz
	// je�eli x wi�kszy od liczby d�wi�k�w w banku, to odtw�rz tylko wszystkie d�wi�ki z banku w losowej kolejno�ci

	void playRandomPic(unsigned int i) {}; 

	// metoda zwraca info, czy aktualnie odtwarzany jest jeden z d�wi�k�w w banku

	bool isPlaying() { return false; }

	bool isLoaded;
	unsigned int size;


};