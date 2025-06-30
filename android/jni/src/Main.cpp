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

//=== ui

#include "application/uiMain.h"
#include "application/uiKeypad.h"

#include "application/Intro.h"
#include "application/MainMenu.h"

// stany aplikacji

uiMain	*pUIMain;
uiKeypad *pUIKeypad;

CIntro				*pIntro;
CMainMenu			*pMainMenu;

//=== zmienne globalne

int					iAppState;			// aktualny stan aplikacji
int					iPrevAppState; 		// poprzedni stan aplikacji

unsigned char		ucLanguage;			// jezyk wyswietlania

CScreen				*pScreen;			// ekran

CTouch				*pTouch;			// dane z ekranu dotykowego

CSprite				*pBackground;		// plik z tlem
CSprite				*pTopBar;			// gorny pasek
CSprite				*pBottomBar;		// dolny pasek

// grafiki do preload screen

CSprite	*pLoadScreen;
CSprite *pGreyBar;
CSprite *pGreenBar;
CSprite *pStart;
CSprite *pConfirmQuit;					// czy na pewno wyjscie z gry ?

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

// do ustawien aplikacji, zeby bylo wiadomo kiedy mamy wczytywac muzyke a kiedy nie

bool	bSettingsMSX;
bool	bSettingsSFX;

int		iLoad;

//=== muzyka

Mix_Music *pMusicIngame[7], *pMusicMenu, *pMusicPostgame, *pMusicVictory;

// load screen - wyswietla sie w trakcie wczytywania danych

void LoadScreen(int iProgress)
{
	int x1,x2,y1,y2, dx, dy;
	float fx;

	pLoadScreen->Render();

	if (pScreen->iSizeX()==1366 && pScreen->iSizeY()==768)
	{
		x1 = 387; y1 = 490;
		x2 = 387+592; y2 = 490+36;
	}

	dx = x2-x1; dy=y2-y1;

	pGreyBar->Resize(x1,y1,x2,y2);
	pGreyBar->Render();

	fx = (float)(dx * (iProgress*0.01f));

	pGreenBar->Resize(x1,y1,x1+(int)fx,y2);
	pGreenBar->Render();

}

//=== wczytaj konfiguracje z pliku

void loadGameConfig(void)
{
/*
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
*/
}


//=== wczytaj ustawienia

void reloadSettings(void)
{
	// wczytaj config
/*
	CGameSettings *pSetup;

	pSetup = new CGameSettings();
	pSetup->bLoad();

	bSettingsMSX = pSetup->isMSX();
	bSettingsSFX = pSetup->isSFX();

	delete pSetup;
*/
}

// przelacz pomiedzy stanami

void State(int i)
{
	iPrevAppState = iAppState;
	iAppState = i;
}

//=== MAIN ===

