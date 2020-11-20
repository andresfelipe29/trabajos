set term pdf

set o 'speedup.pdf'
set title 'speedup'
set xlabel 'N procesadores'
set ylabel 't(1 procesador)/t(N procesadores)'
plot 'scaling.txt' u 1:3

set o 'eficiencia.pdf'
set title 'eficiencia paralela'
set xlabel 'N procesadores'
set ylabel 'speedup/N'
plot 'scaling.txt' u 1:4