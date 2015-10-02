#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	
	int t=0,tmax;
	
	int dt;
	int pos1,pos2;
	
	double v[1000001];
	
	double vacc;
	int nvacc;
	double intvacc=0;

	FILE *inv,*out;
	
	inv=fopen("ld1part_v.trj","r");
	out=fopen("ld1part_vacc.prn","w");
	
	while(!feof(inv)){
		fscanf(inv,"%lf",&v[t]);
		t++;
	}
	tmax=t-1;
	
	for(dt=0;dt<1E5;dt++){
		pos1=0;
		pos2=pos1+dt;
		vacc=0;
		nvacc=0;
		
		while(pos2<tmax){
			vacc+=v[pos1]*v[pos2];
			nvacc++;
			
			pos1++;
			pos2=pos1+dt;
		}
		vacc=vacc/(double)nvacc;
		intvacc+=vacc*0.01;
		
		fprintf(out,"%lf %lf %lf\n", (double)dt*0.01,vacc,intvacc);
	}
}
			
			
