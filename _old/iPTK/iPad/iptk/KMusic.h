//
//  KMusic.h
//  Grizzly
//
//  Created by Julien MEYER on 31/01/10.
//  Copyright 2010 jmApp.com All rights reserved.
//

#ifndef API_KMUSIC__
#define API_KMUSIC__


class KMusic
{	
public:
	
	KMusic();
	~KMusic();
	
	bool playMusic(char * filename);
	void stopMusic();
	void pauseMusic();
	void resumeMusic();
	void setVolume(int volume);
	
};



#endif