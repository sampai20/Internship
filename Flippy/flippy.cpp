#include <bits/stdc++.h>
using namespace std;

const long double EPS = (long double) 1/30;
long double scl = (long double) 0.475;
long double renorm = (1 / (2 * EPS) - 1 / (4 * pow(EPS, 0.5)) + (double) 1/12);
const long double scl_size = 5;
const long double scl_time = 2;

const int N = round(scl_size/EPS);
int S[N];
long double clocks[N]; // TODO segment tree??
const long double TIME = scl_time/(EPS * EPS);
const long double INF = 10 * TIME;
const long double RES = 1e-6;
long double curtime = 0;
long double q = exp(-sqrt(EPS));
default_random_engine generator;
std::uniform_real_distribution<long double> unif(0.0,1.0);

long double high_int(long double b, int s) {
	long double x = exp((s-1) * log(q) - (b * scl) / EPS);
	long double lx = x - (x*x)/2 + (x*x*x)/3;
	lx += log(q) + (b * scl) / EPS;
	return q*b - ((q-1) * EPS * lx) / scl;
	/*if((b * scl) / EPS < 100000) return q*b - ((q-1) * EPS * (log(pow(q, s) + q * exp((b * scl) / EPS)))) / scl;
	return q*b - ((q-1) * EPS * (log(q) + (b * scl) / EPS)) / scl;*/
}

long double actual_hi_int(long double b, int s) {
	if((b * scl) / EPS < 100000) return q*b - ((q-1) * EPS * (log(pow(q, s) + q * exp((b * scl) / EPS)))) / scl;
	return q*b - ((q-1) * EPS * (log(q) + (b * scl) / EPS)) / scl;
}

long double low_int(long double b, int s) {
	long double x = exp((s+1) * log(q) - (b * scl) / EPS);
	long double lx = x - (x*x)/2 + (x*x*x)/3;
	lx += (b * scl) / EPS;
	return ((q-1) * EPS * lx) / scl + b;
	/*if((b * scl) / EPS < 100000) return ((q-1) * EPS * log(pow(q, s+1) + exp((b * scl) / EPS))) / scl + b;
	else return ((q-1) * EPS * (b * scl) / EPS) / scl + b;*/
}

long double actual_lo_int(long double b, int s) {
	if((b * scl) / EPS < 100000) return ((q-1) * EPS * log(pow(q, s+1) + exp((b * scl) / EPS))) / scl + b;
	else return ((q-1) * EPS * (b * scl) / EPS) / scl + b;
}

long double hi_rate(int s) {
	long double alpha = (long double) exp(curtime / (2 * EPS));
	return q * (1 + alpha * pow(q, -s)) / (1 + alpha * pow(q, -s+1));
}

long double lo_rate(int s) {
	long double alpha = (long double) exp(curtime / (2 * EPS));
	return (1 + alpha * pow(q, -s))/(1 + alpha * pow(q, -s-1));
}

long double hi_sample(int s) { // TODO Newton's method
	long double x = unif(generator);
	long double goal = high_int(curtime, s) - log(x);
	long double lo = curtime;
	long double hi = INF;
	for(int i = 0; i < log(INF / RES)/log(2); i++) {
		long double mid = (lo + hi) / 2;
		long double cur = high_int(mid, s);
		if(cur < goal) lo = mid;
		else hi = mid;
	}
	return (lo + hi) / 2 - curtime;

}

long double lo_sample(int s) { // TODO Newton's method
	long double x = unif(generator);
	long double goal = low_int(curtime, s) - log(x);
	long double lo = curtime;
	long double hi = INF;
	for(int i = 0; i < log(INF / RES)/log(2); i++) {
		long double mid = (lo + hi) / 2;
		long double cur = low_int(mid, s);
		if(cur < goal) lo = mid;
		else hi = mid;
	}
	return (lo + hi) / 2 - curtime;

}

void resample(int i) {
	if(S[i] < S[(i+1) % N] && S[i] < S[(i+N-1) % N]) {
		clocks[i] = lo_sample(S[i]);
	}
	else if(S[i] > S[(i+1) % N] && S[i] > S[(i+N-1) % N]) {
		clocks[i] = hi_sample(S[i]);
	}
	else {
		clocks[i] = INF;
	}
}

void flippy_setup() {
	curtime = 0;
	for(int i = 0; i < N; i++) {
		S[i] = i & 1;
	}
	for(int i = 0; i < N; i++) {
		resample(i);
	}
}

void flippy_run(bool output = false) {
	ofstream fout("30-0.475", ofstream::out | ofstream::app);
	curtime = 0;
	int c = 0;
	while(curtime < TIME) {
		c++;
		if(c % 10000 == 0) {
			//cout << curtime << endl;
			//long double renorm =  (1 / (2 * EPS) - 1 / (4 * pow(EPS, 0.5)) + (double) 1/12);
			/*long double renorm = 2;
			for(int i = 0; i < 1; i++) {
				cout << (curtime * EPS * EPS) << ": " << ((long double) pow(EPS, 0.5) * S[i]) + renorm * (curtime * EPS * EPS) << " "; // change to bt/e
			}
			cout << endl;*/
			//cout << '\t' << low_int(curtime, S[0]) << '\t' << actual_lo_int(curtime, S[0]) << endl;
		}
		//cout << curtime << endl;
		int ind = min_element(clocks, clocks+N) - clocks;
		long double tmp = clocks[ind];
		for(int i = 0; i < N; i++) {
			clocks[i] -= tmp;
		}
		curtime += tmp;
		if(S[ind] < S[(ind+1) % N] && S[ind] < S[(ind+N-1) % N]) {
			S[ind] += 2;
		}
		else if(S[ind] > S[(ind+1) % N] && S[ind] > S[(ind+N-1) % N]) {
			S[ind] -= 2;
		}
		resample((ind+1) % N);
		resample(ind);
		resample((ind+N-1) % N);
		
		/*if(output) {
			fout << ind << " " << S[ind] << endl;
		}*/
	}
	for(int i = 0; i < 1; i++) {
		fout << ((long double) pow(EPS, 0.5) * S[i]) + renorm * (curtime * EPS * EPS) << " "; // change to bt/e
	}
	fout << endl;
}

int main() {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	long double s = 0;
	for(int i = 0; i < 500; i++) {
		flippy_setup();
		flippy_run(true);
		cout << i << S[0] << endl;
	}
	return 0;
}