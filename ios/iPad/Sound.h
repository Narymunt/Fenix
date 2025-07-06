#ifndef _igame_sound_
#define _igame_sound_

#include <time.h>
#include "KPTK.h"
#include "KMiscTools.h"
#include "KGraphic.h"
#include "KSound.h"
#include "KMusic.h"
#include "KInput.h"

// pojedynczy dzwiek

class CSound
{
	
public: 

	CSound(char cFilename[]);
    ~CSound();

    void Play(void);
    void Play(unsigned char ucVolume);
    void Stop(void);
    
    void SetVolume(unsigned char ucVolume);
    unsigned char ucGetVolume(void);
    
    bool isPlaying(void);

    
    template< class T > void SafeDelete( T*& pVal )
    {
        delete pVal;
        pVal = NULL;
    }
    
    template< class T > void SafeDeleteArray( T*& pVal )
    {
        delete[] pVal;
        pVal = NULL;
    }
    
    
private:	
    
    bool        m_bPlaying;

    unsigned char m_ucVolume;
    
    char        m_cFilename[200];

 	KSound      *m_pSound;      
    
};

#endif
