// Game.cpp : Defines the entry point for the console application.

#pragma warning(disable : 4996)
#pragma warning(disable : 4244)     // zwrot innego typu niz size_t

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"

#include "gfx/OGL.h"
#include "gfx/Screen.h"
#include "gfx/Sprite.h"
#include "ui/Mouse.h"	
#include "windows/GameSettings.h"
#include "ui/Button.h"
#include "ui/SpriteFont.h"
#include "gfx/FontTTF.h"

// definicje dla windows, pierwsza dla vs2015

#ifdef _WIN32
	FILE _iob[] = { *stdin, *stdout, *stderr };
	extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
// dolaczenie visual leak detector
	#ifdef _DEBUG
	#include "vld/include/vld.h"
	#endif 
#endif

//=== stany aplikacji 

#include "app/Ingame.h"				   // in game - tutaj ukladamy klocki
#include "app/Congratulations.h"		// zwyciêstwo !!! koniec gry !!!

int		iAppState;					// current application state
int		iPrevAppState;				// poprzedni stan aplikacji
int		iLoad;						// na jakim etapie wczytywania danych jestesmy

int		iReturn;					   // funkcje renderujace moga zwracac rozne wartosci

unsigned char	ucLanguage;			// w jakim jezyku wyswietlamy menu etc.

unsigned char	ucVolumeMusic;		// glosnosc muzyki

// stany aplikacji

CIngame				*pIngame;		// MATCH3
CCongratulations	*pCongratulations;	// zwyciêstwo, koniec gry

// ekran

CScreen	*pMainScreen;	// our screen, there can be more than 1

CFontTTF *pFont;

// myszka 

CMouse	*pMouse;

// grafiki do preload screen

CSprite *pBackground;
CSprite *pLoadScreen;
CSprite *pConfirmQuit;					// czy na pewno wyjscie z gry ? 

// do potwierdzenia wyjscia z gry

CButton *pButtonYES;
CButton *pButtonNO;

// czcionka

CSpriteFont *pSpriteFont;

// eventy dla SDL

SDL_Event event;		// sdl event 

// muzyka

Mix_Music *pMusicIngame[7], *pMusicMenu, *pMusicPostgame, *pMusicVictory;

// timery do liczenia klatek

int iFrames, iFPS;
unsigned long ulTimer;	// main application timer
unsigned long ulTimerLast;

char cBuffer[64];

// do ustawien aplikacji, zeby bylo wiadomo kiedy mamy wczytywac muzyke a kiedy nie

bool	bSettingsMSX;
bool	bSettingsSFX;

// ustawienia ekranu wczytane z pliku

int		iScreenX, iScreenY, iMode;

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

void UpOnly(char str[])
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
	pLoadScreen->Render();
}

//=== wczytaj ustawienia

void reloadSettings(void)
{
	// wczytaj config

	CGameSettings *pSetup;

	pSetup = new CGameSettings();
	pSetup->bLoad();

	bSettingsMSX = pSetup->isMSX();
	bSettingsSFX = pSetup->isSFX();

	delete pSetup;
}

//=== wczytaj konfiguracje z pliku

void loadGameConfig(void)
{
	FILE	*plik;
	char linia[1024];

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
		printf("ERROR: no script file %s\n",SCRIPT_FILE);
	
	while (strcmp(linia,"<END>"))
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<GAME>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
			UpOnly(linia);

			iMode = 0;

			if (!strcmp(linia,"FULLSCREEN")) iMode=1;
			if (!strcmp(linia,"AUTO")) iMode=2;

			fscanf(plik,"%d %d\n",&iScreenX,&iScreenY);	// wczytaj parametry ekranu
		} // if 
	} // while <end>

	fclose(plik);
}

// czy w pliku konfiguracyjnym jest zmiana stanu aplikacji ?

