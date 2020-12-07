#include "NumMeth.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
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
double E=0.01;
double E2=0.0;


void F(double x[],double t,double param[],double deriv[]){
    deriv[1]=x[2];
    deriv[2]=-cbrt(x[1])*E;
}
void F2(double x[],double t,double param[],double deriv[]){
    deriv[1]=x[2];
    deriv[2]=-cbrt(x[1])*E2;
}

//the actual function for the pendulum

double pi=2*asin(1);
//pick a value of pi.  This is typo free...
//github example in class.


int main(){
	

	
    double x0=0.0;
	double v0=1.0;
    double t;
	double T=pi;
	//physical parameters
    double dt;
    double dE;
    double b0=1.0;
    double b2=1.0;
    double bprime;
    double epsilon=0.00001;
	//integrator parameters
	
	int dim=2;
	double* param= new double[dim+1];
	double* X=new double[dim+1];
	double* deriv=new double[dim+1];
	//memory allocation

	
	X[1]=x0;
	X[2]=v0;
    dt=pi/1000.0;
    int nstep=((int)(T/dt));
    dE=0.0001;

	
    while (fabs(b0)>epsilon){
        t=0.0;
        X[1]=x0;
        X[2]=v0;
	for(int i=0;i<nstep;i++){
		rk4(X,dim,t,dt,F,param);
        t+=dt;
	}
        b0=X[1];
        if (fabs(b0)<epsilon) {
            t=0.0;
                X[1]=x0;
                X[2]=v0;
            std::ofstream outRK("RK2b_cpp"+ctos(dt)+".txt");
            outRK<<t<<","<<X[1]<<"\n";
            for(int i=0;i<nstep;i++){
                rk4(X,dim,t,dt,F,param);
                t+=dt;
                outRK<<std::setprecision(16)<<t<<","<<X[1]<<"\n";
            }
            break;
        }
        X[1]=x0;
        X[2]=v0;
        E2=E+dE;
        t=0.0;
        cout<<b0<<endl;
        for(int i=0;i<nstep;i++){
            rk4(X,dim,t,dt,F2,param);
            t+=dt;
        }
        b2=X[1];
        bprime=(b2-b0)/dE;
        E=E-b0/bprime;
    }
    cout<<E<<endl;
	
	return 0;
}


