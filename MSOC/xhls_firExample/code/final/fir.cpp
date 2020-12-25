#include "fir.h"

//out_data_t fir_filter (inp_data_t x,   coef_t c[N])
void fir_filter(volatile float* In, volatile int coef[N], volatile float* y)
{


  static inp_data_t shift_reg[N];


  acc_t mult, acc;
  //out_data_t y;
  inp_data_t x;
  coef_t c[N];
  ap_fixed<32,17> temp;


  fir_filter_label1:for (int k=0; k<SAMPLES; k++){
	  x = In[k];
	  acc = 0;
	  Shift_Accum_Loop: for (int i=N-1;i>=0;i--)
	    {
	  #pragma HLS LOOP_TRIPCOUNT min=1 max=16 avg=8

	       if (i==0)
	       {
	         //acc+=x*c[0];
	         shift_reg[0]=x;
	       }
	       else
	       {
	  			shift_reg[i]=shift_reg[i-1];
	  			//acc+=shift_reg[i]*c[i];
	       }
	       temp = (ap_fixed <32,17>)(coef[i])>>16;
	       mult = shift_reg[i]*temp;
	       acc  = acc + mult;

	    }
	  y[k] = acc;
  }


  //y = (out_data_t) acc;

  //return y;

}
