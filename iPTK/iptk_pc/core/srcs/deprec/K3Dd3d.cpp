#define 	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#define D3D_OVERLOADS
#define DIRECT3D_VERSION 0x0700
#include	"K3Dd3d.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	"KWindowD3D.h"
#include	"KMiscTools.h"
#include	<Math.h>
#include 		"KGraphic.h"
//#include 		"KGraphicD3D.h"
#include	<d3dx.h>
#include	<d3dxmath.h>
#include	"matrices.h"
#include	"KPTK.h"

#define	K3Dd3dDEBUG

float			K3Dd3d::_screenWidth = 640;
float			K3Dd3d::_screenHeight = 480 ;
LPDIRECT3DDEVICE7		K3Dd3d::_lpD3DDevice	= NULL ;
bool			K3Dd3d::_useScreenRes = false ;

extern		 void scalemat(D3DMATRIX &mat, float x, float y, float z) ;

struct		vect_t
{
	double		X,Y,Z ;
};

extern	double 	Norme(vect_t v) ;
extern	void 		Normalize(vect_t *pVect) ;
extern	double 		PdtScalaire(vect_t *pVect1, vect_t *pVect2) ;
extern	void 		PdVectoriel(vect_t *Vres, vect_t *v1, vect_t *v2) ;
extern	void		m_GetFaceNormal_vect(vect_t *Vec0, vect_t *Vec1, vect_t *Vec2 , sMeshFace 	*faceptr) ;
void	setPerpectiveDx( D3DMATRIX *mat , float angle, float ratio, float znear, float zfar )  ;



K3Dd3d::K3Dd3d( ) 
{
		 _scaleX = 1 ;
		 _scaleY = 1 ;
		 _scaleZ = 1 ;
		 _textureLoaded = false ;
		 
		surf_texture		= NULL ;
		meshPtr 			= 	NULL ;
		meshFacesPtr  	= 	NULL ;
	     _lpVertexFlat      =  NULL ;
	     _lpVertexGouraud      =  NULL ;
		_pointCount 		=	0;
		_faceCount		=	0 ;

		_eShadeMode 	= ESM_FLAT ;
		_blend				= false ;
		_blendFactor 		= 1 ;

		setAlphaMode( true ) ;
}

K3Dd3d::~K3Dd3d( ) 
{
	
	freeModel( ) ;
}


void	K3Dd3d::initK3Dd3d( long	width , long height , LPDIRECT3DDEVICE7	D3DDevice)
{
	_screenWidth 	= (float)width ;
	_screenHeight 	= (float)height ;

	_lpD3DDevice = D3DDevice ;
	
//	D3DVIEWPORT7 vp = { 0, 0, _screenWidth, _screenHeight, 0.0f, 1.0f };
//	_lpD3DDevice->SetViewport( &vp ) ;
	// Calculate The Aspect Ratio Of The Window

	
//	setPerspective((double)45.0f, (double)( _screenWidth/_screenHeight)   ,(double)0.1f,(double)100.0f);

	
}


void		K3Dd3d::setPerspective( double  fovy, double aspect, double zNear, double zFar )
{
double	 x , y ;

//	if ( _useScreenRes == false  )
//	{
		y = tan(fovy/360 * K_PI)*zNear ;
		x = y*aspect  ;
		setPerpectiveDx( &matProjection , x , y  ,zNear , zFar ) ;
//	}
//	else
//	{
//		setPerpectiveDxNatural(&matProjection  , fovy, aspect ,zNear , zFar ) ;
//	}

}
 
void		K3Dd3d::beginScene( bool	clearScene , bool useScreenResolution ) 
{

    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORVERTEX, true);
 
	D3DVIEWPORT7 vp = { 0, 0, _screenWidth, _screenHeight, 0.0f, 1.0f };
	_lpD3DDevice->SetViewport( &vp ) ;
	
	
//	_lpD3DDevice->BeginScene( ) ;  //already called in flipBackBuffer
	
	//calculate the projection matrix
	setPerspective((double)45.0f, (double)( (double)_screenWidth/(double)_screenHeight)   ,(double)0.1,(double)500);

	D3DMATRIX  mat ;

	if ( useScreenResolution == false  )
	{
		identity500( &mat ) ;
		mat._31 *=-1 ;
		mat._32 *=-1 ;
		mat._33 *=-1 ;
		mat._34 *=-1 ;
		_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);
		}

	else
	{
		ortho(&mat, _screenWidth, _screenHeight, -500, 500);	
	 	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);	 	
 		setPerspective((double)45.0f, (double)( (double)_screenWidth/(double)_screenHeight)   ,(double)0.1,(double)500);

		_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProjection);

	}

	
	if ( clearScene == true )
	{
			D3DRECT D3DRect = { 0, 0, _screenWidth, _screenHeight};
		_lpD3DDevice->Clear(1UL, &D3DRect, D3DCLEAR_ZBUFFER, 0xff000000, 1, 0L );
	}


	
D3DCOLORVALUE LightAmbient= {0.0,0.0,0.0,1.0f};
D3DCOLORVALUE LightSpecular= {1,1,1 , 1.0f};	
D3DCOLORVALUE LightDiffuse= { 1,1,1, 1.0f };
D3DVECTOR       	position = D3DVECTOR(0,0,1100 ) ;
D3DVECTOR       	direction = D3DVECTOR(0,0,1 );

D3DLIGHT7	d3dLight ;

 memset (&d3dLight, 0, sizeof (d3dLight));
 d3dLight.dltType = D3DLIGHT_POINT;
 d3dLight.dcvDiffuse = LightDiffuse;
 d3dLight.dcvSpecular = LightSpecular;
 d3dLight.dcvAmbient = LightAmbient;
 d3dLight.dvPosition = position;
 d3dLight.dvDirection = direction;
 d3dLight.dvRange = D3DLIGHT_RANGE_MAX;
 d3dLight.dvFalloff = 1.0;
 d3dLight.dvAttenuation0 = 1;
 d3dLight.dvTheta = 0;
 d3dLight.dvPhi = 0;


	_lpD3DDevice->LightEnable( 0 , true ) ;
	_lpD3DDevice->SetLight( 0 , &d3dLight ) ;

   _lpD3DDevice->SetRenderState(D3DRENDERSTATE_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL); // Default == D3DMCS_COLOR1
   _lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL); // Default == D3DMCS_COLOR2
   _lpD3DDevice->SetRenderState(D3DRENDERSTATE_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL); // Default == D3DMCS_COLOR2
   _lpD3DDevice->SetRenderState(D3DRENDERSTATE_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL); // Default == D3DMCS_MATERIAL


   D3DMATERIAL7 Material; // Initialize Material

   memset (&Material, 0, sizeof (Material));
   Material.dcvDiffuse.r = 1;
   Material.dcvDiffuse.g = 1;
   Material.dcvDiffuse.b = 1;
   Material.dcvDiffuse.a = 1;

   Material.dcvAmbient.r = 0.5;
   Material.dcvAmbient.g = 0.5;
   Material.dcvAmbient.b = 0.5;
   Material.dcvAmbient.a = 0.5;

   Material.dcvSpecular.r = 1;
   Material.dcvSpecular.g = 1;
   Material.dcvSpecular.b = 1;
   Material.dcvSpecular.a = 1;

   Material.dvPower = (float)50.0;
   _lpD3DDevice->SetMaterial(&Material);

	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, TRUE); //TRUE);
	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_AMBIENT, 0x00ffffff);

	_useScreenRes = useScreenResolution ;


		identity500( &mat ) ;
		mat._31 *=-1 ;
		mat._32 *=-1 ;
		mat._33 *=-1 ;
		mat._34 *=-1 ;
		_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);


}

