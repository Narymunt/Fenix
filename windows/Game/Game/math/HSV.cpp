#include <math.h>

void hsv2rgb(float h, float s, float v, unsigned char *r, unsigned char *g, unsigned char *b)
{
   float fr,fg,fb;

   while (h<0.0) 
      h += 360.0;
   
   while (h>=360.0) 
      h -= 360.0;

   if (s==0.0) 
   {
      fr=v;
      fg=v;
      fb=v;
   }
   else
   {
      float f,p,q,t;
      float i;

      h /= 60.0;
      i = (float)floor(h);
      f = h - i;
      p = (float)(v * (1.0-s));
      q = (float)(v * (1.0-(s*f)));
      t = (float)(v * (1.0-(s*(1.0-f))));

      int o = (int)i;
      switch(o) 
      {
         case 0: fr=v; fg=t; fb=p; break;
         case 1: fr=q; fg=v; fb=p; break;
         case 2: fr=p; fg=v; fb=t; break;
         case 3: fr=p; fg=q; fb=v; break;
         case 4: fr=t; fg=p; fb=v; break;
         case 5: fr=v; fg=p; fb=q; break;
      } // switch
   }

   int ir,ig,ib;

   ir=(int)fr;
   ig=(int)fg;
   ib=(int)fb;
   
   if (ir>255) ir = 255;
   if (ig>255) ig = 255;
   if (ib>255) ib = 255;

   *r = (unsigned char) ir;
   *g = (unsigned char) ig;
   *b = (unsigned char) ib;
}

void rgb2hsv(float r,float g,float b,float* h,float* s,float* v)
{
   float max,min;

   if (r>g)
      max = r;
   else
      max = g;

   if (b>max)
      max = b;

   if (r<g)
      min = r;
   else
      min = g;

   if (b<min)
      min = b;

   *v = max;

   *s = 0.0;
   if (max != 0.0)
      *s = ((max-min)/max);

   if (*s == 0.0)
      *h = -1;
   else {
      float delta = max - min;
      float maxr = max - r;
      float maxg = max - g;
      float maxb = max - b;

      if (r == max)
         *h = ((maxb)-(maxg)) / delta;
      else if (g == max)
         *h = (float)(2.0 + (((maxr)-(maxb)) / delta));
      else if (b == max)
         *h = (float)(4.0 + (((maxg)-(maxr)) / delta));

      *h *= 60.0;
      while (*h < 0.0)
         *h += 360.0;
      while (*h >= 360.0)
         *h -= 360.0;
   } 
}



