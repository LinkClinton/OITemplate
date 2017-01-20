#include"StandSource.hpp"
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>

#define MAX 110000
#define MAXK 202

typedef long long int_t;

int_t dp[2][MAX];

int N, K;

int val[MAX];

int_t sum[MAX];

class Queue {
private:
	int head;
	int tail;
	int size;
	int arr[MAX];
public:
	Queue() { head = 1; tail = 0; size = 0; memset(arr, 0, sizeof(arr)); }
	void push(int value) { arr[++tail] = value; size++; }
	void pop_front() { head++; size--; }
	void pop_back() { tail--; size--; }
	void clear() { head = 1; tail = 0; size = 0; memset(arr, 0, sizeof(arr)); }
	int  count() { return size; }
	int  front_first() { return arr[head]; }
	int  front_second() { return arr[head + 1]; }
	int  back_first() { return arr[tail]; }
	int  back_second() { return arr[tail - 1]; }
};

Queue t;

void Initalize() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++)
		scanf("%d", &val[i]), sum[i] = sum[i - 1] + val[i];

}

int now = 1;
int last = 0;

int main() {
	input::Open();
	output::Open();
	Initalize();

	for (int i = 1; i <= N; i++)
		dp[last][i] = sum[i] * (sum[N] - sum[i]);

	for (int count = 2; count <= K; count++) {
		for (int i = 1; i < N; i++) {
			dp[now][i] = 0;
			for (int j = i - 1; j >= count - 1; j--)
				dp[now][i] = std::max(dp[now][i], dp[last][j] + (sum[i] - sum[j])*(sum[N] - sum[i]));
		}
		now ^= true;
		last ^= true;
	}
	now ^= true;

	int_t ans = 0;
	for (int i = 1; i < N; i++)
		ans = std::max(ans, dp[now][i]);

	printf("%lld\n", ans);
}