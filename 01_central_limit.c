#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	int i, j, N=10, Ninter=1E0;
	
	float r;
	float avg;
	
	FILE *out;
	out=fopen("CLT_N_1_Ni_0.prn","w");
	
	for(i=0;i<Ninter;i++){
		avg=0;
		for(j=0;j<N;j++){
			r=((float)rand()/RAND_MAX-0.5);
			avg+=r;
			
			//printf("%f %f\n", r, expr);
		}
		avg=avg*sqrt(12/(float)N);
		fprintf(out,"%f\n", avg);
	}
}
