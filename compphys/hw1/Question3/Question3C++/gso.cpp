#include <iostream>
#include <math.h>


//define dimensionality; determines number of components for each vector. This code is only implemented to run 3D vectors but can easily be changed to run more
#define dim 3

using namespace std;
//reference dot product function, many dot products will be taken in the code
double dot(double a[dim],double b[dim]);

int main(int argc, char* argv[]){
    
    //initialize input vectors, a=v1 and b=b1 within the context of the homework problem
    double v1[dim]={0,0,0};
    double b1[dim]={0,0,0};
    
    //lets user know they need to enter the starting components if they have not done so
    if (argc < 7){
        std::cerr << "Please enter 3D vector components for vectors a and b (six components total, each seperated by a space)"<<endl;
        return 0;
    }
    
    //user input becomes vector components
    v1[0]=atof(argv[1]);
    v1[1]=atof(argv[2]);
    v1[2]=atof(argv[3]);
    
    b1[0]=atof(argv[4]);
    b1[1]=atof(argv[5]);
    b1[2]=atof(argv[6]);
    
    //dot products which will be used to define c
    double magnb2=dot(b1,b1);
    double magna2=dot(v1,v1);
    
    //definition of c
    double c=sqrt(magnb2/(magnb2-(dot(v1,b1)*dot(v1,b1))/magna2));
        
    //prevents error induced if denominator of c=0, instead assumes solution of {0,0,0}
    if (isinf(c)==true) {
        c=0;
    }
    //initialize vector to exhibit magnitude = |b1| and orthognal to v1
    double v2[dim]={0,0,0};
    
    //apply gso to find v2 components
    for (int i=0; i<dim; i++) {
        v2[i]=c*(b1[i]-(dot(v1,b1)/magna2)*v1[i]);
    }

    //outputs produced vectors, and their dot product;
        cout<<"Vectors produced are v1 components:"<<endl;
        for (int i=0; i<dim; i++) {
            if (i!=2) {
                cout<<v1[i]<<",";
            }
            if (i==2) {
                cout<<v1[i]<<endl;
            }
        }
        
        cout<<"And v2 components:"<<endl;
        for (int i=0; i<dim; i++) {
            if (i!=2) {
                cout<<v2[i]<<",";
            }
            if (i==2) {
                cout<<v2[i]<<endl;
            }
        }
        cout<<"Value of their dot product is "<<dot(v1,v2)<<endl;
        

    
    //final output to check |v2|=|b1|;

    cout<<"|v2|-|b|=  "<<sqrt(dot(v2,v2))-sqrt(dot(b1,b1))<<endl;
    
    
    return 0;
}

//definition of dot product function, takes two vectors and returns their dot product
double dot(double a[dim],double b[dim]){
    double dot=0;
    for (int i=0; i<dim; i++) {
        dot+=a[i]*b[i];
    }
    return dot;
}
