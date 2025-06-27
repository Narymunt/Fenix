#define 	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER

#include	"K3D.h"
#include	"K3DGL.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	"KWindowGL.h"
#include	"KMiscTools.h"
#include	<Math.h>
#include 		"glati.h"

#define	K3DDEBUG

float			K3DGL::_screenWidth = 640;
float			K3DGL::_screenHeight = 480 ;
bool			K3DGL::_useScreenRes = false ;

struct		vect_t
{
	double		X,Y,Z ;
};

double 	Norme(vect_t v) ;
void 		Normalize(vect_t *pVect) ;
double 		PdtScalaire(vect_t *pVect1, vect_t *pVect2) ;
void 		PdVectoriel(vect_t *Vres, vect_t *v1, vect_t *v2) ;
void		m_GetFaceNormal_vect(vect_t *Vec0, vect_t *Vec1, vect_t *Vec2 , sMeshFace 	*faceptr) ;


K3D::K3D( ) 
{
}

K3D::~K3D()
{
}

K3DGL::K3DGL( ) 
{
		 _scaleX = 1 ;
		 _scaleY = 1 ;
		 _scaleZ = 1 ;
		 _textureLoaded = false ;
		 
		surf_texture		= NULL ;
		meshPtr 			= 	NULL ;
		meshFacesPtr  	= 	NULL ;
		_pointCount 		=	0;
		_faceCount		=	0 ;

		_eShadeMode 	= ESM_FLAT ;
		_blend				= false ;
		_blendFactor 		= 1 ;

		setAlphaMode( true ) ;
}

K3DGL::~K3DGL( ) 
{
	
	freeModel( ) ;
}

void	K3DGL::initK3D( long	width , long height )
{
   return;

	_screenWidth 	= (float)width ;
	_screenHeight 	= (float)height ;


	glViewport(0,0,(int)_screenWidth,(int)_screenHeight);							// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window

	//	gluPerspective(45.0f,  (GLfloat)width/(GLfloat)height    ,0.1f,100.0f);

	//setPerspective((double)45.0f, (double)( _screenWidth/_screenHeight)   ,(double)0.1f,(double)100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();		
	
	//init gl
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	
	
}


void		K3DGL::setPerspective( double  fovy, double aspect, double zNear, double zFar )
{
double	 x , y ;
	
	y = tan(fovy/360 * K_PI)*zNear ;
	x = y*aspect  ;
	glFrustum(-x, x, -y, y, zNear, zFar );
	
}
 
void		K3DGL::beginScene( bool	clearScene , bool useScreenResolution ) 
{
GLfloat LightAmbient[]= {1,1,1};
GLfloat LightPosition[]= {1,1,1 , 1.0f};	
GLfloat LightDiffuse[]= { 1,1,1, 1.0f };


	glFlush( ) ;
	glViewport(0,0,(int)_screenWidth,(int)_screenHeight);							// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
//	gluPerspective(45.0f,(GLfloat)_screenWidth/(GLfloat)_screenHeight,0.1f,100.0f);

		setPerspective((double)45.0f, (double)( _screenWidth/_screenHeight)   ,(double)0.1f,(double)500);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();								

	//init gl
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	if ( clearScene == true )
	{
		glClear(  GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	}
	
	glLoadIdentity();									// Reset The Current Modelview Matrix


	
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);

	glEnable(GL_LIGHTING) ;
	glEnable(GL_LIGHT1);

	_useScreenRes = useScreenResolution ;

	if ( useScreenResolution == true )
	{
		
		 glMatrixMode(GL_PROJECTION);      
		 glLoadIdentity();
		 glOrtho(0, _screenWidth ,0, _screenHeight , -500 , 500 );
		 glMatrixMode(GL_MODELVIEW);

		 glLoadIdentity();
	}

}

void		K3DGL::endScene( void ) 
{
	glDisable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_LIGHTING) ;
	glViewport(0,0,(int)_screenWidth,(int)_screenHeight);							// Reset The Current Viewport

}


void		K3DGL::scale( float	sx , float sy , float sz  )
{
	_scaleX = sx ;
	_scaleY = sy ;
	_scaleZ = sz ;
}

