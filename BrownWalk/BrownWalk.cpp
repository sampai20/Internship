// Simulates Wiener Process in 2 Dimensions
// as scaling limit of Random Walk
#include <bits/stdc++.h>
using namespace std;
const int LENGTH_WALK = 1000000;
const int NUM_SIMS = 10000;
int walks[LENGTH_WALK + 1][2];
double maxdis[LENGTH_WALK + 1];
pair<double, double> ndelta(int T) {
	double stepsize = (double) 1/sqrt(T);
	double dx(0), dy(0);
	double s = (double) rand() / RAND_MAX;
	if(s <= 0.25) {
		dx = stepsize;
	}
	else if(s <= 0.5) {
		dy = stepsize;
	}
	else if(s <= 0.75) {
		dx = -stepsize;
	}
	else {
		dy = -stepsize;
	}
	return make_pair(dx, dy);
}
double sim(int T) {
	double cx(0), cy(0);
	for(int i = 1; i <= T; i++) {
		pair<double, double> nd = ndelta(1);
		cx += nd.first;
		cy += nd.second;
		walks[i][0] = cx;
		walks[i][1] = cy;
	}
}
void get_data() {
	double curMax = 0;
	for(int j = 1; j <= LENGTH_WALK; j++) {
		double curDist = sqrt(walks[j][1]*walks[j][1] + walks[j][0]*walks[j][0]);
		curMax = max(curMax, curDist);
		maxdis[j] += curMax / (NUM_SIMS * sqrt(j));
	}
}
void gen_walks() {
	for(int i = 0; i < NUM_SIMS; i++) {
		if(i % 100 == 0) cout << i << endl;
		sim(LENGTH_WALK);
		get_data();
	}
}
int main() {
	srand(time(NULL));
	gen_walks();
	ofstream fout("data.txt");
	for(int i = 1; i <= LENGTH_WALK; i++) {
		fout << maxdis[i] << endl;
	}
	fout.close();
}