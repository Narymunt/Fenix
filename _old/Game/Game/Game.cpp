// Game.cpp : Defines the entry point for the console application.

#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define NTDDI_VERSION 0x0501

#pragma warning(disable : 4996)

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Game.h"

#include "OGL.h"

#ifdef _DEBUG
#include "vld.h"
#endif 

#include "Screen.h"
#include "Sprite.h"
#include "Mouse.h"
#include "GameSettings.h"
#include "Button.h"

//=== stany aplikacji 

#include "eLanguage.h"				// wybor jezyka
#include "ePreload.h"				// loga
#include "eIntro.h"
#include "eMainMenu.h"				// menu glowne, nowa gra, ustawienia itd itp
#include "eLevelMenu.h"
#include "eIngame.h"				// in game - tutaj ukladamy klocki
#include "ePostGame.h"				// zliczanie punktow po levelu do glownego profilu
#include "eHelp.h"					// plansza pomocnicza
#include "eCredits.h"				// autorzy gry
#include "eTroophy.h"				// trofea i osiagniecia dla tego profilu
#include "eSettings.h"				// zmiana ustawien gry
#include "eCongratulations.h"		// zwyciêstwo !!! koniec gry !!!
#include "ePostTroophy.h"			// zdobyte trofea po zakoñczeniu levelu
#include "SpriteFont.h"

int		iAppState;					// current application state
int		iPrevAppState;				// poprzedni stan aplikacji
int		iLoad;						// na jakim etapie wczytywania danych jestesmy

int		iReturn;					// funkcje renderujace moga zwracac rozne wartosci

unsigned char	ucLanguage;			// w jakim jezyku wyswietlamy menu etc.

