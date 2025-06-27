#include "HighScore.h"

#pragma warning(disable : 4996)

CHighScore::CHighScore()
{
    for (int i=0; i<10; i++)
    {
        memset(m_cNameTable[i],90,0);
        m_ulScoreTable[i]=0;
    }
    
	bLoad();
}

CHighScore::~CHighScore()
{
	bSave();
}

unsigned long CHighScore::ulGetScore(unsigned char ucIndex)		// zwraca liczbe puntkow dla danego indeksu
{
	return m_ulScoreTable[ucIndex];
}

char *CHighScore::cGetName(unsigned char ucIndex)
{
	return m_cNameTable[ucIndex];
}

void CHighScore::AddScore(char cName[], unsigned long ulScore)			// dodaje punkty do tablicy jezeli potrzebne
{
	bool bInsert;
	
	bInsert = false;	// jeszcze nie wstawiono

	for (char i=0; i<10; i++)
	{
		if (ulScore >= m_ulScoreTable[i] && !bInsert)
		{
			for (char j=10; j>i; j--)	// scroll punktow na dol
			{
				m_ulScoreTable[j] = m_ulScoreTable[j-1];
				strcpy(m_cNameTable[j],m_cNameTable[j-1]);				
			}
			
			m_ulScoreTable[i] = ulScore;	// wpisz nowe punkty
			strcpy(m_cNameTable[i],cName);

			bInsert = true;
		}
	}

}	

