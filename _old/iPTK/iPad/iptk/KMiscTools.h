/*
 *  KMiscTools.h
 *  JDK
 *
 *  Created by Julien meyer on 04/05/08.
 *  Copyright 2010 jmApp.com All rights reserved.
 *
 */


#ifndef API_KMISCTOOLS__
#define API_KMISCTOOLS__

#include <stdio.h>
#include <stdlib.h>

//#ifdef MAX_PATH
//#undef MAX_PATH
#define	MAX_PATH		512
//#endif

class KMiscTools
{
private:
	
	static	char	currentAppPath[MAX_PATH];
	static	char	currentFilePath[MAX_PATH];
	static	char	currentTempPath[MAX_PATH];
	static	char	currentDocHomePath[MAX_PATH];
	
	static	bool	_inPackage;
	
	static char		currentPath[MAX_PATH*2];


	
public:
	
	static	void initMiscTools();
	static	char * makeHomeDocFilePath(const char *filename);
	static	char * makeTempFilePath(const char *filename);
	static	char * makeFilePath(const char *filename);
	static	void messageBox(char *msg, char *title);
	static	short flipShort(short value);
	static	long flipLong(long value);
	static	long getSeed();
	static	unsigned long getMilliseconds();
	static  void  getSerial( char *s );
	static unsigned short pathSeparator(void) ;
	static	int getDocHome(char * path, unsigned int maxLen) ;
	
	static	int getUserHome(char * path, unsigned int maxLen) ;
	static int	getTempHome(char * path, unsigned int maxLen)	;
	static int  getCurrentDir(char * path, unsigned int maxLen) ;
	static int  getAppHome(char * path, unsigned int maxLen) ;
	static	void appendPath(char * path, char * component) ;
	static  char *concatePath(char * path1, char * path2) ;

	
};


#endif // API_KMISCTOOLS__