int iLoadAppState(void)
{
	int iApp = 0;

	FILE	*plik;
	char linia[1024];

	if ((plik=fopen(SCRIPT_FILE,"r"))==NULL)
		printf("ERROR: no script file %s\n",SCRIPT_FILE);
	
	while (strcmp(linia,"<END>"))
	{
		fscanf(plik,"%s\n",linia);	// wczytaj linie pliku
		UpOnly(linia);

		if (!strcmp(linia,"<APPSTATE>")) // znaleziono obiekt
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
			UpOnly(linia);

			if (!strcmp(linia,"E_LANGUAGE")) iApp=E_LANGUAGE;
			if (!strcmp(linia,"E_PRELOAD")) iApp=E_PRELOAD;
			if (!strcmp(linia,"E_ADS")) iApp=E_ADS;
			if (!strcmp(linia,"E_INTRO")) iApp=E_INTRO;
			if (!strcmp(linia,"E_MAINMENU")) iApp=E_MAINMENU;
			if (!strcmp(linia,"E_SETTINGS")) iApp=E_SETTINGS;
			if (!strcmp(linia,"E_CREDITS")) iApp=E_CREDITS;
			if (!strcmp(linia,"E_PAUSE")) iApp=E_PAUSE;
			if (!strcmp(linia,"E_FREEZE")) iApp=E_FREEZE;
			if (!strcmp(linia,"E_PAUSE")) iApp=E_PROFILE;
			if (!strcmp(linia,"E_LEVELMENU")) iApp=E_LEVELMENU;
			if (!strcmp(linia,"E_PAUSE")) iApp=E_INGAME;
			if (!strcmp(linia,"E_TROOPHY")) iApp=E_TROOPHY;
			if (!strcmp(linia,"E_GAMEOVER")) iApp=E_GAMEOVER;
			if (!strcmp(linia,"E_ENDSCREEN")) iApp=E_ENDSCREEN;
			if (!strcmp(linia,"E_POSTGAME")) iApp=E_POSTGAME;
			if (!strcmp(linia,"E_HELP")) iApp=E_HELP;
			if (!strcmp(linia,"E_POST_TROOPHY")) iApp=E_POST_TROOPHY;
			if (!strcmp(linia,"E_CONGRATULATIONS")) iApp=E_CONGRATULATIONS;
			if (!strcmp(linia,"E_QUIT")) iApp=E_QUIT;
		} // if 
	} // while <end>

	fclose(plik);

	return iApp;
}

//=== main application

int main(int argc, char **argv)
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

	loadGameConfig();

	// auto resolution

	if (iMode==2)
	{
		pMainScreen = new CScreen(true);
		iScreenX = pMainScreen->_iSizeX;
		iScreenY = pMainScreen->_iSizeY;
	}

	// ustawiamy na podstawie parametrow

	if (iMode==1)
		pMainScreen = new CScreen(iScreenX,iScreenY,32,true);

	if (iMode==0)
		pMainScreen = new CScreen(iScreenX,iScreenY,32,false);

   pFont = new CFontTTF("verdana.ttf",20);

	// inicjalizacja myszki

	pMouse = new CMouse(true);

	// czcionka g³ówna

