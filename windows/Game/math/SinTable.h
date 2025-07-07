#pragma once
// sin^cos tables for integers

class SinTable
{

public : 
    
	SinTable();
	~SinTable();
    
	inline int sin256(int i) { return _sin256[i]; }
	inline int cos256(int i) { return _cos256[i]; }

	inline int sin1024(int i) { return _sin1024[i]; }
	inline int cos1024(int i) { return _cos1024[i]; }

    int _sin256[256];
    int _cos256[256];
    
    int _sin1024[256];
    int _cos1024[256];

};
