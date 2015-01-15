#!/bin/sh
gnuplot -persist << PLOT
##### Normal Gnuplot Commands
set terminal postscript color enhanced
set output "run$1_plot.ps"
set xlabel "{/Symbol q}_{c.m.} (Deg.)"
set ylabel "d{/Symbol s}/d{/Symbol W} (mb/sr)"
set title "$2"
set logscale y
set yrange [0.01:10000]
plot "run$1_data.dat" using 1:2:3 with yerrorbars pt 7 lc rgb "black" title "Data",\
"run$1_theory.dat" using 1:2 with lines lc rgb "red" title "Theory"
exit
##### End Gnuplot Commands
PLOT
