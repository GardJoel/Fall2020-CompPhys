#include <iostream>  //needed to print to the screen
#include <fstream>
#include <math.h>

using namespace std;

#define N 1025


int main(){

    double x0=1.0;
    for (int i=1; i<N; i++) {
        double xnew=(x0)*2.0;
        x0=xnew;
        
        if(isinf(xnew)==true){
            cout<<"Highest power of 2 was "<<i-1<<" with value "<<pow(2.0,i-1)<<endl;
            break;
        }
    }
    
    return 0;
}