bool CHighScore::bLoad(void)			// wczytanie danych
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    m_ulScoreTable [0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore0"];
    m_ulScoreTable [1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore1"];
    m_ulScoreTable [2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore2"];
    m_ulScoreTable [3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore3"];
    m_ulScoreTable [4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore4"];
    m_ulScoreTable [5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore5"];
    m_ulScoreTable [6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore6"];
    m_ulScoreTable [7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore7"];
    m_ulScoreTable [8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore8"];
    m_ulScoreTable [9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulHighScore9"];

    
    NSString *sName0 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName0"];
    NSString *sName1 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName1"];
    NSString *sName2 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName2"];
    NSString *sName3 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName3"];
    NSString *sName4 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName4"];
    NSString *sName5 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName5"];
    NSString *sName6 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName6"];
    NSString *sName7 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName7"];
    NSString *sName8 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName8"];
    NSString *sName9 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_HighName9"];
    
    [defaults synchronize];
    
    if (sName0!=nil)
        strcpy(m_cNameTable[0],[sName0 UTF8String]);
    
    if (sName1!=nil)
        strcpy(m_cNameTable[1],[sName1 UTF8String]);

    if (sName2!=nil)
        strcpy(m_cNameTable[2],[sName2 UTF8String]);

    if (sName3!=nil)
        strcpy(m_cNameTable[3],[sName3 UTF8String]);

    if (sName4!=nil)
        strcpy(m_cNameTable[4],[sName4 UTF8String]);

    if (sName5!=nil)
        strcpy(m_cNameTable[5],[sName5 UTF8String]);

    if (sName6!=nil)
        strcpy(m_cNameTable[6],[sName6 UTF8String]);
    
    if (sName7!=nil)
        strcpy(m_cNameTable[7],[sName7 UTF8String]);

    if (sName8!=nil)
        strcpy(m_cNameTable[8],[sName8 UTF8String]);

    if (sName9!=nil)
        strcpy(m_cNameTable[9],[sName9 UTF8String]);
    
	return true;
}

bool CHighScore::bSave(void)			// zapisanie danych
{
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];    
    
    NSString *sName0 = [[NSString alloc] initWithCString:(char*)m_cNameTable[0]  encoding:NSUTF8StringEncoding];
    NSString *sName1 = [[NSString alloc] initWithCString:(char*)m_cNameTable[1]  encoding:NSUTF8StringEncoding];
    NSString *sName2 = [[NSString alloc] initWithCString:(char*)m_cNameTable[2]  encoding:NSUTF8StringEncoding];
    NSString *sName3 = [[NSString alloc] initWithCString:(char*)m_cNameTable[3]  encoding:NSUTF8StringEncoding];
    NSString *sName4 = [[NSString alloc] initWithCString:(char*)m_cNameTable[4]  encoding:NSUTF8StringEncoding];
    NSString *sName5 = [[NSString alloc] initWithCString:(char*)m_cNameTable[5]  encoding:NSUTF8StringEncoding];
    NSString *sName6 = [[NSString alloc] initWithCString:(char*)m_cNameTable[6]  encoding:NSUTF8StringEncoding];
    NSString *sName7 = [[NSString alloc] initWithCString:(char*)m_cNameTable[7]  encoding:NSUTF8StringEncoding];
    NSString *sName8 = [[NSString alloc] initWithCString:(char*)m_cNameTable[8]  encoding:NSUTF8StringEncoding];
    NSString *sName9 = [[NSString alloc] initWithCString:(char*)m_cNameTable[9]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName0 forKey:@"SHODAN9_GemsOfAtlantis_HighName0"];
    [defaults setObject:sName1 forKey:@"SHODAN9_GemsOfAtlantis_HighName1"];
    [defaults setObject:sName2 forKey:@"SHODAN9_GemsOfAtlantis_HighName2"];
    [defaults setObject:sName3 forKey:@"SHODAN9_GemsOfAtlantis_HighName3"];
    [defaults setObject:sName4 forKey:@"SHODAN9_GemsOfAtlantis_HighName4"];
    [defaults setObject:sName5 forKey:@"SHODAN9_GemsOfAtlantis_HighName5"];
    [defaults setObject:sName6 forKey:@"SHODAN9_GemsOfAtlantis_HighName6"];
    [defaults setObject:sName7 forKey:@"SHODAN9_GemsOfAtlantis_HighName7"];
    [defaults setObject:sName8 forKey:@"SHODAN9_GemsOfAtlantis_HighName8"];
    [defaults setObject:sName9 forKey:@"SHODAN9_GemsOfAtlantis_HighName9"];
    
    [defaults setInteger:m_ulScoreTable[0] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore0"];
    [defaults setInteger:m_ulScoreTable[1] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore1"];
    [defaults setInteger:m_ulScoreTable[2] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore2"];
    [defaults setInteger:m_ulScoreTable[3] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore3"];
    [defaults setInteger:m_ulScoreTable[4] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore4"];
    [defaults setInteger:m_ulScoreTable[5] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore5"];
    [defaults setInteger:m_ulScoreTable[6] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore6"];
    [defaults setInteger:m_ulScoreTable[7] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore7"];
    [defaults setInteger:m_ulScoreTable[8] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore8"];
    [defaults setInteger:m_ulScoreTable[9] forKey:@"SHODAN9_GemsOfAtlantis_ulHighScore9"];

    [defaults synchronize];
    
    [sName0 release];
    [sName1 release];
    [sName2 release];
    [sName3 release];
    [sName4 release];
    [sName5 release];
    [sName6 release];
    [sName7 release];
    [sName8 release];
    [sName9 release];
    
	return true;
}

void CHighScore::Setup(void)
{
    for (int i=0; i<10; i++)
    {
        memset(m_cNameTable[i],90,0);
        m_ulScoreTable[i]=0;
    }

    sprintf(m_cNameTable[0],"ADAM");
    m_ulScoreTable[0] = 100000;
    
    sprintf(m_cNameTable[1],"EVA");
    m_ulScoreTable[1] = 90000;
    
    sprintf(m_cNameTable[2],"MAX");
    m_ulScoreTable[2] = 80000;

    sprintf(m_cNameTable[3],"SOFIA");
    m_ulScoreTable[3] = 80000;
    
    sprintf(m_cNameTable[4],"DEXTER");
    m_ulScoreTable[4] = 70000;

    sprintf(m_cNameTable[5],"ANNA");
    m_ulScoreTable[5] = 80000;
    
    sprintf(m_cNameTable[6],"DONALD");
    m_ulScoreTable[6] = 60000;

    sprintf(m_cNameTable[7],"LISA");
    m_ulScoreTable[7] = 50000;
    
    sprintf(m_cNameTable[8],"DAMIAN");
    m_ulScoreTable[8] = 40000;

    sprintf(m_cNameTable[9],"CECYLIA");
    m_ulScoreTable[9] = 30000;
    
    sprintf(m_cNameTable[10],"BORYS");
    m_ulScoreTable[10] = 20000;
    
    bSave();
    
}
