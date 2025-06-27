#include "ytable.h"

CYtable::CYtable()
{

}

CYtable::~CYtable()
{
	if (m_ulLine!=NULL) delete m_ulLine;
}

CYtable::CYtable(unsigned long ulSize, unsigned long ulResolution)
{

	unsigned long t1;

	if ((m_ulLine= new unsigned long[ulSize+1])==NULL)
	{
		fx_debug("ERROR! Out of memory for YTable!");
		return;
	}

	for (t1=0;t1<ulSize+1;t1++)
	{
		m_ulLine[t1]= ulResolution * t1;		// 1*800, 2*800, 3*800
	}

}

unsigned long CYtable::ulLine(int iIndex)
{
	return m_ulLine[iIndex];
}
