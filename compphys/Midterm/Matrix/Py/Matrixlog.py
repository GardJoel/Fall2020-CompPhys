import numpy as np  #import numpy, for arrays
import math			#import math, for power and abs
import time

N=np.array([10,20,50,100,200,500,1000,2000]) #size of the arrays
n=0;
farray=np.zeros((8,2))
for p in range(8):
    n=N[p];
    farray[p][0]=n;
    A=np.zeros((n,n))
    I=np.zeros((n,n))
    summatrix=np.zeros((n,n))
    start=time.time()
    for i in range(n):
        for j in range(n):
            if i==j:
                A[i][j]=2.0/(n+1.0)
                I[i][j]=1.0
            else:
                A[i][j]=1.0/(n+1.0)
                I[i][j]=0.0
    for k in range (1,101):
        summatrix=summatrix+(np.linalg.matrix_power(I-A, k))/k
    summatrix=-summatrix
    end=time.time()
    farray[p][1]=end-start


np.savetxt("pynvt.txt",farray,fmt="%.4e")
