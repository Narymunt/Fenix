// Game.cpp : Defines the entry point for the console application.

//#pragma comment(lib, "opengl32.lib")

#pragma warning(disable : 4996)

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Game.h"

#include "OGL.h"

#include "Screen.h"
#include "Sprite.h"
#include "Mouse.h"
#include "GameSettings.h"

//=== stany aplikacji 

#include "eLanguage.h"		// wybor jezyka
#include "ePreload.h"		// loga
#include "eIntro.h"
#include "eMainMenu.h"		// menu glowne, nowa gra, ustawienia itd itp
#include "eLevelMenu.h"
#include "eIngame.h"		// in game - tutaj ukladamy klocki
#include "ePostGame.h"		// zliczanie punktow po levelu do glownego profilu
#include "eHelp.h"			// plansza pomocnicza
#include "eCredits.h"		// autorzy gry
#include "eTroophy.h"		// trofea i osiagniecia dla tego profilu
#include "eSettings.h"		// zmiana ustawien gry
#include "eCongratulations.h"	// zwyciêstwo !!! koniec gry !!!
#include "ePostTroophy.h"	// zdobyte trofea po zakoñczeniu levelu


// visual leak detector

//#include "vld.h"

int		iAppState;		// current application state
int		iPrevAppState;	// poprzedni stan aplikacji
int		iLoad;			// na jakim etapie wczytywania danych jestesmy

int		iReturn;			// funkcje renderujace moga zwracac rozne wartosci

unsigned char	ucLanguage;		// w jakim jezyku wyswietlamy menu etc.


// stany aplikacji

eLanguage			*pLanguage;		// wybor jezyka
ePreload			*pPreload;		// banery reklamowe
eMainMenu			*pMainMenu;		// main menu application state class
eLevelMenu			*pLevelMenu;	// wybor etapu gry
eIngame				*pIngame;		// MATCH3
ePostGame			*pPostGame;		// zliczanie punktow po levelu
eHelp				*pHelp;			// plansza pomocnicza
eCredits			*pCredits;		// plansza z autorami gry
eTroophy			*pTroophy;		// plansza z osiagnieciami
eSettings			*pSettings;		// zmiana ustawien gry
eCongratulations	*pCongratulations;	// zwyciêstwo, koniec gry
ePostTroophy		*pPostTroophy;	// zdobyte trofea po zakoñczeniu jednorazowej gry


// ekran

CScreen	*pMainScreen;	// our screen, there can be more than 1

// myszka 

CMouse	*pMouse;

// grafiki do preload screen

CSprite	*pLoadScreen;
CSprite *pGreyBar;
CSprite *pGreenBar;

// eventy dla SDL

SDL_Event event;		// sdl event 

// muzyka

Mix_Music *pMusicIngame, *pMusicMenu, *pMusicPostgame;

// timery do liczenia klatek

int frames;
unsigned long ulTimer;	// main application timer

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

void fx_debug(char cInfo[])
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
		
	for (int i=(iScreenX/16); i<iScreenX-(iScreenX/16); i++)
	{
		pGreyBar->Position((float)i,(float)iScreenY-(iScreenY/8));
		pGreyBar->Render();
	}

	for (int i=0; i< (9*iProgress); i+=32)
	{
		pGreenBar->Position((float)((iScreenX/16)+i),iScreenY-(iScreenY/8));
		pGreenBar->Render();
	}
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



//=== main application

