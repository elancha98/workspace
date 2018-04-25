% Gauss-Seidel
function [x,iter]=g_s(A,b,x)
  format long e;
  [m,n]=size(A);
  tol=10^-12;
  for i=1:m
    if (abs(A(i,i)) < tol)
      printf('L element %d de la diagonal es igual a 0\n', i)
    endif
  endfor
  maxit=10;
  D=diag(diag(A));
  L=tril(A,-1);
  U=triu(A,1);
  BGS=(-1).*inv(D+L)*U;
  normB=norm(BGS,2);
  X1=sprintf('Norma sub-2 de B_GS: %f', normB);
  disp(X1);
  vap = eig(BGS);
  radesp = max(abs(vap));
  vconv = -log(radesp);
  X2 = sprintf('Radi espectral de B_GS: %f i la velocitat de convergencia = %f', radesp, vconv);
  disp(X2);
  if (radesp>=1)
    disp('Radi espectral de B mes gran o igual que 1. Gauss-Seidel no convergeix')
    return;
  endif;
  cGS=inv(D+L)*b;
  iter=0;
  errabs=1;
  x0=x;
  div = norm(b - A*x0, 2);
  xnext=x0;
  while ((abs(errabs)>tol) && (iter<maxit))
      x=xnext;
      iter=iter+1;
      xnext=BGS*x+cGS;
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
% >> g_s(A,b,x)