format long e;
e100 = 0.01*100;
b100 = b + 0.1*cos(e100)*e1;

x = A \ b100;
norm(x,1)