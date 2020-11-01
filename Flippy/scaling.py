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
ax.set_ylim(-5, 5)
n = 100
xcoords = list(range(n))
ycoords = [i % 2 for i in range(n)]
ax.set_xlim(0, 1)
infile = open("simplescaling", "r")

def update(frame):
	#print("HIIIIIII")
	if(frame % 50 == 0):
		print(frame)

	p = list(map(float, (infile.readline().split())))
	ycoords = p
	#print(p)
	N = len(ycoords)
	ln.set_data([i/(N-1) for i in range(N)], ycoords)
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
		ycoords = p
	#print(p)
	N = len(ycoords)
	ln.set_data([i/(N-1) for i in range(N)], ycoords)
	return ln, 


ani = FuncAnimation(fig, update, fargs = [], init_func = init, frames = 1, interval= 200, blit=True, repeat=False)


plt.show()
#writer = FFMpegWriter(fps=100)
#ani.save('animation.mp4', writer)