#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "Eigen/Dense"


using namespace std;
using namespace Eigen;


vector<vector<double> > creatematrix(int i,int j);

int main(){
    int Narray[8]={10,20,50,100,200,500,1000,2000};
    int N=0;
    
    for(int run=0;run<8;run++){
        N=Narray[run];
        MatrixXf A(N,N);
        MatrixXf id(N,N);
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i==j) {
                id(i,j)=1.0;
                A(i,j)=2.0/double(N+1);
            }
            else{
                id(i,j)=0.0;
                A(i,j)=1.0/double(N+1);
            }
        }
    }

    
    MatrixXf diff(N,N);
    
        diff=id-A;
    
    int kmax=100;
    int kiter=2;
    MatrixXf powmatrix=diff;
    MatrixXf tempmatrix(N,N);
    MatrixXf summatrix=diff;

    auto start=std::chrono::steady_clock::now();

    while(kiter<=kmax){

        tempmatrix=powmatrix*diff;

        
        summatrix+=tempmatrix/double(kiter);
        powmatrix=tempmatrix;
       
        
        MatrixXf tempmatrix(N,N);
        
        kiter++;
    }
        /*
    std::string
    outname="/users/joelgard/Desktop/compphys/Midterm/Matrix/cppout1.txt";
    std::ofstream outfile;
    outfile.open(outname.c_str());
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if(j<9){
            outfile<<-summatrix[i][j]<<",";
            }
            else{
                outfile<<-summatrix[i][j]<<endl;

            }
        }
    }
        outfile.close();
    */
        
    auto end=std::chrono::steady_clock::now();
    auto timediff=std::chrono::duration_cast<std::chrono::microseconds>(end-start);
      
    std::string
    outname1="/users/joelgard/Desktop/compphys/Midterm/Matrix/Cpp/cppnvteig.txt";
    std::ofstream outfile1;
    outfile1.open(outname1.c_str(),ios_base::app);
        
        outfile1<<N<<","<<timediff.count()/1000000.0<<endl;
        outfile1.close();
       
    }
	return 0;
}


