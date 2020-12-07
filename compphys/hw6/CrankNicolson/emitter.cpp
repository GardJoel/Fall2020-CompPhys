#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include "Eigen/Dense"


using namespace std;
using namespace Eigen;

template<typename T>
std::string ctos(T q){
    std::stringstream ss;
    ss<<q;
    return ss.str();
}

int main(){
    
    //initialize parameters,
    double Darray[3]={1.0,10.0,100.0};
    double D=0;
    double T=10.0;
    double C=1.0;
    double dt=.01;
    double L=100.0;
    int N=1000;
    double dx=L/double(N-1);
    MatrixXd H(N,N);
    MatrixXd id(N,N);
    for (int i=0; i<N; i++) {
           for (int j=0; j<N; j++) {
               if (i==j) {
                   id(i,j)=1.0;
               }
               else{
                   id(i,j)=0.0;
               }
           }
       }
    

    
    for (int d=0; d<3; d++) {
        D=Darray[d];
        int Nstep=int(T/dt);
        VectorXd rho(N);
        for (int i=0; i<N; i++) {
            rho(i)=0.0;
        }
        rho(int(N/2)-1)=N;
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                if (abs(i-j)==1) {
                    H(i,j)=D*dt/(2*dx*dx);
                }
                else if (i==j) {
                    H(i,j)=-D*dt/(dx*dx)+1/2*C*dt;
                }
                else{
                    H(i,j)=0.0;
                }
            }
        }
        
        H(0,1)=D*dt/(dx*dx);
        H(N-2,N-1)=D*dt/(dx*dx);
        
        
        MatrixXd Ti(N,N);
        MatrixXd T(N,N);
        Ti=id-H;
        T=id+H;
        MatrixXd Crank=Ti.inverse()*T;
        std::ofstream outfile("distribution_D"+ctos(D)+".txt");

        for (int i=0; i<Nstep; i++) {
            rho=Crank*rho;
            if (i==Nstep-1) {
                outfile<<rho<<endl;
            }
        }
        outfile.close();
    }
    
       
	return 0;
}