void		K3Dd3d::endScene( void ) 
{
D3DMATRIX	mat ;
//	_lpD3DDevice->EndScene( ) ;  //called in flipbackbuffer
	identity( mat ) ;
	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);
	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &mat);
	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat);
	

	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, FALSE);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
    _lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORVERTEX, true);
 	_lpD3DDevice->LightEnable( 0 , false ) ;
 	
}


void		K3Dd3d::scale( float	sx , float sy , float sz  )
{
	_scaleX = sx ;
	_scaleY = sy ;
	_scaleZ = sz ;
}

//position an object
void		K3Dd3d::displayFlat( float	x , float y , float z  , float	rx , float ry , float rz  ) 
{
	D3DMATRIX  mat , mat2;
													// Reset The Current Modelview Matrix
	// sets a matrix to identity
	ZeroMemory(&mat, sizeof(mat));

	if ( _useScreenRes == true )
	{
		ortho(&mat, _screenWidth, _screenHeight, -500, 500);
	 	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);	 	
	 	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &mat);	 	
		translate(mat, x - (_screenWidth / 2), _screenHeight-y-(_screenHeight/2), z);	
	}

	identity500( &mat ) ;
	mat._31 *=-1 ;
	mat._32 *=-1 ;
	mat._33 *=-1 ;
	mat._34 *=-1 ;
   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);

	if ( _scaleX != 1 || _scaleY != 1 || _scaleZ != 1 )
	{
		scalemat( mat2 , _scaleX, _scaleY , _scaleZ ) ;
   		mat = mat2*mat;
	}

 // rx = -rx;
  // ry = -ry;

	if ( rx!=0 )		{
      rotatex( mat2 , rx) ;
   	mat = mat2*mat;
   }

	if ( ry!=0 )		{
      rotatey( mat2 , ry) ;
   	mat = mat2*mat;
   }

	if ( rz!=0 )		{
      rotatez( mat2 , rz ) ;
   	mat = mat2*mat;
   }

	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat);

	if ( _blend == true )
	{
		_lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);

	}
	else
	{
		_lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, false);
	}
	
	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);

	if  ( surf_texture != NULL )
	{
		surf_texture->selectTexture( ) ;
	}
	else
	{
		_lpD3DDevice->SetTexture(0, NULL );
	}
	
   _lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT);
   _lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, _lpVertexFlat, 3 * _faceCount, 0);
}

//position an object
void		K3Dd3d::display( float	x , float y , float z , float	rx , float ry , float rz  ) 
{

	switch( _eShadeMode )
	{
		case		ESM_FLAT:
			displayFlat(  x , y , z ,rx,ry,rz) ;
		break ;
		
		case		ESM_GOURAUD:
			displayGouraud(  x , y , z , rx,ry,rz ) ;
		break ;
	}
	
}


//position an object
void		K3Dd3d::displayGouraud( float	x , float y , float z , float	rx , float ry , float rz  )
{
	D3DMATRIX  mat , mat2;
													// Reset The Current Modelview Matrix
	// sets a matrix to identity
	ZeroMemory(&mat, sizeof(mat));

	if ( _useScreenRes == true )
	{
		ortho(&mat, _screenWidth, _screenHeight, -500, 500);
	 	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);	 	
	 	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &mat);	 	
		translate(mat, x - (_screenWidth / 2), _screenHeight-y-(_screenHeight/2), z);	
	}

	identity500( &mat ) ;
	mat._31 *=-1 ;
	mat._32 *=-1 ;
	mat._33 *=-1 ;
	mat._34 *=-1 ;
   _lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &mat);

	if ( _scaleX != 1 || _scaleY != 1 || _scaleZ != 1 )
	{
		scalemat( mat2 , _scaleX, _scaleY , _scaleZ ) ;
   		mat = mat2*mat;
	}

 // rx = -rx;
  // ry = -ry;

	if ( rx!=0 )		{
      rotatex( mat2 , rx) ;
   	mat = mat2*mat;
   }

	if ( ry!=0 )		{
      rotatey( mat2 , ry) ;
   	mat = mat2*mat;
   }

	if ( rz!=0 )		{
      rotatez( mat2 , rz ) ;
   	mat = mat2*mat;
   }

	_lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &mat);

	if ( _blend == true )
	{
		_lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, true);

	}
	else
	{
		_lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, false);
	}
	
	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, _sourceAlpha);
	_lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, _destAlpha);

	if  ( surf_texture != NULL )
	{
		surf_texture->selectTexture( ) ;
	}
	else
	{
		_lpD3DDevice->SetTexture(0, NULL );
	}
	
   _lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
   _lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, _lpVertexFlat, 3 * _faceCount, 0);
}

//regular == true pour TGA  false pour additif
void		K3Dd3d::setAlphaMode( bool	regular )
{
    if ( regular == false )
    {
    	   _sourceAlpha 		=  D3DBLEND_SRCALPHA  ;
	   _destAlpha			=	D3DBLEND_DESTALPHA  ;
	  }
    else
    {
 	       _sourceAlpha 	=  D3DBLEND_SRCALPHA ;
	        _destAlpha		=	D3DBLEND_INVSRCALPHA ;
    }
	
}

//enables alpha blending
void		K3Dd3d::enableBlending( bool	allowBlend , float	blendFactor )
{
	_blend 			= allowBlend ;
	_blendFactor 	= blendFactor ;
}

