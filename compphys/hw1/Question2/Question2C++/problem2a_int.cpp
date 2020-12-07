#include <iostream>  //needed to print to the screen
#include <fstream>
#include <math.h>

using namespace std;

#define N 35


int main(){

    int x0=1;
    for (int i=1; i<N; i++) {
        int xnew=(x0)*2;
        x0=xnew;
        if(isnan(sqrt(xnew))==true){
        cout<<"Highest power of two was "<<i-1<<" with value "<<int(pow(2,i-1))<<endl;
            break;
        }
    }
    
    return 0;
}


