
#include	<windows.h>
#include <math.h>

#include <d3d9.h>
#include	<d3dx9.h>

extern	void 	identity(D3DMATRIX *mat) ;
extern	void		 identity500(D3DMATRIX *mat) ;

extern	void 	ortho(D3DMATRIX *mat, float width, float height, float znear, float zfar) ;
extern	void 	translate(D3DMATRIX *mat, float x, float y, float z) ;
extern	void 	scale(D3DMATRIX *mat, float x, float y, float z) ;
extern	void 	rotatex(D3DMATRIX *mat, float angle) ;
extern	void 	rotatey(D3DMATRIX *mat, float angle) ;
extern	void 	rotatez(D3DMATRIX *mat, float angle) ;


