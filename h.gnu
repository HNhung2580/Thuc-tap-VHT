reset
n = 10000 #number of sample
max = 500000 #max value
min = 0 #min value
width = (max - min)/n #interval width

#function used to map a value to the intervals
hist(x,width) = width*floor(x/width)+width/2.0


set xrange [min:max]
set yrange [0:]

#to put an empty boundary around the
#data inside an autoscaled graph.

set xlabel "Sample"
set ylabel "Frequency"
set title "Histogram of the interval value"

#count and plot
plot "time_and_interval.txt" u (hist($1,width)):(1.0) smooth freq w boxes lc rgb"blue" notitle
