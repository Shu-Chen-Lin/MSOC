// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic_phase array holds the angle for the current rotation
// cordic_phase[0] =~ 0.785
// cordic_phase[1] =~ 0.463

//void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
void cordic(volatile float* Theta, volatile float* S, volatile float* C)
//void cordic(volatile float Theta[NUM_DEGREE], volatile float S[NUM_DEGREE], volatile float C[NUM_DEGREE])
{
	THETA_TYPE theta;
	COS_SIN_TYPE s, c;

	for (int i=0; i<NUM_DEGREE;i++){
		theta = Theta[i];

		// Set the initial vector that we will rotate
		// current_cos = I; current_sin = Q
		COS_SIN_TYPE current_cos = 0.60735;
		COS_SIN_TYPE current_sin = 0.0;

		COS_SIN_TYPE factor = 1.0;

		// This loop iteratively rotates the initial vector to find the
		// sine and cosine values corresponding to the input theta angle
		for (int j = 0; j < NUM_ITERATIONS; j++) {
		      // Determine if we are rotating by a positive or negative angle
		      int sigma = (theta < 0) ? -1 : 1;

		      // Multiply previous iteration by 2^(-j)
		      COS_SIN_TYPE cos_shift = current_cos * sigma * factor;
		      COS_SIN_TYPE sin_shift = current_sin * sigma * factor;

		      // Perform the rotation
		      current_cos = current_cos - sin_shift;
		      current_sin = current_sin + cos_shift;

		      // Determine the new theta
		      theta = theta - sigma * cordic_phase[j];

		      factor = factor / 2;
		  }

		  // Set the final sine and cosine values
		  S[i] = current_sin;  C[i] = current_cos;
	}
}
