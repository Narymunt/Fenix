#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include	<d3dxmath.h>



#define  M_PI        3.14159265358979323846f
#define  M_2PI       (2.0f * M_PI)

void 	identity(D3DMATRIX *mat) ;
void identity500(D3DMATRIX *mat) ;

 void 	ortho(D3DXMATRIX *mat, long width, long height, float znear, float zfar) ;
void 	translate(D3DMATRIX *mat, float x, float y, float z) ;
void 	scale(D3DMATRIX *mat, float x, float y, float z) ;
void 	rotatex(D3DMATRIX *mat, float angle) ;
void 	rotatey(D3DMATRIX *mat, float angle) ;
void 	rotatez(D3DMATRIX *mat, float angle) ;
D3DVECTOR operator* (const D3DVECTOR &p, const D3DMATRIX &M)  ;
 void scalemat(D3DMATRIX *mat, float x, float y, float z) ;

// sets a matrix to identity
void identity(D3DMATRIX *mat)
{
D3DXMATRIX		d3dxmatrix ;
D3DMATRIX			*d3dmatrix ;

	D3DXMatrixIdentity( &d3dxmatrix  ) ;

	d3dmatrix = (D3DMATRIX*)&d3dxmatrix ;
	
	memcpy( mat , d3dmatrix , sizeof( D3DMATRIX ) ) ;
/*
	_maryMatrix.matrix[0][0] = d3dxmatrix._11;
	_maryMatrix.matrix[1][0] = d3dxmatrix._21;
	_maryMatrix.matrix[2][0] = d3dxmatrix._31;
	_maryMatrix.matrix[3][0] = d3dxmatrix._41;

	_maryMatrix.matrix[0][1] = d3dxmatrix._12;
	_maryMatrix.matrix[1][1] = d3dxmatrix._22;
	_maryMatrix.matrix[2][1] = d3dxmatrix._32;
	_maryMatrix.matrix[3][1] = d3dxmatrix._42;

	_maryMatrix.matrix[0][2] = d3dxmatrix._13;
	_maryMatrix.matrix[1][2] = d3dxmatrix._23;
	_maryMatrix.matrix[2][2] = d3dxmatrix._33;
	_maryMatrix.matrix[3][2] = d3dxmatrix._43;

	_maryMatrix.matrix[0][3] = d3dxmatrix._14;
	_maryMatrix.matrix[1][3] = d3dxmatrix._24;
	_maryMatrix.matrix[2][3] = d3dxmatrix._34;
	_maryMatrix.matrix[3][3] = d3dxmatrix._44;
*/

}


// sets this matrix to a 2D orthographic matrix
void ortho(D3DXMATRIX *mat, long width, long height, float znear, float zfar)
{
	D3DXMatrixOrthoLH( mat , (float)width , (float)height , znear , zfar ) ;	
}




   
// sets this matrix to a 2D orthographic matrix
void identity500(D3DMATRIX *mat)
{

D3DXMATRIX		d3dxmatrix ;
D3DMATRIX			*d3dmatrix ;

	D3DXMatrixIdentity( &d3dxmatrix  ) ;

	d3dmatrix = (D3DMATRIX*)&d3dxmatrix ;
	
	memcpy( mat , d3dmatrix , sizeof( D3DMATRIX ) ) ;

}

// translation matrix
 void translate(D3DMATRIX *mat, float x, float y, float z)
{
	identity(mat);
//	mat(3,0) = x;
//	mat(3,1) = y;
//	mat(3,2) = z;
}

// scale matrix
 void scale(D3DMATRIX *mat, float x, float y, float z)
{
	identity(mat);
//	mat(0,0) = x;
//	mat(1,1) = y;
//	mat(2,2) = z;
}

 void scalemat(D3DMATRIX *mat, float x, float y, float z)
{
	identity(mat);
//	mat(0,0) = x*mat(0,0);
//	mat(1,1) = y*mat(1,1);
//	mat(2,2) = z*mat(2,2);
}
// rotation x matrix
 void rotatex(D3DMATRIX *mat, float angle)
{
	angle = (M_2PI*angle) /360.0f ;

	identity(mat);
//	mat(1,1) = cosf(angle);
//	mat(1,2) = sinf(angle);
//	mat(2,1) = -sinf(angle);
//	mat(2,2) = cosf(angle);
}

// rotation y matrix
 void rotatey(D3DMATRIX *mat, float angle)
{
	angle = (M_2PI*angle) /360.0f ;

	identity(mat);
//	mat(0,0) = cosf(angle);
//	mat(0,2) = -sinf(angle);
//	mat(2,0) = sinf(angle);
//	mat(2,2) = cosf(angle);
}

// rotation z matrix
 void rotatez(D3DMATRIX *mat, float angle)
{

	angle = (M_2PI*angle) /360.0f ;
	identity(mat);
//	mat(0,0) = cosf(angle);
//	mat(0,1) = sinf(angle);
//	mat(1,0) = -mat(0,1);
//	mat(1,1) = mat(0,0);
}

D3DVECTOR operator* (const D3DVECTOR &p, const D3DMATRIX &M) 
{
 // double x, y, z;
  //float w;
 /*
 x = M(0,0) * p.x + M(1,0) * p.y + M(2,0) * p.z + M(3,0) * 1;
  y = M(0,1) * p.x + M(1,1) * p.y + M(2,1) * p.z + M(3,1) * 1;
  z = M(0,2) * p.x + M(1,2) * p.y + M(2,2) * p.z + M(3,2) * 1;
  w = M(0,3) * p.x + M(1,3) * p.y + M(2,3) * p.z + M(3,3) * 1;


  if (w) {  // Normalize if possible.  W has got to be 1
    float inv = 1.0f / w;
    return D3DVECTOR(x * inv, y * inv, z * inv);
  } else
    return D3DVECTOR(x, y, z);  
*/
	return p ;
	}

