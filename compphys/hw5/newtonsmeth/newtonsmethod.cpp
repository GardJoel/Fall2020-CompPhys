#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

//declare functions to be used
vector<vector<double> > creatematrix(int i,int j);
vector<double> func(double x,double y);
vector<vector<double> > jacobian(double x,double y);
vector<vector<double> > jacobianinv(double x,double y);
vector<double> newtonsmethod(vector<double> guess);

int main(int argc, char* argv[]){
  
    vector<double> myguess(2);
    if (argc < 3){
        std::cerr << "Please enter an x and y coordinate guess "<<endl;
        return 0;
    }
    
    myguess[0]=atof(argv[1]);
    myguess[1]=atof(argv[2]);
    vector<double> vals;
    vals=newtonsmethod(myguess);
    cout<<"Solution for the trial point ("<<myguess[0]<<","<<myguess[1]<<") by Newtons Method is-> x= "<<vals[0]<<", y= "<<vals[1]<<endl;//output the guesses and the solution found
    
}

//creates an i by j matrix
vector<vector<double> > creatematrix(int i,int j){
    vector<double> ddim;
    for (int k=0; k<i; k++) {
        ddim.push_back(0.0);
    }
    vector<vector<double> > matrix;
    for (int k=0;k<j; k++) {
        matrix.push_back(ddim);
    }
    
    return matrix;
}

//define function, two variable here, can be made more general
vector<double> func(double x,double y){
    vector<double> funcvalue;
    for (int i=0; i<2; i++) {
        funcvalue.push_back(0.0);
    }
    funcvalue[0]=x*x*exp(-x*x)+y*y;
    funcvalue[1]=x*x*x*x/(1+y*y*x*x);
    return funcvalue;
}

//define jacobian
vector<vector<double> > jacobian(double x,double y){
    vector<vector<double> > derivs=creatematrix(2,2);
    derivs[0][0]=2.0*x*exp(-x*x)-2.0*x*x*x*exp(-x*x);
    derivs[0][1]=2.0*y;
    derivs[1][0]=4*x*x*x/(1+y*y*x*x)-2*x*x*x*x*x*y*y/((1+y*y*x*x)*(1+y*y*x*x));
    derivs[1][1]=-2*x*x*x*x*x*x*y/((1+y*y*x*x)*(1+y*y*x*x));
    return derivs;
}

//define inverse jacobian matrix, the functions jacobian and jacobian inverse could be combined into one function to find J^-1
vector<vector<double> > jacobianinv(double x,double y){
    vector<vector<double> > jacob=jacobian(x,y);
    double det=jacob[0][0]*jacob[1][1]-jacob[0][1]*jacob[1][0];
    vector<vector<double> > j=creatematrix(2,2);
    j[0][0]=jacob[1][1]/det;
    j[0][1]=-jacob[0][1]/det;
    j[1][0]=-jacob[1][0]/det;
    j[1][1]=jacob[0][0]/det;
    return j;
}

//factor what will be plugged into recursion equation, delta=J^-1*(1-f)
vector<double> deltax(double x,double y){
    vector<double> f;
    for (int i=0; i<2; i++) {
        f.push_back(0.0);
    }
    f[0]=1-func(x,y)[0];
    f[1]=1-func(x,y)[1];
    vector<vector<double> > j;
    j=jacobianinv(x,y);
    vector<double> delta(2);
    for (int i=0; i<2; i++) {
        for (int k=0; k<2; k++) {
            delta[i]+=j[i][k]*f[k];
        }
    }
    return delta;
}

vector<double> newtonsmethod(vector<double> guess){
    //initialize new and old coordinates for recursion, initialize initial funcvalue
    vector<double> vecold;
    for (int i=0; i<2; i++) {
        vecold.push_back(0.0);
    }
    vector<double> vecnew;
    for (int i=0; i<2; i++) {
        vecnew.push_back(0.0);
    }
    vecold=guess;
    vector<double> funcval;
    for (int i=0; i<2; i++) {
        funcval.push_back(0.0);
    }
    funcval=func(vecold[0],vecold[1]);


    while (fabs(funcval[0]-1)>.000001 || fabs(funcval[1]-1)>.000001) {
        vector<double> delta=deltax(vecold[0],vecold[1]);
        //recursion
        for (int i=0; i<2; i++) {
                vecnew[i]=vecold[i]+delta[i];
        }
        //update
        vecold=vecnew;
        funcval=func(vecold[0],vecold[1]);
    }
    //solution
    return vecold;
}
