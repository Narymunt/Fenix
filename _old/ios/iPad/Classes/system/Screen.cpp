#include "Screen.h"

CScreen::CScreen(int iOS) :
_iOS(iOS)
{
    if (iOS == IPHONE4)
    {
        _iSizeX = 960; _iSizeY = 640;
    }
    else if (iOS == IPHONE5)
    {
        _iSizeX = 1136; _iSizeY = 640;
    }
    else if (iOS == IPAD)
    {
        _iSizeX = 1024; _iSizeY = 768;
    }
    else if (iOS == IPAD_HD)
    {
        _iSizeX = 2048; _iSizeY = 1536;
    }
}

CScreen::~CScreen()
{
    
    
}