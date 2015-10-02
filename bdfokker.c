#include "stdio.h"
#include "stdlib.h"
#include "math.h"

float PI=3.14159265359;

int main(){
	
	int t=0,tmax=1E3;
	
	int i, N=9999;
	
	double avg_x, avg_x2,std;
	
	double dt=0.1;
	double kT=1.0;
	double g=1.0;
	double m=1.0;
	
	double D=kT/g;
	
	int ix;
	double x[9999]={0},v[9999];
	int rho[999]={0};
	
	double ran,ran1,ran2;
	double gr1,gr2;
	double pref;
	
	pref=sqrt(2*D/dt);
	
	FILE *outstats,*frho;
	outstats=fopen("bdfokker_test.prn","w");
	frho=fopen("bdrho_test.prn","w");
	
	avg_x=0;
	avg_x2=0;
		
	fprintf(outstats,"%E %E\n",avg_x,avg_x2);
	
	while(t<tmax){
		avg_x=0;
		avg_x2=0;
		for(i=0;i<9999;i++){
			rho[i]=0;
		}
		
		
		for(i=0;i<N;i++){
			ran1=(double)rand()/RAND_MAX;
			ran2=(double)rand()/RAND_MAX;
			gr1=(double)sqrt(-2*log(ran1))*cos(2*PI*ran2);
			gr2=(double)sqrt(-2*log(ran1))*sin(2*PI*ran2);
			
			v[i]=pref*gr1;
			x[i]=x[i]+v[i]*dt;
			
			avg_x+=x[i];
			avg_x2+=x[i]*x[i];
			
			ix=(int)(x[i]+500);
			rho[ix]++;
		}
		
		for(i=0;i<999;i++){
			fprintf(frho,"%f ",(float)rho[i]/(float)N);
		}
		fprintf(frho,"\n");
		
		avg_x=avg_x/(double)N;
		avg_x2=avg_x2/(double)N;
		
		fprintf(outstats,"%E %E\n",avg_x,avg_x2);
		
		t++;
	}
}
			
			
