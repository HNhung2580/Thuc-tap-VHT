reset
n = 10000 #number of sample
max = 0.0012 #max value
min = 0.0008 #min value
#width = (max - min)/n #interval width

#function used to map a value to the intervals
hist(x,width) = width*floor(x/width)+width/2.0

set xrange [0:n]

set yrange [min:max]

#to put an empty boundary around the
#data inside an autoscaled graph.

set xlabel "Sample"
set ylabel "Frequency"
set title "Graph of the interval value"

#count and plot
plot "time_and_interval" 
