import numpy as np
import random as random

v1=[random.uniform(0.0,10.0),random.uniform(0.0,10.0),random.uniform(0.0,10.0)]
v2=[0.0,0.0,0.0]
b=[random.uniform(0.0,10.0),random.uniform(0.0,10.0),random.uniform(0.0,10.0)]

dotb=np.dot(b,b)
dotv=np.dot(v1,v1)
dotvb=np.dot(v1,b)

c=np.sqrt(dotb/(dotb-(dotvb*dotvb)/dotv))

for i in range(0,3):
    v2[i]=c*(b[i]-(dotvb/dotv)*v1[i])
    
print(v2)
print(v1)
print(np.dot(v1,v2))
