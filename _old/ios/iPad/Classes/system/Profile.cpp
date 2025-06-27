// profile graczy

#include "Profile.h"

CProfile::CProfile() :
_ucFirstRun(0)
{

	for (int i=0; i<8; i++)
	{
		m_ulTotalScore[i] = 0;
		m_ulScore[i] = 0;
		m_ulMap[i] = 0;
		m_ulLevel[i] = 0;

		sprintf(m_cName[i],"_____");
	}

	m_ucCurrentProfile = 0;
}

CProfile::~CProfile()
{

}

void CProfile::SetName(char cNewName[])
{
	strcpy(m_cName[m_ucCurrentProfile],cNewName);	// zapamietaj nazwe gracza
}

char *CProfile::pGetName(void)
{
	return m_cName[m_ucCurrentProfile];
}

void CProfile::SetTotalScore(unsigned long ulScore)
{
	m_ulTotalScore[m_ucCurrentProfile] = ulScore;
}

void CProfile::AddTotalScore(unsigned long ulScore)
{
	m_ulTotalScore[m_ucCurrentProfile] += ulScore;
}

unsigned long CProfile::ulGetTotalScore(void)
{
	return m_ulTotalScore[m_ucCurrentProfile];
}

void CProfile::SetScore(unsigned long ulScore)
{
	m_ulScore[m_ucCurrentProfile] = ulScore;
}

void CProfile::AddScore(unsigned long ulScore)
{
	m_ulScore[m_ucCurrentProfile] += ulScore;
}

unsigned long CProfile::ulGetScore(void)
{
	return m_ulScore[m_ucCurrentProfile];
}

void CProfile::SetLevel(unsigned long ulLevel)
{
	m_ulLevel[m_ucCurrentProfile] = ulLevel;
}

void CProfile::AddLevel(unsigned long ulLevel)
{
	m_ulLevel[m_ucCurrentProfile] += ulLevel;
}

unsigned long CProfile::ulGetLevel(void)
{
	if (m_ulTotalScore[m_ucCurrentProfile] < 10000)
		m_ulLevel[m_ucCurrentProfile] = 1; 

	if (m_ulTotalScore[m_ucCurrentProfile] >=10000 && m_ulTotalScore[m_ucCurrentProfile] < 30000)
		m_ulLevel[m_ucCurrentProfile] = 2;

	if (m_ulTotalScore[m_ucCurrentProfile] >=30000 && m_ulTotalScore[m_ucCurrentProfile] < 60000)
		m_ulLevel[m_ucCurrentProfile] = 3;

	if (m_ulTotalScore[m_ucCurrentProfile] >=60000 && m_ulTotalScore[m_ucCurrentProfile] < 100000)
		m_ulLevel[m_ucCurrentProfile] = 4;

	if (m_ulTotalScore[m_ucCurrentProfile] >=100000 && m_ulTotalScore[m_ucCurrentProfile] < 150000)
		m_ulLevel[m_ucCurrentProfile] = 5;

	if (m_ulTotalScore[m_ucCurrentProfile] >=150000 && m_ulTotalScore[m_ucCurrentProfile] < 210000)
		m_ulLevel[m_ucCurrentProfile] = 6;

	if (m_ulTotalScore[m_ucCurrentProfile] >=210000 && m_ulTotalScore[m_ucCurrentProfile] < 280000)
		m_ulLevel[m_ucCurrentProfile] = 7;

	if (m_ulTotalScore[m_ucCurrentProfile] >=280000 && m_ulTotalScore[m_ucCurrentProfile] < 360000)
		m_ulLevel[m_ucCurrentProfile] = 8;

	if (m_ulTotalScore[m_ucCurrentProfile] >=360000 && m_ulTotalScore[m_ucCurrentProfile] < 450000)
		m_ulLevel[m_ucCurrentProfile] = 9;

	if (m_ulTotalScore[m_ucCurrentProfile] >=450000 && m_ulTotalScore[m_ucCurrentProfile] < 550000)
		m_ulLevel[m_ucCurrentProfile] = 10;

	if (m_ulTotalScore[m_ucCurrentProfile] >=550000 && m_ulTotalScore[m_ucCurrentProfile] < 660000)
		m_ulLevel[m_ucCurrentProfile] = 11;

	if (m_ulTotalScore[m_ucCurrentProfile] >=660000 && m_ulTotalScore[m_ucCurrentProfile] < 780000)
		m_ulLevel[m_ucCurrentProfile] = 12;

	if (m_ulTotalScore[m_ucCurrentProfile] >=780000 && m_ulTotalScore[m_ucCurrentProfile] < 910000)
		m_ulLevel[m_ucCurrentProfile] = 13;

	if (m_ulTotalScore[m_ucCurrentProfile] >=910000 && m_ulTotalScore[m_ucCurrentProfile] < 1050000)
		m_ulLevel[m_ucCurrentProfile] = 14;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1050000 && m_ulTotalScore[m_ucCurrentProfile] < 1200000)
		m_ulLevel[m_ucCurrentProfile] = 15;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1200000 && m_ulTotalScore[m_ucCurrentProfile] < 1360000)
		m_ulLevel[m_ucCurrentProfile] = 16;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1360000 && m_ulTotalScore[m_ucCurrentProfile] < 1530000)
		m_ulLevel[m_ucCurrentProfile] = 17;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1530000 && m_ulTotalScore[m_ucCurrentProfile] < 1720000)
		m_ulLevel[m_ucCurrentProfile] = 18;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1720000 && m_ulTotalScore[m_ucCurrentProfile] < 1910000)
		m_ulLevel[m_ucCurrentProfile] = 19;

	if (m_ulTotalScore[m_ucCurrentProfile] >=1910000 )
		m_ulLevel[m_ucCurrentProfile] = 20;

	return m_ulLevel[m_ucCurrentProfile];
}


