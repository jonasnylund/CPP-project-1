import matplotlib.pyplot as plt
import numpy as np


filename = "myfile.bin"
file = open(filename, "rb")

width = np.fromfile(file, dtype=np.int32, count=1)[0]
height = np.fromfile(file, dtype=np.int32, count=1)[0]

x = []
y = []

print(width, height)

for i in range((width+1)*(height+1)):
	x.append(np.fromfile(file, dtype=np.float64, count=1)[0])
	y.append(np.fromfile(file, dtype=np.float64, count=1)[0])

# plt.scatter(x, y, 'b');
x = np.array(x).reshape((height+1, width+1))
y = np.array(y).reshape((height+1, width+1))

for i in range(height+1):
	plt.plot(x[i,:], y[i,:], 'r-')

for i in range(width+1):
	plt.plot(x[:,i], y[:,i], 'r-')

plt.show()