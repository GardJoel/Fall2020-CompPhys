#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

double func(double x);//declare the function for which roots will be found
double bisectionrootfinder(double rootguess);//declare the bisection root finding algortihm

int main(){
  
    double suspectedroots[3]={-1.0,1.0,9.0};//input guesses
    double roots[3];
    cout<<"The roots of the function exp(-x^2)-x^4 are: "<<endl;
    for (int i=0; i<3; i++) {
        roots[i]=bisectionrootfinder(suspectedroots[i]);
        cout<<roots[i]<<endl;//output roots
    }
    
    
    
}
double func(double x){
    double funcvalue=exp(x)-x*x*x*x;//declare function, single variable
    return funcvalue;
}

double bisectionrootfinder(double rootguess){
    double a=0.0;
    double b=0.0;
    double product=5.0;
    double iter=0.001;
    //find starting interval a and b
    while (product>0) {
        a=rootguess-iter;
        b=rootguess+iter;
        product=func(a)*func(b);
        iter+=.001;
    }
    
    double epsilon=5;
    
    //bisect until finding roots
    while (epsilon>0.000001) {
        double func1=func(a);
        double func2=func(b);
        double c=func((a+b)/2);
        if (func1*c<0) {
            b=(a+b)/2;
        }
        if (func2*c<0) {
            a=(a+b)/2;
        }
        
        epsilon=fabs(func(a)-func(b));
    }
    
    return (a+b)/2;
}


