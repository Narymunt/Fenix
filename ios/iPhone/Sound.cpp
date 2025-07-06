// main class

#include "Sound.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

CSound::CSound(char cFilename[])
{
    m_pSound = new KSound();
	m_pSound->loadSample(KMiscTools::makeFilePath(cFilename));
    
    m_ucVolume = 100; 
    m_pSound->setVolume(m_ucVolume);    

    m_bPlaying = false;
}

CSound::~CSound()
{
    SafeDelete(m_pSound);    
}

void CSound::Play(void)
{
    m_pSound->playSample();    
    m_bPlaying = true;
}

void CSound::Play(unsigned char ucVolume)
{
    m_ucVolume = ucVolume;
    m_pSound->setVolume(m_ucVolume);    
    m_pSound->playSample();
    m_pSound->playStream(true);
    m_bPlaying = true;
}

void CSound::Stop(void)
{
    m_pSound->stopSample();
    m_bPlaying = false;
}

void CSound::SetVolume(unsigned char ucVolume)
{
    m_ucVolume = ucVolume;
    m_pSound->setVolume(m_ucVolume);        
}

unsigned char CSound::ucGetVolume(void)
{
    return m_ucVolume;
}

bool CSound::isPlaying(void)
{
    return m_bPlaying;
}
