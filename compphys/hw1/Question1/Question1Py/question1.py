import numpy as np
import matplotlib.pyplot as plt

t0=2.0

xprime=9.0*(np.exp(-t0))/(1.0+9.0*(np.exp(-t0)))/(1.0+9.0*(np.exp(-t0)))

q1file=open('q1py.txt','w')

def x(t):
    return 1.0/(1.0+9.0*(np.exp(-t)))

def xprimeest(x0,x,deltat):
    return ((x-x0)/deltat)
    
def derivdiff(prime,estprime):
    return np.abs(prime-estprime)
    
x0=x(t0)

for t in range(0,-20,-1):
    xnew=x(t0+np.power(10.0,-t))
    xest=xprimeest(x0,xnew,np.power(10.0,-t))
    xvals=np.power(10.0,-t)
    yvals=derivdiff(xprime,xest)
    plt.loglog(xvals,yvals,'b.')
    plt.suptitle('Deviation of Derivative Estimate')
    plt.xlabel('$\Delta$t')
    plt.ylabel('$\delta(\Delta t)$')
    q1file.write(str(np.power(10.0,-t))+","+str(derivdiff(xprime,xest))+"\n")

plt.savefig('q1.png')

plt.show()

q1file.close()
