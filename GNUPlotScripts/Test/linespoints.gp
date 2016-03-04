set style line 1 lc rgb '#8b1a0e' pt 6 ps 2 lt 1 lw 2 
set style line 2 lc rgb '#5e9c36' pt 5 ps 2 lt 1 lw 2
plot for [i=1:$1] "$0" using i with linespoints ls i