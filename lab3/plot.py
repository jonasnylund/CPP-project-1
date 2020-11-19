import matplotlib.pyplot as plt;
import numpy as np;


filename = "output.bin";
file = open(filename, "rb");

width = np.fromfile(file, dtype=int, count=1);
height = np.fromfile(file, dtype=int, count=1);

x = [];
y = [];

for i in range((width+1)*(height+1)):
	x.append(np.fromfile(file, dtype=float, count=1));
	y.append(np.fromfile(file, dtype=float, count=1));


plt.scatter(x, y);
plt.show();