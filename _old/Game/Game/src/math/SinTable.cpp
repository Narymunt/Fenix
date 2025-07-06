// sin^cos tables 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SinTable.h"

CSinTable::CSinTable(void)
{

    float fC;
    
    fC=3.1415927f/128.0f;
    
    for (int iTemp=0, fA=0.0f; iTemp<256; iTemp++, fA+=fC)
    {
		_iSin256[iTemp] = (int)((sin((float)fA)*256.0)+0.5);
		_iCos256[iTemp] = (int)((cos((float)fA)*256.0)+0.5);
    }

    fC=3.1415927/512.0;
    
    for (int iTemp=0, fA=0.0; iTemp<1024; iTemp++, fA+=fC)
    {
		_iSin1024[iTemp] = (int)((sin((float)fA)*512.0)+0.5);
		_iCos1024[iTemp] = (int)((cos((float)fA)*512.0)+0.5);
    }


}

CSinTable::~CSinTable(void)
{

}
    
