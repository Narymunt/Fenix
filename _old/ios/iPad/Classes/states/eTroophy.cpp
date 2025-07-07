#include "eTroophy.h"

// konstruktor, tutaj pakujemy najmniej jak tylko możliwe

eTroophy::eTroophy(CScreen *pScreen) :
_pBackground(NULL), m_ulTimerStart(0),_pScreen(pScreen)
{
    _isActive = false;
    _iOS = pScreen->iOS();
    
    for (int i=0; i<21;i++)
	{
		m_pTroophyLocked[i] = NULL;
		m_pTroophyUnlocked[i] = NULL;
	}
}

eTroophy::~eTroophy()
{
    Close();
}

void eTroophy::Open(void)
{
    _pBackground = new CSprite((char*)"e_troophy",_iOS);

 	char cName[100];
	CProfile *pProfile;
    
	memset(cName,0,100);	// wyzeruj tablice na wszelki wypadek
    
    if (_iOS!=IPAD_HD)
    {
        m_pTroophyLocked[0] = new CSprite((char*)"a00_l.png");
        m_pTroophyUnlocked[0] = new CSprite((char*)"a00_u.png");
        
        for (int i=1; i<21; i++)
        {
            sprintf(cName,"a%.2d_off_static_128.png",i);
            m_pTroophyLocked[i] = new CSprite(cName);
        
            sprintf(cName,"a%.2d_on_static_128.png",i);
            m_pTroophyUnlocked[i] = new CSprite(cName);
        }
    }
    else
    {
        m_pTroophyLocked[0] = new CSprite((char*)"a00_l2.png");
        m_pTroophyUnlocked[0] = new CSprite((char*)"a00_u2.png");
        
        for (int i=1; i<21; i++)
        {
            sprintf(cName,"a%.2d_off_static_256.png",i);
            m_pTroophyLocked[i] = new CSprite(cName);
            
            sprintf(cName,"a%.2d_on_static_256.png",i);
            m_pTroophyUnlocked[i] = new CSprite(cName);
        }

    }
    
	pProfile = new CProfile();
	pProfile->bLoad();
	
	for (int i=0; i<21; i++)
		m_bTroophyLocked[i] = (bool)pProfile->ucTroophy(i);
    
	delete pProfile;
    
    _isActive = true;
    _isMouseLock = true;
}

void eTroophy::Close(void)
{
    SafeDelete(_pBackground);

	for (int i=0; i<21; i++)
	{
		SafeDelete(m_pTroophyLocked[i]);
		SafeDelete(m_pTroophyUnlocked[i]);
	}
    
    _isActive = false;
    _isMouseLock = true;
}

int eTroophy::Render(CTouch *pTouch, unsigned long ulTimer)
{
	float fStepX, fStepY;
	float fSizeX, fSizeY;
    
    if (!pTouch->isPressed())
        _isMouseLock = false;
    
    _pBackground->Render();

	if (_pScreen->iSizeX()<1500)
	{
		fStepX = (_pScreen->iSizeX()-640)/6;
		fStepY = (_pScreen->iSizeY()-512)/5;
		fSizeX = 128;
		fSizeY = 128;
	}
	else
	{
		fStepX = (_pScreen->iSizeX()-1280)/6;
		fStepY = (_pScreen->iSizeY()-1024)/5;
		fSizeX = 256;
		fSizeY = 256;
	}
    
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<5; j++)
		{
			if (!m_bTroophyLocked[(i*5)+j])
			{
				m_pTroophyLocked[(i*5)+j+1]->Position(fStepX+(j*fStepX)+(j*fSizeX),(i*fStepY)+(i*fSizeY));
				m_pTroophyLocked[(i*5)+j+1]->Render();
			}
			else
			{
				m_pTroophyUnlocked[(i*5)+j+1]->Position(fStepX+(j*fStepX)+(j*fSizeX),(i*fStepY)+(i*fSizeY));
				m_pTroophyUnlocked[(i*5)+j+1]->Render();
			}	
		}
	}
    
	if (pTouch->isPressed() && !_isMouseLock)
		return 1;

    return 0;   // nie rob nic
}

