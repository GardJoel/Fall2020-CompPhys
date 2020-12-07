#include <iostream>
#include <fstream>
#include <math.h>

double logistic_calculate(double r, double x);
using namespace std;

int main(){
	
	
    double x=0.01;
    double r=0;
    int N=50;
    std:: ofstream r1file("q5r1.txt");
    std:: ofstream r2file("q5r2.txt");
    
    for (int i=0; i<2; i++) {
        if (i==0) {
            r=2.0;
            r1file<<0<<","<<x<<endl;
        }
        if (i==1) {
            r=2.99;
            r2file<<0<<","<<x<<endl;
        }
        
        for (int j=0; j<N; j++) {
            x=logistic_calculate(r,x);
            
            if (i==0) {
                r1file<<j+1<<","<<x<<endl;
            }
            if (i==1) {
                r2file<<j+1<<","<<x<<endl;
            }
            
        }
    }
    r1file.close();
       r2file.close();
	
	return 0;
}

double logistic_calculate(double r, double x){
	return r*x*(1-x);
}
