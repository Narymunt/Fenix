#include "zipspriteplayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZipSpritePlayer::CZipSpritePlayer(char cFilename[],IDirect3DDevice8	*pDevice)
{
	FILE *plik;
	char linia[1024];
	int iSpritePlayerCount = 0;	// to jest tylko do petli wczytujacej

	m_iZipSpriteCount = 0;	// zerujemy licznik

	// otwieramy plik ze skryptem

	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		fx_debug("ERROR! Brak pliku skryptu dla CZipSpritePlayer!\n");
		return;
	}

	// najpierw liczymy ile jest obrazow

	while (strcmp(linia,"</ZIPSPRITEPLAYER>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
		if (!strcmp(linia,"<XIMAGE>")) m_iZipSpriteCount++;
		
	}

	fclose(plik);

	// inicjalizacja tablic

	m_pActive = new bool [m_iZipSpriteCount];

	m_pCZipSprite = new CZipSprite * [m_iZipSpriteCount];

	m_piZipSpritePlayerStart = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerEnd = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerLoadTime = new int [m_iZipSpriteCount];

	m_piZipSpritePlayerX = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerY = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerXZ = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerYZ = new int [m_iZipSpriteCount];

	m_piZipSpritePlayerXAdd = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerYAdd = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerXZAdd = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerYZAdd = new int [m_iZipSpriteCount];

	m_piZipSpritePlayerRotationAdd = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerRotationX = new int [m_iZipSpriteCount];
	m_piZipSpritePlayerRotationY = new int [m_iZipSpriteCount];

	m_pcZipSpritePlayerFilename = new char * [m_iZipSpriteCount];

	m_piZipSpritePlayerFade = new int [m_iZipSpriteCount];

	for (int i=0; i<m_iZipSpriteCount; i++)	// czyszczenie tablic
	{
		m_pActive[i] = false;

		m_pCZipSprite[i] = NULL;		

		m_piZipSpritePlayerStart[i] = 0;
		m_piZipSpritePlayerEnd[i] = 0;
		m_piZipSpritePlayerLoadTime[i] = 0;

		m_piZipSpritePlayerX[i] = 0;
		m_piZipSpritePlayerY[i] = 0;
		m_piZipSpritePlayerXZ[i] = 0;
		m_piZipSpritePlayerYZ[i] = 0;

		m_piZipSpritePlayerXAdd[i] = 0;
		m_piZipSpritePlayerYAdd[i] = 0;
		m_piZipSpritePlayerXZAdd[i] = 0;
		m_piZipSpritePlayerYZAdd[i] = 0;

		m_piZipSpritePlayerRotationAdd[i] = 0;
		m_piZipSpritePlayerRotationX[i] = 0;
		m_piZipSpritePlayerRotationY[i] = 0;

		m_pcZipSpritePlayerFilename[i] = new char [256];	// tutaj inicjalizacja na nazwe pliku

		m_piZipSpritePlayerFade[i] = 0;
	}

	// ponownie otwieramy plik ze skryptem

	if ((plik=fopen(cFilename,"r"))==NULL)
	{
		fx_debug("ERROR! Brak pliku skryptu dla CZipSpritePlayer!\n");
		return;
	}

	linia[0]=0;	// zamazanie stringa z poprzedniego szukania

	// teraz wczytujemy obiekty

	while (strcmp(linia,"</ZIPSPRITEPLAYER>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku

		if (!strcmp(linia,"<XIMAGE>")) 
		{

			fscanf(plik,"%s\n",m_pcZipSpritePlayerFilename[iSpritePlayerCount]);

			// wspolrzedne X i Y, skala XZ, skala YZ

			fscanf(plik,"%d %d %d %d\n",&m_piZipSpritePlayerX[iSpritePlayerCount], &m_piZipSpritePlayerY[iSpritePlayerCount],
				&m_piZipSpritePlayerXZ[iSpritePlayerCount], &m_piZipSpritePlayerYZ[iSpritePlayerCount]);

			// inkrementacja X i Y

			fscanf(plik,"%d %d %d %d\n",&m_piZipSpritePlayerXAdd[iSpritePlayerCount], &m_piZipSpritePlayerYAdd[iSpritePlayerCount],
				&m_piZipSpritePlayerXZAdd[iSpritePlayerCount], &m_piZipSpritePlayerYZAdd[iSpritePlayerCount]);

			// inkrementacja rotacji

			fscanf(plik,"%d %d %d\n",&m_piZipSpritePlayerRotationAdd[iSpritePlayerCount],
				&m_piZipSpritePlayerRotationX[iSpritePlayerCount],
				&m_piZipSpritePlayerRotationY[iSpritePlayerCount]);

			// poczatek i koniec wyswietlania

			fscanf(plik,"%d\n",&m_piZipSpritePlayerStart[iSpritePlayerCount]);	// timer - poczatek wyswietlania
			fscanf(plik,"%d\n",&m_piZipSpritePlayerEnd[iSpritePlayerCount]);		// timer - koniec wyswietlania
			fscanf(plik,"%d\n",&m_piZipSpritePlayerLoadTime[iSpritePlayerCount]);	// timer - kiedy wczytujemy dane

			// czy jest fade

			fscanf(plik,"%s\n",&linia);	//nazwa pliku
			if (!strcmp(linia,"NOFADE")) m_piZipSpritePlayerFade[iSpritePlayerCount]=0;		// nakladka
			if (!strcmp(linia,"INFADE")) m_piZipSpritePlayerFade[iSpritePlayerCount]=1;		// nakladka
			if (!strcmp(linia,"OUTFADE")) m_piZipSpritePlayerFade[iSpritePlayerCount]=2;		// nakladka

			if (m_piZipSpritePlayerLoadTime[iSpritePlayerCount]==0)
				m_pCZipSprite[iSpritePlayerCount] = new CZipSprite("demo.bin",m_pcZipSpritePlayerFilename[iSpritePlayerCount],"m1randa",255,255,255,255,pDevice);			

			iSpritePlayerCount++;
		}
	}
}

CZipSpritePlayer::~CZipSpritePlayer()
{
	for (int i=0; i<m_iZipSpriteCount; i++)
	{
		if (m_pActive[i])
		{
			delete m_pCZipSprite[i];	
			m_pActive[i] = false;
		}
	}
}

void CZipSpritePlayer::DeInitialize(void)
{
	for (int i=0; i<m_iZipSpriteCount; i++)
	{
		if (m_pActive[i])
		{
			delete m_pCZipSprite[i];	
			m_pActive[i] = false;
		}
	}
}

void CZipSpritePlayer::Initialize(IDirect3DDevice8 *pDevice)
{

}

int CZipSpritePlayer::DrawScene(IDirect3DDevice8 *pDevice, long lTimer)
{

	for (int i=0; i<m_iZipSpriteCount; i++)
	{
		if (lTimer>m_piZipSpritePlayerEnd[i] && m_pCZipSprite[i]!=NULL) // jezeli minal czas to zwalniamy pamiec
		{
			delete m_pCZipSprite[i];
			m_pCZipSprite[i] = NULL;
		}

		if (lTimer>m_piZipSpritePlayerLoadTime[i] && lTimer<m_piZipSpritePlayerEnd[i] && m_pCZipSprite[i]==NULL)	// czy pora na wczytanie obrazka ?
		{
				m_pCZipSprite[i] = new CZipSprite("demo.bin",m_pcZipSpritePlayerFilename[i],"m1randa",255,255,255,255,pDevice);			
		}

		if (lTimer>=m_piZipSpritePlayerStart[i] && lTimer<m_piZipSpritePlayerEnd[i])
		{
			if (m_pCZipSprite[i]==NULL) // doczytanie obrazka jezeli jeszcze nie ma w pamieci
			{
				m_pCZipSprite[i] = new CZipSprite("demo.bin",m_pcZipSpritePlayerFilename[i],"m1randa",255,255,255,255,pDevice);			
			}
			
			// zmiana polozenia

			m_pCZipSprite[i]->SetTranslation((float)m_piZipSpritePlayerX[i]+(((float)(m_piZipSpritePlayerXAdd[i]*(lTimer-m_piZipSpritePlayerStart[i])))/100),
				(float)m_piZipSpritePlayerY[i]+(((float)(m_piZipSpritePlayerYAdd[i]*(lTimer-m_piZipSpritePlayerStart[i])))/100));

			// zmiana skali

			m_pCZipSprite[i]->SetScale((float)(m_piZipSpritePlayerXZ[i]/100)+(((float)(m_piZipSpritePlayerXZAdd[i]*(lTimer-m_piZipSpritePlayerStart[i])))/10000),
				(float)(m_piZipSpritePlayerYZ[i]/100)+(((float)(m_piZipSpritePlayerYZAdd[i]*(lTimer-m_piZipSpritePlayerStart[i])))/10000));

			// zmiana kata

			m_pCZipSprite[i]->SetRotationCenter(m_piZipSpritePlayerRotationX[i],m_piZipSpritePlayerRotationY[i]);
			m_pCZipSprite[i]->SetRotation(((float)(m_piZipSpritePlayerRotationAdd[i]*(lTimer-m_piZipSpritePlayerStart[i])*0.01))/360);

			if (m_piZipSpritePlayerFade[i]==0) m_pCZipSprite[i]->SetModulate(255,255,255,255);

			// fade in

			if (m_piZipSpritePlayerFade[i]==1) 
			{
				if ((lTimer-m_piZipSpritePlayerStart[i])<255)
				{
					m_pCZipSprite[i]->SetModulate((unsigned char)lTimer-m_piZipSpritePlayerStart[i],255,255,255);
				}
				else
				{
					m_pCZipSprite[i]->SetModulate(255,255,255,255);			
				}
			}

			// out fade

			if (m_piZipSpritePlayerFade[i]==2) 
			{
				if ((255-(lTimer-m_piZipSpritePlayerStart[i]))>0)
				{
					m_pCZipSprite[i]->SetModulate(255-(lTimer-m_piZipSpritePlayerStart[i]),
						255-(lTimer-m_piZipSpritePlayerStart[i]),255-(lTimer-m_piZipSpritePlayerStart[i]),
						255-(lTimer-m_piZipSpritePlayerStart[i]));
				}
				else
				{
					m_pCZipSprite[i]->SetModulate(0,0,0,0);
				}
			}

			m_pCZipSprite[i]->Render();
		}
	}

	return 0; 
}