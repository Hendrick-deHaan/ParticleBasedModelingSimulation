#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	int i, j;
	
	int N;
	
	double rad;
	double rx,ry;
	double accept,reject;
	
	FILE *out;
	out=fopen("calc_pi.prn","w");
	
	for(i=0;i<9;i++){
		N=pow(10,i);
		accept=0;
		reject=0;
		for(j=0;j<N;j++){
			rx=(double)rand()/RAND_MAX;
			ry=(double)rand()/RAND_MAX;
			rad=sqrt(pow(rx-0.5,2.0)+pow(ry-0.5,2.0));
			if(rad<=0.5)
				accept++;
			else
				reject++;
		}
		fprintf(out,"%i %lf %lf\n", N, accept/(reject+accept), (accept/(reject+accept))/(0.5*0.5));
	}
}
