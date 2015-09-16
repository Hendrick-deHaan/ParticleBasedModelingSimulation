#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	int i;

	float dt=0.01;
	int intsteps=0;
	
	int N=100;
	
	float L=50;
	
	float ax[99999],ay[99999],vx[99999],vy[99999],x[99999],y[99999];
	float vh;
	float F,t,tmax=1000;
	
	float m=1.0,g=9.8,kT=1.0;
	float k=1.0;

	int coll=0;
	float acoll;
	float aF;
	float P;
	
	float PI=3.14159265359;
	
	float r1,r2,gr1,gr2;
	
	FILE *outo,*outt,*outv;
	outo=fopen("ideal_obs.prn","w");
	outt=fopen("ideal_traj.xyz","w");
	outv=fopen("ideal_vel.prn","w");
	
	for(i=0;i<N;i++){
		x[i]=(float)rand()/RAND_MAX*L-L/2;
		y[i]=(float)rand()/RAND_MAX*L-L/2;
		r1=(float)rand()/RAND_MAX;
		r2=(float)rand()/RAND_MAX;
		gr1=sqrt(kT/(m))*sqrt(-2*log(r1))*cos(2*PI*r2);
		gr2=sqrt(kT/(m))*sqrt(-2*log(r1))*sin(2*PI*r2);
		vx[i]=gr1;
		vy[i]=gr2;
		fprintf(outv,"%f\n%f\n",vx[i],vy[i]);
		ax[i]=0;
		ay[i]=0;
	}	

	acoll=0;
	aF=0;
	intsteps=0;
	while(t<tmax){

		if(intsteps%10==0){
			fprintf(outt,"%i\n",N);
			fprintf(outt,"title\n");
		}
		

		coll=0;
		P=0;
		for(i=0;i<N;i++){
		
			vh=vx[i]+0.5*ax[i]*dt;
			x[i]=x[i]+vh*dt;
			ax[i]=0;	
			vx[i]=vh+0.5*ax[i]*dt;

			vh=vy[i]+0.5*ay[i]*dt;
			y[i]=y[i]+vh*dt;
			ay[i]=0;
			vy[i]=vh+0.5*ay[i]*dt;			
			
			//vy[i]=0;
			
			if(x[i]<-L/2.0 || x[i]>L/2.0){
				vx[i]=-vx[i];
				coll++;
				aF+=2*m*fabs(vx[i])/dt;
			}
			if(y[i]<-L/2.0 || y[i]>L/2.0){
				vy[i]=-vy[i];
				coll++;
				aF+=2*m*fabs(vy[i])/dt;
			}
			
			
			if(intsteps%10==0)
				fprintf(outt,"a%i %f %f 0\n",i,x[i],y[i]);
			
		}
		acoll+=(float)coll;		

		t+=dt;
		intsteps++;
	}
	acoll=acoll/(float)intsteps;
	aF=aF/(float)intsteps;
	P=aF/(4*L);
	printf("%f %f\n",acoll,P);
}
