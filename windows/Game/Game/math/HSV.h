#pragma once

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void hsv2rgb(float h, float s, float v, unsigned char *r, unsigned char *g, unsigned char *b);
void rgb2hsv(float r,float g,float b,float* h,float* s,float* v);