//load a ASE file
bool		K3Dd3d::load( char		*filename , float		scaleFactor , bool		loadTexture )
{
FILE	*f	;
//float	 f1 ;
char		*buffer ;

	freeModel( ) ;

	_textureLoaded = loadTexture ;
	

	f = fopen( filename , "rb" ) ;
	if ( f == NULL )	
	{
		KMiscTools::messageBox( "File not found" , filename ) ;
		return false ;
	}
	
	long fileLength ;
	fseek( f , 0 , SEEK_END ) ;
	fileLength = ftell( f ) ;
	fseek( f , 0 , SEEK_SET ) ;
	
	buffer = new char[fileLength] ;
	//read the whole file in memory for parsing.
	fread( buffer , 1, fileLength , f ) ;
	fclose( f ) ;
	
	unsigned	long chunkPos = 0  ;
	
	_pointCount = extractLongValue( "*MESH_NUMVERTEX" ,  buffer , 0 , fileLength ) ;
	if ( _pointCount <= 0  )
	{
		KMiscTools::messageBox( "No Vertices" , 0 ) ;
		delete [] buffer ;
		return false ;
	}
	
	
	_faceCount = extractLongValue( "*MESH_NUMFACES " , buffer , 0 , fileLength ) ;
	if ( _faceCount <= 0 )
	{
		KMiscTools::messageBox( "No faces in this asc" , 0 ) ;
		delete [] buffer ;
		return false ;
	}

	meshPtr = new s3dPoint[_pointCount] ;

	long		 mcount;
	float		fvalue,fvaluey,fvaluez ;
	char		valuename[50] ;
	memset( valuename ,0 , 50 ) ;
	chunkPos = findChunk( "*MESH_VERTEX_LIST" , buffer , 0 ,  fileLength ) ; ;

//char	progress[256] ;

	//reads all the mesh
	for  ( mcount = 0 ; mcount  <  _pointCount ; mcount++ )
	{
		#ifdef	K3Dd3dDEBUG
//			sprintf( progress , "loading mesh%d / %d" , mcount , _pointCount ) ;
//			KWindow::setTitle( progress ) ;
		#endif
		
		chunkPos = findChunk( "*MESH_VERTEX " , buffer , chunkPos ,  fileLength ) ;
		_snprintf( valuename , 9 , "%d" , mcount ) ;
		chunkPos	= findChunk( valuename , buffer , chunkPos ,  fileLength ) ;		
		chunkPos+=strlen( valuename ) ;
				
		//x
		chunkPos = extractNextFloatValue( buffer , chunkPos , fileLength , &fvalue ) ;
		meshPtr[mcount].x = 	fvalue * scaleFactor ;

		//y
		chunkPos = extractNextFloatValue( buffer , chunkPos , fileLength , &fvaluey ) ;
		meshPtr[mcount].y = 	fvaluey * scaleFactor ;

		//z
		chunkPos = extractNextFloatValue( buffer , chunkPos , fileLength , &fvaluez ) ;
		meshPtr[mcount].z = 	fvaluez * scaleFactor ;
			
	}

	//centers the object
	centerObject(  )  ;


	chunkPos	=  findChunk( "*MESH_FACE_LIST" ,  buffer , chunkPos , fileLength ) ;
	if ( chunkPos <= 0 )
	{
		KMiscTools::messageBox(  "no faces node found! (*MESH_FACE_LIST)" ,0 ) ;
	}
	
	
	meshFacesPtr =  new sMeshFace[_faceCount] ;
	
//	Face 27: A:38 B:37 C:33 
	unsigned long				f1,f2,f3 ;	
	vect_t			v1,v2,v3 ;


	for  ( mcount = 0 ; mcount < _faceCount ; mcount++ )
	{

		chunkPos = findChunk( "*MESH_FACE" , buffer , chunkPos ,  fileLength ) ;
		_snprintf( valuename , 9 , "%d" , mcount ) ;
		chunkPos	= findChunk( valuename , buffer , chunkPos ,  fileLength ) ;		
		chunkPos+=strlen( valuename ) ;

		//triangle ?  
		chunkPos = extractNextLongValue(  buffer , chunkPos , fileLength , &f1) ;
		chunkPos	= extractNextLongValue( buffer , chunkPos , fileLength , &f2 ) ;
		chunkPos = extractNextLongValue( buffer , chunkPos , fileLength , &f3 ) ;
		meshFacesPtr[mcount].pt1 = 	f1;
		meshFacesPtr[mcount].pt2 = 	f2 ;
		meshFacesPtr[mcount].pt3 = 	f3 ;
		
// openGL	v0, v1, v2, 
//pass them to Direct3D as v0, v2, v1. 
	
		v1.X = meshPtr[f1].x ;
		v1.Y = meshPtr[f1].y ;
		v1.Z = meshPtr[f1].z ;

		v2.X = meshPtr[f2].x ;
		v2.Y = meshPtr[f2].y ;
		v2.Z = meshPtr[f2].z ;

		v3.X = meshPtr[f3].x ;
		v3.Y = meshPtr[f3].y ;
		v3.Z = meshPtr[f3].z ;

		//calcul des normales	
		m_GetFaceNormal_vect( &v1  , &v2 , &v3 , &meshFacesPtr[mcount] ) ;

		
	}

	makeGouraud( ) ;

//extracts the texture name
char 	textureName[300];
char 	texturePath[300];
long	l , i ;

	sprintf( texturePath , "%s" , filename ) ;
		
	if ( extractString( buffer , 0 ,fileLength , textureName , 300 ) <= 0 )
	{
		//no texture
		_textureLoaded = false ;
		return true  ;
	}

	l = strlen( textureName ) ;
	if ( l <= 0 )
	{
		extractTextureTable( buffer , fileLength) ;
		//frees the buffer
		delete [] buffer ;
		return true;
	}

	
	i = strlen( texturePath ) ;
	while ( i > 0 )
	{
		if ( texturePath[i] == '\\' || texturePath[i] == ':' ||  texturePath[i] == '/' )		
		{
			texturePath[i] = 0 ;
			break ;
		}
		i-- ;		
	}

	i = strlen( textureName ) ;
	while ( i > 0 )
	{
		if ( textureName[i] == '\\' || textureName[i] == ':' ||  textureName[i] == '/' )		
		{
			break ;
		}
		i-- ;		
	}
	
	memset( _textureFileName , 0 , PTK_MAXPATH ) ;
	strcpy( _textureFileName , textureName ) ;
	
	if ( i > 0 )
	{
		strcat( texturePath , textureName+i ) ;
	}
	else
	{
		strcat( texturePath , "\\"  ) ;
		strcat( texturePath , textureName ) ;	
	}
	

	
	KMiscTools::cleanPath( texturePath ) ;
	
	//loads the texture ( mst be loaded before the textures coordinnates are pulled
	//because rectangular textures work with pixels, not 0-1 range
	if ( _textureLoaded == true )
	{
		surf_texture = (KGraphicD3D*)KPTK::createKGraphic( )  ;

		//MessageBox( 0 , texturePath ,0 , 0 ) ;
		bool	result = surf_texture->loadPicture( texturePath , true, true ); 
		if ( result == false )
		{
			KMiscTools::messageBox( "Could not load texture" , 0 ) ;
		}
	}


	extractTextureTable( buffer , fileLength) ;

	//frees the buffer
	delete [] buffer ;
		
   makeD3DVertexFlat( ) ;
   makeD3DVertexGouraud( ) ;

	
	return true ;
}

