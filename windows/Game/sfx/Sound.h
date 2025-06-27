#pragma once

class Sound
{
public : 
	Sound(char file[]) : isLoaded(false) {};
	~Sound();

	void load() {};

	bool isLoaded;

};