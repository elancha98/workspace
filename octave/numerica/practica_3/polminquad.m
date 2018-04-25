function [coeff,norm2_res] = polminquad(x, y, m)
  A = ones(length(x), m+1);
  for (i = m:-1:1)
    A(:, i) = x' .* A(:, i+1);
  endfor
  [Q,R] = qr_propio(A);
  norm(Q'*Q - eye(length(Q(1, :))))
  z = Q' * y';
  coeff = zeros(1, m+1);
  coeff(end) = z(end) / R(end, end);
  for (i = m:-1:1)
    coeff(i) = (z(i) - R(i, :)*coeff')/R(i,i);
  endfor
  norm2_res = norm(A*coeff'-y')
endfunction