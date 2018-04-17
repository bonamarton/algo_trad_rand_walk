
set term png size 1200,675
set out "const_sigma.png"

set title "Geometric Brownian Motion with constant sigma parameter"

set xrange [ 0 : 30000 ]
set yrange [ 90 : 110 ]

set xlabel "time [min]"
set ylabel "GBM value"

plot "gbm_const_sigma_1m_01.txt" title "mu = -0.5" with line, \
	"gbm_const_sigma_1m_02.txt" title "mu = -0.2" with line, \
	"gbm_const_sigma_1m_03.txt" title "mu = 0.0" with line, \
	"gbm_const_sigma_1m_04.txt" title "mu = 0.2" with line, \
	"gbm_const_sigma_1m_05.txt" title "mu = 0.5" with line
