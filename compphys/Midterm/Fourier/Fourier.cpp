#include <iostream>
#include <math.h>
#include <cmath>
#include <complex>
#include <fstream>
#include <sstream>
#include <vector>

#define pi 3.14159265359

using namespace std;
typedef complex<double> dcomp;


int main(){
    vector<double> x;
    dcomp ci=-1.0;
    ci=sqrt(ci);
	std::string
    data="/users/joelgard/Desktop/compphys/Midterm/Fourier/data.csv";
    
    std::ifstream datafile;
    datafile.open(data.c_str());
    std:: string dataline;
    
    while(std::getline(datafile,dataline,',')){
        
        x.push_back(atof(dataline.c_str()));
                
    }
    datafile.close();
    
    dcomp xprime[128];
    
    for (int k=0; k<x.size(); k++) {
        for (int j=0; j<x.size(); j++) {
            xprime[k]+=x[j]*exp(-ci*double(2*pi*k*j)/128.0);
        }
    }
    
    std::string
    outname="/users/joelgard/Desktop/compphys/Midterm/Fourier/fourier.txt";
    std::ofstream outfile;
    outfile.open(outname.c_str());
    for (int k=0; k<128; k++) {
        outfile<<abs(xprime[k])*abs(xprime[k])/128.0<<endl;
    }
    outfile.close();
    
    double y[128]={0};
    y[127]=(x[1]+x[0])/2.0;
    
    for (int k=0; k<127; k++) {
        y[k]=(x[k+1]+x[k])/2;
    }
    
    dcomp yprime[128];
    
    for (int k=0; k<128; k++) {
        for (int j=0; j<128; j++) {
            yprime[k]+=y[j]*exp(-ci*double(2*pi*k*j)/128.0);
        }
    }
    
    std::string
    outname1="/users/joelgard/Desktop/compphys/Midterm/Fourier/fourier2.txt";
    std::ofstream outfile1;
    outfile1.open(outname1.c_str());
    for (int k=0; k<128; k++) {
        outfile1<<abs(yprime[k])*abs(yprime[k])/128.0<<endl;
    }
    outfile1.close();
    
	return 0;
}


