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
	deriv[2]=x[3];
    deriv[3]=(1-6*x[1])*x[2];
}
//the actual function for the pendulum

double pi=2*asin(1);
//pick a value of pi.  This is typo free...
//github example in class.


int main(){
	

	
    double w0=1.0/2.0;
    double w01=0;
    double w02=-1.0/4.0;
	double v0=1.0;
	double t=0;
	double T=5;
	//physical parameters
    double dt=0.01;
	//integrator parameters
	
	int dim=3;
	double* param= new double[dim+1];
	double* X=new double[dim+1];
	double* deriv=new double[dim+1];
	//memory allocation

	

	
	
 
	X[1]=w0;
	X[2]=w01;
    X[3]=w02;
    int nstep=((int)(T/dt));

	t=0;
	std::ofstream outRK("RK2_cpp"+ctos(dt)+".txt");
	outRK<<t<<","<<X[1]<<"\n";
	for(int i=0;i<nstep;i++){
		rk4(X,dim,t,dt,F,param);
		t+=dt;
		outRK<<std::setprecision(16)<<t<<","<<X[1]<<"\n";
	}
	outRK.close();
	
	
	
	
    
	
	return 0;
}


