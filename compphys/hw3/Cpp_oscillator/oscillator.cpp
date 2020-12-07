#include "NumMeth.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
template<typename T>
std::string ctos(T q){
    std::stringstream ss;
    ss<<q;
    return ss.str();
}


extern void rk4(double x[], int nX, double t, double tau,
				void (*derivsRK)(double x[], double t, double param[], double deriv[]),
				double param[]);
//for reasons I cannot understand, Garcia has chosen to index his functions
//starting at i=1.  x[0] is not updated using is rk4 function, so our vectors will have
//the first element as a null value.  I will keep that notation in this script.
//it is possible he intended the first element to be the time, but this is not
//clear in his function definition.


void F(double x[],double t,double param[],double deriv[]){
    deriv[1]=x[2];
	deriv[2]=2*x[2]-x[1];
}
//the actual function for the pendulum

double pi=2*asin(1);
//pick a value of pi.  This is typo free...
//github example in class.


int main(){
	

	
    double x0=0.0;
	double v0=1.0;
	double t=0;
	double T=5;
	//physical parameters
    double dt;
    double dtarray[6]={0.5,0.1,0.05,0.01,0.005,0.001};
	//integrator parameters
	
	int dim=2;
	double* param= new double[dim+1];
	double* X=new double[dim+1];
	double* deriv=new double[dim+1];
	//memory allocation

	
	
    for (int j=0;j<6;j++){
    dt=dtarray[j];
	X[1]=x0;
	X[2]=v0;
    int nstep=((int)(T/dt));

	t=0;
	std::ofstream outRK("RK_cpp"+ctos(dt)+".txt");
	outRK<<t<<","<<X[1]<<"\n";
	for(int i=0;i<nstep;i++){
		rk4(X,dim,t,dt,F,param);
		t+=dt;
		outRK<<std::setprecision(16)<<t<<","<<X[1]<<"\n";
	}
	outRK.close();
	
	
	
	X[1]=x0+v0*dt+dt*dt*(-x0)/2;
	X[2]=x0;
	t=0;
	std::ofstream outVerlet("verlet_cpp"+ctos(dt)+".txt");
	outVerlet<<t<<","<<X[2]<<"\n";
	outVerlet<<t+dt<<","<<X[1]<<"\n";
        t+=dt;

	for(int i=0;i<nstep-1;i++){
		double xcurr=X[1];
		X[1]=2*X[1]-X[2]+dt*dt*(-X[1]);
		X[2]=xcurr;
		t+=dt;
		outVerlet<<std::setprecision(16)<<t<<","<<X[1]<<"\n";
	}
	outVerlet.close();
    }
	
	return 0;
}


