#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <jni.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "SDL.h"
#include "../SDL_mixer/SDL_mixer.h"
#include "Main.h"

#include "control/Touch.h"

#include "gfx/Screen.h"					// obsluga ekranu
#include "gfx/Sprite.h"
#include "gfx/Button.h"
#include "gfx/SpriteFont.h"

//=== ui

#include "application/Intro.h"
#include "application/MainMenu.h"
#include "application/Ingame.h"

// stany aplikacji

CIntro				*pIntro;
CMainMenu			*pMainMenu;
CIngame				*ingame;

//=== zmienne globalne

int					iAppState;			// aktualny stan aplikacji
int					iPrevAppState; 		// poprzedni stan aplikacji

CScreen				*pScreen;			// ekran

CTouch				*pTouch;			// dane z ekranu dotykowego

// czcionka

// CSpriteFont *pSpriteFont;

//=== zdarzenia

bool 				isEvent;			// ekran odświeżany jest tylko po tym jak wystąpił jakiś event
SDL_Event 			event;
int					iEvent;				// identyfikator zdarzenia z uiMain

// timery do liczenia klatek

int iFrames, iFPS;
unsigned long ulTimer;	// main application timer
unsigned long ulTimerLast;

char cBuffer[64];

//=== muzyka

Mix_Music *pMusicIngame, *pMusicMenu;

// przelacz pomiedzy stanami

void state(int i)
{
	iPrevAppState = iAppState;
	iAppState = i;
}

//=== MAIN ===

int main(int argc, char *argv[])
{
	iAppState = E_MAINMENU;
	state(E_INTRO);

	// inicjalizacja audio

	if (SDL_Init(SDL_INIT_AUDIO)<0)
	{
		printf("ERROR: unable to init audio\n");
		exit(1);
	}

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	Mix_AllocateChannels(8);

	// inicjalizacja grafiki

	pTouch = new CTouch();
	pScreen = new CScreen();

	// inicjalizacja stanow

	pIntro = new CIntro(pScreen);
	pMainMenu = new CMainMenu(pScreen);
	ingame = new CIngame();

	// czcionka glowna

//	pSpriteFont = new CSpriteFont(pMainScreen);

	SDL_Log("=== APPLICATION START ===\n");

	// load music

	pMusicIngame = Mix_LoadMUS("music_ingame.ogg");

	pMusicMenu = Mix_LoadMUS("music_mainmenu.ogg");

	// zerowanie eventow

	isEvent = true;
	ulTimer = SDL_GetTicks();

	while (iAppState != E_QUIT)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					iAppState = E_QUIT;
				break;

				case SDL_KEYDOWN:
					iAppState = E_QUIT;
				break;

				case SDL_FINGERDOWN:
					pTouch->Update(true, event.tfinger.x * pScreen->_iSizeX, event.tfinger.y * pScreen->_iSizeY);
					isEvent = true;
				break;

				case SDL_FINGERMOTION:
					pTouch->Update(true, event.tfinger.x * pScreen->_iSizeX, event.tfinger.y * pScreen->_iSizeY);
					isEvent = true;
				break;

				case SDL_FINGERUP:
					pTouch->Update(false, event.tfinger.x * pScreen->_iSizeX, event.tfinger.y * pScreen->_iSizeY);
					isEvent = true;
				break;

                case SDL_APP_DIDENTERFOREGROUND:
                    SDL_Log("SDL_APP_DIDENTERFOREGROUND");
                    Mix_VolumeMusic(100);
                break;

                case SDL_APP_DIDENTERBACKGROUND:
                    SDL_Log("SDL_APP_DIDENTERBACKGROUND");
                    Mix_VolumeMusic(0);

                    if (iAppState==E_INGAME)	// wycisz efekty specjalne
                    	ingame->mute();

                break;

                case SDL_APP_LOWMEMORY:
                    SDL_Log("SDL_APP_LOWMEMORY");
                break;

                case SDL_APP_TERMINATING:
                    SDL_Log("SDL_APP_TERMINATING");
                    Mix_HaltMusic();
                break;

                case SDL_APP_WILLENTERBACKGROUND:
                    SDL_Log("SDL_APP_WILLENTERBACKGROUND");
                break;

                case SDL_APP_WILLENTERFOREGROUND:
                    SDL_Log("SDL_APP_WILLENTERFOREGROUND");
                break;
			}
		}

		switch(iAppState)
		{
			case E_INTRO:

				if (!pIntro->isActive())
				{
					SDL_Log("STATE: E_INTRO");
					pIntro->Open();
					Mix_PlayMusic(pMusicMenu,-1);
				}

				iEvent = pIntro->iRender(ulTimer, pTouch);

				if (iEvent == 1)
				{
					pIntro->Close();
					state(E_MAINMENU);
				}

			break;

			case E_MAINMENU:

				if (!pMainMenu->isActive())
				{
					pMainMenu->iOpen();

					if (iPrevAppState == E_INGAME || iPrevAppState == E_POSTGAME)
                    {
                   		Mix_VolumeMusic(100);
                   		Mix_HaltMusic();
                   		Mix_PlayMusic(pMusicMenu,200);
                    }
				}
	            else	// assety zaladowane - renderowanie
	            {
	                if (pMainMenu->iRender(ulTimer,pTouch)==1)
	                {
	                	pMainMenu->Close();
						Mix_VolumeMusic(0);
	            		Mix_HaltMusic();
	                    state(E_INGAME);
	                }
	            }
			break;

			case E_INGAME :

				if (!ingame->_isActive)
				{
					SDL_Log("STATE: E_INGAME");
					ingame->Open(pScreen);

            		Mix_PlayMusic(pMusicIngame,200);
            		Mix_VolumeMusic(100);
				}
				else
				{
					if (ingame->Render(ulTimer/10,pTouch)!=0)
					{
						ingame->Close();
						Mix_VolumeMusic(0);
	            		Mix_HaltMusic();
	                    state(E_MAINMENU);
					}

				}

			break;

		}

		pScreen->Flip();
		ulTimer = SDL_GetTicks();

	}

	// wyłączenie muzyki

	Mix_FreeMusic(pMusicIngame);
	Mix_FreeMusic(pMusicMenu);

	// usuniecie obiektów

	SafeDelete(pIntro);
	SafeDelete(pMainMenu);

	delete pTouch;

	delete pScreen;

	exit(0);

}