//load a ASC Milkshape file
bool		K3Dd3d::loadMk( char		*filename , float		scaleFactor , bool		loadTexture )
{
FILE	*f	;
//float	 f1 ;
char		*buffer , *bufferPtr;
long		i ;

	freeModel( ) ;

	_textureLoaded = loadTexture ;
	
	f = fopen( filename , "rb" ) ;
	if ( f == NULL )	
	{
		KMiscTools::messageBox( "File not found" , filename ) ;
		return false ;
	}
	
	long fileLength ;
	fseek( f , 0 , SEEK_END ) ;
	fileLength = ftell( f ) ;
	fseek( f , 0 , SEEK_SET ) ;
	
	fileLength++ ;	
	buffer = new char[fileLength] ;
	//read the whole file in memory for parsing.
	fread( buffer , 1, fileLength , f ) ;
	fclose( f ) ;
	buffer[fileLength-1] = 0 ;
	
	
	unsigned	long chunkPos = 0  ;
	
	_pointCount = extractLongValue( "object\" 0 0" ,  buffer , 0 , fileLength ) ;
	if ( _pointCount <= 0  )
	{
		KMiscTools::messageBox( "No Vertices" , 0 ) ;
		delete [] buffer ;
		return false ;
	}

	char	valueinText[256] ;
	
	sprintf( valueinText , "%d" , _pointCount ) ;
	
	chunkPos =  findChunk(  "object\" 0 0" , buffer ,0  , fileLength ) ;
	chunkPos =  findChunk(  valueinText , buffer , 0 , fileLength ) ;
	chunkPos+=strlen( valueinText ) ;
	
	bufferPtr = buffer+chunkPos ;
	
	long	index , data ;
	float	x,y,z,u,v ;
	
	//find the end of line
	do	{		bufferPtr++ ;	}while( *bufferPtr != 0x0a );
		  
  	meshPtr = new s3dPoint[_pointCount] ;

	for ( i = 0 ; i <  _pointCount ; i++ )
	{
	//	0 -0.187877 -0.450484 0.108471 0.608471 1.950484 -1
		sscanf( bufferPtr ,"%d %f %f %f %f %f %d" , &index , &x , &y ,&z ,&u , &v , &data ) ;
		
		sprintf(  valueinText ,"%d %f %f %f %f %f %d" , index , x , y ,z ,u , v , data ) ;
		meshPtr[i].x = x*scaleFactor ;
		meshPtr[i].y = y*scaleFactor ;
		meshPtr[i].z = z*scaleFactor ;
		do		{	bufferPtr++ ;	}while( *bufferPtr != 0x0d );
	
	}

	//centers the object
	centerObject(  )  ;
	
	
	//read the number of normals ( we don't need them , but need to skip them)
	
	sscanf( bufferPtr , "%d" , &index ) ;
		
	do		{	bufferPtr++ ;	}while( *bufferPtr != 0x0d );

	for ( i = 0 ; i <  index ; i++ )
	{
		sscanf( bufferPtr ,"%f %f %f" ,  &x , &y ,&z ) ;
		do		{	bufferPtr++ ;	}while( *bufferPtr != 0x0d );
	}

	//reads the number of faces
	sscanf( bufferPtr , "%d" , &index ) ;
	do		{	bufferPtr++ ;	}while( *bufferPtr != 0x0d );
	
	_faceCount = index ;
	if ( _faceCount <= 0 )
	{
		KMiscTools::messageBox( "No faces in this asc" , 0 ) ;
		delete [] buffer ;
		return false ;
	}

	long		 mcount;

	meshFacesPtr =  new sMeshFace[_faceCount] ;
	

	vect_t					v1,v2,v3 ;
	
	//	Face  ID vertex1, vertex2,vertex3, normal1,normal2,normal3, flag 
	long	idx , f1 , f2 , f3 , n1,n2,n3 , id ;
	
	for  ( mcount = 0 ; mcount < _faceCount ; mcount++ )
	{
		sscanf( bufferPtr , "%d %d  %d  %d  %d  %d  %d  %d" , &idx ,&f1 , &f2 , &f3 , &n1,&n2,&n3 , &id ) ;
		do		{	bufferPtr++ ;	}while( *bufferPtr != 0x0d );
		
		meshFacesPtr[mcount].pt1 = 	f1;
		meshFacesPtr[mcount].pt2 = 	f2 ;
		meshFacesPtr[mcount].pt3 = 	f3 ;
		
	
		v1.X = meshPtr[f1].x ;
		v1.Y = meshPtr[f1].y ;
		v1.Z = meshPtr[f1].z ;

		v2.X = meshPtr[f2].x ;
		v2.Y = meshPtr[f2].y ;
		v2.Z = meshPtr[f2].z ;

		v3.X = meshPtr[f3].x ;
		v3.Y = meshPtr[f3].y ;
		v3.Z = meshPtr[f3].z ;

		//calcul des normales	
		m_GetFaceNormal_vect( &v1  , &v2 , &v3 , &meshFacesPtr[mcount] ) ;
	}

	makeGouraud( ) ;
	//loads the texture ( mst be loaded before the textures coordinnates are pulled
	//because rectangular textures work with pixels, not 0-1 range

/*
	

	if ( _textureLoaded == true )
	{
		surf_texture = new KGraphic ;

		bool	result = surf_texture->loadPicture( KMiscTools::makeFilePath( "vjoueur.jpg" ) ) ;
		if ( result == false )
		{
			KMiscTools::messageBox( "Could not load texture" , 0 ) ;
		}
	}

	extractTextureTable( buffer , fileLength) ;
*/
	//frees the buffer
	delete [] buffer ;
		
   makeD3DVertexFlat( ) ;
   makeD3DVertexGouraud( ) ;

	
	return true ;
}

void			K3Dd3d::setShadeMode( EShadeMode		eShadeMode	 ) 
{
	_eShadeMode = eShadeMode  ;
}

//calculate the gouraud normals
void			K3Dd3d::makeGouraud( void )
{
long				fi , pi ;
float				 totalnorms ;
s3dPoint		normal3dpt ;
sMeshFace		*fptr ;

	if ( _faceCount <= 1 )		return ;


	for ( pi = 0 ; pi < _pointCount ; pi++ )
	{
//	#ifdef	K3Dd3dDEBUG
//		sprintf( progress , "gouraud calculation  :  %d/%d" ,pi, _pointCount ) ;
//		KWindow::setTitle( progress ) ;
//	#endif
	
		normal3dpt.x 	= 0 ;
		normal3dpt.y 	= 0 ;
		normal3dpt.z 	= 0 ;
		totalnorms		= 0 ;
		
		//does the average of the normals of the vertex that share a face
		for ( fi = 0 ; fi < _faceCount ; fi++ )
		{	
			fptr =  &meshFacesPtr[fi] ;
			if ( isTouching( pi , fi ) == true )	
			{
			
				normal3dpt.x +=		fptr->nx ;
				normal3dpt.y +=		fptr->ny ;
				normal3dpt.z +=		fptr->nz ;
				totalnorms++ ; 
			}
			
			if ( totalnorms > 0 )
			{
				meshPtr[pi].nx = (normal3dpt.x / totalnorms)  ;
				meshPtr[pi].ny = (normal3dpt.y / totalnorms)  ;
				meshPtr[pi].nz = (normal3dpt.z / totalnorms ) ;

				if ( totalnorms >=2 )	break ;

			}
			else
			{
				meshPtr[pi].nx = fptr->nx   ;
				meshPtr[pi].ny = fptr->ny  ;
				meshPtr[pi].nz = fptr->nz  ;
			}
			
		}
	}
	

}