float CProfile::fGetProgress(void)
{

	float fProgress;

	if (m_ulTotalScore[m_ucCurrentProfile] < 10000)
	{
		m_ulLevel[m_ucCurrentProfile] = 1; 
		fProgress = (float)(m_ulTotalScore[m_ucCurrentProfile] / 10000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=10000 && m_ulTotalScore[m_ucCurrentProfile] < 30000)
	{
		m_ulLevel[m_ucCurrentProfile] = 2;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-10000) / 20000.0f ) * 100.0f;
	}
	
	if (m_ulTotalScore[m_ucCurrentProfile] >=30000 && m_ulTotalScore[m_ucCurrentProfile] < 60000)
	{
		m_ulLevel[m_ucCurrentProfile] = 3;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-30000) / 30000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=60000 && m_ulTotalScore[m_ucCurrentProfile] < 100000)
	{
		m_ulLevel[m_ucCurrentProfile] = 4;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-60000) / 40000.0f) * 100.0f;		
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=100000 && m_ulTotalScore[m_ucCurrentProfile] < 150000)
	{
		m_ulLevel[m_ucCurrentProfile] = 5;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-100000) / 50000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=150000 && m_ulTotalScore[m_ucCurrentProfile] < 210000)
	{
		m_ulLevel[m_ucCurrentProfile] = 6;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-150000) / 60000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=210000 && m_ulTotalScore[m_ucCurrentProfile] < 280000)
	{
		m_ulLevel[m_ucCurrentProfile] = 7;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-210000) / 70000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=280000 && m_ulTotalScore[m_ucCurrentProfile] < 360000)
	{
		m_ulLevel[m_ucCurrentProfile] = 8;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-280000) / 80000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=360000 && m_ulTotalScore[m_ucCurrentProfile] < 450000)
	{
		m_ulLevel[m_ucCurrentProfile] = 9;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-360000) / 90000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=450000 && m_ulTotalScore[m_ucCurrentProfile] < 550000)
	{
		m_ulLevel[m_ucCurrentProfile] = 10;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-450000) / 100000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=550000 && m_ulTotalScore[m_ucCurrentProfile] < 660000)
	{
		m_ulLevel[m_ucCurrentProfile] = 11;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-550000) / 110000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=660000 && m_ulTotalScore[m_ucCurrentProfile] < 780000)
	{
		m_ulLevel[m_ucCurrentProfile] = 12;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-660000) / 120000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=780000 && m_ulTotalScore[m_ucCurrentProfile] < 910000)
	{
		m_ulLevel[m_ucCurrentProfile] = 13;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-780000) / 130000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=910000 && m_ulTotalScore[m_ucCurrentProfile] < 1050000)
	{
		m_ulLevel[m_ucCurrentProfile] = 14;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-910000) / 140000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1050000 && m_ulTotalScore[m_ucCurrentProfile] < 1200000)
	{
		m_ulLevel[m_ucCurrentProfile] = 15;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1050000) / 150000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1200000 && m_ulTotalScore[m_ucCurrentProfile] < 1360000)
	{
		m_ulLevel[m_ucCurrentProfile] = 16;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1200000) / 160000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1360000 && m_ulTotalScore[m_ucCurrentProfile] < 1530000)
	{
		m_ulLevel[m_ucCurrentProfile] = 17;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1360000) / 170000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1530000 && m_ulTotalScore[m_ucCurrentProfile] < 1720000)
	{
		m_ulLevel[m_ucCurrentProfile] = 18;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1530000) / 180000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1720000 && m_ulTotalScore[m_ucCurrentProfile] < 1910000)
	{
		m_ulLevel[m_ucCurrentProfile] = 19;
		fProgress = (float)( (m_ulTotalScore[m_ucCurrentProfile]-1720000) / 190000.0f) * 100.0f;
	}

	if (m_ulTotalScore[m_ucCurrentProfile] >=1910000 )
	{
		m_ulLevel[m_ucCurrentProfile] = 20;
		fProgress = 100.0f;
	}

	return fProgress;
}

