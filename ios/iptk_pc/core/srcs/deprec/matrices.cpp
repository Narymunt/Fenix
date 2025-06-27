#include <math.h>
#define D3D_OVERLOADS
#define DIRECT3D_VERSION 0x0700
#include <d3d.h>
#include	<d3dxmath.h>

void	setPerpectiveDx( D3DMATRIX *mat , float x, float y, float znear, float zfar )  ;


#define  M_PI        3.14159265358979323846f
#define  M_2PI       (2.0f * M_PI)

void 	identity(D3DMATRIX &mat) ;
void 	ortho(D3DMATRIX *mat, float width, float height, float znear, float zfar) ;
void 	translate(D3DMATRIX &mat, float x, float y, float z) ;
void 	scale(D3DMATRIX &mat, float x, float y, float z) ;
void 	rotatex(D3DMATRIX &mat, float angle) ;
void 	rotatey(D3DMATRIX &mat, float angle) ;
void 	rotatez(D3DMATRIX &mat, float angle) ;
D3DVECTOR operator* (const D3DVECTOR &p, const D3DMATRIX &M)  ;
 void scalemat(D3DMATRIX &mat, float x, float y, float z) ;
 void identity500(D3DMATRIX *mat) ;
void	setPerpectiveDxNatural( D3DMATRIX *mat , float fovy, float aspect, float znear, float zfar ) ;

// sets a matrix to identity
void identity(D3DMATRIX &mat)
{

	ZeroMemory(&mat, sizeof(mat));
	mat(0,0) = 1;
	mat(1,1) = 1;
	mat(2,2) = 1;
	mat(3,3) = 1;

}


// sets this matrix to a 2D orthographic matrix
void ortho(D3DMATRIX *mat, float width, float height, float znear, float zfar)
{


	ZeroMemory( mat, sizeof(mat));

D3DXMATRIX	d3dxMat ;

 D3DXMatrixOrthoLH( &d3dxMat , width , height , znear , zfar ) ;	

 mat->m[0][0] =d3dxMat.m00  ;
 mat->m[0][1]=d3dxMat.m01  ;
 mat->m[0][2]=d3dxMat.m02  ;
 mat->m[0][3] =d3dxMat.m03  ;

 mat->m[1][0]=d3dxMat.m10  ;
 mat->m[1][1]=d3dxMat.m11  ;
 mat->m[1][2]=d3dxMat.m12  ;
 mat->m[1][3]=d3dxMat.m13  ;

 mat->m[2][0]=d3dxMat.m20  ;
 mat->m[2][1]=d3dxMat.m21  ;
 mat->m[2][2]=d3dxMat.m22  ;
 mat->m[2][3]=d3dxMat.m23  ;

 mat->m[3][0]=d3dxMat.m30  ;
 mat->m[3][1]=d3dxMat.m31  ;
 mat->m[3][2]=d3dxMat.m32  ;
 mat->m[3][3]=d3dxMat.m33  ; 

}




void	setPerpectiveDxNatural( D3DMATRIX *mat , float fovy, float aspect, float znear, float zfar ) 
{

	ZeroMemory( mat, sizeof(mat));

D3DXMATRIX	d3dxMat ;

D3DXMatrixPerspectiveFovLH( &d3dxMat , fovy, aspect, znear, zfar ) ;
  
 mat->m[0][0] =d3dxMat.m00  ;
 mat->m[0][1]=d3dxMat.m01  ;
 mat->m[0][2]=d3dxMat.m02  ;
 mat->m[0][3] =d3dxMat.m03  ;

 mat->m[1][0]=d3dxMat.m10  ;
 mat->m[1][1]=d3dxMat.m11  ;
 mat->m[1][2]=d3dxMat.m12  ;
 mat->m[1][3]=d3dxMat.m13  ;

 mat->m[2][0]=d3dxMat.m20  ;
 mat->m[2][1]=d3dxMat.m21  ;
 mat->m[2][2]=d3dxMat.m22  ;
 mat->m[2][3]=d3dxMat.m23  ;

 mat->m[3][0]=d3dxMat.m30  ;
 mat->m[3][1]=d3dxMat.m31  ;
 mat->m[3][2]=d3dxMat.m32  ;
 mat->m[3][3]=d3dxMat.m33  ; 

}