//precalculates the d3d object
void K3Dd3d::makeD3DVertexFlat( void ) {
   unsigned long		i ;
   s3dPoint	*pointPtr   ;
   sMeshFace	*facePtr ;
   D3DVERTEX *lpCurVertex;

   _lpVertexFlat = new D3DVERTEX [3 * _faceCount];

   lpCurVertex = _lpVertexFlat;
	for ( i =  0 ; i < _faceCount ; i++ )
	{		
		facePtr = &meshFacesPtr[i] ;

      // normal
      D3DVECTOR vNormal = D3DVECTOR (facePtr->nx, facePtr->ny, facePtr->nz);

		//first point of triangle
		pointPtr	= &meshPtr[facePtr->pt1] ; 				
      lpCurVertex[0] = D3DVERTEX(D3DVECTOR (pointPtr->x, pointPtr->y, pointPtr->z),
         D3DVECTOR (facePtr->nx, facePtr->ny, facePtr->nz),      facePtr->texCoords[0].x ,facePtr->texCoords[0].y);
                  
		//second point of the triangle
		pointPtr	= &meshPtr[facePtr->pt2] ; 
	     lpCurVertex[2] = D3DVERTEX(D3DVECTOR (pointPtr->x, pointPtr->y, pointPtr->z),
         D3DVECTOR (facePtr->nx, facePtr->ny, facePtr->nz),    facePtr->texCoords[1].x ,facePtr->texCoords[1].y);

  		//3rd point of the triangle
		pointPtr	= &meshPtr[facePtr->pt3] ; 
	      lpCurVertex[1] = D3DVERTEX(D3DVECTOR (pointPtr->x, pointPtr->y, pointPtr->z),
						         D3DVECTOR (facePtr->nx, facePtr->ny, facePtr->nz),
         						   facePtr->texCoords[2].x ,facePtr->texCoords[2].y);
         
      lpCurVertex += 3;
	}
}


//precalculates the d3d object
void K3Dd3d::makeD3DVertexGouraud( void ) {
   unsigned long		i ;
   s3dPoint	*pointPtr   ;
   sMeshFace	*facePtr ;
   D3DVERTEX *lpCurVertex;

   _lpVertexGouraud = new D3DVERTEX [3 * _faceCount];

   lpCurVertex = _lpVertexGouraud;
	for ( i =  0 ; i < _faceCount ; i++ )
	{		
		facePtr = &meshFacesPtr[i] ;

      // normal
      D3DVECTOR vNormal = D3DVECTOR (facePtr->nx, facePtr->ny, facePtr->nz);

		//first point of triangle
		pointPtr	= &meshPtr[facePtr->pt1] ; 				
      lpCurVertex[0] = D3DVERTEX(D3DVECTOR (pointPtr->x, pointPtr->y, pointPtr->z),
         D3DVECTOR (pointPtr->nx, pointPtr->ny, pointPtr->nz),      facePtr->texCoords[0].x ,facePtr->texCoords[0].y);
                  
		//second point of the triangle
		pointPtr	= &meshPtr[facePtr->pt2] ; 
	     lpCurVertex[2] = D3DVERTEX(D3DVECTOR (pointPtr->x, pointPtr->y, pointPtr->z),
         D3DVECTOR (pointPtr->nx, pointPtr->ny, pointPtr->nz),    facePtr->texCoords[1].x ,facePtr->texCoords[1].y);

  		//3rd point of the triangle
		pointPtr	= &meshPtr[facePtr->pt3] ; 
	      lpCurVertex[1] = D3DVERTEX(D3DVECTOR (pointPtr->x, pointPtr->y, pointPtr->z),
						         D3DVECTOR (pointPtr->nx, pointPtr->ny, pointPtr->nz),
         						   facePtr->texCoords[2].x ,facePtr->texCoords[2].y);
         
      lpCurVertex += 3;
	}
}

//if a face is touching this one
inline	bool			K3Dd3d::isTouching( long	pointIndex , long		faceIndex )
{
sMeshFace		*fptr ;

	fptr = &meshFacesPtr[faceIndex] ;
	
	if (  fptr->pt1 == pointIndex  ) 		return true ;
	if (  fptr->pt2 == pointIndex  ) 		return true ;
	if (  fptr->pt3 == pointIndex  ) 		return true ;

	return false ;
}

//set texture ( not to reload the same texture )
void			K3Dd3d::setTexture( KGraphic *texturePtr )
{
   KGraphicD3D *textureD3DPtr = (KGraphicD3D *) texturePtr;

	if ( _textureLoaded == true &&  surf_texture != NULL )
	{
			delete	surf_texture ;
	}
	
	surf_texture = textureD3DPtr ;
	_textureLoaded = false ;
}

//save in native K3Dd3d format
bool			K3Dd3d::saveK3D( char *filename )
{
sK3DHeader		K3Dd3dh ;

	if ( _faceCount <= 0 )		return false ;

	memset( &K3Dd3dh , 0 , sizeof( sK3DHeader ) );
	K3Dd3dh.tag = 'K3D ' ;
	strcpy( K3Dd3dh.textureFilename , _textureFileName ) ;
	K3Dd3dh._pointCount 	=  _pointCount  ; 
	K3Dd3dh._faceCount 	=  _faceCount  ;
	
	FILE	*f ;
	f = fopen( filename , "wb" ) ;
	if ( f == NULL )		return false ;
	
	fwrite( &K3Dd3dh , sizeof( sK3DHeader ) ,1 , f ) ;
	fwrite( meshPtr , sizeof( s3dPoint ) , _pointCount , f ) ;
	fwrite( meshFacesPtr , sizeof( sMeshFace ) , _faceCount , f ) ;

	fclose( f ) ;

	return true ;
}

