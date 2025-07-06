#pragma once

//=== templates for deleting objects

template< class T > void SafeDelete( T*& pVal )
{
    if (pVal != NULL)
	{
		delete pVal;
		pVal = NULL;
	}
}
    
template< class T > void SafeDeleteArray( T*& pVal )
{
    delete[] pVal;
    pVal = NULL;
}
