% Jacobi
function [x,iter]=jacobi(A,b,x)
  format long e;
  pi
  [m,n]=size(A);
  tol=10^-12;
  for i=1:m
    if (abs(A(i,i)) < tol)
      printf('L element %d de la diagonal es igual a 0\n', i)
    endif
  endfor
  maxit=10;
  D=diag(diag(A));
  BJ=inv(D)*(D-A);
  normB=norm(BJ,2);
  X1=sprintf('Norma sub-2 de B_J: %f', normB);
  disp(X1)
  vap = eig(BJ);
  radesp = max(abs(vap));
  vconv = -log(radesp);
  X2 = sprintf('Radi espectral de B_J: %f i la velocitat de convergencia: %f', radesp, vconv);
  disp(X2);
  if (radesp>=1)
    disp('Radi espectral de B mes gran o igual que 1. Jacobi no convergeix')
    return;
  endif
  cJ=inv(D)*b;
  iter=0;
  errabs=1;
  x0=x;
  div = norm(b - A*x0, 2);
  xnext=x0;
  while ((abs(errabs)>tol) && (iter<maxit))
      x=xnext;
      iter=iter+1;
      xnext=BJ*x+cJ;
      disp("res_"); disp(iter); disp(": "); disp(norm(b-A*x, 2)/div); disp("\n");
      disp("norm_"); disp(iter); disp(": "); disp(norm(x, inf)); disp("\n");
      errabs=norm(xnext-x,inf);
  endwhile
  XD=sprintf('\nEstimacio error absolut a la solucio iterativa: %e',errabs);
  disp(XD)
  XD1=sprintf('\nIteracions usades: %d \n',iter);
  disp(XD1)
  disp('Solucio aproximada:');
  disp(xnext)
endfunction


% Exemple de crida des de la finestra de comandes:
% >> A=[5 -2 1;-1 -7 3;2 -1 8];
% >> x=[0 0 0]';
% >> b=[3 -2 1]';
% >> jacobi(A,b,x)