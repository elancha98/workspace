r = [2.70, 2.0, 1.61, 1.20, 1.02];
a = [48, 67, 83, 108, 126];
a = a * pi/180;

[coeff, norm2_res] = polminquad(r .* cos(a), r, 1);

p = coeff(2)
e = -coeff(1)


t = -pi:0.01:pi;
figure(1);
plot(r.*cos(a), r.*sin(a), "@r", "linewidth", 5, p*cos(t)./(1+e*cos(t)),
  p*sin(t)./(1+e*cos(t)), "b", "linewidth", 2);
title('aproximacion de p y e');


t = 48*pi/180:0.01:126*pi/180;

[coeff, norm2_res] = polminquad(a, r, 3);
figure(2);
plot(polyval(coeff, t) .* cos(t), polyval(coeff, t) .* sin(t), "b",
  "linewidth", 2, r.*cos(a), r.*sin(a), "@r", "linewidth", 5);
title('aproximacion de r(\phi) de grado 3', "interpreter", "tex");


[coeff, norm2_res] = polminquad(a, r, 4);
figure(3);
plot(polyval(coeff, t) .* cos(t), polyval(coeff, t) .* sin(t), "b",
  "linewidth", 2, r.*cos(a), r.*sin(a), "@r", "linewidth", 5);
title('aproximacion de r(\phi) de grado 4');