#include <bits/stdc++.h>
using namespace std;
const int WIDTH = 100;
const int NUM_PIECES = 7;
const int NUM_TIME = 500;
const int TICK_PER_SEC = 100;
const int PRINT_EVERY = 50;
const int NUM_TRIALS = 10000;
int curw = WIDTH;
pair<int, int> pieces[7][4] = {
	{{0, 0}, {0, 1}, {0, 2}, {0, 3}}, // I
	{{0, 0}, {1, 0}, {2, 0}, {2, 1}}, // L
	{{0, 0}, {1, 0}, {2, 0}, {2, -1}}, // J
	{{0, 0}, {1, 0}, {1, 1}, {2, 0}}, // T
	{{0, 0}, {1, 0}, {1, 1}, {0, 1}}, // O
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, // Z
	{{0, 0}, {1, 0}, {1, -1}, {2, -1}} // S
}; // TODO precompute rotations?

int interface[WIDTH][NUM_TRIALS]; // topmost cell in each column

void rot(int i, int n) {
	if(n == 0) return;
	for(int j = 0; j < 4; j++) {
		pieces[i][j] = make_pair(-pieces[i][j].second, pieces[i][j].first);
	}
	return rot(i, n-1);
}

int mod(int b, int m) {
	return ((b % m) + m) % m;
}

void place_piece(int trial, ostream &sfile = cout) {
	int piece = rand() % NUM_PIECES;
	//cout << "Placing piece " << piece << endl;
	int cx = rand() % curw;
	int num_rot = rand() % 4;
	rot(piece, num_rot);
	int cy = -1000; // -inf
	for(int i = 0; i < 4; i++) {
		int cur_x = mod(cx + pieces[piece][i].first, curw);
		cy = max(cy, interface[cur_x][trial] + 1 - pieces[piece][i].second);
	}
	//sfile << piece << endl;
	for(int i = 0; i < 4; i++) {
		int cur_x = mod(cx + pieces[piece][i].first, curw);
		interface[cur_x][trial] = max(interface[cur_x][trial], cy + pieces[piece][i].second);
		//sfile << cur_x << " " << cy + pieces[piece][i].second << endl;
	}
}

void output_state(ofstream &ofile) {
	for(int i = 0; i < NUM_TRIALS; i++) {
		for(int j = 0; j < WIDTH; j++) {
			ofile << interface[j][i] << " ";
		}
	}
	ofile << endl;
}

double stdev(int* arr) {
	double mean = 0;
	for(int i = 0; i < NUM_TRIALS; i++) {
		mean += (double) arr[i] / NUM_TRIALS;
	}
	double var = 0;
	for(int i = 0; i < NUM_TRIALS; i++) {
		var += (mean - arr[i]) * (mean - arr[i]);
	}
	var /= NUM_TRIALS;
	return sqrt(var);
}

void output_avg(ofstream &ofile) {
	double s(0), sms(0), bis(0), s0(0);
	for(int i = 0; i < NUM_TRIALS; i++) {
		double sm(1000000000), bi(-1000000000);
		for(int j = 0; j < WIDTH; j++) {
			s += (double) interface[j][i] / (WIDTH * NUM_TRIALS);
			sm = min(sm, (double) interface[j][i] / (NUM_TRIALS));
			bi = max(bi, (double) interface[j][i] / (NUM_TRIALS));
		}
		sms += sm;
		bis += bi;
	}
	ofile << setprecision(6) << sms << " " << bis << " " << s << " " << stdev(interface[0]) << endl;
}

void output_stdev(ofstream &ofile) {
	ofile << stdev(interface[0]) << endl;
}

int main() {
	srand(time(NULL));
	ofstream fout("100w_exp_small");
	//ofstream sfile("samplegrid");

	for(curw = 100; curw <= 100; curw += 10) {
		for(int i = 0; i < NUM_TIME * TICK_PER_SEC; i++) {
			if(i % 100 == 0) cout << i << endl;
			for(int j = 0; j < NUM_TRIALS; j++) {
				if((double) rand() / RAND_MAX  < ((double) curw / (TICK_PER_SEC))) {
					place_piece(j);
				}
			}
			if(i % PRINT_EVERY == 0) output_stdev(fout);
		}
		for(int i = 0; i < curw; i++) {
			for(int j = 0; j < NUM_TRIALS; j++)
				interface[i][j] = 0;
		}
	}
}