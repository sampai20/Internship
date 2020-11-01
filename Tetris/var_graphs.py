import random
from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
l = []
with open("exp_small", "r") as f:
	for line in f:
		l.append(float(line))
xax = [10*i for i in range(len(l))]
plt.title("Average standard deviation as a function of N")
plt.plot(xax, l)
plt.show()