void	setPerpectiveDx( D3DMATRIX *mat , float x, float y, float znear, float zfar ) 
{

	ZeroMemory( mat, sizeof(mat));

D3DXMATRIX	d3dxMat ;


  D3DXMatrixPerspectiveOffCenterLH(&d3dxMat, -x, x, -y, y,znear, zfar);
  
 mat->m[0][0] =d3dxMat.m00  ;
 mat->m[0][1]=d3dxMat.m01  ;
 mat->m[0][2]=d3dxMat.m02  ;
 mat->m[0][3] =d3dxMat.m03  ;

 mat->m[1][0]=d3dxMat.m10  ;
 mat->m[1][1]=d3dxMat.m11  ;
 mat->m[1][2]=d3dxMat.m12  ;
 mat->m[1][3]=d3dxMat.m13  ;

 mat->m[2][0]=d3dxMat.m20  ;
 mat->m[2][1]=d3dxMat.m21  ;
 mat->m[2][2]=d3dxMat.m22  ;
 mat->m[2][3]=d3dxMat.m23  ;

 mat->m[3][0]=d3dxMat.m30  ;
 mat->m[3][1]=d3dxMat.m31  ;
 mat->m[3][2]=d3dxMat.m32  ;
 mat->m[3][3]=d3dxMat.m33  ; 

}
   
// sets this matrix to a 2D orthographic matrix
void identity500(D3DMATRIX *mat)
{

	ZeroMemory( mat, sizeof(mat));

D3DXMATRIX	d3dxMat ;
D3DXMatrixIdentity( &d3dxMat );

//D3DXMatrixOrtho( &d3dxMat , 1,1,-1,1 ) ;

 mat->m[0][0] =d3dxMat.m00  ;
 mat->m[0][1]=d3dxMat.m01  ;
 mat->m[0][2]=d3dxMat.m02  ;
 mat->m[0][3] =d3dxMat.m03  ;

 mat->m[1][0]=d3dxMat.m10  ;
 mat->m[1][1]=d3dxMat.m11  ;
 mat->m[1][2]=d3dxMat.m12  ;
 mat->m[1][3]=d3dxMat.m13  ;

 mat->m[2][0]=d3dxMat.m20  ;
 mat->m[2][1]=d3dxMat.m21  ;
 mat->m[2][2]=d3dxMat.m22  ;
 mat->m[2][3]=d3dxMat.m23  ;

 mat->m[3][0]=d3dxMat.m30  ;
 mat->m[3][1]=d3dxMat.m31  ;
 mat->m[3][2]=d3dxMat.m32  ;
 mat->m[3][3]=d3dxMat.m33  ; 

}

// translation matrix
 void translate(D3DMATRIX &mat, float x, float y, float z)
{
	identity(mat);
	mat(3,0) = x;
	mat(3,1) = y;
	mat(3,2) = z;
}

// scale matrix
 void scale(D3DMATRIX &mat, float x, float y, float z)
{
	identity(mat);
	mat(0,0) = x;
	mat(1,1) = y;
	mat(2,2) = z;
}

 void scalemat(D3DMATRIX &mat, float x, float y, float z)
{
	identity(mat);
	mat(0,0) = x*mat(0,0);
	mat(1,1) = y*mat(1,1);
	mat(2,2) = z*mat(2,2);
}
// rotation x matrix
 void rotatex(D3DMATRIX &mat, float angle)
{
	angle = (M_2PI*angle) /360.0f ;

	identity(mat);
	mat(1,1) = cosf(angle);
	mat(1,2) = sinf(angle);
	mat(2,1) = -sinf(angle);
	mat(2,2) = cosf(angle);
}

// rotation y matrix
 void rotatey(D3DMATRIX &mat, float angle)
{
	angle = (M_2PI*angle) /360.0f ;

	identity(mat);
	mat(0,0) = cosf(angle);
	mat(0,2) = -sinf(angle);
	mat(2,0) = sinf(angle);
	mat(2,2) = cosf(angle);
}

// rotation z matrix
 void rotatez(D3DMATRIX &mat, float angle)
{

	angle = (M_2PI*angle) /360.0f ;
	identity(mat);
	mat(0,0) = cosf(angle);
	mat(0,1) = sinf(angle);
	mat(1,0) = -mat(0,1);
	mat(1,1) = mat(0,0);
}

D3DVECTOR operator* (const D3DVECTOR &p, const D3DMATRIX &M) 
{
  double x, y, z;
  float w;
  x = M(0,0) * p.x + M(1,0) * p.y + M(2,0) * p.z + M(3,0) * 1;
  y = M(0,1) * p.x + M(1,1) * p.y + M(2,1) * p.z + M(3,1) * 1;
  z = M(0,2) * p.x + M(1,2) * p.y + M(2,2) * p.z + M(3,2) * 1;
  w = M(0,3) * p.x + M(1,3) * p.y + M(2,3) * p.z + M(3,3) * 1;


  if (w) {  // Normalize if possible.  W has got to be 1
    float inv = 1.0f / w;
    return D3DVECTOR(x * inv, y * inv, z * inv);
  } else
    return D3DVECTOR(x, y, z);  
}

