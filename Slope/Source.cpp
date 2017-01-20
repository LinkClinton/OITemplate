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
	int n;
	N = 0;
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		if (val[i] == 0) continue;
		N++;
		sum[N] = sum[N - 1] + val[i];
	}
	if (K >= N) K = N - 1;
}

int now = 1;
int last = 0;

//i>j>k
bool NeedPopFront(int i, int k, int j) {
	int_t g_jk = (dp[last][j] - dp[last][k]);
	if (g_jk > (sum[N] - sum[i])*(sum[j] - sum[k])) return true;
	return false;
}

bool NeedPopBack(int i, int j, int k) {
	int_t g_ij = (dp[last][i] - dp[last][j])*(sum[j] - sum[k]);
	int_t g_jk = (dp[last][j] - dp[last][k])*(sum[i] - sum[j]);
	if (g_ij > g_jk) return true;
	return false;
}
//#include"debug.hpp"

int main() {
	//input::Open();
	//output::Open();
	Initalize();
	for (int i = 1; i <= N; i++)
		dp[last][i] = sum[i] * (sum[N] - sum[i]);

	for (int count = 2; count <= K; count++) {
		for (int i = 1; i <= count - 1; i++)
			dp[now][i] = 0;
		t.clear();
		t.push(count - 1);
		for (int i = count; i < N; i++) {
			dp[now][i] = dp[last][i - 1] + (sum[i] - sum[i - 1])*(sum[N] - sum[i]);
			while (t.count() >= 2 && NeedPopFront(i, t.front_first(), t.front_second()))
				t.pop_front();
			int p = t.front_first();
			dp[now][i] = std::max(dp[now][i], dp[last][p] + (sum[i] - sum[p])*(sum[N] - sum[i]));
			while (t.count() >= 2 && NeedPopBack(i, t.back_first(), t.back_second()))
				t.pop_back();
			t.push(i);
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