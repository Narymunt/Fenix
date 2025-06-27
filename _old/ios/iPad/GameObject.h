// game object - general object class

#pragma once

#include <stdio.h>

class CGameObject
{

public:

	CGameObject();
	~CGameObject();

	void				isActive(bool bState);		// are data loaded ? 
	bool				isActive(void);				// return flag

	void				Open(void);			// load 
	void				Close(void);		// unload

	inline void			isMouseLock(bool b) { _isMouseLock = b; }
	inline bool			isMouseLock(void) { return _isMouseLock; }

    inline int          iOS(void) { return _iOS; }
    inline void         iOS(int i) { _iOS = i; }
    
    template< class T > void SafeDelete( T*& pVal )
    {
        if (pVal!=NULL)
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
    
    
protected:

	bool				_isActive;			// data loaded or not ? 
	bool				_isMouseLock;		// czy myszka jest zablokowana po poprzednim ekranie ?
    
    int                 _iOS;

};

