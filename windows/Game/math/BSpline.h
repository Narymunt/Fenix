#pragma once

#include <vector>
#include <list>
#include "EquationSystem.h"


class BSpline
{

public:
	BSpline();

	void reset();

	void addPoint(float x, float y);
	void calculateSpline(bool linear = false);
	
   float getXPoint(float t);
	float getYPoint(float t);

	bool getNextPoint(float &x, float &y, float &t); // goes one arclength

	int getMaxT() { return (int)mXPoints.size() - 1; }

	std::vector<float> mXPoints;
	std::vector<float> mYPoints;
	std::vector<float> mArcLengths;
	std::vector<float> mXCoef;
	std::vector<float> mYCoef;

	float getPoint(float t, std::vector<float> &theCoef);

	void calculateSplinePrv(std::vector<float> &thePoints, std::vector<float> &theCoef);
	void calculateSplinePrvLinear(std::vector<float> &thePoints, std::vector<float> &theCoef);
	void calculateSplinePrvSemiLinear(std::vector<float> &thePoints, std::vector<float> &theCoef);
	void calcArcLengths();

};

