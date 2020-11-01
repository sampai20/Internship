add_library('controlP5')
from random import *
from math import *

N = 100
buffer = 0
gap = 1200 / (N)
state = [[False for i in range(N)] for j in range(N)]
updlist = [[False for i in range(N)] for j in range(N)]
temp = 1
run = False

def draw_square(i, j):
    if state[i][j]:
        fill(0)
        stroke(0)
    else:
        fill(255)
        stroke(255)
    rect(gap*i+buffer, gap*j + buffer, gap, gap)
    
def surr_sum(i, j):
    s = 0
    s += state[i-1][j]
    s += state[i][(j+1) % N]
    s += state[i][j-1]
    s += state[(i+1) % N][j]
    return 2 * s - 4

def singlemove():
    global updlist
    global state
    i = choice(list(range(N)))
    j = choice(list(range(N)))
    pi, pj = choice([(i-1, j), (i, (j+1) % N), (i, j-1), ((i+1) % N, j)])
    #print(i, j, pi, pj)
    if state[i][j] == state[pi][pj]:
        return False
    dE = 2 * (state[i][j] - state[pi][pj]) * (surr_sum(i, j) - surr_sum(pi, pj) - 2 * state[pi][pj] + 2 * state[i][j])
    #print(dE)
    if (dE <= 0) or (log(random()) < -dE / temp) :
        #print(i, j, "to", pi, pj)
        state[i][j] = not state[i][j]
        state[pi][pj] = not state[pi][pj]
        updlist[i][j] = True
        updlist[pi][pj] = True
        return True
    """elif (log(random()) < -dE / temp):
        print("here", i, j, -dE / temp)
        state[i][j], state[pi][pj] = state[pi][pj], state[i][j]
        updlist[i][j] = True
        updlist[pi][pj] = True
        return"""
        
    

def setup():
    global cp5
    global tempSlider
    cp5 = ControlP5(this)
    tempSlider = cp5.addSlider("temp").setPosition(0, 1400).setSize(1000, 100).setRange(0.1, 10).setValue(temp)
    size(1200, 1600)
    for i in range(N):
        for j in range(N):
            state[i][j] = choice([True, False])
            draw_square(i, j)

def draw():
    global temp
    global updlist
    temp = tempSlider.getValue()
    print(temp)
    #saveFrame("frmslowbig/ising_####.png")
    updlist = [[False for i in range(N)] for j in range(N)]
    for i in range(N*N):
        singlemove()
    for i in range(N):
        for j in range(N):
            if updlist[i][j]:
                draw_square(i, j)
    

        
