import random
from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import normaltest
from matplotlib import colors
from matplotlib.patches import Polygon
from matplotlib.ticker import PercentFormatter
from matplotlib.animation import FFMpegWriter
from matplotlib.animation import FuncAnimation


plt.rcParams['animation.ffmpeg_path'] = 'C:\\FFmpeg\\bin\\ffmpeg.exe'
fig, ax = plt.subplots(figsize = (20, 5))
ln, = ax.plot([], [])
ax.set_ylim(-5, 20)
n = 100
xcoords = list(range(n))
ycoords = [i % 2 for i in range(n)]
ax.set_xlim(0, n)
infile = open("sampleflips", "r")

def update(frame):
	#print("HIIIIIII")
	if(frame % 50 == 0):
		print(frame)

	p = list(map(int, (infile.readline().split())))
	ycoords[p[0]] = p[1]
	#print(p)
	ln.set_data(xcoords, ycoords)
	return ln, 

def init():
	ln.set_data([], [])
	return ln,

def updatemulti(frame, skip):
	if(frame % 50 == 0):
		print(frame)
	p = []
	for i in range(skip):
		p = list(map(int, (infile.readline().split())))
		ycoords[p[0]] = p[1]
	#print(p)
	ln.set_data(xcoords, ycoords)
	return ln, 


ani = FuncAnimation(fig, updatemulti, fargs = [2], init_func = init, frames = 10000, interval= 1, blit=True, repeat=False)


plt.show()
#writer = FFMpegWriter(fps=100)
#ani.save('animation.mp4', writer)