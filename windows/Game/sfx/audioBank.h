#pragma once
#include "sound.h"

class AudioBank
{
public : 
	
	AudioBank(char file[]) : isLoaded(false),size(0) {};
	~AudioBank();

	void load() {};
	void play() {};	// odtwarza wszystkie po kolei
	
	void playRandom(unsigned int i) {}; // odtwórz x razy losowe dŸwiêki, ka¿dy kolejny losowy
	
	// odtwórz x razy losowe dŸwiêki, ale ka¿dy tylko raz
	// je¿eli x wiêkszy od liczby dŸwiêków w banku, to odtwórz tylko wszystkie dŸwiêki z banku w losowej kolejnoœci

	void playRandomPic(unsigned int i) {}; 

	// metoda zwraca info, czy aktualnie odtwarzany jest jeden z dŸwiêków w banku

	bool isPlaying() { return false; }

	bool isLoaded;
	unsigned int size;


};