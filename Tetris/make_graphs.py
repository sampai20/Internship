import random
from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
sm, bi, av, st = [], [], [], []
with open("100w_exp_small", 'r') as f:
	for line in f:
		st.append(float(line.split()[0]))

sm_slope = [sm[i] / (i/10) for i in range(1, len(sm))]
bi_slope = [bi[i] / (i/10) for i in range(1, len(bi))]
av_slope = [av[i] / (i/10) for i in range(1, len(av))]
st_sqr = [st[i] * st[i] for i in range(len(st))]
st_line = [pow(st[i], 3) for i in range(len(st))]
xax = [i/10 for i in range(len(st))]
axs, figs = plt.subplots(3)
plt.suptitle("Plots for N = 1000", y=1.08)
figs[2].plot(xax, st_line)
figs[0].plot(xax, st)
figs[1].plot(xax, st_sqr)
figs[0].title.set_text("Standard Deviation vs. Time")
figs[1].title.set_text("Standard Deviation Squared vs. Time")
figs[2].title.set_text("Standard Deviation Cubed vs. Time")
plt.tight_layout()
plt.show()