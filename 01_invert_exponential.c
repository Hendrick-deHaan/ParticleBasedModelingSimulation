#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	int i, N=1000000;
	
	float r, expr;
	
	float lambda=5.0;
	
	FILE *out;
	out=fopen("invert_expo.prn","w");
	
	for(i=0;i<N;i++){
		r=(float)rand()/RAND_MAX;
		expr=-log(-r+1.0)/lambda;
		fprintf(out,"%f %f\n", r, expr);
		//printf("%f %f\n", r, expr);
	}	

}
