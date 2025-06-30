
#pragma warning(disable : 4244)


float fHermite(float p1,float p2,float r1,float r2,float t) 
{
  return p1*( 2.0*(t*t*t)-3.0*(t*t)+1.0)+
         r1*(     (t*t*t)-2.0*(t*t)+t  )+
         p2*(-2.0*(t*t*t)+3.0*(t*t)    )+
         r2*(     (t*t*t)-    (t*t)    );
}

