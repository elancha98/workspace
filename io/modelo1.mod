param n := 100;
param a := 1;
param b := 1;

set PUNTOS := 0..n;

param x {i in PUNTOS} := a*(i/n)^2; #quitaremos el ^2 para obtener la distribucion lineal

var y {i in PUNTOS}>=10e-8;

minimize tiempo:
	1/sqrt(2*9.8) * (sum {i in 1..n}
	sqrt(( (x[i] - x[i-1])^2 + (y[i] - y[i-1])^2)/y[i-1]));
	
subject to inicio:
	y[0] = 10e-8;
	
subject to final:
	y[n] = b;