#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
using namespace std;
mt19937 rgen;
uniform_real_distribution<double> uran (0.0, 1.0);

int seed;


int main(){
    seed=2;
    rgen=mt19937(seed);
    
    double T=10.0;
    int n=0;
    int N=100000;
    double x;
    
    std::ofstream outfile("randdist.txt");

    while (n<N) {
        x=pow(T,uran(rgen));
        outfile<<x<<endl;
        n++;
    }
    
    return 0;

}
