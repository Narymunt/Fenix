
#pragma once
// sin^cos tables for integers

class CSinTable
{

public : 
    
	CSinTable();
	~CSinTable();
    
	inline int iSin256(int i) { return _iSin256[i]; }
	inline int iCos256(int i) { return _iCos256[i]; }

	inline int iSin1024(int i) { return _iSin1024[i]; }
	inline int iCos1024(int i) { return _iCos1024[i]; }

protected : 

    int _iSin256[256];
    int _iCos256[256];
    
    int _iSin1024[256];
    int _iCos1024[256];

};
