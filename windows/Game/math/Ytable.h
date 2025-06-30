#pragma once

class Ytable  
{
						
public:

	Ytable();
	Ytable(unsigned long ulSize, unsigned long ulResolution);	// size * resolution

	virtual ~Ytable();

	unsigned long ulLine(int iIndex);
	

	unsigned long	*m_ulLine;

};
