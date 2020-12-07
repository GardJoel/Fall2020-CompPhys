#include "Eigen/Eigenvalues"
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


int main(){
    Eigen::MatrixXd matrix(50,50);
    
    for (int i=0; i<50; i++) {
        for (int j=0; j<50; j++) {
            if (abs(i-j)<3) {
                matrix(i,j)=1.0;
            }
            else{
                matrix(i,j)=0.0;
            }
        }
    }
        
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(matrix);
    
    cout<<"The largest eigenvalue is:"<<endl;
    cout<<es.eigenvalues()(49)<<endl<<endl;
    cout<<"The unit Eigenvector corresponding to the largest Eigenvalue is:"<<endl;
    cout<<es.eigenvectors().col(49)<<endl<<endl;
    double b0[50];
    for (int i=0; i<50; i++) {
        b0[i]=1.0;
    }
    double bk[50]={0.0};
    double epsilon=5;
    double diff[50];
    double mag1=5;
    int iter=0;
    while (epsilon>0.000001*mag1) {
        double mag=0;
        for (int i=0; i<50; i++) {
            mag+=b0[i]*b0[i];
        }
        
        mag=sqrt(mag);
        
        for (int i=0; i<50; i++) {
            for (int j=0; j<50; j++) {
                bk[i]+=matrix(i,j)*b0[j]/mag;
            }
        }
        
        epsilon=0;
        for (int i=0; i<50; i++) {
            diff[i]=bk[i]-b0[i];
            epsilon+=diff[i]*diff[i];
            b0[i]=bk[i];
        }
        for (int i=0; i<50; i++) {
            bk[i]=0.0;
        }
        mag=0;
           for (int i=0; i<50; i++) {
                 mag+=b0[i]*b0[i];
             }
             mag1=sqrt(mag);
        epsilon=sqrt(epsilon);
        iter++;
    }
    cout<<"b_kmax has components:"<<endl;
    for (int i=0; i<50; i++) {
        cout<<b0[i]<<endl;
    }
    cout<<"normalized b_kmax components compared to normalized principle eigenvector:"<<endl;
    
    for (int i=0; i<50; i++) {
        cout<<b0[i]/mag1<<","<<es.eigenvectors().col(49)(i)<<endl;
    }
    
    cout<<"M.b_kmax directly compared to lambda.b_kmax :"<<endl;
    double mbk[50];
    double lambdabk[50];
    for (int i=0; i<50; i++) {
        for (int j=0; j<50; j++) {
            mbk[i]+=matrix(i,j)*b0[j];
        }
        lambdabk[i]=es.eigenvalues()(49)*b0[i];
    }
    for (int i=0; i<50; i++) {
        cout<<mbk[i]<<","<<lambdabk[i]<<endl;
    }
	return 0;
}