int main(int argc, char **argv)
{

	atexit(SDL_Quit);
	
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
		iScreenX = pMainScreen->iSizeX();
		iScreenY = pMainScreen->iSizeY();
	}
	// ustawiamy na podstawie parametrow

	if (iMode==1)
		pMainScreen = new CScreen(iScreenX,iScreenY,32,true);

	if (iMode==0)
		pMainScreen = new CScreen(iScreenX,iScreenY,32,false);

	pMouse = new CMouse();

	// wczytaj config

	CGameSettings *pSetup;

	pSetup = new CGameSettings();
	pSetup->bLoad();

	bSettingsMSX = pSetup->isMSX();
	bSettingsSFX = pSetup->isSFX();

	delete pSetup;

	// ekran wczytywania danych

	pLoadScreen = new CSprite(pMainScreen,"GFX_LOAD_SCREEN");
	pGreyBar = new CSprite(pMainScreen,"BAR_GREY");
	pGreenBar = new CSprite(pMainScreen,"BAR_GREEN");

	// inicjalizacja malych komponentow

	iLoad = 0;	// progress bar, zeby nie przenosil z poprzedniego stanu

	pPreload = new ePreload();
	pLanguage = new eLanguage();
	pMainMenu = new eMainMenu();
	pLevelMenu = new eLevelMenu();
	pIngame = new eIngame();
	pPostGame = new ePostGame();
	pHelp = new eHelp();
	pCredits = new eCredits();
	pTroophy = new eTroophy();
	pSettings = new eSettings();
	pCongratulations = new eCongratulations();
	pPostTroophy = new ePostTroophy();

	// load music

	pMusicIngame = Mix_LoadMUS("data/music_ingame.ogg");
	pMusicMenu = Mix_LoadMUS("data/music_mainmenu.ogg");
	pMusicPostgame = Mix_LoadMUS("data/music_postgame.ogg");

	// hide cursor

	SDL_ShowCursor(SDL_DISABLE); 
	
	frames = 0;

	SDL_WM_SetCaption("SHODAN9 : GAME", "SHODAN9 : GAME");

	iPrevAppState = E_SETTINGS;
	iAppState = E_LANGUAGE; //E_MAINMENU;	// start aplikacji

	ulTimer = SDL_GetTicks();

	while(iAppState!=E_QUIT)
	{

		oglClear();		// clear screen

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				iAppState = E_QUIT;
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
				 //If the left mouse button was pressed 
				 if( event.button.button == SDL_BUTTON_LEFT ) 
					 pMouse->isLeft(true);

				 if( event.button.button == SDL_BUTTON_RIGHT ) 
					 pMouse->isRight(true);

			 }

			if( event.type == SDL_MOUSEBUTTONUP ) 
			{ 
				//If the left mouse button was released 
				if( event.button.button == SDL_BUTTON_LEFT )
					pMouse->isLeft(false);

				if( event.button.button == SDL_BUTTON_LEFT )
					pMouse->isRight(false);				
			}

		}

		switch	(iAppState)
		{	

			case	E_LANGUAGE:

				if (!pLanguage->isActive())
					pLanguage->Open(pMainScreen);

				if (pLanguage->Render(ulTimer,pMouse)!=0)
				{	
					if (ucLanguage==0)
					{
						iAppState = E_PRELOAD;	// pierwsze uruchomienie aplikacji
					}
					else
					{
						iAppState = E_MAINMENU;	// kolejna zmiana jezyka
						iPrevAppState = E_PRELOAD;	// przeskakujemy preload przy zmianie jezyka z menu glownego
					}

					ucLanguage = pLanguage->ucLanguage();

					pLanguage->Close();
				}
	
			break;

			case	E_PRELOAD:

				if (!pPreload->isActive()) // nie zawiera danych
				{
					pPreload->Open(pMainScreen);
					
					if (bSettingsMSX)
						Mix_PlayMusic(pMusicMenu,200);
				}
				
				// przelaczyc ? 
					
				if (pPreload->Render(ulTimer,pMouse))
				{
					pPreload->Close();		// zwalniamy zasoby, ale zapamietujemy ustawienia
					iAppState=E_MAINMENU;
					iPrevAppState = E_PRELOAD;
				}

			break;

			case	E_MAINMENU:
				if (!pMainMenu->isActive())
				{
					pMainMenu->ucLanguage(ucLanguage);	// ustawiamy jezyk zanim zainicjalizujemy assety
					iLoad = pMainMenu->Open(pMainScreen);

					if (iLoad==101)
					{
						if (iPrevAppState == E_SETTINGS)	// zaktualizuj ustawienia
						{
							CGameSettings *pSetup;

							pSetup = new CGameSettings();
							pSetup->bLoad();

							bSettingsMSX = pSetup->isMSX();
							bSettingsSFX = pSetup->isSFX();

							delete pSetup;
						}

						if (iPrevAppState == E_INGAME || iPrevAppState == E_POSTGAME || iPrevAppState == E_SETTINGS)
						{
							if (bSettingsMSX)
							{
								Mix_HaltMusic();
								Mix_PlayMusic(pMusicMenu,200);
							}
						}
					}
					else
					{
						LoadScreen(iLoad);
					}
				}
				else	// assety zaladowane - renderowanie
				{

					switch (pMainMenu->Render(ulTimer,pMouse,KEYPRESSED))
					{

						// START - wybor etapu
	
						case 1:
							pMainMenu->Close();
							iAppState = E_LEVELMENU;
							iPrevAppState = E_MAINMENU;
						break;

						// SETTINGS - ustawienia

						case 2:
							pMainMenu->Close();
							iAppState = E_SETTINGS;
							iPrevAppState = E_MAINMENU;
						break;

						// TROPHY ROOM

						case 3:
							pMainMenu->Close();
							iAppState = E_TROOPHY;
							iPrevAppState = E_MAINMENU;
						break;	

						// HELP

						case 4:
							pMainMenu->Close();
							iAppState = E_HELP;
							iPrevAppState = E_MAINMENU;
						break;

						// SUPPORT / CREDITS

						case 5: 
							pMainMenu->Close();
							iAppState = E_CREDITS;
							iPrevAppState = E_MAINMENU;
						break;

						// QUIT

						case 6:
							pMainMenu->Close();
							iAppState = E_QUIT;
							PostQuitMessage(0);
						break;

						// ZMIANA JEZYKA

						case 10:
							pMainMenu->Close();
							iAppState = E_LANGUAGE;
							iPrevAppState = E_MAINMENU;
						break;
					}
				}
			break;

			case	E_LEVELMENU:
		
				if (!pLevelMenu->isActive())
				{
					pLevelMenu->Open(pMainScreen);
					
					if (iPrevAppState != E_PRELOAD && iPrevAppState!=E_MAINMENU)
					{
						if (bSettingsMSX)
						{
							Mix_HaltMusic();
							Mix_PlayMusic(pMusicMenu,200);
						}
					}
				}

				iReturn = pLevelMenu->Render(ulTimer,pMouse);

				if (iReturn>99)	// wejscie do koniec gry
				{
					pLevelMenu->Close();
					iAppState = E_CONGRATULATIONS;
					iPrevAppState = E_LEVELMENU;
				}


				if (iReturn>0 && iReturn <100)
				{
					pLevelMenu->Close();
					iAppState = E_INGAME;
					iPrevAppState = E_LEVELMENU;
				}

				if (iReturn<0)
				{
					pLevelMenu->Close();
					iAppState = E_MAINMENU;
					iPrevAppState = E_LEVELMENU;
				}
				
			break;

			case	E_INGAME:
				if (!pIngame->isActive())
				{
					pIngame->Open(pLevelMenu->iGetCurrentLevel(),pMainScreen);

					if (iPrevAppState == E_LEVELMENU)
					{
						if (bSettingsMSX)
						{
							Mix_HaltMusic();
							Mix_PlayMusic(pMusicIngame,200);
						}
					}
				}

				if (pIngame->Render(ulTimer/10,pMouse)<0)
				{
					pIngame->Close();		
					iAppState = E_POST_TROOPHY;
					iPrevAppState = E_INGAME;
				}
			break;		

			case	E_POST_TROOPHY:

				if (!pPostTroophy->isActive())
				{
					pPostTroophy->Open(pMainScreen);

					for (int i=0; i<20; i++)	// dane graficzne juz rozladowane, ale tablica trzyma ustawienia z ostatniej gry
						pPostTroophy->ucNewTroophy(i,pIngame->ucNewTroophy(i));

					if (!pPostTroophy->reOpen())
					{
						pPostTroophy->Close();
						iAppState = E_POSTGAME;					
					}
				}
				else
				{				
					if (pPostTroophy->Render(ulTimer,pMouse))
					{
						pPostTroophy->Close();
						iAppState = E_POSTGAME;
					}
				}

			break;

			case	E_POSTGAME:

				if (!pPostGame->isActive())
				{
					pPostGame->Open(pMainScreen);
				
					if (bSettingsMSX)
					{
						Mix_HaltMusic();
						Mix_PlayMusic(pMusicPostgame,200);
					}
				}
	
				switch (pPostGame->Render(ulTimer,pMouse))
				{
					case 1:
						Mix_HaltMusic();
						iAppState = E_MAINMENU;
						iPrevAppState = E_POSTGAME;
						pPostGame->Close();
					break;

					case 2:
						Mix_HaltMusic();
						iAppState = E_INGAME;
						iPrevAppState = E_LEVELMENU;
						pPostGame->Close();
					break;
				}

			break;

			case	E_HELP:

				if(!pHelp->isActive())
					pHelp->Open(pMainScreen);

				if (pHelp->Render(ulTimer,pMouse))
				{
					iAppState = E_MAINMENU;
					iPrevAppState = E_HELP;
					pHelp->Close();
				}

			break;

			case	E_CREDITS:

				if(!pCredits->isActive())
					pCredits->Open(pMainScreen);

				if (pCredits->Render(ulTimer,pMouse))
				{
					iAppState = E_MAINMENU;
					iPrevAppState = E_CREDITS;
					pCredits->Close();
				}

			break;

			case	E_TROOPHY:

				if(!pTroophy->isActive())
					pTroophy->Open(pMainScreen);

				if (pTroophy->Render(ulTimer,pMouse))
				{
					iAppState = E_MAINMENU;
					iPrevAppState = E_TROOPHY;
					pTroophy->Close();
				}

			break;

			case	E_SETTINGS:

				if (!pSettings->isActive())
					pSettings->Open(pMainScreen);

				if (pSettings->Render(ulTimer,pMouse))
				{
					iAppState = E_MAINMENU;
					iPrevAppState = E_SETTINGS;
					pSettings->Close();
				}

			break;

			case	E_CONGRATULATIONS:

				if (!pCongratulations->isActive())
					pCongratulations->Open(pMainScreen);

				if (pCongratulations->Render(ulTimer,pMouse))
				{
					iAppState = E_MAINMENU;
					iPrevAppState = E_CONGRATULATIONS;
					pCongratulations->Close();
				}

			break;

		}	// switch

		pMouse->Render();

		oglFlip();		// show the screen

		frames++;
		ulTimer = SDL_GetTicks();

		if(SDL_GetTicks() - ulTimer > 1000)
		{
			printf("FPS: %i\n", frames);
			frames = 0;
		}
	}

	Mix_FreeMusic(pMusicIngame);
	Mix_FreeMusic(pMusicMenu);
	Mix_FreeMusic(pMusicPostgame);

	// usun stany aplikacji

	delete pPreload;	
	delete pLanguage;	
	delete pMainMenu;	
	delete pLevelMenu;	
	delete pIngame;		
	delete pPostGame;	
	delete pHelp;		
	delete pCredits;	
	delete pTroophy;	
	delete pSettings;	
	delete pCongratulations;
	delete pPostTroophy;

	// usun load screen

	delete pLoadScreen;
	delete pGreyBar;
	delete pGreenBar;

	// zwolnij myszke

	delete pMouse;
	delete pMainScreen;

	SDL_Quit();
		
	return 0;
}

