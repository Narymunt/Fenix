#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define NTDDI_VERSION 0x0501

#pragma warning(disable : 4996)
#pragma warning(disable : 4244)     // zwrot innego typu niz size_t

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_ttf.lib")
#pragma comment(lib, "SDL_mixer.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#ifdef main
#undef main
#endif

// ustawienia aplikacji
// window_x/y sa do domyslnego ustawienia okna
// EDIT_MODE jest do ustawiania leveli, wtedy 2560x1440 fullscreen, z dodatkowymi kontrolkami do edycji obiektow itp

#define DEBUG_MODE		1
#define FULLSCREEN		0
#define WINDOW_X		1024
#define WINDOW_Y		768
#define EDIT_MODE		0

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"

#include "gfx/OGL.h"
#include "gfx/Screen.h"
#include "gfx/Sprite.h"
#include "ui/Mouse.h"	
#include "common/GameSettings.h"
#include "ui/Button.h"
#include "ui/SpriteFont.h"
#include "gfx/FontTTF.h"

//=== stany aplikacji 

#include "app/Ingame.h"					// in game - tutaj ukladamy klocki
#include "app/Congratulations.h"		// zwyciêstwo !!! koniec gry !!!

#include "app/SceneEditor.h"			// edytor do scenek

int		appState= SCENE_EDITOR;			// current application state
int		prevState = SETTINGS;			// poprzedni stan aplikacji
inline void state(int s) { prevState = appState; appState = s; }

int		loadStatus=0;					// na jakim etapie wczytywania danych jestesmy

int		ret;							// funkcje renderujace moga zwracac rozne wartosci

unsigned char	appLanguage;			// w jakim jezyku wyswietlamy menu etc.
unsigned char	musicVolume;			// glosnosc muzyki

// stany aplikacji

CIngame				*appIngame;			// MATCH3
CCongratulations	*appCongratulations;	// zwyciêstwo, koniec gry

// edytory

CSceneEditor		*appSceneEditor;

// elementy g³ówne

CScreen				*screen;	// our screen, there can be more than 1
CFontTTF			*font;
CMouse				*mouse; // myszka  

// grafiki do preload screen

CSprite *background = NULL;
CSprite *loadScreen = NULL;
CSprite *confirmQuit = NULL;					// czy na pewno wyjscie z gry ? 

// do potwierdzenia wyjscia z gry

CButton *yesButton = NULL;
CButton *noButton = NULL;

CSpriteFont *spriteFont = NULL; // czcionka
SDL_Event event;		// sdl event 

// muzyka

Mix_Music *ingameMusic[7], *menuMusic, *postgameMusic, *victoryMusic;

// timery do liczenia klatek

int framesCount = 0;
int fps = 0;
unsigned long timer = 0;	// main application timer
unsigned long timerLast = 0;

char buffer[1024];

// do ustawien aplikacji, zeby bylo wiadomo kiedy mamy wczytywac muzyke a kiedy nie

bool	msxSettings = true;
bool	sfxSettings = true;

// ustawienia ekranu 

int	screenX = 0, screenY = 0;

size_t getTotalSystemMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
	return status.ullAvailPhys/1024;
}

void _debug(char cInfo[])
{
	FILE *plik;
	
	plik = fopen("debug.log","at");
	fprintf(plik,cInfo);
	
	fclose(plik);
}

//=== podnoszenie literek

void upStr(char str[])
{
	int i=0;
	char c;
	
	while (str[i])
	{
		c = str[i];
		str[i]= toupper(c);
		i++;
	}
}

// load screen - wyswietla sie w trakcie wczytywania danych

void LoadScreen(int iProgress)
{
	loadScreen->render();
}

//=== wczytaj ustawienia

void reloadSettings(void)
{
	CGameSettings *setup = new CGameSettings();
	setup->load();

	msxSettings = setup->_isMSX;
	sfxSettings = setup->_isSFX;

	delete setup;
}

//=== MAIN ===

