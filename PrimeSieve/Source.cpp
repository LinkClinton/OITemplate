#include<iostream>
#include<cstring>
#include<cstdio>
#define MAX 12000

bool IsPrime[MAX];

int prime[MAX];

int phi[MAX];

int mu[MAX];

void Get(int N) {
	memset(IsPrime, true, sizeof(IsPrime));
	for (int i = 2; i <= N; i++) {
		if (IsPrime[i]) {
			prime[++prime[0]] = i;
			phi[i] = i - 1;
			mu[i] = -1;
		}
		for (int j = 1; j <= prime[0]; j++) {
			if (i*prime[j] > N) break;
			IsPrime[i*prime[j]] = false;
			if (i%prime[j] == 0) {
				mu[i*prime[j]] = 0;
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}
			else mu[i*prime[j]] = -mu[i],
				phi[i*prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}

int N;

void Initalize() {
	std::cin >> N;
}

int main() {
	Initalize();
	Get(N);
	bool end = true;
}