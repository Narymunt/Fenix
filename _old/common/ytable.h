#pragma once

#include "debug.h"

class CYtable  
{
						
public:

	CYtable();
	CYtable(unsigned long ulSize, unsigned long ulResolution);	// size * resolution

	virtual ~CYtable();

	unsigned long ulLine(int iIndex);
	
private: 

	unsigned long	*m_ulLine;

};

#endif 
