#pragma once

#include <vector>
#include <list>

class CSpline
{

public:
	CSpline();

	void Reset();

	void AddPoint(float x, float y);
	void CalculateSpline(bool linear = false);
	
   float GetXPoint(float t);
	float GetYPoint(float t);

	bool GetNextPoint(float &x, float &y, float &t); // goes one arclength

	int GetMaxT() { return (int)mXPoints.size() - 1; }

protected:
	
   std::vector<float> mXPoints;
	std::vector<float> mYPoints;
	std::vector<float> mArcLengths;
	std::vector<float> mXCoef;
	std::vector<float> mYCoef;

	float GetPoint(float t, std::vector<float> &theCoef);

   void CalculateSplinePrv(std::vector<float> &thePoints, std::vector<float> &theCoef);
	void CalculateSplinePrvLinear(std::vector<float> &thePoints, std::vector<float> &theCoef);
	void CalculateSplinePrvSemiLinear(std::vector<float> &thePoints, std::vector<float> &theCoef);
	void CalcArcLengths();

};

