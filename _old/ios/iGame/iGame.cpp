#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <memory>
#include "SDL.h"
#include "SDL_mixer.h"
#include "ResourcePath.h"
#include "Screen.h"
#include "Sprite.h"
#include "Mouse.h"

using namespace std;

CScreen *pScreen;

CMouse  *pMouse;

CSprite *pFullHD;
CSprite *pSprite;

bool    isActive;       // czy aplikacja jest na ekranie, czy w tle - jezeli w tle, to nie renderujemy

unsigned long   lFrameCount = 0;    // licznik wyrenderowanych klatek
unsigned int    iFPS;               // licznik fps
unsigned long   ulTimer = 0;
unsigned long   ulTimerLast = 0;

unsigned char   ucVolumeMusic;

//=== glowna klasa ekranu

class Graphics
{
private:
    
    SDL_Window* _window;
    
public:
    
    Graphics(SDL_Window* window)
    {
        _window = window;
    }
    
    void update()
    {
        if (isActive)
        {
            glClearColor(rand() % 255 / 255.0f, rand() % 255 / 255.0f, rand() % 255 / 255.0f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
            pFullHD->Render();
            pSprite->Render(lFrameCount%pScreen->_iSizeX,0,1.0f);
            
            SDL_GL_SwapWindow(_window);
            
            lFrameCount++;
            iFPS++;
            
            ulTimer = SDL_GetTicks();
            
            if(ulTimer - ulTimerLast> 1000)
            {
                printf("FPS: %d\n", iFPS);
                iFPS = 0;
                ulTimerLast = ulTimer;
            }
            
        }
    }
};

//=== funkcja pomocnicza dla klasy ekranu

void UpdateFrame(void* param)
{
    Graphics* graphics = (Graphics*)param;
    graphics->update();
}

int EventFilter(void* userdata, SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_FINGERMOTION:
            SDL_Log("Finger Motion");
            return 0;
            
        case SDL_FINGERDOWN:
            SDL_Log("Finger Down");
            return 0;
            
        case SDL_FINGERUP:
            SDL_Log("Finger Up");
            return 0;
    }
    
    return 1;
}


int main(int argc, char *argv[])
{
    
    // inicjalizacja audio
    
    if (SDL_Init(SDL_INIT_AUDIO)<0)
    {
        printf("ERROR: unable to init audio\n");
        exit(1);
    }
    
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_AllocateChannels(8);
    
    pScreen = new CScreen();    
    pMouse = new CMouse();
    
    unique_ptr<Graphics> graphics = unique_ptr<Graphics>(new Graphics(pScreen->_window));
    
    SDL_iPhoneSetAnimationCallback(pScreen->_window, 1, UpdateFrame, graphics.get());
    SDL_AddEventWatch(EventFilter, NULL);
    
    SDL_Log("My resource path is %s", getResourcePath().c_str());
    
    // wczytaj dane
    
    pSprite = new CSprite((char*)"Icon.png");
    pFullHD = new CSprite((char*)"Assets/fullHD.jpg");
    pFullHD->Fullscreen(pScreen);
    
    //Game Loop
    
    SDL_Event event;
    
    auto done = false;
    
    ulTimer = SDL_GetTicks();
    
    while (!done)
    {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                    
                case SDL_APP_DIDENTERFOREGROUND:
                    SDL_Log("SDL_APP_DIDENTERFOREGROUND");
                    isActive=true;
                break;
                    
                case SDL_APP_DIDENTERBACKGROUND:
                    SDL_Log("SDL_APP_DIDENTERBACKGROUND");
                    isActive=false;
                break;
                    
                case SDL_APP_LOWMEMORY:
                    SDL_Log("SDL_APP_LOWMEMORY");
                    break;
                    
                case SDL_APP_TERMINATING:
                    SDL_Log("SDL_APP_TERMINATING");
                    break;
                    
                case SDL_APP_WILLENTERBACKGROUND:
                    SDL_Log("SDL_APP_WILLENTERBACKGROUND");
                    isActive=false;
                    break;
                    
                case SDL_APP_WILLENTERFOREGROUND:
                    SDL_Log("SDL_APP_WILLENTERFOREGROUND");
                    break;

                case SDL_MOUSEMOTION:
                    pMouse->Update(event.motion.x, event.motion.y, pMouse->_isPress);
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    pMouse->Update(event.motion.x, event.motion.y, true);
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    pMouse->Update(event.motion.x, event.motion.y,false);
                    break;
                    
                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_RESIZED:
                        {
                            SDL_Log("Window %d resized to %dx%d", event.window.windowID, event.window.data1, event.window.data2);
                            
                            break;
                        }
                    }
                }
            }
        }
    }
    
    delete pSprite;
    delete pMouse;
    delete pScreen;
    

    SDL_Quit();
    
    return 0;
}
