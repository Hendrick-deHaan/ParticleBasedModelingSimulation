#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	
	int t=0,tmax=1E6;
	
	double dt=0.01;
	double kT=1.0;
	double g=1.0;
	
	double D=kT/g;
	
	double x,v;
	
	double ran,ran1,ran2;
	double gr1,gr2;
	double pref;
	
	FILE *outx,*outv;
	outx=fopen("bd1part_x.trj","w");
	outv=fopen("bd1part_v.trj","w");
	
	x=0;
	v=1.0;

	pref=sqrt(2*D/dt);
		
	
	while(t<tmax){
		
		ran1=(double)rand()/RAND_MAX;
		ran2=(double)rand()/RAND_MAX;
		gr1=(double)sqrt(-2*log(ran1))*cos(2*3.14159265*ran2);
		gr2=(double)sqrt(-2*log(ran1))*sin(2*3.14159265*ran2);
		
		v=pref*gr1;
		
		x=x+v*dt;
		
		fprintf(outx,"%E\n",x);
		fprintf(outv,"%E\n",v);
		
		t++;
	}
}
			
			
