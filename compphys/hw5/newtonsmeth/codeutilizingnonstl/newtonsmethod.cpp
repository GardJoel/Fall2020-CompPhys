#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

//declare functions to be used
vector<double> func(double x,double y);
Matrix2f jacobian(double x,double y);
Matrix2f jacobianinv(double x,double y);
vector<double> newtonsmethod(vector<double> guess);

int main(){
  
    vector<double> myguess(2);//guess at root values, I have chosen large-ish values here, this is not a requirement
    myguess[0]=-200;
    myguess[1]=200;
    vector<double> vals;
    vals=newtonsmethod(myguess);
    cout<<"Final output for the trial point ("<<myguess[0]<<","<<myguess[1]<<") is-> x= "<<vals[0]<<", y="<<vals[1]<<endl;//output the guesses and the solution found
    return 0;
    
}
//define function, two variable here, can be made more general
vector<double> func(double x,double y){
    vector<double> funcvalue(2);
    funcvalue[0]=x*x*exp(-x*x)+y*y;
    funcvalue[1]=x*x*x*x/(1+y*y*x*x);
    return funcvalue;
}

//define jacobian
Matrix2f jacobian(double x,double y){
    Matrix2f derivs;
    derivs(0,0)=2.0*x*exp(-x*x)-2.0*x*x*x*exp(-x*x);
    derivs(0,1)=2.0*y;
    derivs(1,0)=4*x*x*x/(1+y*y*x*x)-2*x*x*x*x*x*y*y/((1+y*y*x*x)*(1+y*y*x*x));
    derivs(1,1)=-2*x*x*x*x*x*x*y/((1+y*y*x*x)*(1+y*y*x*x));
    return derivs;
}

//define inverse jacobian matrix, the functions jacobian and jacobian inverse could be combined into one function to find J^-1
Matrix2f jacobianinv(double x,double y){
    Matrix2f j;
    j=jacobian(x,y);
    cout<<j<<endl;
    cout<<j.inverse()<<endl;
    return j.inverse();
}

//factor what will be plugged into recursion equation, delta=J^-1*(1-f)
Vector2f deltax(double x,double y){
    Vector2f f;
    f<<1-func(x,y)[0],1-func(x,y)[1];
    Matrix2f j=jacobianinv(x,y);
    Vector2f delta=j*f;
    return delta;
}

vector<double> newtonsmethod(vector<double> guess){
    //initialize new and old coordinates for recursion, initialize initial funcvalue
    vector<double> vecold(2);
    vector<double> vecnew(2);
    vecold=guess;
    vector<double> funcval(2);
    funcval=func(vecold[0],vecold[1]);

    //recursively update coordiantes until they have reached the condition required to produce the solution; other conditions are possible to same roots, this is one which requires only one condition as opposed to multiple
    while (fabs(funcval[0]/funcval[1])>1.00001 || fabs(funcval[1]/funcval[0])>1.00001) {
        Vector2f delta=deltax(vecold[0],vecold[1]);
        //recursion
        for (int i=0; i<2; i++) {
                vecnew[i]=vecold[i]+delta(i);
        }
        //update
        vecold=vecnew;
        cout<<"Iteration Coordinates: "<<vecold[0]<<","<<vecold[1]<<endl;
        funcval=func(vecold[0],vecold[1]);
    }
    //solution
    return vecold;
}
