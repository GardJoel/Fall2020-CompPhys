data1=load('data_3.csv');
tvals=data1(:,1);
xvals=data1(:,2);

vals=[100000,.0001];  %initial guess.  We have 3 parameters in our fit function
bestfit=fminsearch(@(x)lsquares(tvals,xvals,@fitfunction,x),vals);  
%minimize the squared error.  Note that matlab doesn't have an easy
%single function that performs a least squares search, so we had to 
%define a function to do it by defining lsquares (squared error between data 
%and fit), and using the fminsearch function to minimize that.
figure %plot data and fit
hold on
plot(tvals,xvals,'o')
plot(tvals,fitfunction(tvals,bestfit),'k','Linewidth',2)
title('Biexponential Fit');
xlabel('t');
ylabel('x(t)');

disp(bestfit);


function x=fitfunction(t,params)
    A=params(1);
    omega=params(2);
    x=A*exp(-t/omega);  %our fit function
end

function d=lsquares(tvals,xvals,fitfunction,params)  %computes the squared error between fit and data
    d=sum((xvals-fitfunction(tvals,params)).^2);
end
