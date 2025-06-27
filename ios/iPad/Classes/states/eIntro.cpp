// main class
#include <MediaPlayer/MediaPlayer.h>
#include <UIKit/UIKit.h>
#include <iAd/iAd.h>
#include "eIntro.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eIntro::eIntro(int iOS) :
_pBackground(0)
{
    m_bActive = false;
    m_ulTimer = 0;
    m_ulStart = 0;
    
    _iOS = iOS;
}

eIntro::~eIntro()
{
    if (m_bActive)
    {        
        Close();
        m_bActive = false;
    }    
}

void eIntro::Open(void)
{
   _pBackground = new CSprite((char*)"e_lang",_iOS);
    
    m_bActive = true;
}

void eIntro::Close(void)
{
    [moviePlayer.view removeFromSuperview];
    [moviePlayer release];
    
    SafeDelete(_pBackground);
    
    m_bActive = false;
}

int eIntro::Render(CTouch *pTouch, unsigned long ulTimer)
{
    
    if (m_ulStart == 0)
    {
        m_ulStart = ulTimer;

//        [MPMoviePlayerController preparePrerollAds];
        
        if (_iOS == IPHONE4)
        {
            filepath   =   [[NSBundle mainBundle] pathForResource:@"iphone4.mp4" ofType:nil];
        }
        else if (_iOS == IPHONE5)
        {
            filepath   =   [[NSBundle mainBundle] pathForResource:@"iphone5.mp4" ofType:nil];
        }
        else
        {
            filepath   =   [[NSBundle mainBundle] pathForResource:@"ipad.mp4" ofType:nil];
        }
        
        fileURL    =   [NSURL fileURLWithPath:filepath];
        moviePlayer = [[MPMoviePlayerController alloc] initWithContentURL:fileURL];
        
        backgroundWindow = [[UIApplication sharedApplication] keyWindow];
        [moviePlayer.view setFrame:backgroundWindow.frame];
        [backgroundWindow addSubview:moviePlayer.view];        
        
        moviePlayer.controlStyle = MPMovieControlStyleNone;
        moviePlayer.scalingMode = MPMovieScalingModeAspectFill;
        moviePlayer.fullscreen = YES;

//        [moviePlayer play];
        [moviePlayer playPrerollAdWithCompletionHandler:^(NSError *error)
        {
             NSLog(@"error playing ad %@", error.userInfo);
            [moviePlayer play];
        }];
    }
    
    m_ulTimer = ulTimer - m_ulStart;
    
    if (m_ulTimer>12000)
    {
        _pBackground->Render();
        return 255;
    }
    
    
    return 0;   // nie rob nic
}

bool eIntro::isActive(void)
{
    return m_bActive;
}