//position an object
void		K3DGL::displayFlat( float	x , float y , float z  , float	rx , float ry , float rz  ) 
{
static	GLfloat		rtri = 0 ;
unsigned long		i ;
s3dPoint	*pointPtr   ;
sMeshFace	*facePtr ;

	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	if ( _useScreenRes == true )
	{
		glTranslatef( x,_screenHeight-y,z );					
	}
	else
	{
		glTranslatef( x , y,z );						
	}

	if ( _scaleX != 1 || _scaleY != 1 || _scaleZ != 1 )
	{
		glScalef( _scaleX, _scaleY , _scaleZ ) ;
	}

	if ( rx!=0 )		{glRotatef( rx ,1,0,0 ) ;}
	if ( ry!=0 )		{glRotatef( ry ,0,1,0 ) ;}
	if ( rz!=0 )		{glRotatef( rz ,0,0,1 ) ;}


	if ( _blend == true )
	{
		glEnable( GL_BLEND ) ;
	}
	else
	{
		glDisable( GL_BLEND ) ;	
	}
	
	glBlendFunc(  _sourceAlpha , _destAlpha  );	
	

	if  ( surf_texture != NULL )
	{
		surf_texture->selectTexture( ) ;
	}
	else
	{
		glDisable( GL_TEXTURE_2D ) ;
		glDisable( GL_TEXTURE_RECTANGLE_NV ) ;
	}
	

	glEnable( GL_COLOR ) ;
 	glShadeModel(GL_FLAT);
	glDisable(GL_COLOR_MATERIAL);
	
	glColor4f( 1,1,1,1);	
		
	glBegin(GL_TRIANGLES);					

	//draw
	for ( i =  0 ; i < _faceCount ; i++ )
	{		
		facePtr = &meshFacesPtr[i] ;
		
		//normal for light
		glNormal3f( facePtr->nx, facePtr->ny , facePtr->nz  ) ;
	
		//first point of triangle
		pointPtr	= &meshPtr[facePtr->pt1] ; 				

		glTexCoord2f( facePtr->texCoords[0].x ,facePtr->texCoords[0].y );
		glVertex3f( pointPtr->x, pointPtr->y , pointPtr->z ) ;

		//second point of the triangle
		pointPtr	= &meshPtr[facePtr->pt2] ; 
		glTexCoord2f( facePtr->texCoords[1].x ,facePtr->texCoords[1].y );
		glVertex3f( pointPtr->x, pointPtr->y , pointPtr->z ) ;

		//3rd point of the triangle
		pointPtr	= &meshPtr[facePtr->pt3] ; 
		glTexCoord2f( facePtr->texCoords[2].x ,facePtr->texCoords[2].y );
		glVertex3f( pointPtr->x, pointPtr->y , pointPtr->z ) ;
			
	}

	glEnd();								// Start Drawing A Triangle


//	glColor3f(1.0f,1.0f,1.0f);	
	
}

//position an object
void		K3DGL::display( float	x , float y , float z , float	rx , float ry , float rz  ) 
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
void		K3DGL::displayGouraud( float	x , float y , float z , float	rx , float ry , float rz  )
{
static	GLfloat		rtri = 0 ;
unsigned long		i ;
s3dPoint	*pointPtr   ;
sMeshFace	*facePtr ;

	glLoadIdentity();									// Reset The Current Modelview Matrix
			
	if ( _useScreenRes == true )
	{
		glTranslatef( x,_screenHeight-y,z );					
	}
	else
	{
		glTranslatef( x , y,z );						
	}

	if ( _scaleX != 1 || _scaleY != 1 || _scaleZ != 1 )
	{
		glScalef( _scaleX, _scaleY , _scaleZ ) ;
	}
	
	if ( rx!=0 )		{glRotatef( rx ,1,0,0 ) ;}
	if ( ry!=0 )		{glRotatef( ry ,0,1,0 ) ;}
	if ( rz!=0 )		{glRotatef( rz ,0,0,1 ) ;}

	if ( _blend == true )
	{
		glEnable( GL_BLEND ) ;
	}
	else
	{
		glDisable( GL_BLEND ) ;	
	}
	
	glBlendFunc(  _sourceAlpha , _destAlpha  );	
	
	if  ( surf_texture != NULL )
	{
		surf_texture->selectTexture( ) ;
	}
	else
	{
//		KWindow::setTitle( "texture missing" ) ;
		glDisable( GL_TEXTURE_2D ) ;
		glDisable( GL_TEXTURE_RECTANGLE_NV ) ;	
	}
	
		
	glEnable( GL_COLOR ) ;
 	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	
	
	glColor4f( 0.7,0.7,0.7,1);	
	

	
	glBegin(GL_TRIANGLES);					

	//draw
	for ( i =  0 ; i < _faceCount ; i++ )
	{
		
		facePtr = &meshFacesPtr[i] ;
		

		//first point of triangle
		pointPtr	= &meshPtr[facePtr->pt1] ; 				

		glNormal3f( pointPtr->nx, pointPtr->ny , pointPtr->nz  ) ;
		glTexCoord2f( facePtr->texCoords[0].x ,facePtr->texCoords[0].y );
		glVertex3f( pointPtr->x, pointPtr->y , pointPtr->z ) ;

		//second point of the triangle
		pointPtr	= &meshPtr[facePtr->pt2] ; 

		glNormal3f( pointPtr->nx, pointPtr->ny , pointPtr->nz  ) ;
		glTexCoord2f( facePtr->texCoords[1].x ,facePtr->texCoords[1].y );
		glVertex3f( pointPtr->x, pointPtr->y , pointPtr->z ) ;

		//3rd point of the triangle
		pointPtr	= &meshPtr[facePtr->pt3] ; 
		glNormal3f( pointPtr->nx, pointPtr->ny , pointPtr->nz  ) ;
		glTexCoord2f( facePtr->texCoords[2].x ,facePtr->texCoords[2].y );
		glVertex3f( pointPtr->x, pointPtr->y , pointPtr->z ) ;
			
	}
	
	glEnd();								// Start Drawing A Triangle

	glColor4f( 1,1,1,1);	

//	glColor3f(1.0f,1.0f,1.0f);	
	
}

