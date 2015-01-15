#!/bin/sh
gnuplot -persist << PLOT
##### Normal Gnuplot Commands
set terminal postscript color enhanced
set output "run406_run407_plot.ps"
set xlabel "{/Symbol q}_{c.m.} (Deg.)"
set ylabel "d{/Symbol s}/d{/Symbol W} (mb/sr)" 
set title "Combined Overlay Plot"
set logscale y
set yrange [0.001:10000]
plot "run406_theory.dat" using 1:2 with lines linecolor rgb "#FF0000" title "^{12}C(^{3}He,^{3}He)^{12}C at 20 MeV  ", "run407_theory.dat" using 1:2 with lines linecolor rgb "#D2691E" title "^{14}N(^{3}He,^{3}He)^{14}N at 20 MeV  "
exit
##### End Gnuplot Commands
PLOT
