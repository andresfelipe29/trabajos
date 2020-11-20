set term pdf
f(x)=x
g(x)=1

set o 'speedup.pdf'
set title 'speedup'
set xlabel 'N procesadores'
set ylabel 't(1 procesador)/t(N procesadores)'
plot 'scaling.txt' u 1:3 w l t 'speedup', f(x) t 'speedup ideal'

set o 'eficiencia.pdf'
set title 'eficiencia paralela'
set xlabel 'N procesadores'
set ylabel 'speedup/N'
plot 'scaling.txt' u 1:4 w l t 'eficiencia', g(x) t 'eficiencia ideal'