//	pSpriteFont = new CSpriteFont(pMainScreen);

	// sprawdz ustawienia

	reloadSettings();

	// ekran wczytywania danych

	pLoadScreen = new CSprite("background.jpg");
   pLoadScreen->Resize(0,0,pMainScreen->_iSizeX, pMainScreen->_iSizeY);
   pLoadScreen->Render();
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

	// inicjalizacja malych komponentow

	iLoad = 0;	// progress bar, zeby nie przenosil z poprzedniego stanu

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
	
	iFrames = 0;
	iFPS = 0;
	ulTimer = 0;
	ulTimerLast = 0;

	SDL_WM_SetCaption("SHODAN9 : GAME", "SHODAN9 : GAME");

	iPrevAppState = E_SETTINGS;

	iAppState = iLoadAppState();

	if (!iAppState)
		iAppState = E_INGAME;			// start aplikacji

	ulTimer = SDL_GetTicks();

	ucVolumeMusic = 0;

	while(iAppState!=E_QUIT)
	{

		if (bSettingsMSX && ucVolumeMusic!=128)	// fade muzyki, maksymalna glosnosc to 128
		{
			Mix_VolumeMusic(ucVolumeMusic);
			ucVolumeMusic++;
		}

		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (iAppState == E_MAINMENU || iAppState == E_INGAME || iAppState == E_LEVELMENU || iAppState == E_POSTGAME || iAppState == E_POST_TROOPHY)
				{
					if (iAppState != E_CONFIRM_QUIT)
					{
						iPrevAppState = iAppState;
						iAppState = E_CONFIRM_QUIT;
					}
					else
					{
						iAppState = iPrevAppState;
					}
						iAppState = E_QUIT; // DO USUNIÊCIA !!!
				}
			}

			 if( event.type == SDL_MOUSEMOTION ) 
			 { 
				 //Get the mouse offsets 
				 pMouse->fMouseX(event.motion.x); 
				 pMouse->fMouseY(event.motion.y);
			 }

			  //If a mouse button was pressed 
			 if( event.type == SDL_MOUSEBUTTONDOWN ) 
			 { 

				 // zapamietaj wspolrzedne klikniecia

				 pMouse->fMouseXClick(event.motion.x);	
				 pMouse->fMouseYClick(event.motion.y);

				 //If the left mouse button was pressed 
				 if (event.button.button == SDL_BUTTON_LEFT)
				 {
					 pMouse->isLeft(true);
				 }

				 if (event.button.button == SDL_BUTTON_RIGHT)
				 {
					 pMouse->isRight(true);
				 }

			 }

			if( event.type == SDL_MOUSEBUTTONUP ) 
			{ 
				//If the left mouse button was released 
				if( event.button.button == SDL_BUTTON_LEFT )
					pMouse->isLeft(false);

				if( event.button.button == SDL_BUTTON_RIGHT )
					pMouse->isRight(false);				
			}

		}

		switch	(iAppState)
		{	

			case	E_INGAME:

            pFont->Print("kicha i pompa prezesie",255,128,64,10,10);
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

			case	E_CONGRATULATIONS:

				if (!pCongratulations->_isOpen)
				{
					pCongratulations->Open(pMainScreen);

					if (bSettingsMSX)
					{
						ucVolumeMusic = 0;
						Mix_VolumeMusic(ucVolumeMusic);
						Mix_HaltMusic();
						Mix_PlayMusic(pMusicVictory,-1);
					}
					else
					{
						ucVolumeMusic = 0;
						Mix_VolumeMusic(ucVolumeMusic);
						Mix_HaltMusic();
					}
				}

				if (pCongratulations->Render(ulTimer,pMouse))
				{
					iAppState = E_MAINMENU;
					iPrevAppState = E_CONGRATULATIONS;
					pCongratulations->Close();
				}

			break;

		}	// switch

//		pMouse->Render();

		sprintf(cBuffer, "%d", iFPS);
//		pSpriteFont->Print(10, 10, 1, 0.05f, 0.05f, cBuffer);

		oglFlip();		// show the screen

		iFrames++;
		ulTimer = SDL_GetTicks();

		if(ulTimer - ulTimerLast> 1000)
		{
			iFPS = iFrames;
			//printf("FPS: %d\n", iFPS);
			iFrames = 0;
			ulTimerLast = ulTimer;
		}


	}

	for (int i=0; i<7; i++)
	{
		Mix_FreeMusic(pMusicIngame[i]);
	}

	Mix_FreeMusic(pMusicMenu);
	Mix_FreeMusic(pMusicPostgame);
	Mix_FreeMusic(pMusicVictory);

	// usun stany aplikacji

	delete pIngame;		
	delete pCongratulations;

	// usun load screen

	delete pLoadScreen;
	delete pConfirmQuit;

	delete pButtonYES;
	delete pButtonNO;

	// zwolnij myszke, ekran, itd
   delete pFont;
	delete pSpriteFont;
	delete pMouse;
	delete pMainScreen;

   TTF_Quit();
	SDL_Quit();
		
	return 0;
}

