#include	<windows.h>
#include	"KSpline.h"

#define	B1(t)		(t*t)
#define	B2(t)		(2*t*(1-t))
#define	B3(t)		((1-t)*(1-t))


KSpline::KSpline( ) 
{

}


KSpline::~KSpline( ) 
{

}


//methode avec 1 point de controle unique
void		KSpline::getPointFromCtrlPoint( KPoint	*kPoint , KPoint	*controlP1, KPoint	*controlP2 , KPoint	*controlP3 , double position) 
{
double	b1,b2,b3 ;

	if ( kPoint == NULL )		return ;
	
	b1 = B1(position ) ;
	b2 = B2(position ) ;
	b3 = B3(position ) ;
	
	kPoint->x  = 	controlP1->x*b1 	+ controlP2->x*b2 + controlP3->x*b3;
	kPoint->y 	= 	controlP1->y*b1 	+ controlP2->y*b2 + controlP3->y*b3;
}


//position = position
void		KSpline::getPoint( KPoint	*kPoint , double	x1,double y1	,double	x2,double y2 , double coefX1 , double coefY1 , double coefX2 , double coefY2 , double position) 
{
double a ;
double b ;

	if ( kPoint == NULL )		return ;

	a = 1-position ;
 	b = position;

	// Get a point on the curve
	kPoint->x 	= (x1*a*a*a + coefX1*3*a*a*b + coefX2*3*a*b*b + x2*b*b*b) ;
	kPoint->y	= (y1*a*a*a + coefY1*3*a*a*b + coefY2*3*a*b*b + y2*b*b*b) ;
	

}