int main(int argc, char *argv[])
{
	iAppState = E_MAIN;
	iPrevAppState = E_MAIN;

	ucLanguage = (LANG_POLAND);			// domyślnie język polski

	// inicjalizacja audio

	if (SDL_Init(SDL_INIT_AUDIO)<0)
	{
		printf("ERROR: unable to init audio\n");
		exit(1);
	}

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	Mix_AllocateChannels(8);

	bSettingsSFX = true;
	bSettingsMSX = true;

	loadGameConfig();

	// inicjalizacja grafiki

	pTouch = new CTouch();
	pScreen = new CScreen();

	// inicjalizacja stanow

	pUIMain = new uiMain(pScreen);
	pUIKeypad = new uiKeypad(pScreen);

	pIntro = new CIntro(pScreen);
	pMainMenu = new CMainMenu(pScreen);

	// dodatkowe grafiki

	pBackground = new CSprite((char*)"background.png");
	pBackground->Resize(0,0,pScreen->iSizeX(), pScreen->iSizeY());

	pTopBar = new CSprite(pScreen,(char*)"topbar");
	pTopBar->Resize(0,0,pScreen->iSizeX(),pScreen->iSizeY()/16);

	pBottomBar = new CSprite(pScreen,(char*)"bottombar");
	pBottomBar->Resize(0,pScreen->iSizeY()-(pScreen->iSizeY()/16),pScreen->iSizeX(), pScreen->iSizeY());

	// czcionka glowna

//	pSpriteFont = new CSpriteFont(pMainScreen);

	// sprawdz ustawienia

	reloadSettings();

	// ekran wczytywania danych
/*
	pLoadScreen = new CSprite(pMainScreen,"GFX_LOAD_SCREEN");
	pGreyBar = new CSprite(pMainScreen,"BAR_GREY");
	pGreenBar = new CSprite(pMainScreen,"BAR_GREEN");
*/

	// ekran w trakcie wczytywania muzyki itd

//	pStart = new CSprite(pMainScreen,"START");
//	pStart->Render();
//	pScreen->Flip();

	iLoad = 0;// progress bar, zeby nie przenosil z poprzedniego stanu

	SDL_Log("=== APPLICATION START ===\n");

	State(E_INTRO);

	// load music

	pMusicIngame[0] = Mix_LoadMUS("music_ingame01.ogg");
	pMusicIngame[1] = Mix_LoadMUS("music_ingame02.ogg");
	pMusicIngame[2] = Mix_LoadMUS("music_ingame03.ogg");
	pMusicIngame[3] = Mix_LoadMUS("music_ingame04.ogg");
	pMusicIngame[4] = Mix_LoadMUS("music_ingame05.ogg");
	pMusicIngame[5] = Mix_LoadMUS("music_ingame06.ogg");
	pMusicIngame[6] = Mix_LoadMUS("music_ingame07.ogg");

	pMusicMenu = Mix_LoadMUS("music_mainmenu.ogg");
	pMusicPostgame = Mix_LoadMUS("music_postgame.ogg");
	pMusicVictory = Mix_LoadMUS("music_victory.ogg");

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
					pTouch->Update(true, event.tfinger.x * pScreen->iSizeX(), event.tfinger.y * pScreen->iSizeY());
					isEvent = true;
				break;

				case SDL_FINGERMOTION:
					pTouch->Update(true, event.tfinger.x * pScreen->iSizeX(), event.tfinger.y * pScreen->iSizeY());
					isEvent = true;
				break;

				case SDL_FINGERUP:
					pTouch->Update(false, event.tfinger.x * pScreen->iSizeX(), event.tfinger.y * pScreen->iSizeY());
					isEvent = true;
				break;
			}
		}

		switch(iAppState)
		{
			case E_INTRO:

				if (!pIntro->isActive())
				{
					pIntro->Open();

					if (bSettingsMSX)
					{
						Mix_PlayMusic(pMusicMenu,-1);
					}
					else
					{
						Mix_VolumeMusic(0);
						Mix_HaltMusic();
					}
				}

				iEvent = pIntro->iRender(ulTimer, pTouch);

				if (iEvent == 1)
				{
					pIntro->Close();
					State(E_MAIN);
				}

			break;

			case E_MAINMENU:

				if (!pMainMenu->isActive())
				{
					pMainMenu->ucLanguage(ucLanguage);
					iLoad = pMainMenu->Open();

					if (_iLoad == 101)
					{
	                    if (_iPrevAppState == E_SETTINGS)	// zaktualizuj ustawienia
	                    {
	                        reloadSettings();
	                    }

	                    if (_iPrevAppState == E_INGAME || _iPrevAppState == E_POSTGAME ||
	                        _iPrevAppState == E_SETTINGS || _iPrevAppState == E_CONGRATULATIONS)
	                    {
	                        if (_bSettingsMSX)
	                        {
	                            if (!_pMusic) _pMusic->stopMusic();

	                            SafeDelete(_pMusic);
	                            _pMusic = new KMusic();
	                            _pMusic->playMusic(KMiscTools::makeFilePath("music_mainmenu.mp3"));
	                        }

	                    }
	                    LoadScreen(100);
					}
					else
					{
	                    LoadScreen(_iLoad);
					}
				}
	            else	// assety zaladowane - renderowanie
	            {
	                iMode = _pMainMenu->Render(m_pTouch,m_ulTimer);

	                switch (iMode)
	                {
							// START - wybor etapu

	                    case 1:
	                        _pMainMenu->Close();
	                        State(E_LEVELMENU);
							break;

							// SETTINGS - ustawienia

	                    case 2:
	                        _pMainMenu->Close();
	                        State(E_SETTINGS);
							break;

							// TROPHY ROOM

	                    case 3:
	                        _pMainMenu->Close();
	                        _iAppState = E_TROOPHY;
	                        _iPrevAppState = E_MAINMENU;
							break;

							// HELP

	                    case 4:
	                        _pMainMenu->Close();
	                        _iAppState = E_HELP;
	                        _iPrevAppState = E_MAINMENU;
							break;

							// SUPPORT / CREDITS

	                    case 5:
	                        _pMainMenu->Close();
	                        _iAppState = E_CREDITS;
	                        _iPrevAppState = E_MAINMENU;
							break;

							// ZMIANA JEZYKA

	                    case 10:
	                        _pMainMenu->Close();
	                        _iAppState = E_LANGUAGE;
	                        _iPrevAppState = E_MAINMENU;
							break;
	                }

	            }

			break;

		}

		pScreen->Flip();
		ulTimer = SDL_GetTicks();

	}

	// wyłączenie muzyki

	for (int i=0; i<7; i++)
	{
		Mix_FreeMusic(pMusicIngame[i]);
	}

	Mix_FreeMusic(pMusicMenu);
	Mix_FreeMusic(pMusicPostgame);
	Mix_FreeMusic(pMusicVictory);

	// usuniecie obiektów

	delete pUIMain;
	delete pUIKeypad;

	SafeDelete(pIntro);

	delete pTouch;

	delete pTopBar;
	delete pBackground;

	delete pScreen;

	exit(0);

}
