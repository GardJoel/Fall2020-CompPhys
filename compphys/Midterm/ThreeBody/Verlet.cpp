#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

double magnitude3(Vector2d x, Vector2d y);
Vector2d accel(Vector2d x, Vector2d y, Vector2d z);


template<typename T>
std::string ctos(T q){
    std::stringstream ss;
    ss<<q;
    return ss.str();
}

int main(){

    Vector2d r1;
    Vector2d r2;
    Vector2d r3;
    Vector2d r1curr;
    Vector2d r2curr;
    Vector2d r3curr;
    Vector2d r1old;
    r1old<<0.0,0.0;
    Vector2d r2old;
    r2old<<0.0,1.0;
    Vector2d r3old;
    r3old<<0.0,-1.0;
    Vector2d v01;
    v01<<0.0,0.0;
    Vector2d v02;
    v02<<1.0,0.0;
    Vector2d v03;
    v03<<-1.0,0.0;
    Vector2d a1;
    Vector2d a2;
    Vector2d a3;
    
    double T=50;
    double dt=0.01;
    int N=int(50/dt);
    double t=0;
    a1=accel(r1old,r2old,r3old);
    a2=accel(r2old,r1old,r3old);
    a3=accel(r3old,r1old,r2old);
    
    r1=dt*dt*a1/2.0;
    r2=r2old+v02*dt+dt*dt*a2/2.0;
    r3=r3old+v03*dt+dt*dt*a3/2.0;
    
    std::ofstream outVerlet1("verlet1.txt");
    std::ofstream outVerlet2("verlet2.txt");
    std::ofstream outVerlet3("verlet3.txt");
    outVerlet1<<r1old(0)<<","<<r1old(1)<<endl;
    outVerlet2<<r2old(0)<<","<<r2old(1)<<endl;
    outVerlet3<<r3old(0)<<","<<r3old(1)<<endl;
    outVerlet1<<r1(0)<<","<<r1(1)<<endl;
    outVerlet2<<r2(0)<<","<<r2(1)<<endl;
    outVerlet3<<r3(0)<<","<<r3(1)<<endl;
    
    t+=dt;
    
    for (int i=0; i<N-1; i++) {
        r1curr=r1;
        r2curr=r2;
        r3curr=r3;
        a1=accel(r1,r2,r3);
        a2=accel(r2,r1,r3);
        a3=accel(r3,r1,r2);
        r1=2*r1-r1old+dt*dt*a1;
        r2=2*r2-r2old+dt*dt*a2;
        r3=2*r3-r3old+dt*dt*a3;
        r1old=r1curr;
        r2old=r2curr;
        r3old=r3curr;

        t+=dt;
        outVerlet1<<r1(0)<<","<<r1(1)<<endl;
        outVerlet2<<r2(0)<<","<<r2(1)<<endl;
        outVerlet3<<r3(0)<<","<<r3(1)<<endl;
    }
    
    
	return 0;
}

double magnitude3(Vector2d x, Vector2d y){
    Vector2d diff=x-y;
    double mag=sqrt((diff).dot(diff));
    return mag*mag*mag;
}

Vector2d accel(Vector2d x, Vector2d y, Vector2d z){
    Vector2d accel;
    accel=-(x-y)/magnitude3(x,y)-(x-z)/magnitude3(x,z);
    return accel;
}
