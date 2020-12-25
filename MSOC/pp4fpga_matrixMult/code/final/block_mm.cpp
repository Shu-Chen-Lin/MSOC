#include "block_mm.h"

void blockmatmul(hls::stream<blockvec> &Arows, hls::stream<blockvec> &Bcols,
		blockmat &ABpartial, DTYPE it){
#pragma HLS DATAFLOW
	int counter = it % (SIZE/BLOCK_SIZE);
	static DTYPE A[BLOCK_SIZE][SIZE];
	if(counter==0){ // only load the A rows when necessary
		loadA:
		for(int i=0; i<SIZE; i++){
			blockvec tempA = Arows.read();
			for(int j=0; j<BLOCK_SIZE; j++) {
				A[j][i] = tempA.a[j];
			}
		}
	}
	
	DTYPE AB[BLOCK_SIZE][BLOCK_SIZE] = {0};
	
	partialsum:
	for(int k=0; k<SIZE; k++) {
		blockvec tempB = Bcols.read();
		for(int i=0; i<BLOCK_SIZE; i++){
#pragma HLS PIPELINE II=1
			for(int j=0; j<BLOCK_SIZE; j++) {
				AB[i][j] = AB[i][j]+A[i][k]*tempB.a[j];
			}
		}
	}
	
	writeout:
	for(int i=0; i<BLOCK_SIZE; i++){
#pragma HLS PIPELINE II=1
		for(int j=0; j<BLOCK_SIZE; j++) {
			ABpartial.out[i][j] = AB[i][j];
		}
	}
}
