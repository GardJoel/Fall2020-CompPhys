v1=10*rand([1 3]);
v2=[0.0 0.0 0.0];
b=10*rand([1 3]);

vdot=dot(v1,v1);
bdot=dot(b,b);
vbdot=dot(v1,b);

c=sqrt(bdot/(bdot-vbdot*vbdot/vdot));

for i=1:3
v2(i)=c*(b(i)-(vbdot/vdot)*v1(i));
end
disp("v1 and v2 are:")
disp(v1);
disp(v2);
disp("The dot product is "+dot(v1,v2))
disp("|v2|-|b|= "+(sqrt(dot(v2,v2))-sqrt(bdot)))