int main(int argc, char *argv[])
{  
	atexit(SDL_Quit);

   if (TTF_Init()==-1)
   {
		printf("ERROR: unable to init TTF\n");
		exit(1);
   }

	if (SDL_Init(SDL_INIT_AUDIO)<0)
	{
		printf("ERROR: unable to init audio\n");
		exit(1);
	}
	
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	Mix_AllocateChannels(8);

	if (FULLSCREEN)
	{
		screen = new CScreen();
		screenX = screen->_sizeX;
		screenY = screen->_sizeY;
	}
	else
	{
		screen = new CScreen(WINDOW_X, WINDOW_Y, false);
	}

	font = new CFontTTF((char*)"data/consola.ttf",20);
	mouse = new CMouse(true); // inicjalizacja myszki

	//pSpriteFont = new CSpriteFont(pMainScreen); // czcionka g³ówna

	reloadSettings(); // sprawdz ustawienia

	loadScreen = new CSprite((char*)"background.jpg"); // ekran wczytywania danych
	loadScreen->fullscreen(screen);
	loadScreen->render();

	// to potrzebne aby w dowolnym momencie reagowac na ESC
	//	pConfirmQuit = new CSprite(pMainScreen, "QUIT_SCREEN");
	//	pButtonYES = new CButton(pMainScreen, "BUTTON_OK_PROFILE");
	//	pButtonNO = new CButton(pMainScreen, "BUTTON_CANCEL_PROFILE");

/*
	if (pMainScreen->iSizeX() < 1500)
	{
		pButtonYES->setPosition(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2);
		pButtonYES->setHotCoords(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2, pMainScreen->iSizeX() / 4 + 128, pMainScreen->iSizeY() / 2 + 128);

		pButtonNO->setPosition((pMainScreen->iSizeX() / 4) * 3 - 128, pMainScreen->iSizeY() / 2);
		pButtonNO->setHotCoords((pMainScreen->iSizeX() / 4) * 3 - 128, pMainScreen->iSizeY() / 2, (pMainScreen->iSizeX() / 4) * 3, pMainScreen->iSizeY() / 2 + 128);
	}
	else
	{
		pButtonYES->setPosition(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2);
		pButtonYES->setHotCoords(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2, pMainScreen->iSizeX() / 4 + 256, pMainScreen->iSizeY() / 2 + 256);

		pButtonNO->setPosition((pMainScreen->iSizeX() / 4) * 3 - 256, pMainScreen->iSizeY() / 2);
		pButtonNO->setHotCoords((pMainScreen->iSizeX() / 4) * 3 - 256, pMainScreen->iSizeY() / 2, (pMainScreen->iSizeX() / 4) * 3, pMainScreen->iSizeY() / 2 + 256);
	}
*/

	// ekran w trakcie wczytywania muzyki itd
	//	pStart = new CSprite(pMainScreen,"START");
	//	pStart->Render();
	
	oglFlip();

	// inicjalizacja komponentow

	appSceneEditor = new CSceneEditor();

	//	pIngame = new CIngame();
	//	pCongratulations = new CCongratulations();

	// load music

/*
	pMusicIngame[0] = Mix_LoadMUS("data/music_ingame01.ogg");
	pMusicIngame[1] = Mix_LoadMUS("data/music_ingame02.ogg");
	pMusicIngame[2] = Mix_LoadMUS("data/music_ingame03.ogg");
	pMusicIngame[3] = Mix_LoadMUS("data/music_ingame04.ogg");
	pMusicIngame[4] = Mix_LoadMUS("data/music_ingame05.ogg");
	pMusicIngame[5] = Mix_LoadMUS("data/music_ingame06.ogg");
	pMusicIngame[6] = Mix_LoadMUS("data/music_ingame07.ogg");

	pMusicMenu = Mix_LoadMUS("data/music_mainmenu.ogg");
	pMusicPostgame = Mix_LoadMUS("data/music_postgame.ogg");
	pMusicVictory = Mix_LoadMUS("data/music_victory.ogg");
*/

	// hide cursor

//	SDL_ShowCursor(SDL_DISABLE); 

	SDL_WM_SetCaption("SHODAN9 : GAME", "SHODAN9 : GAME");

	timer = SDL_GetTicks();

	while(appState!=QUIT)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (appState == MAINMENU || appState == INGAME || appState == LEVELMENU || appState == POSTGAME || appState == POST_TROOPHY)
				{
					if (appState != CONFIRM_QUIT) 
					{
						state(CONFIRM_QUIT);
					}
					else
					{
						appState = prevState;
					}
				}
				else
				{
					appState = QUIT; // DO USUNIÊCIA !!!
				}
			}

			 if( event.type == SDL_MOUSEMOTION ) 
			 { 
				 //Get the mouse offsets 
				 mouse->_x = event.motion.x; 
				 mouse->_y = event.motion.y;
			 }
			  
			 if( event.type == SDL_MOUSEBUTTONDOWN ) // zapamietaj wspolrzedne klikniecia
			 { 
				 mouse->_xClick = event.motion.x;	
				 mouse->_yClick = event.motion.y;

				 if (event.button.button == SDL_BUTTON_LEFT)
					 mouse->_isL = true;

				 if (event.button.button == SDL_BUTTON_RIGHT)
					 mouse->_isR = true;
			 }

			if( event.type == SDL_MOUSEBUTTONUP) //If the left mouse button was released 
			{ 				
				if( event.button.button == SDL_BUTTON_LEFT )
					mouse->_isL = false;

				if( event.button.button == SDL_BUTTON_RIGHT )
					mouse->_isR = false;				
			}
		}

