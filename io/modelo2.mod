param n := 100;
param a := 1;
param b := 1;

set PUNTOS := 0..n;

var x {i in PUNTOS};
var y {i in PUNTOS}>=10e-8;

minimize tiempo:
	1/sqrt(2*9.8) * (sum {i in 1..n}
	sqrt(( (x[i] - x[i-1])^2 + (y[i] - y[i-1])^2)/max(10e-12,y[i-1])));
	
subject to inicio_x:
	x[0] = 0;
subject to inicio_y:
	y[0] = 10e-8;
subject to final_x:
	x[n] = a;
subject to final_y:
	y[n] = b;
	
subject to increment {i in 1..n}:
	x[i] - x[i-1] >= 10e-6
	