//load a native K3Dd3d format
bool			K3Dd3d::loadK3D( char *filename , bool loadTexture)
{
sK3DHeader		K3Dd3dh ;

	freeModel( ) ;
	_textureLoaded = loadTexture ;
	
	memset( &K3Dd3dh , 0 , sizeof( sK3DHeader ) ) ;
	
	FILE	*f ;
	f = fopen( filename , "rb" ) ;
	if ( f == NULL )		return false ;
	
	fread( &K3Dd3dh , sizeof( sK3DHeader ) ,1 , f ) ;
	
	_faceCount 	= KMiscTools::flipLong( K3Dd3dh._faceCount ) ;
	_pointCount 	= KMiscTools::flipLong( K3Dd3dh._pointCount ) ;

	
	strcpy( _textureFileName ,  K3Dd3dh.textureFilename ) ;

	
	if ( _faceCount <= 0 || _pointCount <= 0 )
	{
		MessageBox( 0 , "Error _faceCount <= 0 || _pointCount <= 0",0,0 ) ;
		fclose( f ) ;
		return false ;
	}
	
	meshPtr  = new s3dPoint[_pointCount] ;
	if ( meshPtr == NULL )		
	{
		MessageBox( 0 , "Error meshPtr==NULL",0,0 ) ;
		fclose( f ) ;
		return false ;
	}

	fread( meshPtr , sizeof( s3dPoint ) , _pointCount , f ) ;
	
	
	
	meshFacesPtr  = new sMeshFace[_faceCount] ;
	if ( meshFacesPtr == NULL )		
	{
		MessageBox( 0 , "Error meshFacesPtr==NULL",0,0 ) ;

		fclose( f ) ;
		return false ;
	}

	fread( meshFacesPtr , sizeof( sMeshFace ) , _faceCount , f ) ;

	fclose( f ) ;
	
   makeD3DVertexFlat( ) ;
   makeD3DVertexGouraud( ) ;

//loads the texture if enabled
	if ( _textureLoaded == false )		return true ;
	

//extracts the texture name

char 	textureName[300];
char 	texturePath[300];
long	i ;

	sprintf( texturePath , "%s" , filename ) ;
	
	i = strlen( texturePath ) ;
	while ( i > 0 )
	{
		if ( texturePath[i] == '\\' || texturePath[i] == ':' ||  texturePath[i] == '/' )		
		{
			texturePath[i] = 0 ;
			break ;
		}
		i-- ;		
	}
	
	strcpy( textureName , _textureFileName ) ;
	i = strlen( textureName ) ;
	while ( i > 0 )
	{
		if ( textureName[i] == '\\' || textureName[i] == ':' ||  textureName[i] == '/' )		
		{
			break ;
		}
		i-- ;		
	}

	memset( _textureFileName , 0 , PTK_MAXPATH ) ;
	strcpy( _textureFileName , textureName ) ;
	
	if ( i > 0 )
	{
		strcat( texturePath , textureName+i ) ;
	}
	else
	{
		strcat( texturePath , "\\"  ) ;
		strcat( texturePath , textureName ) ;	
	}

	KMiscTools::cleanPath( texturePath ) ;

	
	surf_texture = (KGraphicD3D*)(KPTK::createKGraphic( ) ) ;	
	bool	result = surf_texture->loadPicture( texturePath ,true,true ); 
	if ( result == false )
	{
		KMiscTools::messageBox( "Could not load texture" , 0 ) ;
	}
 


	return true ;	
}

//build the texture table
void			K3Dd3d::extractTextureTable( char	*buffer , long	bufferLength )
{
long		mcount ;
long		chunkPos , textureCount ;
sTextureCoord		*texturePtr ;
sMeshFace			*oneMeshfacePtr ;

//	rectangularTextures =  KWindow::getRectangleTexCap( ) ;


	chunkPos = 0 ;
	
	textureCount = extractLongValue( "*MESH_NUMTVERTEX" ,  buffer , chunkPos , bufferLength ) ;
	if ( textureCount <= 0 )
	{
		//no textures
		return  ;	
	}
	
	texturePtr = new sTextureCoord[textureCount] ;
	//generates the texture table with U and V
	float		tc1 ;
	//extract textures coordinnates
	chunkPos = findChunk( "*MESH_TVERTLIST" , buffer , chunkPos ,  bufferLength ) ;
	
	char		valuename[10] ;
	
	for  ( mcount = 0 ; mcount < textureCount ; mcount++ )
	{
//		#ifdef	K3Dd3dDEBUG
//			sprintf( progress , "textures coordinates  calculation  :  %d/%d" ,mcount, textureCount ) ;
//			KWindow::setTitle( progress ) ;
//		#endif
	
		chunkPos = findChunk( "*MESH_TVERT" , buffer , chunkPos ,  bufferLength ) ;
		_snprintf( valuename , 9 , "%d" , mcount ) ;
		chunkPos	= findChunk( valuename , buffer , chunkPos ,  bufferLength ) ;		
		chunkPos+=strlen( valuename ) ;

	//	chunkPos = extractNextFloatValue(  buffer , chunkPos , bufferLength , &tc1) ;
	
		//triangle ?  
		chunkPos = extractNextFloatValue(  buffer , chunkPos , bufferLength , &tc1) ;
		texturePtr[mcount].u = 	tc1;
		
		chunkPos	= extractNextFloatValue( buffer , chunkPos , bufferLength , &tc1 ) ;
		texturePtr[mcount].v = 	tc1 ;		
	}

	long	textureFaceCount = extractLongValue( "*MESH_NUMTVFACES " , buffer , chunkPos , bufferLength ) ;
	
	if ( textureFaceCount > _faceCount )
	{
		KMiscTools::messageBox( "Texture mapping count doesn't match polygon count" , 0 ) ;
	}
	
	//jumps to the TFACE List.
	chunkPos = findChunk( "*MESH_TFACELIST" , buffer , chunkPos ,  bufferLength ) ;
	
	unsigned long		p1,p2,p3 ;

	for  ( mcount = 0 ; mcount < _faceCount ; mcount++ )
	{
//		#ifdef	K3Dd3dDEBUG
//			sprintf( progress , "textures initialization for each face  :  %d/%d" ,mcount, _faceCount ) ;
//			KWindow::setTitle( progress ) ;
//		#endif
		
			oneMeshfacePtr = &meshFacesPtr[mcount] ;
			oneMeshfacePtr->texCoords[0].x =	0 ;
			oneMeshfacePtr->texCoords[0].y = 0 ;
			oneMeshfacePtr->texCoords[1].x =	0 ;
			oneMeshfacePtr->texCoords[1].y = 0 ;
			oneMeshfacePtr->texCoords[2].x =	0 ;
			oneMeshfacePtr->texCoords[2].y = 0 ;
	}
		
	for  ( mcount = 0 ; mcount < textureFaceCount ; mcount++ )
	{
//		#ifdef	K3Dd3dDEBUG
//			sprintf( progress , "texture mapping  for each face  :  %d/%d" ,mcount, textureFaceCount ) ;
//			KWindow::setTitle( progress ) ;
//		#endif


		chunkPos = findChunk( "*MESH_TFACE" , buffer , chunkPos ,  bufferLength ) ;
		_snprintf( valuename , 9 , "%d" , mcount ) ;
		chunkPos	= findChunk( valuename , buffer , chunkPos ,  bufferLength ) ;		
		chunkPos	+=strlen( valuename ) ;
	
		//gets the texture coordinnates index
		chunkPos = extractNextLongValue( buffer , chunkPos , bufferLength , &p1 ) ;
		chunkPos = extractNextLongValue( buffer , chunkPos , bufferLength , &p2 ) ;
		chunkPos = extractNextLongValue( buffer , chunkPos , bufferLength , &p3 ) ;
		
		
		
		if ( mcount < _faceCount )
		{
			oneMeshfacePtr = &meshFacesPtr[mcount] ;
			oneMeshfacePtr->texCoords[0].x = texturePtr[p1].u ;
			oneMeshfacePtr->texCoords[0].y = 1-texturePtr[p1].v ;
			oneMeshfacePtr->texCoords[1].x = texturePtr[p2].u ;
			oneMeshfacePtr->texCoords[1].y = 1-texturePtr[p2].v ;
			oneMeshfacePtr->texCoords[2].x = texturePtr[p3].u ;
			oneMeshfacePtr->texCoords[2].y = 1-texturePtr[p3].v ;
		}
	
	}
	
	

	delete	[]	texturePtr ;
	texturePtr = NULL ;
}

