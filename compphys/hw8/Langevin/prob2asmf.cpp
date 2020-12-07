#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstring>
#include <random>

using namespace std;

mt19937 rgen (1);
//initialize the generator
uniform_real_distribution<double> uran (0.0, 1.0);
//uniform distribution between 0 and 1
normal_distribution<double> gran (0.0,1.0);

#define Three_Dim

#ifdef Three_Dim
#define dim 3
#endif

#define kT 1.0
#define m 1.0
#define k1 0.1
#define k2 1.0
#define zeta 1.0
#define dt 0.01
#define rtol .05
#define nsim 1000
#define PI 3.14159265
#define N 10000

double velocity(double a[dim],double b[dim], double aold[dim],double bold[dim], double t);
double com2(double a[dim],double b[dim]);

//template <typename T>
//std::string NumberToString ( T Number )
//{
  //  std::ostringstream ss;
    //ss << Number;
    //return ss.str();
//}
//useful for multiple output files (iteratively) if needed
int main(){
    double kick=sqrt(2*kT*dt/zeta);
    double storev[N]={0.0};
    double storeR[N]={0.0};

    
    for (int n=0;n<nsim;n++){
    double posa[dim]={0.5,0.0,0.0};
    double posb[dim]={-0.5,0.0,0.0};
    double newposa[dim]={0.5,0.0,0.0};
    double newposb[dim]={-0.5,0.0,0.0};
    double oldposa[dim]={0.5,0.0,0.0};
    double oldposb[dim]={-0.5,0.0,0.0};
    


    
    for (int i=0; i<N; i++) {
        for (int j=0; j<dim; j++) {
            newposa[j]=posa[j];
            newposb[j]=posb[j];
            if (j==0) {
                newposa[j]+=(posa[j]-oldposa[j])*(1-zeta*dt/2/m)/(1+zeta*dt/2/m);
                newposb[j]+=(posb[j]-oldposb[j])*(1-zeta*dt/2/m)/(1+zeta*dt/2/m);
                newposa[j]+=(-k2*(posa[j]-1.0)+gran(rgen)*kick-k1*posa[j])*dt*dt/m/(1+zeta*dt/2/m);
                newposb[j]+=(-k2*(posb[j]-1.0)+gran(rgen)*kick-k1*posb[j])*dt*dt/m/(1+zeta*dt/2/m);
            }
            else{
            newposa[j]+=(posa[j]-oldposa[j])*(1-zeta*dt/2/m)/(1+zeta*dt/2/m);
            newposb[j]+=(posb[j]-oldposb[j])*(1-zeta*dt/2/m)/(1+zeta*dt/2/m);
            newposa[j]+=(gran(rgen)*kick-k1*posa[j])*dt*dt/m/(1+zeta*dt/2/m);
            newposb[j]+=(gran(rgen)*kick-k1*posb[j])*dt*dt/m/(1+zeta*dt/2/m);
            }
            oldposa[j]=posa[j];
            posa[j]=newposa[j];
            oldposb[j]=posb[j];
            posb[j]=newposb[j];

        }
        storev[i]+=velocity(posa,posb,oldposa,oldposb,dt)*velocity(posa,posb,oldposa,oldposb,dt)/((double)(nsim));
        storeR[i]+=com2(posa,posb)/((double)(nsim));
        cout<<storeR[i]<<endl;
    }
    

    }
    ofstream outfilea;
    outfilea.open("cpp_v.txt");
    
    
        for (int j=0; j<N; j++) {
            outfilea<<storev[j]<<endl;
        }
    
    outfilea.close();
    
    ofstream outfileb;
    outfileb.open("cpp_R.txt");
    
    
        for (int j=0; j<N; j++) {
            outfileb<<storeR[j]<<endl;
        }
    
    outfileb.close();
    
    return 0;
}
double velocity(double a[dim],double b[dim], double aold[dim],double bold[dim],double t){
    //double comold[dim];
    //double com[dim];
    double distance=0.0;
    
    for (int j=0; j<dim; j++) {
        //comold[j]=(aold[j]-bold[j])/2.0;
        //com[j]=(a[j]-b[j])/2.0;
        distance+=(a[j]-aold[j])*(a[j]-aold[j]);
    }
    
    distance=sqrt(distance);
    
    return distance/t;
}
double com2(double a[dim],double b[dim]){
    double com[dim];
    double distance=0.0;
    for (int j=0; j<dim; j++) {
        com[j]=(a[j]+b[j])/2.0;
        distance+=com[j]*com[j];
    }
    
    return distance;
}
