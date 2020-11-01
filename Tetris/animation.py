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
fig, ax = plt.subplots(figsize = (6, 6))
ln, = plt.plot([], [], 'ro')
ax.set_ylim(0, 100)
ax.set_xlim(0, 100)
infile = open("samplegrid")

def draw_square(x, y, f):
	colors = ["cyan", "orange", "b", "darkviolet", "yellow", "lawngreen", "red"]
	ax.fill([x, x, x+1, x+1], [y-1, y, y, y-1], colors[f % len(colors)])

def return_square(x, y, f):
	colors = ["cyan", "orange", "b", "darkviolet", "yellow", "lawngreen", "red"]
	return Polygon([[x, y-1], [x, y], [x+1, y], [x+1, y-1]], closed = True, color = colors[f])

def update(frame):
	ps = []
	#print("HIIIIIII")
	p = int(infile.readline())
	for i in range(4):
		x, y = map(int, infile.readline().split())
		draw_square(x, y, p)
		#print(return_square(x, y, p).get_xy())

def init():
	l = []
	return l,

def updatetwice(frame):
	update(frame)
	update(frame)


ani = FuncAnimation(fig, updatetwice, frames = 400 , interval= 1, blit=False, repeat=False)


#plt.show()
writer = FFMpegWriter(fps=50)
ani.save('animation.mp4', writer)