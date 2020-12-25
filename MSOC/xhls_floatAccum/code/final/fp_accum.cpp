/************************************************
Copyright (c) 2016, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software 
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ap_int.h>
#include <ap_fixed.h>

#define NUM_ELEM 128

void hls_fp_accumulator(float window0[NUM_ELEM], int* Out)
//float hls_fp_accumulator(float window0[NUM_ELEM])
{

	float window1[NUM_ELEM/2] = {0.0};
	float window2[NUM_ELEM/4] = {0.0};
	float window3[NUM_ELEM/8] = {0.0};
	float window4[NUM_ELEM/16]= {0.0};
	float window5[NUM_ELEM/32]= {0.0};
	float window6[NUM_ELEM/64]= {0.0};

	float result = 0.0;

	L1: for(ap_uint<7> x=0; x.to_uint()<NUM_ELEM/2; x++)
    {
#pragma HLS PIPELINE
    	 window1[x] = window0[x] +  window0[NUM_ELEM/2+x];
	}
	L2: for(ap_uint<7> x=0; x.to_uint()<NUM_ELEM/4; x++)
    {
#pragma HLS PIPELINE

    	 window2[x] = window1[x] +  window1[NUM_ELEM/4+x];
	}
	L3: for(ap_uint<7> x=0; x.to_uint()<NUM_ELEM/8; x++)
    {
#pragma HLS PIPELINE

    	 window3[x] = window2[x] +  window2[NUM_ELEM/8+x];
	}
	L4: for(ap_uint<7> x=0; x.to_uint()<NUM_ELEM/16; x++)
    {
#pragma HLS PIPELINE

    	 window4[x] = window3[x] +  window3[NUM_ELEM/16+x];
	}
	L5: for(ap_uint<7> x=0; x.to_uint()<NUM_ELEM/32; x++)
    {
#pragma HLS PIPELINE

    	 window5[x] = window4[x] +  window4[NUM_ELEM/32+x];
	}
	L6: for(ap_uint<7> x=0; x.to_uint()<NUM_ELEM/64; x++)
    {
#pragma HLS PIPELINE

    	 window6[x] = window5[x] +  window5[NUM_ELEM/64+x];
	}

	float out = window6[0] + window6[1];
	*Out = out*65536;

	//return result;
}