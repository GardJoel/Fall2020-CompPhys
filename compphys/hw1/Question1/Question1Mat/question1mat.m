
qfile=fopen('q1.txt','w');

for titer=0:20
   t0=2.0;
   x0=xcal(t0);
   xprime=9.0*exp(-t0)/((1.0+9.0*exp(-t0))*(1.0+9.0*exp(-t0)));
   x=xcal(t0+power(10.0,titer));
   xprimest=est(x,x0,power(10.0,titer));
   diff=derivdiff(xprime,xprimest);
   fprintf(qfile,'%f,%f\n',power(10.0,titer),diff);
end


function x=xcal(t)
	x=1.0/(1.0+9.0*exp(-t));
end

function xprimeest=est(a,b,dt)
    xprimeest=(a-b)/dt;
end

function diff=derivdiff(x,x0)
    diff=abs(x-x0);
end

