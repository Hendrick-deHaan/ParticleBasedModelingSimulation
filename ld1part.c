#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	
	int t=0,tmax=1E6;
	
	double dt=0.01;
	double kT=1.0;
	double g=1.0;
	
	double x,v,vh,a;
	
	double ran,ran1,ran2;
	double gr1,gr2;
	double pref1,pref2;
	
	FILE *outx,*outv,*outt;
	outx=fopen("ld1part_x_test.trj","w");
	outv=fopen("ld1part_v_test.trj","w");
	outt=fopen("ld1part_t_test.xyz","w");
	
	x=0;
	v=1.0;
	
	pref1=g;
	pref2=sqrt(2*kT*g/dt);
	
	ran1=(double)rand()/RAND_MAX;
	ran2=(double)rand()/RAND_MAX;
	gr1=(double)sqrt(-2*log(ran1))*cos(2*3.14159265*ran2);
	gr2=(double)sqrt(-2*log(ran1))*sin(2*3.14159265*ran2);
		
	a=-pref1*v+pref2*gr1;
	
	while(t<tmax){
		
		fprintf(outt,"2\n");
		fprintf(outt,"title\n");
		fprintf(outt,"a1 %f 0 0\n",x);
		fprintf(outt,"a2 0 0 0\n");
		
		vh=v+0.5*a*dt;
		
		x=x+vh*dt;
		
		ran1=(double)rand()/RAND_MAX;
		ran2=(double)rand()/RAND_MAX;
		gr1=(double)sqrt(-2*log(ran1))*cos(2*3.14159265*ran2);
		gr2=(double)sqrt(-2*log(ran1))*sin(2*3.14159265*ran2);
		
		a=-pref1*vh+pref2*gr1;
		
		v=vh+0.5*a*dt;
		
		fprintf(outx,"%E\n",x);
		fprintf(outv,"%E\n",v);
		
		t++;
	}
}
			
			
