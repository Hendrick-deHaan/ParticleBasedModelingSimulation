#include "stdio.h"
#include "stdlib.h"

int main(){

	float dt=0.01;
	
	float a,v,x,v0,x0;
	float dv,dx;
	float F,t,tmax=100;
	float U,K,E;
	
	float m=1.0,g=9.8;
	float k=1.0;
	
	v0=10;
	x0=0;
	
	x=x0;
	v=v0;
	a=-k*x/m;
	
	FILE *outdat,*outtraj;
	outdat=fopen("traj_euler.prn","w");
	outtraj=fopen("euler_traj.xyz","w");

	U=m*g*x;
	K=0.5*m*v*v;
	E=U+K;
	
	fprintf(outdat,"%f %f %f\n",x,v,E);
	
	while(t<tmax){
		
		fprintf(outtraj,"1\n");
		fprintf(outtraj,"title\n");
		fprintf(outtraj,"a1 %f 0 0\n",x);		
		
		a=-k*x/m;
		
		dv=a*dt;
		
		dx=v*dt;
		
		v=v+dv;
		
		x=x+dx;

		U=0.5*k*x*x;
		K=0.5*m*v*v;
		E=U+K;
		
		fprintf(outdat,"%f %f %f\n",x,v,E);
		
		t+=dt;
	}
}
