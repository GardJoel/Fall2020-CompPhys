#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>


using namespace std;

vector<vector<double> > creatematrix(int i,int j);

int main(){
    int Narray[8]={10,20,50,100,200,500,1000,2000};
    int N=0;
    
    for(int run=0;run<8;run++){
        N=Narray[run];
    

    vector<vector<double> > A=creatematrix(N,N);
    vector<vector<double> > id=creatematrix(N,N);
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i==j) {
                id[i][j]=1.0;
            }
            else{
                id[i][j]=0.0;
            }
        }
    }

    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i==j) {
                A[i][j]=2.0/double(N+1);
            }
            else{
                A[i][j]=1.0/double(N+1);
            }
        }
    }
    
    vector<vector<double> > diff=creatematrix(N,N);
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            diff[i][j]=id[i][j]-A[i][j];
        }
    }
    
    int kmax=100;
    int kiter=2;
    vector<vector<double> > powmatrix=diff;
    vector<vector<double> > tempmatrix=creatematrix(N,N);
    vector<vector<double> > summatrix=diff;

    auto start=std::chrono::steady_clock::now();

    while(kiter<=kmax){
        for (int l=0; l<N; l++){
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                tempmatrix[l][i]+=powmatrix[l][j]*diff[j][i];
            }
        }
        }
        
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                summatrix[i][j]+=tempmatrix[i][j]/double(kiter);
                powmatrix[i][j]=tempmatrix[i][j];
            }
        }
        
        for (int i=0; i<N; i++) {
                   for (int j=0; j<N; j++) {
                       tempmatrix[i][j]=0.0;
                   }
               }
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
    outname1="/users/joelgard/Desktop/compphys/Midterm/Matrix/cppnvt.txt";
    std::ofstream outfile1;
    outfile1.open(outname1.c_str(),ios_base::app);
        
        outfile1<<N<<","<<timediff.count()/1000000.0<<endl;
        outfile1.close();
       
    }
	return 0;
}

vector<vector<double> > creatematrix(int i,int j){
    vector<vector<double> > matrix;
    vector<double> ddim;
    for (int k=0; k<i; k++) {
        ddim.push_back(0.0);
    }
    
    for (int k=0; k<j; k++) {
        matrix.push_back(ddim);
    }
    
    return matrix;
}