//		loadScreen->render();

		switch	(appState)
		{	
			case SCENE_EDITOR :

				if (!appSceneEditor->_isOpen)
					appSceneEditor->open(screen);

				if (appSceneEditor->render(timer, mouse))
				{
					appSceneEditor->close();
					state(INGAME);
				}

			break;

			case INGAME:

            font->Print("INGAME",255,128,64,10,10);
/*            
            if (!pIngame->isActive())
				{
					pIngame->Open(pMainScreen);

					if (iPrevAppState == E_LEVELMENU)
					{
						if (bSettingsMSX)
						{
							ucVolumeMusic = 0;
							Mix_VolumeMusic(ucVolumeMusic);
							Mix_HaltMusic();
							Mix_PlayMusic(pMusicIngame[1],200);
						}
						else
						{
							ucVolumeMusic = 0;
							Mix_VolumeMusic(ucVolumeMusic);
							Mix_HaltMusic();
						}
					}
				}

            pIngame->Render(ulTimer,pMouse);

			if (pIngame->isFinished())
			{
				pIngame->Close();		
				iAppState = E_POST_TROOPHY;
				iPrevAppState = E_INGAME;
			}
*/
			break;		

			case CONGRATULATIONS:

				if (!appCongratulations->_isOpen)
				{
					appCongratulations->Open(screen);

					if (msxSettings)
					{
						musicVolume= 0;
						Mix_VolumeMusic(musicVolume);
						Mix_HaltMusic();
						Mix_PlayMusic(victoryMusic,-1);
					}
					else
					{
						musicVolume= 0;
						Mix_VolumeMusic(musicVolume);
						Mix_HaltMusic();
					}
				}

				if (appCongratulations->Render(timer,mouse))
				{
					appState = MAINMENU;
					prevState = CONGRATULATIONS;
					appCongratulations->Close();
				}

			break;

		}	// switch

		mouse->render();

		// info debugowe

		sprintf(buffer, "%d", fps);
		
		std::string s = std::to_string((unsigned long long)fps);
		font->Print(s, 255, 255, 255, 0, 200);
		font->Print("FPS", 255, 255, 255, 30, 200);

		std::string strX = std::to_string((unsigned long long)mouse->_x);
		font->Print(strX, 255, 255, 255, 0, 0);

		std::string strY = std::to_string((unsigned long long)mouse->_y);
		font->Print(strY, 255, 255, 255, 200, 0);

		std::string cX = std::to_string((unsigned long long)(mouse->_x*screen->_revPixelX));
		font->Print(cX, 255, 255, 255, 0, 100);

		std::string cY = std::to_string((unsigned long long)(mouse->_y*screen->_revPixelY));
		font->Print(cY, 255, 255, 255, 200, 100);

//		spriteFont->print(10, 10, 1, 0.05f, 0.05f, buffer);

		oglFlip();		// show the screen

		framesCount++;
		timer = SDL_GetTicks();

		if(timer - timerLast > 1000)
		{
			fps = framesCount;
			framesCount = 0;
			timerLast = timer;
		}
	}

	
	for (int i=0; i<7; i++)
	{
		Mix_FreeMusic(ingameMusic[i]);
	}

	Mix_FreeMusic(menuMusic);
	Mix_FreeMusic(postgameMusic);
	Mix_FreeMusic(victoryMusic);

	// usun stany aplikacji

	safeDelete(appSceneEditor);
	safeDelete(appIngame);		
	safeDelete(appCongratulations);

	// usun load screen

	safeDelete(loadScreen);
	safeDelete(confirmQuit);

	safeDelete (yesButton);
	safeDelete (noButton);

	// zwolnij myszke, ekran, itd
	safeDelete (font);
	safeDelete (spriteFont);
	safeDelete (mouse);
	safeDelete (screen);

	TTF_Quit();
	SDL_Quit();
	exit(0);
	return 0;
}

