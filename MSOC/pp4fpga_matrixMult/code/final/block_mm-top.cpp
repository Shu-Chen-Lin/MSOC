#include "block_mm.h"
#include <stdlib.h>
using namespace std;

void matmatmul_sw(DTYPE A[SIZE][SIZE], DTYPE B[SIZE][SIZE],
		DTYPE out[SIZE][SIZE]) {
	DTYPE sum = 0;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<BLOCK_SIZE; j++) {
			sum = 0;
			for(int k=0; k<BLOCK_SIZE; k++) {
				sum = sum + A[i][k]*B[k][j];
			}
			out[i][j] = sum;
		}
	}
}

int main() {
	int fail = 0;
	hls::stream<blockvec> strm_matrix1("strm_matrix1");
	hls::stream<blockvec> strm_matrix2("strm_matrix2");
	blockvec strm_matrx1_element, strm_matrix2_element;
	blockmat block_out;
	DTYPE A[SIZE][SIZE], B[SIZE][SIZE];
	DTYPE matrix_swout[SIZE][SIZE], matrix_hwout[SIZE][SIZE];
	
	initmatrices:
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<BLOCK_SIZE; j++) {
			A[i][j] = i+j;
			B[i][j] = i+j;
			matrix_swout[i][j] = 0;
			matrix_hwout[i][j] = 0;
		}
	}
	
	int row, col, it=0;
	for(int it1=0; it1<SIZE; it1=it1+BLOCK_SIZE) {
		for(int it2=0; it2<SIZE; it2=it2+BLOCK_SIZE) {
			row = it1;
			col = it2;
			
			for(int k=0; k<SIZE; k++){
				for(int i=0; i<BLOCK_SIZE; i++){
					if(it%(SIZE/BLOCK_SIZE)==0){
						strm_matrx1_element.a[i] = A[row+i][k];
					}
					strm_matrix2_element.a[i] = B[k][col+i];
				}
				if(it%(SIZE/BLOCK_SIZE)==0)
					strm_matrix1.write(strm_matrx1_element);
				strm_matrix2.write(strm_matrix2_element);
			}
			blockmatmul(strm_matrix1, strm_matrix2, block_out, it);
			
			for(int i=0; i<BLOCK_SIZE; i++){
				for(int j=0; j<BLOCK_SIZE; j++){
					matrix_hwout[row+i][col+j] = block_out.out[i][j];
				}
			}
			it = it+1;
		}
	}

	matmatmul_sw(A, B, matrix_swout);
	for(int i=0; i<BLOCK_SIZE; i++){
		for(int j=0; j<BLOCK_SIZE; j++){
			if(matrix_swout[i][j] != matrix_hwout[i][j]) {
				fail=1;
				printf("%d,%d,%d,%d\n",i,j,matrix_swout[i][j],matrix_hwout[i][j]);
			}

			if(fail==1)
				cout<<"Failed"<<endl;
			else
				cout<<"passed"<<endl;
			return 0;
		}
	}
}
