import numpy as np
import matplotlib.pyplot as plt

with open('bin/TimeState.txt') as f:
    lines = f.readlines()
    time = [float(line.split()[0]) for line in lines]
    control = [float(line.split()[1]) for line in lines]
    f = plt.figure()
    f.set_figwidth(15)
    f.set_figheight(10)
    plt.plot(time, control)
    plt.savefig("PID_Plot.png")
    plt.show()