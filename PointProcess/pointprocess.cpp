#include <bits/stdc++.h>
using namespace std;
std::default_random_engine generator;
std::uniform_real_distribution<double> unif(0.0,1.0);

double quad_solve(double a, double b, double c) {
	return (-b + sqrt(b*b - 4 * a * c))/(2*a);
}

double sample() {
	double p = unif(generator);
	return sqrt(-2 * log(1 - p));
}

double sample2() {
	double p = unif(generator);
	return quad_solve(0.5, 1, log(1-p));
}

int main() {
	double buckets[100] = {0};
	for(int i = 0; i < 100000; i++) {
		double s = sample2();
		buckets[(int) (s * 10)] += (double) 1/100000;
		
	}
	double s = 0;
	for(int i = 0; i < 100; i++) {
		s += buckets[i];
		cout << 0.1 * i << " " << buckets[i] << endl;
	}
	cout << s << endl;
}