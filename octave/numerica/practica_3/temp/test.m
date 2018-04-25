format long;

for (u = 0:0.1:2*pi)
  for (v = 0:0.1:2*pi)
    B = [-sin(u), cos(u); cos(v), -sin(v)];
    A = inv(B);
    res = A(1,1)^2 + A(1,2)^2 - A(2,1)^2 - A(2,2)^2;
    if (res != 0)
      res
      u
      v
      B
      A
      A(1,1)^2 + A(1,2)^2
      A(2,1)^2 + A(2,2)^2
      return;
    endif
  endfor
endfor