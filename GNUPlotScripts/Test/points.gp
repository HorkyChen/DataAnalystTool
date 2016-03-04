set style fill solid 1.0 border -1
set style line 1 lc rgb 'red' pt 16 ps 2 lt 1 lw 2 
set style line 2 lc rgb '#8e9c36' pt 5 ps 2 lt 1 lw 2
set style line 3 lc rgb 'green' pt 6 ps 2 lt 1 lw 2
set style line 4 lc rgb 'blue' pt 31 ps 2 lt 1 lw 2
set style line 1 lc rgb 'red' pt 5 ps 2 lt 1 lw 2 
set style line 2 lc rgb '#8e9c36' pt 16 ps 2 lt 1 lw 2
set style line 3 lc rgb 'green' pt 31 ps 2 lt 1 lw 2
set style line 4 lc rgb 'blue' pt 6 ps 2 lt 1 lw 2
set style line 3 lc rgb 'green' pt 16 ps 2 lt 1 lw 2
set style line 4 lc rgb 'blue' pt 5 ps 2 lt 1 lw 2

plot for [i=1:"$1"] "$0" using i:xticlabel($1+1) ls i with $2 title columnheader