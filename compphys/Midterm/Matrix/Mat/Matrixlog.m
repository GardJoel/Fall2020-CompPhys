for niter=1:8
N=[10 20 50 100 200 500 1000 2000];
n=N(niter);
A=zeros(n,n);
id=zeros(n,n);
diff=zeros(n,n);
temp=zeros(n,n);
pow=zeros(n,n);
sum=zeros(n,n);

 for i=1:n
    for k=1:n
        if i==k
           A(i,k)=2.0/(n+1);
           id(i,k)=1.0;
        end
        if i~=k
           A(i,k)=1.0/(n+1);
           id(i,k)=0.0;
        end
    end
 end
diff=id-A;
sum=diff;
pow=diff;
kmax=100.0;
kiter=2.0;
tic
 while kiter<=kmax
  temp=pow*diff;
  pow=temp;
  sum=sum+pow/kiter;
    
  kiter=kiter+1;
 end

sum=-sum;

out=[n;toc];

fileID = fopen('/Users/joelgard/Desktop/compphys/Midterm/Matrix/Mat/matnvt.txt','a');
fprintf(fileID,'%6.2f %12.8f\n',out);
fclose(fileID);


end