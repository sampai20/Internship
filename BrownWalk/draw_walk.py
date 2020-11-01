import random
from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
f = open("recentwalk.txt", 'r')
x = []
y = []
for line in f:
	x.append(float(line.split()[0]))
	y.append(float(line.split()[1]))

point_color = list(range(len(x)))
plt.scatter(x, y, s=1, cmap=plt.cm.Greens)
plt.show()