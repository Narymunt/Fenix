/*
 *  KSound.h
 *  jmApp.com
 *
 */

#ifndef API_KSOUND__
#define API_KSOUND__

//#include "SoundEngine.h"
//#include "MyOpenALSupport.h"



#import <OpenAL/al.h>
#import <OpenAL/alc.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/ExtendedAudioFile.h>

enum {
	kSoundEngineErrUnitialized			= 1,
	kSoundEngineErrInvalidID			= 2,
	kSoundEngineErrFileNotFound			= 3,
	kSoundEngineErrInvalidFileFormat	= 4,
	kSoundEngineErrDeviceNotFound		= 5
};


enum EsoundType
{
	e_sample ,
	e_music ,
	e_undefined
};

class KSound
{
private:
	
	int						sample_id;
	EsoundType				type;
	static	long			_instanceCount;

	UInt32					soundID;
	ALuint					sourceID;
	ALuint					bufferID;	
	ALCcontext	*			mContext;
	ALCdevice	*			mDevice;
	
//	AVAudioPlayer *			audioPlayer;
	
	
public:
	
	KSound() ; 
	~KSound() ;
	
	void			initOpenAL();
	void			cleanUpOpenAL();
	UInt32			audioFileSize(AudioFileID fileDescriptor);
	AudioFileID		openAudioFile(char *filename);
	OSStatus		LoadFileDataInfo(const char *inFilePath, AudioFileID &outAFID, AudioStreamBasicDescription &outFormat, UInt32 &outDataSize);
	ALenum			GetALFormat(AudioStreamBasicDescription inFileFormat);

	bool	loadSample(const char * filename);
	void	playSample();	
	void	stopSample();
	bool	loadStream(const char * filename);
	void	playStream(bool loop);
	void	pauseStream();
	void	resumeStream(float volume=1);
	void	setStreamVolume(float volume);
	void	stopStream( void );
	void	setVolume(int volume);
	void	freeStream( void ) ;
	void	freeSample( void ) ;
	void	vibrate() ;


};

#endif // API_KSOUND__