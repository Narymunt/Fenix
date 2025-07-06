// Released under MIT License
/*
 Copyright (c) 2010 by Julien Meyer. Web: http://www.jmApp.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "KMusic.h"

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

AVAudioPlayer * audioPlayer = NULL;

KMusic::KMusic()
{
}

KMusic::~KMusic()
{
}

bool KMusic::playMusic(char * filename, bool loop)
{
	if(audioPlayer != NULL) {
		return false;
	}
	NSString * fileStr = [NSString stringWithFormat:@"%s", filename];
	NSURL *url = [NSURL fileURLWithPath:fileStr];
	NSError *error;
	audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
	if(loop) {
		audioPlayer.numberOfLoops = -1;
	}
	else {
		audioPlayer.numberOfLoops = 0;		
	}
	if (audioPlayer == nil)
		NSLog(@"%@", [error description]);				
	else 
		[audioPlayer play];		
	return true;
}

void KMusic::stopMusic()
{
	if(audioPlayer) {
		[audioPlayer stop];
		[audioPlayer release];
		audioPlayer = nil;
	}
}

void KMusic::pauseMusic()
{
	if(audioPlayer) {
		[audioPlayer pause];
	}
}

void KMusic::resumeMusic()
{
	if(audioPlayer) {
		[audioPlayer play];
	}
}

void KMusic::setVolume(int volume)
{
	if(audioPlayer) {
		audioPlayer.volume = ((float)volume / 100.0f);
	}
}