//ectracts a long
unsigned	long		K3Dd3d::extractLongValue ( char *chunkName , char *dataPtr , long startposition  , long bufferlen )
{
char		valueText[260] ;
long		chunkPos , chunkDelimiter ;
long		value , i , l ;
/*
  Mesh dolph02
  {
  285;
*/
	memset( valueText , 0 , 260 ) ;
	
	chunkPos =  findChunk( chunkName ,  dataPtr , startposition , bufferlen ) ;
	
	chunkPos+=strlen( chunkName ) ;
	//chunkPos =  findChunk( ":" ,  dataPtr , chunkPos , bufferlen ) ;


	//find the start of the value now ( can be a minus  or a number )
	do
	{
		if ( dataPtr[chunkPos] == '-' )		break ;
		if ( dataPtr[chunkPos] == '0' )		break ;
		if ( dataPtr[chunkPos] == '1' )		break ;
		if ( dataPtr[chunkPos] == '2' )		break ;
		if ( dataPtr[chunkPos] == '3' )		break ;
		if ( dataPtr[chunkPos] == '4' )		break ;
		if ( dataPtr[chunkPos] == '5' )		break ;
		if ( dataPtr[chunkPos] == '6' )		break ;
		if ( dataPtr[chunkPos] == '7' )		break ;
		if ( dataPtr[chunkPos] == '8' )		break ;
		if ( dataPtr[chunkPos] == '9' )		break ;
		chunkPos++ ;
		if ( chunkPos >= bufferlen )		return -1 ;
	}while( true ) ;

	chunkDelimiter = findChunk( " " ,  dataPtr , chunkPos , bufferlen ) ;

	strncpy( valueText , dataPtr+chunkPos , (chunkDelimiter-chunkPos) ) ;
	l = strlen( valueText ) ;
	if ( l <= 0 )		return 0 ;
	
	for( i = 0 ; i < l ; i++ )
	{
		if ( valueText[i] == 0x0a || valueText[i] == 0x0d  )		valueText[i] = 0 ;
	}

	value = atol( valueText ) ;
	
	return 	value ;
}

inline	unsigned long		K3Dd3d::extractNextFloatValue ( char *dataPtr , long startposition  , long bufferlen , float	*floatValue )
{
char		valueText[260] ;
long		chunkPos , chunkDelimiter ;
long		  l ;
float		value ;

	memset( valueText , 0 , 260 ) ;
	
	chunkPos =  startposition ;



	//find the start of the value now ( can be a minus  or a number )
	do
	{
		if ( dataPtr[chunkPos] == '-' )		break ;
		if ( dataPtr[chunkPos] == '0' )		break ;
		if ( dataPtr[chunkPos] == '1' )		break ;
		if ( dataPtr[chunkPos] == '2' )		break ;
		if ( dataPtr[chunkPos] == '3' )		break ;
		if ( dataPtr[chunkPos] == '4' )		break ;
		if ( dataPtr[chunkPos] == '5' )		break ;
		if ( dataPtr[chunkPos] == '6' )		break ;
		if ( dataPtr[chunkPos] == '7' )		break ;
		if ( dataPtr[chunkPos] == '8' )		break ;
		if ( dataPtr[chunkPos] == '9' )		break ;
		chunkPos++ ;
		if ( chunkPos >= bufferlen )		return -1 ;
	}while( true ) ;

	//find the end of the value now ( can be a minus  or a number )
	chunkDelimiter = chunkPos ;

	do
	{
		chunkDelimiter++ ;
		if ( chunkDelimiter >= bufferlen )		return -1 ;

		if ( dataPtr[chunkDelimiter] == '.' )		continue ;
		if ( dataPtr[chunkDelimiter] == '-' )		continue ;
		if ( dataPtr[chunkDelimiter] == '0' )		continue ;
		if ( dataPtr[chunkDelimiter] == '1' )		continue ;
		if ( dataPtr[chunkDelimiter] == '2' )		continue ;
		if ( dataPtr[chunkDelimiter] == '3' )		continue ;
		if ( dataPtr[chunkDelimiter] == '4' )		continue ;
		if ( dataPtr[chunkDelimiter] == '5' )		continue ;
		if ( dataPtr[chunkDelimiter] == '6' )		continue ;
		if ( dataPtr[chunkDelimiter] == '7' )		continue ;
		if ( dataPtr[chunkDelimiter] == '8' )		continue ;
		if ( dataPtr[chunkDelimiter] == '9' )		continue ;
		
		break ;
	}while( true ) ;


	strncpy( valueText , dataPtr+chunkPos , (chunkDelimiter-chunkPos) ) ;
	
	valueText[chunkDelimiter-chunkPos] = 0 ;
	
	l = strlen( valueText ) ;
	if ( l <= 0 )		return 0 ;
	
	
	
	value = (float)atof( valueText ) ;

	*floatValue = value ;
	
	return 	chunkDelimiter ;
}
//*BITMAP "E:\Cr_ation\Darkfusion\models\Vaisseaujoueur\v_joueur.jpg"
unsigned long		K3Dd3d::extractString ( char *dataPtr , long startposition  , long bufferlen ,  char *destBuffer , long lendestBuffer)
{
long		cpdep,cpend ;
char		extractedString[512] ;
		
		memset( extractedString , 0 , 512 ) ;
		
		cpdep = findChunk( "*BITMAP" , dataPtr , startposition , bufferlen ) ;
		if ( cpdep < 0 )	return 0 ;
		cpdep = findChunk( "\"" , dataPtr , cpdep , bufferlen ) ;
		cpend = findChunk( "\"" , dataPtr , cpdep+1 , bufferlen ) ;
		
		strncpy( extractedString ,dataPtr+cpdep+1 ,  cpend-(cpdep+1)  ) ;
		_snprintf( destBuffer , 	lendestBuffer , "%s" , extractedString ) ;
		return cpend-cpdep ;
}

