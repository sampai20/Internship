import random
from tqdm import tqdm
from math import *
from statistics import variance
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import normaltest
from matplotlib import colors
from matplotlib.ticker import PercentFormatter

EPS = 1/30
renorm = (1 / (2 * EPS) - 1 / (4 * pow(EPS, 0.5)) + 1/12)
curtime = 2/(EPS * EPS)
shift = 0

def scale(k):
	return pow(EPS, 0.5) * (k) + renorm * (curtime * EPS * EPS)

def invscale(k):
	return (k - renorm * (curtime * EPS * EPS)) / pow(EPS, 0.5)

def eq_bin(x):
	return [pow(EPS, 0.5) * (k) + renorm * (curtime * EPS * EPS) for k in range(floor(invscale(-5)), ceil(invscale(5)))]

def draw_hist(time):
	f = open("30-0.55", "r")
	l = []
	for line in f:
		l.append(float(line) - shift/ time)
	plt.hist(l, eq_bin(3))
	plt.title("Frequency of Height, N=30, subcritical case")
	plt.xlabel("Height")
	plt.ylabel("Number of Occurrences")
	stat, p = normaltest(l)
	a = sum(l)/len(l)
	v = sum(pow(i - a, 2) for i in l)/len(l)
	print(v)
	print(stat, p)

draw_hist(1)
#avg_sim(4, 1, 0.001, 100000, 10000, f)
plt.show()