//regular == true pour TGA  false pour additif
void		K3DGL::setAlphaMode( bool	regular )
{
	if ( regular == false )
	{
		_sourceAlpha 	=  GL_SRC_ALPHA ;
		_destAlpha		=	GL_DST_ALPHA ;
	}
	else
	{
		_sourceAlpha 	=  GL_SRC_ALPHA ;
		_destAlpha		=	GL_ONE_MINUS_SRC_ALPHA ;
	}
	
}

//enables alpha blending
void		K3DGL::enableBlending( bool	allowBlend , float	blendFactor )
{
	_blend 			= allowBlend ;
	_blendFactor 	= blendFactor ;
}

//load a ASE file
bool		K3DGL::load( char		*filename , float		scaleFactor , bool		loadTexture )
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
	float		fvalue ;
	char		valuename[50] ;
	memset( valuename ,0 , 50 ) ;
	chunkPos = findChunk( "*MESH_VERTEX_LIST" , buffer , 0 ,  fileLength ) ; ;

//char	progress[256] ;

	//reads all the mesh
	for  ( mcount = 0 ; mcount  <  _pointCount ; mcount++ )
	{
		#ifdef	K3DDEBUG
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
		chunkPos = extractNextFloatValue( buffer , chunkPos , fileLength , &fvalue ) ;
		meshPtr[mcount].y = 	fvalue * scaleFactor ;

		//z
		chunkPos = extractNextFloatValue( buffer , chunkPos , fileLength , &fvalue ) ;
		meshPtr[mcount].z = 	fvalue * scaleFactor ;
			
	}

	//centers the object
	centerObject(  )  ;


	chunkPos	=  findChunk( "*MESH_FACE_LIST" ,  buffer , chunkPos , fileLength ) ;
	if ( chunkPos <= 0 )
	{
		KMiscTools::messageBox(  "no faces node found! (*MESH_FACE_LIST)" ,0 ) ;
	}
	
//	#ifdef	K3DDEBUG
//		sprintf( progress , "face count :  %d" , _faceCount ) ;
//		KWindow::setTitle( progress ) ;
//	#endif
	
	meshFacesPtr =  new sMeshFace[_faceCount] ;
	
//	Face 27: A:38 B:37 C:33 
	unsigned long				f1,f2,f3 ;	
	vect_t			v1,v2,v3 ;


	for  ( mcount = 0 ; mcount < _faceCount ; mcount++ )
	{
//		#ifdef	K3DDEBUG
//			sprintf( progress , "loading faces  :  %d / %d" , mcount , _faceCount ) ;
//			KWindow::setTitle( progress ) ;
//		#endif

		chunkPos = findChunk( "*MESH_FACE" , buffer , chunkPos ,  fileLength ) ;
		_snprintf( valuename , 9 , "%d" , mcount ) ;
		chunkPos	= findChunk( valuename , buffer , chunkPos ,  fileLength ) ;		
		chunkPos+=strlen( valuename ) ;

		//triangle ?  
		chunkPos = extractNextLongValue(  buffer , chunkPos , fileLength , &f1) ;
		meshFacesPtr[mcount].pt1 = 	f1;
		
		chunkPos	= extractNextLongValue( buffer , chunkPos , fileLength , &f2 ) ;
		meshFacesPtr[mcount].pt2 = 	f2 ;

		chunkPos = extractNextLongValue( buffer , chunkPos , fileLength , &f3 ) ;
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
		surf_texture = new KGraphicGL ;

		//MessageBox( 0 , texturePath ,0 , 0 ) ;
		bool	result = surf_texture->loadPicture( texturePath , false, true ); 
		if ( result == false )
		{
			KMiscTools::messageBox( "Could not load texture" , 0 ) ;
		}
	}


	extractTextureTable( buffer , fileLength) ;

	//frees the buffer
	delete [] buffer ;
		

	
	return true ;
}

//load a ASC Milkshape file
bool		K3DGL::loadMk( char		*filename , float		scaleFactor , bool		loadTexture )
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
		

	
	return true ;
}

void			K3DGL::setShadeMode( EShadeMode		eShadeMode	 ) 
{
	_eShadeMode = eShadeMode  ;
}

