#pragma once

#include <vector>
#include <list>

class EquationSystem
{
public:
	typedef std::vector<int> IntVector;

	std::vector<float> eqs;
	std::vector<float> sol;

	int mRowSize;
	int mCurRow;

public:
	EquationSystem(int theNumVariables);

	void SetCoefficient(int theRow, int theCol, float theValue);
	void SetConstantTerm(int theRow, float theValue);

	void SetCoefficient(int theCol, float theValue) { SetCoefficient(mCurRow, theCol, theValue); }
	void SetConstantTerm(float theValue) { SetConstantTerm(mCurRow, theValue); }
	void NextEquation() { mCurRow++; }

	void Solve();
	void CheckRanges();
};
