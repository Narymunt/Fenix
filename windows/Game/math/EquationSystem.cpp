#pragma warning(disable:4305)
#pragma warning(disable:4244)

#include "EquationSystem.h"
#include <math.h>


EquationSystem::EquationSystem(int theNumVariables)
{
	mRowSize = theNumVariables + 1;
	mCurRow = 0;
	eqs.resize(mRowSize * theNumVariables);
	sol.resize(theNumVariables);
}

void EquationSystem::SetCoefficient(int theRow, int theCol, float theValue)
{
	int anIndex = mRowSize*theRow + theCol;
	
	eqs[anIndex] = theValue;
}

void EquationSystem::SetConstantTerm(int theRow, float theValue)
{
	int anIndex = mRowSize*theRow + mRowSize-1;
		
	eqs[anIndex] = theValue;
}

void EquationSystem::Solve()
{
   int i, j, k, max, r, N;
   float temp;

   r = mRowSize;
   N = mRowSize - 1;

//   CheckRanges();

   //first do triangulation
   for(i=0;i<N;i++) 
   {
	   // Find maximum element in column i
       max = i;
       for(j=i+1;j<N;j++)
           if( fabs(eqs[j*r+i]) > fabs(eqs[max*r+i]) ) max = j;

	   // Swap row with maximum element with row i
	   for(k=0;k<N+1;k++) 
		   std::swap(eqs[i*r+k],eqs[max*r+k]);

	   // Zero out column i in all lower rows by subtracting a multiple of row i from each lower row
		for(j=i+1;j<N;j++) 
		{
			float mult = eqs[j*r+i] / eqs[i*r+i];
			if (mult==0)
				continue;

			for(k=N;k>=i;k--) 
				eqs[j*r+k] -= eqs[i*r+k] * mult;
		}
   }

   //now do the back substitution
   for(j=N-1;j>=0;j--) 
   {
       temp=0;
       for(k=j+1; k<N; k++)
           temp += eqs[j*r+k] * sol[k];
   
	   sol[j] = (eqs[j*r+N] - temp) / eqs[j*r+j];
   }
}
