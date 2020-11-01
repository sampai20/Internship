#include <bits/stdc++.h>
using namespace std;

const double EPS = (double) 1/500;
const int N = floor(1/EPS);
int S[N];
double clocks[N]; // TODO segment tree??
const double TIME = 1 / (EPS * EPS);
const double INF = 10*TIME;
const double RES = 1e-6;
double curtime = 0;
double q = exp(-EPS);
double alph = 1;
default_random_engine generator;
std::uniform_real_distribution<double> unif(0.0,1.0);

double hi_rate(int s) {
	double alpha = alph;
	return q * (1 + alpha * pow(q, -s)) / (1 + alpha * pow(q, -s+1));
}

double lo_rate(int s) {
	double alpha = alph;
	return (1 + alpha * pow(q, -s))/(1 + alpha * pow(q, -s-1));
}

double high_int(double b, int s) {
	//return 2 * (q - 1) * EPS * pow(q, s-1) * log(2 * EPS * pow(q, s) + q * b) + b;
	return hi_rate(s) * b;
}

double low_int(double b, int s) {
	//return q * (b - 2 * (q - 1) * EPS * pow(q, s) * log(2 * EPS * pow(q, s+1) + b));
	return lo_rate(s) * b;
}

double hi_sample(int s) { // TODO Newton's method
	double x = 0.5;
	return -log(x) / hi_rate(s);

}

double hi_sample2(int s) {
	double x = 0.5;
	double target = -log(x) + high_int(curtime, s);
	double lo = curtime;
	double hi = INF;
	for(int i = 0; i < (log(INF) - log(RES))/log(2); i++) {
		double mid = (lo + hi) / 2;
		double curint = high_int(mid, s);
		if(curint < target) lo = mid;
		else hi = mid;
	}
	return (lo + hi) / 2 - curtime;
}

double lo_sample(int s) { // TODO Newton's method
	double x = unif(generator);
	return -log(x) / lo_rate(s);

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
	for(int i = 0; i < N; i++) {
		S[i] = 0 + (i & 1);
	}
	for(int i = 0; i < N; i++) {
		resample(i);
	}
	cout << hi_rate(500) << " " << lo_rate(500) << endl;
}

void flippy_run(bool output = false) {
	ofstream fout("simplescaling", ofstream::out | ofstream::app);
	curtime = 0;
	int count = 0;
	while(curtime < TIME) {
		count++;
		if(count % 100000 == 0) cout << curtime << endl;
		//cout << curtime << endl;
		int ind = min_element(clocks, clocks+N) - clocks;
		double tmp = clocks[ind];
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
		
		/*for(int i = 0; i < N; i++) {
			cout << S[i] << " ";
		}
		cout << endl;*/
		/*if(output) {
			fout << ind << " " << S[ind] << endl;
		}*/
	}
	for(int i = 0; i < N; i++) {
		fout << (double) pow(EPS, 0.5) * (S[i] - log(alph)/log(q)) << " ";
	}
	fout << endl;
}

int main() {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	cout << hi_sample(5) << " " << hi_sample2(5) << endl;
	/*flippy_setup();
	flippy_run(false);
	for(int i = 0; i < N; i++) {
		cout << S[i] << " ";
	}
	cout << endl;
	return 0;*/
}