#include "stdio.h"
#include "stdlib.h"
#include "math.h"

float PI=3.14159265359;

int main(){
	
	int t=0,tmax=1E3;
	
	int i, N=9999;
	
	double avg_x, avg_x2,std;
	
	double dt=0.01;
	double kT=1.0;
	double g=1.0;
	double m=1.0;
	
	double x[9999],v[9999],vh[9999],a[99999];
	
	double ran,ran1,ran2;
	double gr1,gr2;
	double pref1,pref2;
	
	pref1=g;
	pref2=sqrt(2*kT*g/dt);
	
	FILE *outstats,*outt;
	outstats=fopen("ldmultipart.prn","w");
	outt=fopen("ldmultipart_t.xyz","w");
	
	avg_x=0;
	avg_x2=0;
	for(i=0;i<N;i++){
		x[i]=0;
		ran1=(float)rand()/RAND_MAX;
		ran2=(float)rand()/RAND_MAX;
		gr1=sqrt(kT/(m))*sqrt(-2*log(ran1))*cos(2*PI*ran2);
		gr2=sqrt(kT/(m))*sqrt(-2*log(ran1))*sin(2*PI*ran2);
		v[i]=gr1;
		a[i]=-pref1*v[i]+pref2*gr2;
		avg_x+=x[i];
		avg_x2+=x[i]*x[i];
	}
	avg_x=avg_x/(double)N;
	avg_x2=avg_x2/(double)N;
		
	fprintf(outstats,"%E %E\n",avg_x,avg_x2);
	
	while(t<tmax){
		avg_x=0;
		avg_x2=0;
		
		fprintf(outt,"%i\n",N);
		fprintf(outt,"title\n");
		
		for(i=0;i<N;i++){
			
			fprintf(outt,"a%i %f 0 0\n",i,x[i]);
			
			vh[i]=v[i]+0.5*a[i]*dt;
			
			x[i]=x[i]+vh[i]*dt;
			
			ran1=(double)rand()/RAND_MAX;
			ran2=(double)rand()/RAND_MAX;
			gr1=(double)sqrt(-2*log(ran1))*cos(2*PI*ran2);
			gr2=(double)sqrt(-2*log(ran1))*sin(2*PI*ran2);
			
			a[i]=-pref1*vh[i]+pref2*gr1;
			
			v[i]=vh[i]+0.5*a[i]*dt;
			
			avg_x+=x[i];
			avg_x2+=x[i]*x[i];
		}
		
		avg_x=avg_x/(double)N;
		avg_x2=avg_x2/(double)N;
		
		fprintf(outstats,"%E %E\n",avg_x,avg_x2);
		
		t++;
	}
}
			
			
