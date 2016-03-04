set border 3 back ls 11
set tics nomirror

set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set key bottom right

set style line 1 lc rgb '#8b1a0e' pt 1 ps 1 lt 1 lw 2 
set style line 2 lc rgb '#5e9c36' pt 6 ps 1 lt 1 lw 2
     
plot "$0" using 1:xticlabels(2) title "$1" with linespoints linestyle 1