//calculate the gouraud normals
void			K3DGL::makeGouraud( void )
{
long				fi , pi ;
float				 totalnorms ;
s3dPoint		normal3dpt ;
sMeshFace		*fptr ;
//char				progress[256];

	if ( _faceCount <= 1 )		return ;


	for ( pi = 0 ; pi < _pointCount ; pi++ )
	{
//	#ifdef	K3DDEBUG
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
				meshPtr[pi].nx = normal3dpt.x / totalnorms  ;
				meshPtr[pi].ny = normal3dpt.y / totalnorms  ;
				meshPtr[pi].nz = normal3dpt.z / totalnorms  ;

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

//if a face is touching this one
inline	bool			K3DGL::isTouching( long	pointIndex , long		faceIndex )
{
sMeshFace		*fptr ;

	fptr = &meshFacesPtr[faceIndex] ;
	
	if (  fptr->pt1 == pointIndex  ) 		return true ;
	if (  fptr->pt2 == pointIndex  ) 		return true ;
	if (  fptr->pt3 == pointIndex  ) 		return true ;

	return false ;
}

//set texture ( not to reload the same texture )
void			K3DGL::setTexture( KGraphic*texturePtr )
{
	if ( _textureLoaded == true &&  surf_texture != NULL )
	{
			delete	surf_texture ;
	}
	
	surf_texture = texturePtr ;
	_textureLoaded = false ;
}

//save in native k3d format
bool			K3DGL::saveK3D( char *filename )
{
sK3DHeader		k3dh ;

	if ( _faceCount <= 0 )		return false ;

	memset( &k3dh , 0 , sizeof( sK3DHeader ) );
	k3dh.tag = 'k3d ' ;
	strcpy( k3dh.textureFilename , _textureFileName ) ;
	k3dh._pointCount 	=  _pointCount  ; 
	k3dh._faceCount 	=  _faceCount  ;
	
	FILE	*f ;
	f = fopen( filename , "wb" ) ;
	if ( f == NULL )		return false ;
	
	fwrite( &k3dh , sizeof( sK3DHeader ) ,1 , f ) ;
	fwrite( meshPtr , sizeof( s3dPoint ) , _pointCount , f ) ;
	fwrite( meshFacesPtr , sizeof( sMeshFace ) , _faceCount , f ) ;

	fclose( f ) ;

	return true ;
}

//load a native k3d format
bool			K3DGL::loadK3D( char *filename , bool loadTexture)
{
sK3DHeader		k3dh ;

	freeModel( ) ;
	_textureLoaded = loadTexture ;
	
	memset( &k3dh , 0 , sizeof( sK3DHeader ) ) ;
	
	FILE	*f ;
	f = fopen( filename , "rb" ) ;
	if ( f == NULL )		return false ;
	
	fread( &k3dh , sizeof( sK3DHeader ) ,1 , f ) ;
	
	_faceCount 	= KMiscTools::flipLong( k3dh._faceCount ) ;
	_pointCount 	= KMiscTools::flipLong( k3dh._pointCount ) ;

	
	strcpy( _textureFileName ,  k3dh.textureFilename ) ;

	
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

	
	surf_texture = new KGraphicGL ;	
	bool	result = surf_texture->loadPicture( texturePath ,true,true ); 
	if ( result == false )
	{
		KMiscTools::messageBox( "Could not load texture" , 0 ) ;
	}
 


	return true ;	
}

//build the texture table
void			K3DGL::extractTextureTable( char	*buffer , long	bufferLength )
{
long		mcount ;
long		chunkPos , textureCount ;
sTextureCoord		*texturePtr ;
sMeshFace			*oneMeshfacePtr ;
//bool						rectangularTextures ;
//char						progress[256] ;

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
//		#ifdef	K3DDEBUG
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
//		#ifdef	K3DDEBUG
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
//		#ifdef	K3DDEBUG
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
unsigned	long		K3DGL::extractLongValue ( char *chunkName , char *dataPtr , long startposition  , long bufferlen )
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

inline	unsigned long		K3DGL::extractNextFloatValue ( char *dataPtr , long startposition  , long bufferlen , float	*floatValue )
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
unsigned long		K3DGL::extractString ( char *dataPtr , long startposition  , long bufferlen ,  char *destBuffer , long lendestBuffer)
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

inline		unsigned long		K3DGL::extractNextLongValue ( char *dataPtr , long startposition  , long bufferlen , unsigned long	*longValue )
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
void				K3DGL::centerObject( void ) 
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
inline		unsigned	long		K3DGL::findChunk( char *chunkName , char *dataPtr , long startposition  , long bufferlen )
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
void		K3DGL::freeModel( void )
{
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

double	 PdtScalaire(vect_t *pVect1, vect_t *pVect2)
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