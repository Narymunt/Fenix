#ifndef _igame_config_
#define _igame_config_

#define SCREEN_X                        1024
#define SCREEN_Y                        768

#define MMENU_OPTIONS_X                 16
#define MMENU_OPTIONS_Y                 688
#define MMENU_OPTIONS_SIZE_X            64
#define MMENU_OPTIONS_SIZE_Y            64

#define MMENU_ABOUT_X                   940
#define MMENU_ABOUT_Y                   688
#define MMENU_ABOUT_SIZE_X              64
#define MMENU_ABOUT_SIZE_Y              64

#define MMENU_CLOSE_X                   940
#define MMENU_CLOSE_Y                   16
#define MMENU_CLOSE_SIZE_X              64
#define MMENU_CLOSE_SIZE_Y              64

#define MMENU_PLAY_X                    420
#define MMENU_PLAY_Y                    256
#define MMENU_PLAY_SIZE_X               128
#define MMENU_PLAY_SIZE_Y               128

#define MMENU_PROFILE_X                 400
#define MMENU_PROFILE_Y                 680
#define MMENU_PROFILE_SIZE_X            164
#define MMENU_PROFILE_SIZE_Y            66
#define MMENU_PROFILE_INC_Y             85

#define MMENU_TROPHY_X                  850
#define MMENU_TROPHY_Y                  688
#define MMENU_TROPHY_SIZE_X             64
#define MMENU_TROPHY_SIZE_Y             64

#define MMENU_WINDMILL_BASE_X           270
#define MMENU_WINDMILL_BASE_Y           546
#define MMENU_WINDMILL_BASE_SIZE_X      64
#define MMENU_WINDMILL_BASE_SIZE_Y      64

#define MMENU_WINDMILL_WINGS_X          270
#define MMENU_WINDMILL_WINGS_Y          526
#define MMENU_WINDMILL_WINGS_SIZE_X     64
#define MMENU_WINDMILL_WINGS_SIZE_Y     64
#define MMENU_WINDMILL_WINGS_ROTATION   1

// stan aplikacji

#define E_PRELOAD       10           // wczytywanie aplikacji
#define E_ADS           20           // banery, reklamy itd.
#define E_INTRO         30           // intro do gry
#define E_MAINMENU      40           // menu główne gry
#define E_SETTINGS      50           // ustawienia gry
#define E_CREDITS       60           // autorzy gry itd. 
#define E_PAUSE         70           // pauza w grze
#define E_FREEZE        80           // zamrożenie stanu gry np. w przypadku gdy telefon dzwoni
#define E_PROFILE       90           // ustawianie profilu gracza
#define E_LEVELMENU     100          // wybor etapu w grze
#define E_INGAME        110          // GLOWNY MODUŁ GRY
#define E_TROOPHY       120          // ekran z nagrodami
#define E_GAMEOVER      130          // koniec gry
#define E_ENDSCREEN     140          // ekran końcowy, kup pełną wersje itp.
#define E_QUIT          255

// typ zdarzenia

#define EVT_NORMAL          10          // odtwarza i po ostatniej klatce nie wyswietla nic
#define EVT_NORMAL_LAST     20          // odtwarza i po ostatniej klatce wyswietla ostatnia klatke
#define EVT_NORMAL_FIRST    30          // odtwarza i po ostatniej klatce wyswietla ciagle pierwsza
#define EVT_NORMAL_LOOP     40          // odtwarza i po ostatniej klatce rozpoczyna od nowa
#define EVT_NORMAL_REVERSE  50          // odtwarza i po ostatniej klatce odtwarza odwrotnie n=liczba klatek -n
#define EVT_NORMAL_TALK     60          // odtwarza tak dlugo dopoki odtwarzany jest dany dzwiek

// typ ludzika

#define JELLY_BLUE      10
#define JELLY_RED       20

#define CALLBACK

#define min(a,b) \
({ typeof (a) _a = (a); \
typeof (b) _b = (b); \
_a < _b ? _a : _b; })
#define __max(a,b) \
({ typeof (a) _a = (a); \
typeof (b) _b = (b); \
_a > _b ? _a : _b; })

#define O_BINARY (0)

#endif