// zapis profilu

bool CProfile::bSave(void)
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
//    [defaults setInteger:score forKey:@"GOA_ulScore"];
//     newScore = [defaults integerForKey:@"GOA_ulScore"];

    [defaults setInteger:m_ucCurrentProfile forKey:@"SHODAN9_GemsOfAtlantis_ucCurrentProfile"];
    
    // profil #1
    
    NSString *sName0 = [[NSString alloc] initWithCString:(char*)m_cName[0]  encoding:NSUTF8StringEncoding];

    [defaults setObject:sName0 forKey:@"SHODAN9_GemsOfAtlantis_cName0"];
    [defaults setInteger:m_ulTotalScore[0] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore0"];
    [defaults setInteger:m_ulScore[0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0"];
    [defaults setInteger:m_ulMap[0] forKey:@"SHODAN9_GemsOfAtlantis_ulMap0"];
    [defaults setInteger:m_ulLevel[0] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel0"];
    
    [defaults setInteger:m_ucTroophy[0][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_0"];
    [defaults setInteger:m_ucTroophy[0][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_1"];
    [defaults setInteger:m_ucTroophy[0][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_2"];
    [defaults setInteger:m_ucTroophy[0][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_3"];
    [defaults setInteger:m_ucTroophy[0][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_4"];
    [defaults setInteger:m_ucTroophy[0][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_5"];
    [defaults setInteger:m_ucTroophy[0][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_6"];
    [defaults setInteger:m_ucTroophy[0][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_7"];
    [defaults setInteger:m_ucTroophy[0][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_8"];
    [defaults setInteger:m_ucTroophy[0][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_9"];
    [defaults setInteger:m_ucTroophy[0][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_10"];
    [defaults setInteger:m_ucTroophy[0][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_11"];
    [defaults setInteger:m_ucTroophy[0][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_12"];
    [defaults setInteger:m_ucTroophy[0][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_13"];
    [defaults setInteger:m_ucTroophy[0][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_14"];
    [defaults setInteger:m_ucTroophy[0][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_15"];
    [defaults setInteger:m_ucTroophy[0][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_16"];
    [defaults setInteger:m_ucTroophy[0][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_17"];
    [defaults setInteger:m_ucTroophy[0][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_18"];
    [defaults setInteger:m_ucTroophy[0][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore0_19"];
   
    // profil #2
    
    NSString *sName1 = [[NSString alloc] initWithCString:(char*)m_cName[1]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName1 forKey:@"SHODAN9_GemsOfAtlantis_cName1"];
    [defaults setInteger:m_ulTotalScore[1] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore1"];
    [defaults setInteger:m_ulScore[1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1"];
    [defaults setInteger:m_ulMap[1] forKey:@"SHODAN9_GemsOfAtlantis_ulMap1"];
    [defaults setInteger:m_ulLevel[1] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel1"];
    
    [defaults setInteger:m_ucTroophy[1][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_0"];
    [defaults setInteger:m_ucTroophy[1][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_1"];
    [defaults setInteger:m_ucTroophy[1][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_2"];
    [defaults setInteger:m_ucTroophy[1][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_3"];
    [defaults setInteger:m_ucTroophy[1][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_4"];
    [defaults setInteger:m_ucTroophy[1][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_5"];
    [defaults setInteger:m_ucTroophy[1][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_6"];
    [defaults setInteger:m_ucTroophy[1][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_7"];
    [defaults setInteger:m_ucTroophy[1][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_8"];
    [defaults setInteger:m_ucTroophy[1][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_9"];
    [defaults setInteger:m_ucTroophy[1][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_10"];
    [defaults setInteger:m_ucTroophy[1][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_11"];
    [defaults setInteger:m_ucTroophy[1][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_12"];
    [defaults setInteger:m_ucTroophy[1][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_13"];
    [defaults setInteger:m_ucTroophy[1][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_14"];
    [defaults setInteger:m_ucTroophy[1][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_15"];
    [defaults setInteger:m_ucTroophy[1][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_16"];
    [defaults setInteger:m_ucTroophy[1][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_17"];
    [defaults setInteger:m_ucTroophy[1][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_18"];
    [defaults setInteger:m_ucTroophy[1][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore1_19"];

    // profil #3
    
    NSString *sName2 = [[NSString alloc] initWithCString:(char*)m_cName[2]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName2 forKey:@"SHODAN9_GemsOfAtlantis_cName2"];
    [defaults setInteger:m_ulTotalScore[2] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore2"];
    [defaults setInteger:m_ulScore[2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2"];
    [defaults setInteger:m_ulMap[2] forKey:@"SHODAN9_GemsOfAtlantis_ulMap2"];
    [defaults setInteger:m_ulLevel[2] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel2"];
    
    [defaults setInteger:m_ucTroophy[2][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_0"];
    [defaults setInteger:m_ucTroophy[2][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_1"];
    [defaults setInteger:m_ucTroophy[2][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_2"];
    [defaults setInteger:m_ucTroophy[2][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_3"];
    [defaults setInteger:m_ucTroophy[2][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_4"];
    [defaults setInteger:m_ucTroophy[2][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_5"];
    [defaults setInteger:m_ucTroophy[2][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_6"];
    [defaults setInteger:m_ucTroophy[2][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_7"];
    [defaults setInteger:m_ucTroophy[2][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_8"];
    [defaults setInteger:m_ucTroophy[2][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_9"];
    [defaults setInteger:m_ucTroophy[2][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_10"];
    [defaults setInteger:m_ucTroophy[2][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_11"];
    [defaults setInteger:m_ucTroophy[2][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_12"];
    [defaults setInteger:m_ucTroophy[2][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_13"];
    [defaults setInteger:m_ucTroophy[2][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_14"];
    [defaults setInteger:m_ucTroophy[2][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_15"];
    [defaults setInteger:m_ucTroophy[2][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_16"];
    [defaults setInteger:m_ucTroophy[2][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_17"];
    [defaults setInteger:m_ucTroophy[2][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_18"];
    [defaults setInteger:m_ucTroophy[2][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore2_19"];
    
    // profil #4
    
    NSString *sName3 = [[NSString alloc] initWithCString:(char*)m_cName[3]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName3 forKey:@"SHODAN9_GemsOfAtlantis_cName3"];
    [defaults setInteger:m_ulTotalScore[3] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore3"];
    [defaults setInteger:m_ulScore[3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3"];
    [defaults setInteger:m_ulMap[3] forKey:@"SHODAN9_GemsOfAtlantis_ulMap3"];
    [defaults setInteger:m_ulLevel[3] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel3"];
    
    [defaults setInteger:m_ucTroophy[3][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_0"];
    [defaults setInteger:m_ucTroophy[3][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_1"];
    [defaults setInteger:m_ucTroophy[3][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_2"];
    [defaults setInteger:m_ucTroophy[3][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_3"];
    [defaults setInteger:m_ucTroophy[3][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_4"];
    [defaults setInteger:m_ucTroophy[3][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_5"];
    [defaults setInteger:m_ucTroophy[3][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_6"];
    [defaults setInteger:m_ucTroophy[3][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_7"];
    [defaults setInteger:m_ucTroophy[3][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_8"];
    [defaults setInteger:m_ucTroophy[3][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_9"];
    [defaults setInteger:m_ucTroophy[3][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_10"];
    [defaults setInteger:m_ucTroophy[3][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_11"];
    [defaults setInteger:m_ucTroophy[3][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_12"];
    [defaults setInteger:m_ucTroophy[3][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_13"];
    [defaults setInteger:m_ucTroophy[3][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_14"];
    [defaults setInteger:m_ucTroophy[3][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_15"];
    [defaults setInteger:m_ucTroophy[3][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_16"];
    [defaults setInteger:m_ucTroophy[3][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_17"];
    [defaults setInteger:m_ucTroophy[3][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_18"];
    [defaults setInteger:m_ucTroophy[3][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore3_19"];
    
    // profil #5
    
    NSString *sName4 = [[NSString alloc] initWithCString:(char*)m_cName[4]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName4 forKey:@"SHODAN9_GemsOfAtlantis_cName4"];
    [defaults setInteger:m_ulTotalScore[4] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore4"];
    [defaults setInteger:m_ulScore[4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4"];
    [defaults setInteger:m_ulMap[4] forKey:@"SHODAN9_GemsOfAtlantis_ulMap4"];
    [defaults setInteger:m_ulLevel[4] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel4"];
    
    [defaults setInteger:m_ucTroophy[4][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_0"];
    [defaults setInteger:m_ucTroophy[4][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_1"];
    [defaults setInteger:m_ucTroophy[4][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_2"];
    [defaults setInteger:m_ucTroophy[4][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_3"];
    [defaults setInteger:m_ucTroophy[4][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_4"];
    [defaults setInteger:m_ucTroophy[4][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_5"];
    [defaults setInteger:m_ucTroophy[4][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_6"];
    [defaults setInteger:m_ucTroophy[4][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_7"];
    [defaults setInteger:m_ucTroophy[4][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_8"];
    [defaults setInteger:m_ucTroophy[4][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_9"];
    [defaults setInteger:m_ucTroophy[4][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_10"];
    [defaults setInteger:m_ucTroophy[4][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_11"];
    [defaults setInteger:m_ucTroophy[4][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_12"];
    [defaults setInteger:m_ucTroophy[4][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_13"];
    [defaults setInteger:m_ucTroophy[4][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_14"];
    [defaults setInteger:m_ucTroophy[4][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_15"];
    [defaults setInteger:m_ucTroophy[4][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_16"];
    [defaults setInteger:m_ucTroophy[4][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_17"];
    [defaults setInteger:m_ucTroophy[4][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_18"];
    [defaults setInteger:m_ucTroophy[4][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore4_19"];

    // profil #6
    
    NSString *sName5 = [[NSString alloc] initWithCString:(char*)m_cName[5]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName5 forKey:@"SHODAN9_GemsOfAtlantis_cName5"];
    [defaults setInteger:m_ulTotalScore[5] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore5"];
    [defaults setInteger:m_ulScore[5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5"];
    [defaults setInteger:m_ulMap[5] forKey:@"SHODAN9_GemsOfAtlantis_ulMap5"];
    [defaults setInteger:m_ulLevel[5] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel5"];
    
    [defaults setInteger:m_ucTroophy[5][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_0"];
    [defaults setInteger:m_ucTroophy[5][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_1"];
    [defaults setInteger:m_ucTroophy[5][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_2"];
    [defaults setInteger:m_ucTroophy[5][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_3"];
    [defaults setInteger:m_ucTroophy[5][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_4"];
    [defaults setInteger:m_ucTroophy[5][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_5"];
    [defaults setInteger:m_ucTroophy[5][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_6"];
    [defaults setInteger:m_ucTroophy[5][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_7"];
    [defaults setInteger:m_ucTroophy[5][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_8"];
    [defaults setInteger:m_ucTroophy[5][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_9"];
    [defaults setInteger:m_ucTroophy[5][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_10"];
    [defaults setInteger:m_ucTroophy[5][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_11"];
    [defaults setInteger:m_ucTroophy[5][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_12"];
    [defaults setInteger:m_ucTroophy[5][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_13"];
    [defaults setInteger:m_ucTroophy[5][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_14"];
    [defaults setInteger:m_ucTroophy[5][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_15"];
    [defaults setInteger:m_ucTroophy[5][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_16"];
    [defaults setInteger:m_ucTroophy[5][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_17"];
    [defaults setInteger:m_ucTroophy[5][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_18"];
    [defaults setInteger:m_ucTroophy[5][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore5_19"];
    
    // profil #7
    
    NSString *sName6 = [[NSString alloc] initWithCString:(char*)m_cName[6]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName6 forKey:@"SHODAN9_GemsOfAtlantis_cName6"];
    [defaults setInteger:m_ulTotalScore[6] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore6"];
    [defaults setInteger:m_ulScore[6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6"];
    [defaults setInteger:m_ulMap[6] forKey:@"SHODAN9_GemsOfAtlantis_ulMap6"];
    [defaults setInteger:m_ulLevel[6] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel6"];
    
    [defaults setInteger:m_ucTroophy[6][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_0"];
    [defaults setInteger:m_ucTroophy[6][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_1"];
    [defaults setInteger:m_ucTroophy[6][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_2"];
    [defaults setInteger:m_ucTroophy[6][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_3"];
    [defaults setInteger:m_ucTroophy[6][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_4"];
    [defaults setInteger:m_ucTroophy[6][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_5"];
    [defaults setInteger:m_ucTroophy[6][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_6"];
    [defaults setInteger:m_ucTroophy[6][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_7"];
    [defaults setInteger:m_ucTroophy[6][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_8"];
    [defaults setInteger:m_ucTroophy[6][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_9"];
    [defaults setInteger:m_ucTroophy[6][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_10"];
    [defaults setInteger:m_ucTroophy[6][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_11"];
    [defaults setInteger:m_ucTroophy[6][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_12"];
    [defaults setInteger:m_ucTroophy[6][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_13"];
    [defaults setInteger:m_ucTroophy[6][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_14"];
    [defaults setInteger:m_ucTroophy[6][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_15"];
    [defaults setInteger:m_ucTroophy[6][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_16"];
    [defaults setInteger:m_ucTroophy[6][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_17"];
    [defaults setInteger:m_ucTroophy[6][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_18"];
    [defaults setInteger:m_ucTroophy[6][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore6_19"];
    
    // profil #8
    
    NSString *sName7 = [[NSString alloc] initWithCString:(char*)m_cName[7]  encoding:NSUTF8StringEncoding];
    
    [defaults setObject:sName7 forKey:@"SHODAN9_GemsOfAtlantis_cName7"];
    [defaults setInteger:m_ulTotalScore[7] forKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore7"];
    [defaults setInteger:m_ulScore[7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7"];
    [defaults setInteger:m_ulMap[7] forKey:@"SHODAN9_GemsOfAtlantis_ulMap7"];
    [defaults setInteger:m_ulLevel[7] forKey:@"SHODAN9_GemsOfAtlantis_ulLevel7"];
    
    [defaults setInteger:m_ucTroophy[7][0] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_0"];
    [defaults setInteger:m_ucTroophy[7][1] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_1"];
    [defaults setInteger:m_ucTroophy[7][2] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_2"];
    [defaults setInteger:m_ucTroophy[7][3] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_3"];
    [defaults setInteger:m_ucTroophy[7][4] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_4"];
    [defaults setInteger:m_ucTroophy[7][5] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_5"];
    [defaults setInteger:m_ucTroophy[7][6] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_6"];
    [defaults setInteger:m_ucTroophy[7][7] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_7"];
    [defaults setInteger:m_ucTroophy[7][8] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_8"];
    [defaults setInteger:m_ucTroophy[7][9] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_9"];
    [defaults setInteger:m_ucTroophy[7][10] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_10"];
    [defaults setInteger:m_ucTroophy[7][11] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_11"];
    [defaults setInteger:m_ucTroophy[7][12] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_12"];
    [defaults setInteger:m_ucTroophy[7][13] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_13"];
    [defaults setInteger:m_ucTroophy[7][14] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_14"];
    [defaults setInteger:m_ucTroophy[7][15] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_15"];
    [defaults setInteger:m_ucTroophy[7][16] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_16"];
    [defaults setInteger:m_ucTroophy[7][17] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_17"];
    [defaults setInteger:m_ucTroophy[7][18] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_18"];
    [defaults setInteger:m_ucTroophy[7][19] forKey:@"SHODAN9_GemsOfAtlantis_ulScore7_19"];

    
    [defaults synchronize];
    
    [sName0 release];
    [sName1 release];
    [sName2 release];
    [sName3 release];
    [sName4 release];
    [sName5 release];
    [sName6 release];
    [sName7 release];
    
	return true;
}

bool CProfile::bLoad(void)
{

    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    //    [defaults setInteger:score forKey:@"GOA_ulScore"];
    //     newScore = [defaults integerForKey:@"GOA_ulScore"];
    
    //    [defaults setInteger:m_ucCurrentProfile forKey:@"SHODAN9_GemsOfAtlantis_ucCurrentProfile"];
    
    m_ucCurrentProfile = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ucCurrentProfile"];
    
    // profil #1
    
    NSString *sName0 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName0"];
    
    [defaults synchronize];
    
    strcpy(m_cName[0],[sName0 UTF8String]);
    
    m_ulTotalScore[0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore0"];
    m_ulScore[0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0"];
    m_ulMap[0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap0"];
    m_ulLevel[0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel0"];

    m_ucTroophy[0][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_0"];
    m_ucTroophy[0][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_1"];
    m_ucTroophy[0][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_2"];
    m_ucTroophy[0][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_3"];
    m_ucTroophy[0][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_4"];
    m_ucTroophy[0][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_5"];
    m_ucTroophy[0][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_6"];
    m_ucTroophy[0][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_7"];
    m_ucTroophy[0][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_8"];
    m_ucTroophy[0][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_9"];
    m_ucTroophy[0][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_10"];
    m_ucTroophy[0][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_11"];
    m_ucTroophy[0][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_12"];
    m_ucTroophy[0][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_13"];
    m_ucTroophy[0][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_14"];
    m_ucTroophy[0][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_15"];
    m_ucTroophy[0][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_16"];
    m_ucTroophy[0][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_17"];
    m_ucTroophy[0][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_18"];
    m_ucTroophy[0][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore0_19"];

    // profil #2
    
    NSString *sName1 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName1"];
    
    [defaults synchronize];
    
    strcpy(m_cName[1],[sName1 UTF8String]);
    
    m_ulTotalScore[1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore1"];
    m_ulScore[1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1"];
    m_ulMap[1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap1"];
    m_ulLevel[1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel1"];
    
    m_ucTroophy[1][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_0"];
    m_ucTroophy[1][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_1"];
    m_ucTroophy[1][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_2"];
    m_ucTroophy[1][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_3"];
    m_ucTroophy[1][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_4"];
    m_ucTroophy[1][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_5"];
    m_ucTroophy[1][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_6"];
    m_ucTroophy[1][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_7"];
    m_ucTroophy[1][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_8"];
    m_ucTroophy[1][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_9"];
    m_ucTroophy[1][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_10"];
    m_ucTroophy[1][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_11"];
    m_ucTroophy[1][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_12"];
    m_ucTroophy[1][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_13"];
    m_ucTroophy[1][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_14"];
    m_ucTroophy[1][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_15"];
    m_ucTroophy[1][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_16"];
    m_ucTroophy[1][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_17"];
    m_ucTroophy[1][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_18"];
    m_ucTroophy[1][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore1_19"];
    
    // profil #3
    
    NSString *sName2 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName2"];
    
    [defaults synchronize];
    
    strcpy(m_cName[2],[sName2 UTF8String]);
    
    m_ulTotalScore[2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore2"];
    m_ulScore[2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2"];
    m_ulMap[2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap2"];
    m_ulLevel[2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel2"];
    
    m_ucTroophy[2][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_0"];
    m_ucTroophy[2][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_1"];
    m_ucTroophy[2][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_2"];
    m_ucTroophy[2][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_3"];
    m_ucTroophy[2][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_4"];
    m_ucTroophy[2][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_5"];
    m_ucTroophy[2][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_6"];
    m_ucTroophy[2][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_7"];
    m_ucTroophy[2][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_8"];
    m_ucTroophy[2][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_9"];
    m_ucTroophy[2][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_10"];
    m_ucTroophy[2][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_11"];
    m_ucTroophy[2][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_12"];
    m_ucTroophy[2][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_13"];
    m_ucTroophy[2][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_14"];
    m_ucTroophy[2][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_15"];
    m_ucTroophy[2][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_16"];
    m_ucTroophy[2][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_17"];
    m_ucTroophy[2][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_18"];
    m_ucTroophy[2][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore2_19"];
    
    // profil #4
    
    NSString *sName3 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName3"];
    
    [defaults synchronize];
    
    strcpy(m_cName[3],[sName3 UTF8String]);
    
    m_ulTotalScore[3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore3"];
    m_ulScore[3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3"];
    m_ulMap[3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap3"];
    m_ulLevel[3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel3"];
    
    m_ucTroophy[3][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_0"];
    m_ucTroophy[3][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_1"];
    m_ucTroophy[3][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_2"];
    m_ucTroophy[3][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_3"];
    m_ucTroophy[3][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_4"];
    m_ucTroophy[3][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_5"];
    m_ucTroophy[3][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_6"];
    m_ucTroophy[3][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_7"];
    m_ucTroophy[3][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_8"];
    m_ucTroophy[3][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_9"];
    m_ucTroophy[3][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_10"];
    m_ucTroophy[3][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_11"];
    m_ucTroophy[3][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_12"];
    m_ucTroophy[3][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_13"];
    m_ucTroophy[3][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_14"];
    m_ucTroophy[3][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_15"];
    m_ucTroophy[3][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_16"];
    m_ucTroophy[3][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_17"];
    m_ucTroophy[3][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_18"];
    m_ucTroophy[3][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore3_19"];

    // profil #5
    
    NSString *sName4 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName4"];
    
    [defaults synchronize];
    
    strcpy(m_cName[4],[sName4 UTF8String]);
    
    m_ulTotalScore[4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore4"];
    m_ulScore[4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4"];
    m_ulMap[4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap4"];
    m_ulLevel[4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel4"];
    
    m_ucTroophy[4][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_0"];
    m_ucTroophy[4][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_1"];
    m_ucTroophy[4][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_2"];
    m_ucTroophy[4][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_3"];
    m_ucTroophy[4][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_4"];
    m_ucTroophy[4][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_5"];
    m_ucTroophy[4][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_6"];
    m_ucTroophy[4][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_7"];
    m_ucTroophy[4][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_8"];
    m_ucTroophy[4][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_9"];
    m_ucTroophy[4][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_10"];
    m_ucTroophy[4][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_11"];
    m_ucTroophy[4][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_12"];
    m_ucTroophy[4][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_13"];
    m_ucTroophy[4][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_14"];
    m_ucTroophy[4][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_15"];
    m_ucTroophy[4][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_16"];
    m_ucTroophy[4][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_17"];
    m_ucTroophy[4][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_18"];
    m_ucTroophy[4][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore4_19"];

    // profil #6
    
    NSString *sName5 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName5"];
    
    [defaults synchronize];
    
    strcpy(m_cName[5],[sName5 UTF8String]);
    
    m_ulTotalScore[5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore5"];
    m_ulScore[5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5"];
    m_ulMap[5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap5"];
    m_ulLevel[5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel5"];
    
    m_ucTroophy[5][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_0"];
    m_ucTroophy[5][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_1"];
    m_ucTroophy[5][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_2"];
    m_ucTroophy[5][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_3"];
    m_ucTroophy[5][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_4"];
    m_ucTroophy[5][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_5"];
    m_ucTroophy[5][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_6"];
    m_ucTroophy[5][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_7"];
    m_ucTroophy[5][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_8"];
    m_ucTroophy[5][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_9"];
    m_ucTroophy[5][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_10"];
    m_ucTroophy[5][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_11"];
    m_ucTroophy[5][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_12"];
    m_ucTroophy[5][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_13"];
    m_ucTroophy[5][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_14"];
    m_ucTroophy[5][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_15"];
    m_ucTroophy[5][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_16"];
    m_ucTroophy[5][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_17"];
    m_ucTroophy[5][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_18"];
    m_ucTroophy[5][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore5_19"];
    
    // profil #7
    
    NSString *sName6 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName6"];
    
    [defaults synchronize];
    
    strcpy(m_cName[6],[sName6 UTF8String]);
    
    m_ulTotalScore[6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore6"];
    m_ulScore[6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6"];
    m_ulMap[6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap6"];
    m_ulLevel[6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel6"];
    
    m_ucTroophy[6][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_0"];
    m_ucTroophy[6][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_1"];
    m_ucTroophy[6][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_2"];
    m_ucTroophy[6][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_3"];
    m_ucTroophy[6][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_4"];
    m_ucTroophy[6][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_5"];
    m_ucTroophy[6][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_6"];
    m_ucTroophy[6][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_7"];
    m_ucTroophy[6][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_8"];
    m_ucTroophy[6][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_9"];
    m_ucTroophy[6][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_10"];
    m_ucTroophy[6][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_11"];
    m_ucTroophy[6][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_12"];
    m_ucTroophy[6][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_13"];
    m_ucTroophy[6][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_14"];
    m_ucTroophy[6][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_15"];
    m_ucTroophy[6][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_16"];
    m_ucTroophy[6][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_17"];
    m_ucTroophy[6][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_18"];
    m_ucTroophy[6][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore6_19"];
    
    // profil #8
    
    NSString *sName7 = [defaults stringForKey:@"SHODAN9_GemsOfAtlantis_cName7"];
    
    [defaults synchronize];
    
    strcpy(m_cName[7],[sName7 UTF8String]);
    
    m_ulTotalScore[7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulTotalScore7"];
    m_ulScore[7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7"];
    m_ulMap[7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulMap7"];
    m_ulLevel[7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulLevel7"];
    
    m_ucTroophy[7][0] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_0"];
    m_ucTroophy[7][1] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_1"];
    m_ucTroophy[7][2] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_2"];
    m_ucTroophy[7][3] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_3"];
    m_ucTroophy[7][4] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_4"];
    m_ucTroophy[7][5] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_5"];
    m_ucTroophy[7][6] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_6"];
    m_ucTroophy[7][7] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_7"];
    m_ucTroophy[7][8] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_8"];
    m_ucTroophy[7][9] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_9"];
    m_ucTroophy[7][10] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_10"];
    m_ucTroophy[7][11] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_11"];
    m_ucTroophy[7][12] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_12"];
    m_ucTroophy[7][13] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_13"];
    m_ucTroophy[7][14] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_14"];
    m_ucTroophy[7][15] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_15"];
    m_ucTroophy[7][16] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_16"];
    m_ucTroophy[7][17] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_17"];
    m_ucTroophy[7][18] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_18"];
    m_ucTroophy[7][19] = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis_ulScore7_19"];   
    
    [defaults synchronize];
    
	// poprawka dla etapu, jezeli ktos ma etap 0 lub > 10 to zamieniamy na 1

	for (int i=0; i<8; i++)
	{
		if (m_ulLevel[i]>9 || m_ulLevel[i]<1)
			m_ulLevel[i] = 1;
	}

	return true;
}

bool CProfile::bSetup(void)
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    _ucFirstRun = [defaults integerForKey:@"SHODAN9_GemsOfAtlantis"];
    
    if (_ucFirstRun==0)
    {
        _ucFirstRun = 1;
        [defaults setInteger:_ucFirstRun forKey:@"SHODAN9_GemsOfAtlantis"];
    
        [defaults synchronize];

        sprintf(m_cName[0],"YOU");
        
        m_ulTotalScore[0] = 0;
        m_ulScore[0] = 0;
        m_ulMap[0] = 0;
        m_ulLevel[0] = 0;
        
        for (int j=0; j!=20; j++)
            m_ucTroophy[0][j]=0;
        
        
        for (int i=1; i!=8; i++)
        {
            sprintf(m_cName[i],"PLAYER");
            
            m_ulTotalScore[i] = 0;
            m_ulScore[i] = 0;
            m_ulMap[i] = 0;
            m_ulLevel[i] = 0;
            
            for (int j=0; j!=20; j++)
                m_ucTroophy[i][j]=0;
        }
        
        bSave();
        
        return true;
        
    }
    
    return false;
}

void CProfile::ucTroophy(int iIndex, unsigned char ucValue)
{
	m_ucTroophy[m_ucCurrentProfile][iIndex] = ucValue;
}

unsigned char CProfile::ucTroophy(int iIndex)
{
	return m_ucTroophy[m_ucCurrentProfile][iIndex];
}

//=== mapa oznacza poziom / miejsce na mapie, ktore wybieramy w eLevelMenu

void CProfile::ulMap(unsigned long ul)
{
	m_ulMap[m_ucCurrentProfile] = ul;
}

unsigned long CProfile::ulMap(void)
{
	return m_ulMap[m_ucCurrentProfile];
}

void CProfile::ucCurrentProfile(unsigned char ucProfile)	// ktory profil jest aktualnie u¿ywany
{
	m_ucCurrentProfile = ucProfile;
}

unsigned char CProfile::ucCurrentProfile(void)
{
	return m_ucCurrentProfile;
}

int CProfile::iNameSize(void)
{
	return strlen(m_cName[m_ucCurrentProfile]);
}

