// Simulates two exponential random variables
#include <bits/stdc++.h>
using namespace std;
int ndelta(double p, double q, double tstep) {
	int d = 0;
	if(((double) rand() / RAND_MAX) < p * tstep) {
		d++;
	}
	if(((double) rand() / RAND_MAX) < q * tstep) {
		d--;
	}
	return d;
}
int sim(double p, double q, double tstep, int numsteps) {
	int curpos = 0;
	for(int i = 0; i < numsteps; i++) {
		curpos += ndelta(p, q, tstep);
	}
	return curpos;
}
void write_to_file(double p, double q, double tstep, int numsteps, int numsims) {
	ofstream fout;
	fout.open("4-1-0.001-100000.txt", ios_base::app);
	for(int i = 0; i < numsims; i++) {
		if(i % 1000 == 0) cout << i << endl;
		fout << sim(p, q, tstep, numsteps) << endl;
	}
}
int main() {
	srand(time(NULL));
	write_to_file(4, 1, 0.001, 100000, 100000);
}