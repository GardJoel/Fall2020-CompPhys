#include <iostream>  //needed to print to the screen
#include <math.h>    //can now run abs() funciton for absolute value

double squared(double x);  //declare the function to compute a square

using namespace std; //not needed to fix, just preference

#define N 10 //size of the array

int main(){
	
	double matrix[10][10]={0}; //create an array
	for(int i=0;i<N;i++){  //loop over i
		for(int j=0;j<N;j++){  //loop over j, this was fixed from being an infinite loop, i.e. j=0;j<N;i++ was changed to j=0;j<N;j++
            
            
            //below changed layout of value declaration for clarity and to ensure i-j is converted to double BEFORE abs is applied
			double value=abs((double)(i-j));  //compute |i-j|
			matrix[i][j]=squared(value);  // plug |i-j| into the matrix
		}
	}
	
    //below outputs fine, no changes made (could possible typeset for aligned columns but is easily readable in the current form)
	for(int i=0;i<N;i++){  //loop over i
		for(int j=0;j<N;j++){  //loop over j
			cout<<matrix[i][j]<<" ";  //print the matrix to the terminal
		}
		cout<<"\n";//print a new line
	}
	return 0;
}

//below, fixed function to take double as argument instead of int
double squared(double x){  //define the function to compute a square
	return x*x;  //compute x^2 and return it
}
