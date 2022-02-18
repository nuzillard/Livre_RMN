set term postscript eps enhanced size 2,2
set output 'surf1.ps'
#set term pstricks
#set output 'surf1.tex'
unset border
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
#set view 60,320,1,1
set samples 100,100
set isosamples 25, 25
set noclabel
set hidden3d
set arrow from -2,-2.3,0 to 2,-2.3,0
set label "{/Times-Italic F}_{/Times 1}" at 0,-2.9,0
set arrow from 2.3,2,0 to 2.3,-2,0
set label "{/Times-Italic F}_{/Times 2}" at 2.5,0,0
splot  f(x,y) lt 1

