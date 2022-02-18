set term postscript eps enhanced size 2,2
set output 'cont1.ps'
#set term pstricks
#set output 'cont1.tex'
#unset border
a=0.4
f(x,y)=( 1/(1+(x/a)**2) ) * ( 1/(1+(y/a)**2) )
set xrange[-2:2]
set yrange[-2:2]
set zrange[-1:1]
unset key
set ticslevel 0
unset xtics
unset ytics
unset ztics
set view 0,0,1,1
#set samples 100,100
#11 lines pour les x (de 0 Ã  10), 13 pour les y
set isosamples 50, 50
set cntrparam levels incremental 0.05, 0.1, 0.95
set noclabel
set nosurface
set contour
set arrow from 2,-2.3,0 to -2,-2.3,0
set label "{/Times-Italic F}_{/Times 2}" at 0,-2.8,0
set arrow from -2.3,2,0 to -2.3,-2,0
set label "{/Times-Italic F}_{/Times 1}" at -3,0,0
splot  f(x,y) lt 1

