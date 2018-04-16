set term png size 1920,1080
set out "const_sigma.png"

set title "Geometric Brownian Motion with const. sigma"

set xrange [ 0 : 80000 ]
set yrange [ 0 : 200 ]

set xlabel "time [min]"
set ylabel "GBM value"

plot "gbm_const_sigma_1m_01.txt" with lines