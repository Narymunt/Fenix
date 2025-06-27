
//#define DIRECT3D_VERSION 0x0700

#include	<d3d9.h>
#include	"kptk.h"

#include	"KGraphic.h"
#include	"KWindow.h"

#include	"KMiscTools.h"

#include	"KBatchGL.h"
#include	"KWindowGL.h"
#include	"KGraphicGL.h"

#include	"KBatchDX9.h"
#include	"KWindowDX9.h"
#include	"KGraphicDX9.h"

//#include	"KWindowD3D.h"
//#include	"KGraphicD3D.h"
//#include	"K3DD3D.h"
//#include	"K3DGL.h"
//#include	"KBatchGDI.h"
//#include	"KWindowGDI.h"

Erenderer		KPTK::_renderer = /*K_DIRECTX*/  K_DIRECTX9;
int KPTK::_window_width = 0;
int KPTK::_window_height = 0;

KPTK::KPTK( ) 
{
}

KPTK::~KPTK( ) 
{
}

KWindow	*KPTK::createKWindow( Erenderer er, int win_width, int win_height ) 
{
	_renderer = er ;
	_window_width = win_width;
	_window_height = win_height;

	KMiscTools::initMiscTools( NULL ) ;

//	if (_renderer == K_DIRECTX )		return ( new KWindowD3D(use3d)) ;
//	if (_renderer == K_GDI )		return ( new KWindowGDI()) ;

	if (_renderer == K_DIRECTX9 )		return ( new KWindowDX9(false/*use3d*/)) ;
	
	return ( new KWindowGL(false/*use3d*/)  ) ;

}


//create kgraphic
KGraphic	*KPTK::createKGraphic( void ) 
{
	
//	if (_renderer == K_DIRECTX )		return ( new KGraphicD3D ) ;
//	if (_renderer == K_GDI )		return ( new KGraphicGDI ) ;

	if (_renderer == K_DIRECTX9 )		return ( new KGraphicDX9 ) ;
	
	return ( new KGraphicGL ) ;

}


//delete  kgraphic
void	KPTK::deleteKGraphic( KGraphic *kGraphicPtr ) 
{
	if ( kGraphicPtr == NULL )	return ;
	
	delete kGraphicPtr ;
	kGraphicPtr = NULL ;
}

//delete  kWindow
void	KPTK::deleteKWindow( KWindow *kWindowPtr ) 
{
	if ( kWindowPtr == NULL )	return ;
	
	delete kWindowPtr ;
	kWindowPtr = NULL ;
}

void	KPTK::deleteKBatch( KBatch *kBatchPtr ) 
{
	if ( kBatchPtr == NULL )	return ;
	
	delete kBatchPtr ;
	kBatchPtr = NULL ;
}

KBatch		*KPTK::createKBatch( void )
{
//	if (_renderer == K_DIRECTX )		
//	{
//		return new KBatchD3D ;
//	}

	if (_renderer == K_DIRECTX9 )		
	{
		return new KBatchDX9 ;
	}

	if (_renderer == K_OPENGL )		
	{
		return new KBatchGL;
	}
	
	//if (_renderer == K_GDI )		
	//{
	////	return new KBatchGDI ;
	//}

	
	return NULL ;
}



//create kgraphic
KGraphic	*KPTK::createKGraphic( char	*filename ) 
{
	KGraphic	*tmpk ;

/*
	if (_renderer == K_DIRECTX )		
	{
		tmpk =  new KGraphicD3D  ;
		tmpk->loadPicture( filename , true, true ) ;
		return tmpk ;
	}
*/

	if (_renderer == K_DIRECTX9 )		
	{
		tmpk =  new KGraphicDX9  ;
		tmpk->loadPicture( filename , true, true ) ;
		return tmpk ;
	}

	if (_renderer == K_OPENGL )		
	{
		tmpk =  new KGraphicGL  ;
		tmpk->loadPicture( filename , true, true ) ;
		return tmpk ;
	}
	
//	if (_renderer == K_GDI )		
//	{
//	//	tmpk =  new KGraphicGDI  ;
////		tmpk->loadPicture( filename , true, true ) ;
////	return tmpk ;
//	}

	return NULL ;
}

//K3D			*KPTK::createK3D( void ) 
//{
////	if (_renderer == K_DIRECTX )		return ( new K3Dd3d  ) ;
//	return ( new K3DGL  ) ;
//}
