#include "stdio.h"
#include "stdlib.h"

int main(){

	float dt=0.01;
	
	float a,v,x,v0,x0;
	float vh;
	float dv,dx;
	float F,t,tmax=100;
	float U,K,E;
	
	float m=1.0,g=9.8;
	float k=1.0;

	FILE *out;
	out=fopen("traj_vv.prn","w");
	
	v0=10;
	x0=0;
	
	x=x0;
	v=v0;
	a=-k*x/m;

	U=m*g*x;
	K=0.5*m*v*v;
	E=U+K;
	
	fprintf(out,"%f %f %f\n",x,v,E);

	while(t<tmax){
		
		vh=v+0.5*a*dt;
		
		x=x+vh*dt;
		
		a=-k*x/m;
		
		v=vh+0.5*a*dt;

		U=0.5*k*x*x;
		K=0.5*m*v*v;
		E=U+K;
		
		fprintf(out,"%f %f %f\n",x,v,E);
		
		t+=dt;
	}
}
