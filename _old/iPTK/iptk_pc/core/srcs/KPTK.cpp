//
////#define DIRECT3D_VERSION 0x0700
//
//#include	"kptk.h"
//
//#include	"KGraphic.h"
//#include	"KWindow.h"
//
//#include	"KMiscTools.h"
//
//#include	"KWindowGL.h"
//#include	"KGraphicGL.h"
//#include	"KBatchGL.h"
//
//#include	"KWindowDX9.h"
//#include	"KGraphicDX9.h"
//#include	"KBatchDX9.h"
//
////#include	"K3DD3D.h"
////#include	"K3DGL.h"
////#include	"KBatchD3D.h"
////#include	"KWindowD3D.h"
////#include	"KGraphicD3D.h"
////#include	"KBatchGDI.h"
////#include	"KWindowGDI.h"
//
//Erenderer		KPTK::_renderer = K_DIRECTX  ;
//
//KPTK::KPTK( ) 
//{
//}
//
//KPTK::~KPTK( ) 
//{
//}
//
//KWindow	*KPTK::createKWindow( Erenderer er, bool use3d ) 
//{
//	_renderer = er ;
//
//KMiscTools::initMiscTools( ) ;
//
//	if (_renderer == K_DIRECTX )		return ( new KWindowD3D(use3d)) ;
////	if (_renderer == K_GDI )		return ( new KWindowGDI()) ;
//	
//	return ( new KWindowGL(use3d)  ) ;
//
//}
//
//
////create kgraphic
//KGraphic	*KPTK::createKGraphic( void ) 
//{
//	
//	if (_renderer == K_DIRECTX )		return ( new KGraphicD3D ) ;
////	if (_renderer == K_GDI )		return ( new KGraphicGDI ) ;
//	
//	return ( new KGraphicGL ) ;
//
//}
//
//
////delete  kgraphic
//void	KPTK::deleteKGraphic( KGraphic *kGraphicPtr ) 
//{
//	if ( kGraphicPtr == NULL )	return ;
//	
//	delete kGraphicPtr ;
//	kGraphicPtr = NULL ;
//}
//
////delete  kWindow
//void	KPTK::deleteKWindow( KWindow *kWindowPtr ) 
//{
//	if ( kWindowPtr == NULL )	return ;
//	
//	delete kWindowPtr ;
//	kWindowPtr = NULL ;
//}
//
//void	KPTK::deleteKBatch( KBatch *kBatchPtr ) 
//{
//	if ( kBatchPtr == NULL )	return ;
//	
//	delete kBatchPtr ;
//	kBatchPtr = NULL ;
//}
//
//KBatch		*KPTK::createKBatch( void )
//{
//	if (_renderer == K_DIRECTX )		
//	{
//		return new KBatchD3D ;
//	}
//
//
//	if (_renderer == K_OPENGL )		
//	{
//		return new KBatchGL;
//	}
//	
//	if (_renderer == K_GDI )		
//	{
//	//	return new KBatchGDI ;
//	}
//
//	
//	return NULL ;
//}
//
//
//
////create kgraphic
//KGraphic	*KPTK::createKGraphic( char	*filename ) 
//{
//KGraphic	*tmpk ;
//
//	if (_renderer == K_DIRECTX )		
//	{
//		tmpk =  new KGraphicD3D  ;
//		tmpk->loadPicture( filename , true, true ) ;
//		return tmpk ;
//	}
//
//
//	if (_renderer == K_OPENGL )		
//	{
//		tmpk =  new KGraphicGL  ;
//		tmpk->loadPicture( filename , true, true ) ;
//		return tmpk ;
//	}
//	
//	if (_renderer == K_GDI )		
//	{
//	//	tmpk =  new KGraphicGDI  ;
////		tmpk->loadPicture( filename , true, true ) ;
////	return tmpk ;
//	}
//
//	return NULL ;
//}
//
//K3D			*KPTK::createK3D( void ) 
//{
//	if (_renderer == K_DIRECTX )		return ( new K3Dd3d  ) ;
//	return ( new K3DGL  ) ;
//}