unsigned char	ucVolumeMusic;		// glosnosc muzyki

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
CSprite *pStart;			
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
	int x1,x2,y1,y2, dx, dy;
	float fx;

	pLoadScreen->Render();

	if (pMainScreen->iSizeX()==1366 && pMainScreen->iSizeY()==768)
	{
		x1 = 387; y1 = 490; 
		x2 = 387+592; y2 = 490+36;
	} 
	else if (pMainScreen->iSizeX()==1024 && pMainScreen->iSizeY()==768)
	{
		x1 = 207; y1 = 480; 
		x2 = 820; y2 = 511;
	}
	else if (pMainScreen->iSizeX() == 1920 && pMainScreen->iSizeY() == 1080)
	{
		x1 = 542; y1 = 684;
		x2 = 542+839; y2 = 684+52;
	}
	else if (pMainScreen->iSizeX() == 2560 && pMainScreen->iSizeY() == 1440)
	{
		x1 = 721; y1 = 916;
		x2 = 721+1121; y2 = 916+64;
	}

	dx = x2-x1; dy=y2-y1;

	pGreyBar->Resize(x1,y1,x2,y2);		
	pGreyBar->Render();

	fx = (float)(dx * (iProgress*0.01f));

	pGreenBar->Resize(x1,y1,x1+(int)fx,y2);
	pGreenBar->Render();

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

	pMainScreen->InitDictionary();	// inicjalizacja slownika

	// inicjalizacja myszki

	pMouse = new CMouse();

	// czcionka g³ówna

	pSpriteFont = new CSpriteFont(pMainScreen);

	// sprawdz ustawienia

	reloadSettings();

	// ekran wczytywania danych

	pLoadScreen = new CSprite(pMainScreen,"GFX_LOAD_SCREEN");
	pGreyBar = new CSprite(pMainScreen,"BAR_GREY");
	pGreenBar = new CSprite(pMainScreen,"BAR_GREEN");
	pConfirmQuit = new CSprite(pMainScreen, "QUIT_SCREEN");

	pButtonYES = new CButton(pMainScreen, "BUTTON_OK_PROFILE");
	pButtonNO = new CButton(pMainScreen, "BUTTON_CANCEL_PROFILE");

	if (pMainScreen->iSizeX() < 1500)
	{
		pButtonYES->SetPosition(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2);
		pButtonYES->SetHotCoords(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2, pMainScreen->iSizeX() / 4 + 128, pMainScreen->iSizeY() / 2 + 128);

		pButtonNO->SetPosition((pMainScreen->iSizeX() / 4) * 3 - 128, pMainScreen->iSizeY() / 2);
		pButtonNO->SetHotCoords((pMainScreen->iSizeX() / 4) * 3 - 128, pMainScreen->iSizeY() / 2, (pMainScreen->iSizeX() / 4) * 3, pMainScreen->iSizeY() / 2 + 128);
	}
	else
	{
		pButtonYES->SetPosition(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2);
		pButtonYES->SetHotCoords(pMainScreen->iSizeX() / 4, pMainScreen->iSizeY() / 2, pMainScreen->iSizeX() / 4 + 256, pMainScreen->iSizeY() / 2 + 256);

		pButtonNO->SetPosition((pMainScreen->iSizeX() / 4) * 3 - 256, pMainScreen->iSizeY() / 2);
		pButtonNO->SetHotCoords((pMainScreen->iSizeX() / 4) * 3 - 256, pMainScreen->iSizeY() / 2, (pMainScreen->iSizeX() / 4) * 3, pMainScreen->iSizeY() / 2 + 256);
	}
	// ekran w trakcie wczytywania muzyki itd

	pStart = new CSprite(pMainScreen,"START");
	pStart->Render();
	oglFlip();

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

	// hide cursor

	SDL_ShowCursor(SDL_DISABLE); 
	
	iFrames = 0;
	iFPS = 0;
	ulTimer = 0;
	ulTimerLast = 0;

	SDL_WM_SetCaption("SHODAN9 : GAME", "SHODAN9 : GAME");

	iPrevAppState = E_SETTINGS;

	iAppState = iLoadAppState();

	if (!iAppState)
		iAppState = E_LANGUAGE;			// start aplikacji

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
				}
			}

			// F9 = screenshot

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F9)
			{
				SDL_Surface * image = SDL_CreateRGBSurface(SDL_SWSURFACE, pMainScreen->iSizeX(), pMainScreen->iSizeY(), 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);

				glReadBuffer(GL_FRONT);
				glReadPixels(0, 0, pMainScreen->iSizeX(), pMainScreen->iSizeY(), GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

				SDL_SaveBMP(image, "screenshot.bmp");
				SDL_FreeSurface(image);
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
					pMouse->iState(MOUSE_NONE);
					
					if (bSettingsMSX)
					{
						Mix_PlayMusic(pMusicMenu,200);
						ucVolumeMusic = 0;
						Mix_VolumeMusic(ucVolumeMusic);
					}
					else
					{
						ucVolumeMusic = 0;
						Mix_VolumeMusic(ucVolumeMusic);
						Mix_HaltMusic();
					}
				}
				
				// przelaczyc ? 
					
				if (pPreload->Render(ulTimer/10,pMouse))
				{
					pMouse->iState(MOUSE_ARROW);
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
					pMouse->iState(MOUSE_WAIT);			// zmien kursor myszy na czekanie

					if (iLoad==101)
					{
						pMouse->iState(MOUSE_ARROW);	// kursor myszy na strzalke

						if (iPrevAppState == E_SETTINGS)	// zaktualizuj ustawienia
						{
							reloadSettings();
						}

						if (iPrevAppState == E_INGAME || iPrevAppState == E_POSTGAME || iPrevAppState == E_SETTINGS || iPrevAppState == E_CONGRATULATIONS)
						{
							if (bSettingsMSX)
							{
								ucVolumeMusic = 0;
								Mix_VolumeMusic(ucVolumeMusic);
								Mix_HaltMusic();
								Mix_PlayMusic(pMusicMenu,200);
							}
							else
							{
								ucVolumeMusic = 0;
								Mix_VolumeMusic(ucVolumeMusic);
								Mix_HaltMusic();
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
							ucVolumeMusic = 0;
							Mix_VolumeMusic(ucVolumeMusic);
							Mix_HaltMusic();
							Mix_PlayMusic(pMusicMenu,200);
						}
						else
						{
							ucVolumeMusic = 0;
							Mix_VolumeMusic(ucVolumeMusic);
							Mix_HaltMusic();
						}
					}
				}

				iReturn = pLevelMenu->Render(ulTimer,pMouse);

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
							ucVolumeMusic = 0;
							Mix_VolumeMusic(ucVolumeMusic);
							Mix_HaltMusic();
							Mix_PlayMusic(pMusicIngame[pLevelMenu->iGetCurrentLevel()-1],200);
						}
						else
						{
							ucVolumeMusic = 0;
							Mix_VolumeMusic(ucVolumeMusic);
							Mix_HaltMusic();
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

					ucVolumeMusic = 0;
					Mix_VolumeMusic(ucVolumeMusic);
					Mix_HaltMusic();

					for (int i=0; i<20; i++)									// dane graficzne juz rozladowane, ale tablica trzyma ustawienia z ostatniej gry
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
						ucVolumeMusic = 0;
						Mix_VolumeMusic(ucVolumeMusic);
						Mix_HaltMusic();
						Mix_PlayMusic(pMusicPostgame,200);
					}
					else
					{
						ucVolumeMusic = 0;
						Mix_VolumeMusic(ucVolumeMusic);
						Mix_HaltMusic();
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

					case 100:
						Mix_HaltMusic();
						iAppState = E_CONGRATULATIONS;
						iPrevAppState = E_POSTGAME;
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
					reloadSettings();	// wczytaj na nowo ustawienia dotyczace muzyki
				}

			break;

			case	E_CONGRATULATIONS:

				if (!pCongratulations->isActive())
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

			case	E_CONFIRM_QUIT:

				pConfirmQuit->Render();						

				if (pMainScreen->iSizeX() == 1024)
				{
					if (ucLanguage == LANG_POLAND)
					{
						pSpriteFont->Print(200, 128, 1, 0.15f, 0.15f, "koniec gry?");
					}
					else if (ucLanguage == LANG_GERMANY)
					{
						pSpriteFont->Print(100, 128, 1, 0.15f, 0.15f, "ausfahrt spiel?");
					}
					else if (ucLanguage == LANG_FRANCE)
					{
						pSpriteFont->Print(100, 128, 1, 0.15f, 0.15f, "jeu de sortie?");
					}
					else if (ucLanguage == LANG_ITALY)
					{
						pSpriteFont->Print(100, 128, 1, 0.15f, 0.15f, "gioco di uscita?");
					}
					else if (ucLanguage == LANG_SPAIN)
					{
						pSpriteFont->Print(150, 128, 1, 0.15f, 0.15f, "juego salida?");
					}
					else if (ucLanguage == LANG_TURKEY)
					{
						pSpriteFont->Print(150, 128, 1, 0.15f, 0.15f, "cikis oyunu?");
					}
					else if (ucLanguage == LANG_BRASIL || ucLanguage == LANG_PORTUGAL)
					{
						pSpriteFont->Print(100, 128, 1, 0.15f, 0.15f, "jogo de saida?");
					}
					else if (ucLanguage == LANG_SWEDEN)
					{
						pSpriteFont->Print(100, 128, 1, 0.15f, 0.15f, "avsluta spelet?");
					}
					else if (ucLanguage == LANG_DENMARK)
					{
						pSpriteFont->Print(200, 128, 1, 0.15f, 0.15f, "afslut spil?");
					}
					else if (ucLanguage == LANG_NORWAY)
					{
						pSpriteFont->Print(50, 128, 1, 0.15f, 0.15f, "avslutte spillet?");
					}
					else
					{
						pSpriteFont->Print(256, 128, 1, 0.15f, 0.15f, "exit game?");
					}
				} // 1024
				else if (pMainScreen->iSizeX() == 1366)
				{
					if (ucLanguage == LANG_POLAND)
					{
						pSpriteFont->Print(300, 128, 1, 0.15f, 0.15f, "koniec gry?");
					}
					else if (ucLanguage == LANG_GERMANY)
					{
						pSpriteFont->Print(300, 128, 1, 0.15f, 0.15f, "ausfahrt spiel?");
					}
					else if (ucLanguage == LANG_FRANCE)
					{
						pSpriteFont->Print(300, 128, 1, 0.15f, 0.15f, "jeu de sortie?");
					}
					else if (ucLanguage == LANG_ITALY)
					{
						pSpriteFont->Print(250, 128, 1, 0.15f, 0.15f, "gioco di uscita?");
					}
					else if (ucLanguage == LANG_SPAIN)
					{
						pSpriteFont->Print(350, 128, 1, 0.15f, 0.15f, "juego salida?");
					}
					else if (ucLanguage == LANG_TURKEY)
					{
						pSpriteFont->Print(350, 128, 1, 0.15f, 0.15f, "cikis oyunu?");
					}
					else if (ucLanguage == LANG_BRASIL || ucLanguage == LANG_PORTUGAL)
					{
						pSpriteFont->Print(300, 128, 1, 0.15f, 0.15f, "jogo de saida?");
					}
					else if (ucLanguage == LANG_SWEDEN)
					{
						pSpriteFont->Print(300, 128, 1, 0.15f, 0.15f, "avsluta spelet?");
					}
					else if (ucLanguage == LANG_DENMARK)
					{
						pSpriteFont->Print(350, 128, 1, 0.15f, 0.15f, "afslut spil?");
					}
					else if (ucLanguage == LANG_NORWAY)
					{
						pSpriteFont->Print(200, 128, 1, 0.15f, 0.15f, "avslutte spillet?");
					}
					else
					{
						pSpriteFont->Print(420, 128, 1, 0.15f, 0.15f, "exit game?");
					}
				}
				else if (pMainScreen->iSizeX() == 1920)
				{
					if (ucLanguage == LANG_POLAND)
					{
						pSpriteFont->Print(500, 128, 1, 0.25f, 0.25f, "koniec gry?");
					}
					else if (ucLanguage == LANG_GERMANY)
					{
						pSpriteFont->Print(300, 128, 1, 0.25f, 0.25f, "ausfahrt spiel?");
					}
					else if (ucLanguage == LANG_FRANCE)
					{
						pSpriteFont->Print(300, 128, 1, 0.25f, 0.25f, "jeu de sortie?");
					}
					else if (ucLanguage == LANG_ITALY)
					{
						pSpriteFont->Print(250, 128, 1, 0.25f, 0.25f, "gioco di uscita?");
					}
					else if (ucLanguage == LANG_SPAIN)
					{
						pSpriteFont->Print(350, 128, 1, 0.25f, 0.25f, "juego salida?");
					}
					else if (ucLanguage == LANG_TURKEY)
					{
						pSpriteFont->Print(150, 128, 1, 0.25f, 0.25f, "cikis oyunu?");
					}
					else if (ucLanguage == LANG_BRASIL || ucLanguage == LANG_PORTUGAL)
					{
						pSpriteFont->Print(400, 128, 1, 0.25f, 0.25f, "jogo de saida?");
					}
					else if (ucLanguage == LANG_SWEDEN)
					{
						pSpriteFont->Print(300, 128, 1, 0.25f, 0.25f, "avsluta spelet?");
					}
					else if (ucLanguage == LANG_DENMARK)
					{
						pSpriteFont->Print(450, 128, 1, 0.25f, 0.25f, "afslut spil?");
					}
					else if (ucLanguage == LANG_NORWAY)
					{
						pSpriteFont->Print(200, 128, 1, 0.25f, 0.25f, "avslutte spillet?");
					}
					else
					{
						pSpriteFont->Print(520, 128, 1, 0.25f, 0.25f, "exit game?");
					}
				} // 1920
				else if (pMainScreen->iSizeX() == 2560)
				{
					if (ucLanguage == LANG_POLAND)
					{
						pSpriteFont->Print(700, 128, 1, 0.3f, 0.3f, "koniec gry?");
					}
					else if (ucLanguage == LANG_GERMANY)
					{
						pSpriteFont->Print(500, 128, 1, 0.3f, 0.3f, "ausfahrt spiel?");
					}
					else if (ucLanguage == LANG_FRANCE)
					{
						pSpriteFont->Print(500, 128, 1, 0.3f, 0.3f, "jeu de sortie?");
					}
					else if (ucLanguage == LANG_ITALY)
					{
						pSpriteFont->Print(400, 128, 1, 0.3f, 0.3f, "gioco di uscita?");
					}
					else if (ucLanguage == LANG_SPAIN)
					{
						pSpriteFont->Print(600, 128, 1, 0.3f, 0.3f, "juego salida?");
					}
					else if (ucLanguage == LANG_TURKEY)
					{
						pSpriteFont->Print(600, 128, 1, 0.3f, 0.3f, "cikis oyunu?");
					}
					else if (ucLanguage == LANG_BRASIL || ucLanguage == LANG_PORTUGAL)
					{
						pSpriteFont->Print(500, 128, 1, 0.3f, 0.3f, "jogo de saida?");
					}
					else if (ucLanguage == LANG_SWEDEN)
					{
						pSpriteFont->Print(500, 128, 1, 0.3f, 0.3f, "avsluta spelet?");
					}
					else if (ucLanguage == LANG_DENMARK)
					{
						pSpriteFont->Print(600, 128, 1, 0.3f, 0.3f, "afslut spil?");
					}
					else if (ucLanguage == LANG_NORWAY)
					{
						pSpriteFont->Print(400, 128, 1, 0.3f, 0.3f, "avslutte spillet?");
					}
					else
					{
						pSpriteFont->Print(700, 128, 1, 0.3f, 0.3f, "exit game?");
					}
				} // 2560

				if (pButtonYES->Render(pMouse) == ON_LEFT)
				{
					pButtonNO->Render(pMouse);

					if (iPrevAppState == E_INGAME)
					{
						pIngame->Close();
						iAppState = E_MAINMENU;
					}
					else if (iPrevAppState == E_POSTGAME)
					{
						pPostGame->Close();
						iAppState = E_MAINMENU;
					}
					else if (iPrevAppState == E_POST_TROOPHY)
					{
						pPostTroophy->Close();
						iAppState = E_MAINMENU;
					}
					else if (iPrevAppState == E_LEVELMENU)
					{
						pLevelMenu->Close();
						iAppState = E_MAINMENU;
					}
					else
					{
						iAppState = E_QUIT;
					}
				}

				if (pButtonNO->Render(pMouse) == ON_LEFT)
				{
					iAppState = iPrevAppState;
				}

			break;


		}	// switch

		pMouse->Render();

//		sprintf(cBuffer, "%d", iFPS);
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
	delete pStart;
	delete pConfirmQuit;

	delete pButtonYES;
	delete pButtonNO;

	// zwolnij myszke, ekran, itd

	delete pSpriteFont;
	delete pMouse;
	delete pMainScreen;

	SDL_Quit();
		
	return 0;
}

