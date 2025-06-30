#pragma warning(disable:4305)
#pragma warning(disable:4244)

#include "BSpline.h"
#include <math.h>

BSpline::BSpline()
{
}

void BSpline::reset()
{
	mXPoints.clear();
	mYPoints.clear();
	mArcLengths.clear();
	mXCoef.clear();
	mYCoef.clear();
}

void BSpline::addPoint(float x, float y)
{
	mXPoints.push_back(x);
	mYPoints.push_back(y);
}

void BSpline::calcArcLengths()
{
	mArcLengths.clear();

	int numCurves = (int)mXPoints.size()-1;
	for (int i=0; i<numCurves; i++)
	{
		float x1 = mXPoints[i];
		float y1 = mYPoints[i];

		float x2 = mXPoints[i+1];
		float y2 = mYPoints[i+1];

		float aLength = sqrtf((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
		mArcLengths.push_back(aLength);
	}
}

bool BSpline::getNextPoint(float &x, float &y, float &t)
{
	int anIndex = floorf(t);
	if (anIndex<0 || anIndex>=(int)mXPoints.size()-1)
	{
		x = getXPoint(t);
		y = getYPoint(t);
		return false;
	}

	float aLength = 1 / (mArcLengths[anIndex]*100);
	float ox = getXPoint(t);
	float oy = getYPoint(t);
	float nt = t;
	float nx,ny;

	while (true)
	{
		nt += aLength;
		nx = getXPoint(nt);
		ny = getYPoint(nt);

		float dist = (nx-ox)*(nx-ox) + (ny-oy)*(ny-oy);
		if (dist >= 1.0f)
			break;

		if (nt > mXPoints.size()-1)
			break;
	}

	x = nx;
	y = ny;
	t = nt;
	return true;
}

void BSpline::calculateSplinePrv(std::vector<float> &thePoints, std::vector<float> &theCoef)
{
	if(thePoints.size()<2)
		return;

	int numCurves = (int)thePoints.size()-1;
	int numVariables = numCurves*4;

	int i;

	EquationSystem aSystem(numVariables);

	// c0 = 0 // derivative 0 at first point
	aSystem.SetCoefficient(2,1);
	aSystem.NextEquation();

	int c = 0;
	for (i=0; i<numCurves; i++, c+=4)
	{
		// d0 = p0
		aSystem.SetCoefficient(c+3,1);
		aSystem.SetConstantTerm(thePoints[i]);
		aSystem.NextEquation();

		// a0 + b0 + c0 = p1 - p0
		aSystem.SetCoefficient(c,1);
		aSystem.SetCoefficient(c+1,1);
		aSystem.SetCoefficient(c+2,1);
		aSystem.SetConstantTerm(thePoints[i+1] - thePoints[i]);
		aSystem.NextEquation();

		// 3a0 + 2b0 + c0 - c1 = 0
		aSystem.SetCoefficient(c,3);
		aSystem.SetCoefficient(c+1,2);
		aSystem.SetCoefficient(c+2,1);
		if (i<numCurves-1) 
			aSystem.SetCoefficient(c+6,-1);

		aSystem.NextEquation();

		// 6a0 + 2b0 - 2b1 = 0;
		if (i<numCurves-1)
		{
			aSystem.SetCoefficient(c,6);
			aSystem.SetCoefficient(c+1,2);
			aSystem.SetCoefficient(c+5,-2);
			aSystem.NextEquation();
		}
	}
	aSystem.Solve();
	theCoef = aSystem.sol;
}

void BSpline::calculateSplinePrvSemiLinear(std::vector<float> &thePoints, std::vector<float> &theCoef)
{
	if(thePoints.size()<2)
		return;

	int numCurves = (int)thePoints.size()-1;

	int i;
	std::vector<float> aNewPoints;

	// Add curve points
	for (i=0; i<numCurves; i++)
	{
		float mix = mArcLengths[i];
		if (mix <= 100)
			mix = 1;
		else
			mix = 100/mix;

		mix = 0.3f;
	
		float p1 = thePoints[i];
		float p2 = thePoints[i+1];
		if (i>0)
			aNewPoints.push_back(mix*p2 + (1-mix)*p1);
		else
			aNewPoints.push_back(p1);

		if (i<numCurves-1)
			aNewPoints.push_back(mix*p1 + (1-mix)*p2);
		else
			aNewPoints.push_back(p2);		
	}
	thePoints = aNewPoints;


	numCurves = (int)aNewPoints.size()-1;
	theCoef.resize(numCurves*4);
	for (i=0; i<numCurves; i++)
	{
		float p1 = aNewPoints[i];
		float p2 = aNewPoints[i+1];

		int c = i*4;

		if ((i&1) && i<numCurves-1)
		{
			float p0 = aNewPoints[i-1];
			float p3 = aNewPoints[i+2];
			float A,B,C,D;

			D = p1;
			C = p1-p0; // derivative of first curve
			A = -2*(p2-2*p1+p0)-C+(p3-p2);
			B = -A + p2-2*p1+p0;

			theCoef[c] = A;			
			theCoef[c+1] = B;		
			theCoef[c+2] = C;	
			theCoef[c+3] = D;		
		}
		else // straight line
		{
			theCoef[c] = 0;			// A = 0
			theCoef[c+1] = 0;		// B = 0
			theCoef[c+2] = p2-p1;	// C = p2-p1
			theCoef[c+3] = p1;		// D = p1
		}
	}

}

void BSpline::calculateSplinePrvLinear(std::vector<float> &thePoints, std::vector<float> &theCoef)
{
	if(thePoints.size()<2)
		return;

	int numCurves = (int)thePoints.size()-1;
	theCoef.resize(numCurves*4);
	for (int i=0; i<numCurves; i++)
	{
		int c = i*4;

		float p1 = thePoints[i];
		float p2 = thePoints[i+1];

		theCoef[c] = 0;			// A = 0
		theCoef[c+1] = 0;		// B = 0
		theCoef[c+2] = p2-p1;	// C = p2-p1
		theCoef[c+3] = p1;		// D = p1
	}

}

void BSpline::calculateSpline(bool linear)
{
	calcArcLengths();
	
	if (linear)
	{
		calculateSplinePrvLinear(mXPoints,mXCoef);
		calculateSplinePrvLinear(mYPoints,mYCoef);
	}
	else
	{
		calculateSplinePrv(mXPoints,mXCoef);
		calculateSplinePrv(mYPoints,mYCoef);
	}
	calcArcLengths();
}

float BSpline::getPoint(float t, std::vector<float> &theCoef)
{
	int anIndex = floorf(t);
	if (anIndex<0)
	{
		anIndex = 0;
		t = 0;
	}
	else if(anIndex>=(int)mXPoints.size()-1)
	{
		anIndex = (int)mXPoints.size()-2;
		t = anIndex+1;
	}

	float s = t-anIndex;
	anIndex*=4;

	float A = theCoef[anIndex];
	float B = theCoef[anIndex+1];
	float C = theCoef[anIndex+2];
	float D = theCoef[anIndex+3];
	float s2 = s*s;
	float s3 = s2*s;

	return A*s3 + B*s2 + C*s + D;
}

float BSpline::getXPoint(float t)
{
	return getPoint(t,mXCoef);
}

float BSpline::getYPoint(float t)
{
	return getPoint(t,mYCoef);
}

