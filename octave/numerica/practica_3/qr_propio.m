function [Q, R] = qr_propio(A)
  Q = A;
  for (i = 1:length(Q(1, :)))
    n = norm(Q(:, i));
    R(i, i) = n;
    Q(:, i) /= n;
    for (j = i+1:length(Q(1, :)))
      R(i, j) = dot(Q(:, i), Q(:, j));
      Q(:, j) -= R(i,j) * Q(:, i);
    endfor
  endfor
endfunction