inline		unsigned long		K3Dd3d::extractNextLongValue ( char *dataPtr , long startposition  , long bufferlen , unsigned long	*longValue )
{
char		valueText[260] ;
long		chunkPos , chunkDelimiter ;
long		  l ;
unsigned long		value ;

	memset( valueText , 0 , 260 ) ;
	
	chunkPos =  startposition ;



	//find the start of the value now ( can be a minus  or a number )
	do
	{
		if ( dataPtr[chunkPos] == '-' )		break ;
		if ( dataPtr[chunkPos] == '0' )		break ;
		if ( dataPtr[chunkPos] == '1' )		break ;
		if ( dataPtr[chunkPos] == '2' )		break ;
		if ( dataPtr[chunkPos] == '3' )		break ;
		if ( dataPtr[chunkPos] == '4' )		break ;
		if ( dataPtr[chunkPos] == '5' )		break ;
		if ( dataPtr[chunkPos] == '6' )		break ;
		if ( dataPtr[chunkPos] == '7' )		break ;
		if ( dataPtr[chunkPos] == '8' )		break ;
		if ( dataPtr[chunkPos] == '9' )		break ;
		chunkPos++ ;
		if ( chunkPos >= bufferlen )		return -1 ;
	}while( true ) ;

	//find the end of the value now ( can be a minus  or a number )
	chunkDelimiter = chunkPos ;

	do
	{
		chunkDelimiter++ ;
		if ( chunkDelimiter >= bufferlen )		return -1 ;

		if ( dataPtr[chunkDelimiter] == '.' )		continue ;
		if ( dataPtr[chunkDelimiter] == '-' )		continue ;
		if ( dataPtr[chunkDelimiter] == '0' )		continue ;
		if ( dataPtr[chunkDelimiter] == '1' )		continue ;
		if ( dataPtr[chunkDelimiter] == '2' )		continue ;
		if ( dataPtr[chunkDelimiter] == '3' )		continue ;
		if ( dataPtr[chunkDelimiter] == '4' )		continue ;
		if ( dataPtr[chunkDelimiter] == '5' )		continue ;
		if ( dataPtr[chunkDelimiter] == '6' )		continue ;
		if ( dataPtr[chunkDelimiter] == '7' )		continue ;
		if ( dataPtr[chunkDelimiter] == '8' )		continue ;
		if ( dataPtr[chunkDelimiter] == '9' )		continue ;
		
		break ;
	}while( true ) ;


	strncpy( valueText , dataPtr+chunkPos , (chunkDelimiter-chunkPos) ) ;
	
	valueText[chunkDelimiter-chunkPos] = 0 ;
	
	l = strlen( valueText ) ;
	if ( l <= 0 )		return 0 ;
	
	
	
	value = atol( valueText ) ;

	*longValue = value ;
	
	return 	chunkDelimiter ;
}

//centers the object
void				K3Dd3d::centerObject( void ) 
{
s3dPoint		ptMin, ptMax , ptMedian , *ptPtr;
unsigned long				i ;


	if ( _pointCount <= 0 )		return ;
	
	ptMin.x = 0 ;
	ptMin.y = 0 ;
	ptMin.z = 0 ;

	ptMax.x = 0 ;
	ptMax.y = 0 ;
	ptMax.z = 0 ;

	for ( i = 0 ; i < _pointCount ; i++ )
	{
		ptPtr = &meshPtr[i] ;
		//find the minimal and maximal points
		if ( ptPtr->x <  ptMin.x )		ptMin.x = ptPtr->x ;
		if ( ptPtr->y <  ptMin.y )		ptMin.y = ptPtr->y ;
		if ( ptPtr->z <  ptMin.z )		ptMin.z = ptPtr->z ;

		if ( ptPtr->x >  ptMax.x )		ptMax.x = ptPtr->x ;
		if ( ptPtr->y >  ptMax.y )		ptMax.y = ptPtr->y ;
		if ( ptPtr->z >  ptMax.z )		ptMax.z = ptPtr->z ;
	}

	ptMedian.x 	= ( ptMax.x + ptMin.x  ) /2 ;
	ptMedian.y 	= ( ptMax.y + ptMin.y  ) /2 ;
	ptMedian.z		= ( ptMax.z + ptMin.z  ) /2 ;
	
	//ok we now have min and max points. we really center the model
	for ( i = 0 ; i < _pointCount ; i++ )
	{
		ptPtr = &meshPtr[i] ;
		
		ptPtr->x -= ptMedian.x ;
		ptPtr->y -= ptMedian.y ;
		ptPtr->z -= ptMedian.z ;
	}
	

	
}

//find the start of a chunk
inline		unsigned	long		K3Dd3d::findChunk( char *chunkName , char *dataPtr , long startposition  , long bufferlen )
{
unsigned 	long		i , j  ;
unsigned 	long		scanUntil , lentoscan;


	scanUntil = bufferlen - strlen( chunkName ) ;
	if ( scanUntil <= 0 )		
	{
		KMiscTools::messageBox( "Missing chunk" , chunkName ) ;
		return -1 ;
	}
	
	lentoscan = strlen( chunkName ) ;
	
	for ( i = startposition ; i < scanUntil ; i++ )
	{
		for ( j = 0 ; j < lentoscan ; j++ )
		{
			if ( 	strncmp( chunkName ,  dataPtr+i , lentoscan )	== 0 )		return  i ;
		}	
	}


	return -1 ;
}

/*
*MESH_NUMVERTEX 468
		*MESH_NUMFACES 901
*/
//frees the memory allocated by the X
void		K3Dd3d::freeModel( void )
{
   if ( _lpVertexFlat !=    NULL )
   {
      delete [] _lpVertexFlat;
      _lpVertexFlat = NULL;
   }

   if ( _lpVertexGouraud !=    NULL )
   {
      delete [] _lpVertexGouraud;
      _lpVertexGouraud = NULL;
   }

	if ( meshPtr 	!= 	NULL )
	{
		delete	[]	meshPtr  ;
		meshPtr = NULL ;
	}

	if ( meshFacesPtr 	!= 	NULL )
	{
		delete	[]	meshFacesPtr  ;
		meshFacesPtr = NULL ;
	}

	if ( surf_texture != NULL && _textureLoaded == true )
	{
		delete	surf_texture ;
		surf_texture = NULL ;
	}
	
	
	_pointCount 		=	0;
	_faceCount			=	0 ;
}


/*
//sunHP helpers
double Norme(vect_t v)
{
    return sqrt(v.X*v.X + v.Y*v.Y + v.Z*v.Z);
}

inline			void Normalize(vect_t *pVect)
{
   float length, len;
   length = (float)Norme(*pVect);
   len=1.0f/length;
   pVect->X *= len;
   pVect->Y *= len;
   pVect->Z *= len;
}

float PdtScalaire(vect_t *pVect1, vect_t *pVect2)
{
   return (pVect1->X*pVect2->X + pVect1->Y*pVect2->Y + pVect1->Z*pVect2->Z);
}

void PdVectoriel(vect_t *Vres, vect_t *v1, vect_t *v2)
{
   Vres->X = (v1->Y * v2->Z) - (v1->Z * v2->Y);
   Vres->Y = (v1->Z * v2->X) - (v1->X * v2->Z);
   Vres->Z = (v1->X * v2->Y) - (v1->Y * v2->X);
}

void	 m_GetFaceNormal_vect(vect_t *Vec0, vect_t *Vec1, vect_t *Vec2 , sMeshFace 	*faceptr)
{
   vect_t    p, q, n;

   p.X = Vec1->X - Vec0->X;
   p.Y = Vec1->Y - Vec0->Y;
   p.Z = Vec1->Z - Vec0->Z;
       
   q.X = Vec2->X - Vec0->X;  
   q.Y = Vec2->Y - Vec0->Y;  
   q.Z = Vec2->Z - Vec0->Z;  
       
   PdVectoriel(&n,&p,&q);
   Normalize(&n);

	faceptr->nx = n.X ;
	faceptr->ny = n.Y ;
	faceptr->nz = n.Z ;
}
*/