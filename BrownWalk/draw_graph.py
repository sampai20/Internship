import random
from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
data = []
with open("data.txt", 'r') as f:
	for line in f:
		data.append(float(line))
plt.plot(data)
plt.title("Average Maximal Distance vs. Time")
plt.xlabel("Time")
plt.ylabel("Average Maximal Distance")
plt.show()