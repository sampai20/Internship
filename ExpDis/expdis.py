import random
from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import normaltest
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
def getnextpos(curpos, p, q, timestep):
	if random.random() < p * timestep:
		curpos += 1
	if random.random() < q * timestep:
		curpos -= 1
	return curpos


def simulate(p, q, timestep, numsteps):
	l = [0]
	for i in range(numsteps):
		l.append(getnextpos(l[-1], p, q, timestep))
	return l

def avg_sim(p, q, timestep, numsteps, n, f):
	s = 0
	for i in tqdm(range(n)):
		l = simulate(p, q, timestep, numsteps)
		#print(l)
		f.write(str(l[-1]) + "\n")
		#s += l[-1]
	return s / n

def eq_bin(x):
	return [(0.25 + 0.5 * a)/(2 ** x) for a in range(3 * (2 ** x), 9 * (2**x))]

def draw_hist(time):
	f = open("4-1-0.0001-1000000.txt", "r")
	l = []
	for line in f:
		l.append(int(line) / time)
	plt.hist(l, eq_bin(3))
	plt.title("Frequency of Average Speeds")
	plt.xlabel("Average Speed")
	plt.ylabel("Number of Occurrences")
	stat, p = normaltest(l)
	print(stat, p)

draw_hist(100)
#avg_sim(4, 1, 0.001, 100000, 10000, f)
plt.show()