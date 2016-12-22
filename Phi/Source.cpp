#include<iostream>
#include<cstring>
#include<cstdio>
#define MAX 4100000

int N;
int MAXN;
int phi[MAX];
long long sum[MAX];
long long ans = 0;

void Get(int N) {
	for (int i = 1; i <= N; i++)
		phi[i] = i;
	for (int i = 2; i <= N; i++) {
		if (phi[i] == i) {
			for (int j = 1; i*j <= N; j++)
				phi[i*j] = phi[i*j] / (i) * (i - 1);
		}
	}
	for (int i = 2; i <= N; i++)
		sum[i] = sum[i - 1] + phi[i];
}

void Initalize() {
	std::cin >> N;
	ans = 0;
}

int main() {
	Get(MAX - 10000);
	while (true) {
		Initalize();
		if (N == 0) break;
		for (int i = 1; i <= N; i++) {
			ans += sum[N / i] * (long long)i;
		}
		std::cout << ans << std::endl;
	}
}