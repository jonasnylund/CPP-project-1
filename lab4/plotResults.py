import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d

def true_vals(x, y, mode):
    if mode == "xder":
        return (1/50)*(x*np.cos(x/10)*np.cos(x**2/100) - 5*np.sin(x/10)*np.sin(x**2/100))
    elif mode == "yder":
        return 1
    elif mode == "Laplace":
        return (1/2500)*(np.cos(x/10)*(50*np.cos(x**2/100) - (x**2 + 25)*np.sin(x**2/100)) - 10*x*np.sin(x/10)*np.cos(x**2/100))

def main():
    clrs = ["blue", "red", "green", "yellow"]
    variants = ["u", "xder", "yder", "Laplace"]
    # variants = ["u", "xder"]

    for i, filename_base in enumerate(variants):
        filename = filename_base + ".txt"
        with open(filename, 'r') as f:
            lines = list(f.readlines())
            rows, cols = lines[0].split(", ")
            lines = lines[1:]
            lines = np.vstack(tuple(line.strip("\n").split(", ") for line in lines))
            data = np.array(lines, dtype='float32')

        fig = plt.figure()
        ax = plt.axes(projection='3d')

        err_fig = plt.figure()
        err_ax = plt.axes(projection='3d')

        x = data[:,0]
        y = data[:,1]
        z = data[:,2]
        
        ax.scatter(x, y, z, c=clrs[i])
        if i > 0:
            true_z = true_vals(x, y, mode=variants[i])
            ax.scatter(x, y, true_z, c='k')
            err_ax.scatter(x, y, np.abs(z - true_z), c = 'r')
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        ax.set_title(variants[i])
        err_ax.set_xlabel("x")
        err_ax.set_ylabel("y")
        err_ax.set_zlabel("z")
        err_ax.set_title(variants[i]+" abs. err.")
    
    plt.show()

if __name__ == "__main__":
    main()
