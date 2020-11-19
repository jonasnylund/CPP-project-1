import matplotlib.pyplot as plt;
import numpy as np;


filename = "myfile.bin";
file = open(filename, "rb");

width = np.fromfile(file, dtype=int, count=1)[0];
height = np.fromfile(file, dtype=int, count=1)[0];

x = [];
y = [];

for i in range((width+1)*(height+1)):
	x.append(np.fromfile(file, dtype=float, count=1)[0]);
	y.append(np.fromfile(file, dtype=float, count=1)[0]);

# plt.scatter(x, y, 'b');

for i in range(width*height):
	plt.plot([x[i+1], x[i], x[i+width+1]], [y[i+1], y[i], y[i+width+1]], 'r')

# for i in range(width):
# 	plt.plot([x[(width+1)*(height+1)-width - 1 + i], x[(width+1)*(height+1)-width + i]], [y[(width+1)*(height+1)-width -1 + i], y[(width+1)*(height+1)-width + i]], 'r')

# for i in range(height):
# 	plt.plot([x[(i+1)*(width+1)-1], x[(i+2)*(width+1)-1]], [x[(i+1)*(width+1)-1], y[(i+2)*(width+1)-1]], 'r');

plt.show();