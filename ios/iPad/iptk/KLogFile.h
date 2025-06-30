#ifndef API_KLOGFILE__
#define API_KLOGFILE__

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

class KLogFile
{
private:
	
	static FILE *f;
	
	static void Init();
	
public:
		
	~KLogFile();

	static void logDebug(const char *msg, ...);
	static void Close();

};


#endif // API_KLOGFILE__
