% Sobre-relaxacio, si w == -1, agafarem el w optimitzat
% -2 si es tridiagonal per blocs i podem usar la formula per optimitzar w
 function [x,iter]=s_r(A,b,x,w)
   format long e;	
  tol=10^-12;
  maxit=10;
  L = tril(A,-1); % es el mateix que: tril(A) - diag(diag(A));
  U = triu(A,1); % es el mateix que: triu(A) - diag(diag(A));
  D = diag(diag(A));

  if (w == -1)
    w_aux = 0.001;
    radesp = 1;
    while (w_aux < 2)
      Bwaux=inv(D+(w_aux*L))*(((1-w_aux)*D) - (w_aux*U));
      vap = eig(Bwaux);
      radesp_aux = max(abs(vap));
      if (radesp_aux < radesp)
        radesp = radesp_aux;
        w = w_aux;
      endif
      w_aux = w_aux + 0.001;
    endwhile
  endif
  if (w == -2)
    D=diag(diag(A));
    BJ=inv(D)*(D-A);
    vap = eig(BJ);
    radesp = max(abs(vap));
    w = 2/(1+(1-radesp^2)^(1/2));
    Bw=inv(D+(w*L))*(((1-w)*D) - (w*U));
    vap = eig(Bw);
    radesp = max(abs(vap));
    X1 = sprintf('\nSi es correcte, el seguent nombre ha de ser 0: %f\n', radesp-w+1);
    disp(X1);
  endif

  Bw=inv(D+(w*L))*(((1-w)*D) - (w*U));
  normB=norm(Bw,2);
  X1=sprintf('w = %f, norma sub-2 de B_w: %f', w, normB);
  disp(X1);
  vap = eig(Bw);
  radesp = max(abs(vap));
  vconv = -log(radesp);
  X2 = sprintf('Radi espectral de B_w: %f i la velocitat de convergencia = %f', radesp, vconv);
  disp(X2)
  if (radesp>=1)
    disp('Radi espectral de B_w mes gran o igual que 1. Sobre-relaxacio no convergeix')
    return;
  endif;
  Cw=w*inv(D+(w*L))*b;
  iter=0;
  errabs=1;
  x0=x;
  div = norm(b - A*x0, 2);
  xnext=x0;
  while ((abs(errabs)>tol) && (iter<maxit))
      x=xnext;		 
      iter=iter+1;
      xnext=Bw*x+Cw;
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
% >> s_r(A,b,x, -1)

% Exemple 2:
% >> A=[4 0 1 1;0 4 0 1;1 0 4 0;1 1 0 4];
% >> x=[0 0 0 0]';
% >> b=[1 2 3 4]';
% >> s_r(A,b,x,-1);