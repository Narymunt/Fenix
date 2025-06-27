//////////////////////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <ctype.h>
#include "zipsprite.h"
#include "event.h"
#include "eventevt.h"

class CZipSpritePlayer
{
public:
	
	CZipSpritePlayer();
	CZipSpritePlayer(char cFilename[],IDirect3DDevice8	*pDevice);
	virtual ~CZipSpritePlayer();

	virtual void Initialize(IDirect3DDevice8 *pDevice);
	virtual void DeInitialize(void);

	virtual int	 DrawScene(IDirect3DDevice8 *pDevice, long lTimer);

private:

	int			m_iZipSpriteCount;

	bool		*m_pActive;			// ktore animacje sa wczytane, to jest znacznik czy mamy dla tego licznika
										// sprawdzac pozostale parametry
	
	CZipSprite	**m_pCZipSprite;		// tutaj nasze obiekty

	int			*m_piZipSpritePlayerStart;	// od kiedy ma sie pojawic obrazek
	int			*m_piZipSpritePlayerEnd;		// do kiedy ma sie pojawiæ obrazek
	int			*m_piZipSpritePlayerLoadTime;	// kiedy ma zostaæ wczytany obrazek

	int			*m_piZipSpritePlayerX;	// poczatkowa wspolrzedna X
	int			*m_piZipSpritePlayerY;	// poczatkowa wspolrzedna Y
	int			*m_piZipSpritePlayerXZ;	// poczatkowa skala X
	int			*m_piZipSpritePlayerYZ;	// poczatkowa skala Y

	int			*m_piZipSpritePlayerXAdd;		// o ile ma sie zwiekszac X na tik zegara
	int			*m_piZipSpritePlayerYAdd;		// o ile ma sie zwiekszac Y na tik zegara
	int			*m_piZipSpritePlayerXZAdd;	// o ile ma sie zwiekszac skala X na tik zegara
	int			*m_piZipSpritePlayerYZAdd;	// o ile ma sie zwiekszac skala Y na tik zegara

	int			*m_piZipSpritePlayerRotationAdd; // o ile ma sie zwiekszac kat
	int			*m_piZipSpritePlayerRotationX;	// wspolrzedne na teksturze do obrotu
	int			*m_piZipSpritePlayerRotationY;	// wspolrzedne na teksturze do obrotu

	int			*m_piZipSpritePlayerCount;	// ile jest obrazkow
	char		**m_pcZipSpritePlayerFilename;
	int			*m_piZipSpritePlayerFade;				


};

#endif 
