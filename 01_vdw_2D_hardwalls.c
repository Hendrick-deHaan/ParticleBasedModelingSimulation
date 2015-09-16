#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
	int i,j;

	float dt=0.01;
	int intsteps=0;
	
	int N=100;
	
	float L=25;
	
	float ax[99999],ay[99999],vx[99999],vy[99999],x[99999],y[99999];
	float vhx[99999],vhy[99999];
	float t,tmax=100;
	
	float r;
	float eps=1.0;
	float sig=1.0;
	float rc=pow(2.0,1.0/6.0)*sig;
	
	float F,Fx,Fy;
	
	float m=1.0,g=9.8,kT=1.0;
	float k=1.0;

	int coll=0;
	float acoll;
	float P,aF;
	int tooclose=0;
	int placed;
	
	float PI=3.14159265359;
	
	float r1,r2,gr1,gr2;
	
	float av2=0,av2p;
	
	FILE *outo,*outt,*outv;
	outo=fopen("vdw_obs.prn","w");
	outt=fopen("vdw_traj.xyz","w");
	outv=fopen("vdw_vel.prn","w");
	
	for(i=0;i<N;i++){
		//printf("%i\n",i);
		if(i==0)
			placed=1;
		else
			placed=0;
		while(!placed){
			x[i]=(float)rand()/RAND_MAX*L-L/2;
			y[i]=(float)rand()/RAND_MAX*L-L/2;
			tooclose=0;
			for(j=0;j<i;j++){
				r=sqrt( pow(x[i]-x[j],2.0) + pow(y[i]-y[j],2.0) );
				if(r < rc){
					tooclose=1;
				}
			}
			if(!tooclose)
				placed=1;
		}	
		r1=(float)rand()/RAND_MAX;
		r2=(float)rand()/RAND_MAX;
		gr1=sqrt(kT/(m))*sqrt(-2*log(r1))*cos(2*PI*r2);
		gr2=sqrt(kT/(m))*sqrt(-2*log(r1))*sin(2*PI*r2);
		vx[i]=gr1;
		vy[i]=gr2;
		
		av2+=vx[i]*vx[i]+vy[i]*vy[i];
		
		fprintf(outv,"%f\n%f\n",vx[i],vy[i]);
		ax[i]=0;
		ay[i]=0;
	}	

	printf("Done setup!\n");
	av2=av2/(float)N;
	printf("initial T: %f\n",m*av2/2.0);

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
		av2p=av2;
		av2=0;

		
		for(i=0;i<N;i++){
			vhx[i]=vx[i]+0.5*ax[i]*dt;
			x[i]=x[i]+vhx[i]*dt;
			
			vhy[i]=vy[i]+0.5*ay[i]*dt;	
			y[i]=y[i]+vhy[i]*dt;
		}
		for(i=0;i<N;i++){
			ax[i]=0;
			ay[i]=0;
			for(j=0;j<N;j++){
				if(i!=j){
					r=sqrt( pow(x[i]-x[j],2.0) + pow(y[i]-y[j],2.0) );
					if(r < rc){
						F=-4*eps*( -12.0*pow(sig,12.0)/pow(r,13.0) + 6.0*pow(sig,6.0)/pow(r,7.0) );
						Fx=F*(x[i]-x[j])/r;
						Fy=F*(y[i]-y[j])/r;
						ax[i]+=Fx/m;
						ay[i]+=Fy/m;
					}
				}
			}
			
			vx[i]=vhx[i]+0.5*ax[i]*dt;
			vy[i]=vhy[i]+0.5*ay[i]*dt;	

			
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
	P=aF/(4.0*L);
	printf("%f %f\n",acoll,P);
}
