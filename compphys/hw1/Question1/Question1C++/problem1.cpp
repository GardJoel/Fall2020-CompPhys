#include <iostream>  //needed to print to the screen
#include <math.h>    //used for predefined exp(),pow(), and abs() functions
#include <fstream>   //write to file

using namespace std;

//reference functions and define constants
#define N -20

double x(double t);
double xprimeest(double x0,double x, double deltat);
double derivdiff(double prime,double estprime);

int main(){
    //readies for output of data to a file in the desired directory
    string dir="/users/joelgard/Desktop/compphys/hw1/Question1C++";//desired path
    string mkdir="mkdir -p"+dir;//create desired path if it does not exist
    string fn=dir+"/q1.txt";//desired file name located in path
    std::ofstream outfile;//prepare to stream output to data file
    outfile.open(fn.c_str());//open data file
    
    
    //define initial value of t
    double t0=2.0;
    
    //define functional derivative value at t0
    double xprime=9*exp(-(t0))/((1+9*exp(-t0))*((1+9*exp(-(t0)))));
                     
    
    //define initial function value to be plugged into derivative estimate
    double x0=x(t0);
    

    for (double t=0;t>N;t-=1){
        
        //define current value of function at t0 + delta t
        double xnew=x(t0+pow(10,-t));
        
        //estimate the derivative with initial x, current x, and delta t
        double xest=xprimeest(x0,xnew,pow(10,-t));
        
        //output to datafile
        outfile<<pow(10,-t)<<","<<derivdiff(xprime,xest)<<endl;
        
    }
    
    
	
    //close data file
            outfile.close();
    
    return 0;
}


//definition of function
double x(double t){
    return 1/(1+9*exp(-t));
};

//definition of derivative estimate
double xprimeest(double x0,double x, double deltat){
    return (x-x0)/deltat;
};
 
//magnitude of the difference between two numbers; will be used to calculate magnitude of the difference between functional derivative and estimated derivative
double derivdiff(double prime,double estprime){
    return abs(prime-estprime);
};

