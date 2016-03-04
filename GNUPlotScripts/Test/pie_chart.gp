reset
#set term postscript eps color enhanced size 5cm,5cm
#set output "pie_chart.eps"

set angles degrees
set size square
set style fill solid 1.0 border -1

set object 1 circle at screen 0.45,0.45 size \
  screen 0.3 arc [0   :50  ] fillcolor rgb "red" front
angle = 50/2
set label 1 '1989' at  screen (0.45+0.35*cos(angle)),(0.45+0.35*sin(angle))

set object 2 circle at screen 0.45,0.45 size \
  screen 0.3 arc [50  :150] fillcolor rgb "orange" front
angle = 50+(150-50)/2
set label 2 '1990' at  screen (0.45+0.35*cos(angle)),(0.45+0.35*sin(angle))

set object 3 circle at screen 0.45,0.45 size \
  screen 0.3 arc [150:220] fillcolor rgb "forest-green" front
angle = 150+(220-150)/2
set label 3 '1991' at  screen (0.45+0.35*cos(angle)),(0.45+0.35*sin(angle))

set object 4 circle at screen 0.45,0.45 size \
  screen 0.3 arc [220:330] fillcolor rgb "dark-magenta" front
angle = 220+(330-220)/2
set label 4 '1992' at  screen (0.45+0.35*cos(angle)),(0.45+0.35*sin(angle))

set object 5 circle at screen 0.45,0.45 size \
  screen 0.3 arc [330:360] fillcolor rgb "yellow" front
angle = 330+(360-330)/2
set label 5 '1993' at  screen (0.45+0.35*cos(angle)),(0.45+0.35*sin(angle))

#plot a white line, i.e., plot nothing
unset border
unset tics
unset key
plot x with lines lc rgb "#ffffff"
set output
