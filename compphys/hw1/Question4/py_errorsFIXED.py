import numpy as np  #import numpy, for arrays
import math			#import math, for power and abs

n=10 #size of the arrays

matrix=np.zeros((n,n))	#create an array of zeros of size n
for i in range(n):		#loop over i
	for j in range(n):	#loop over j
		matrix[i,j]=np.power(abs(i-j),2)  #compute |i-j|^2; was missing np.

print(matrix)#print the desired matrix; took out loops to instead simply display matrix directly
