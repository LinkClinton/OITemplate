#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>

#define MAX 210000
#define mod 1000000007

typedef long long int_t;

std::vector<int> m[MAX];
int N, M, x, y;
int in[MAX];
int origin[MAX];
int_t dp[MAX];

int_t fast_pow(int_t x, int n) {
	int_t ans = 1;
	while (n) {
		if (n & 1)ans = (ans*x) % mod;
		x = (x*x) % mod;
		n >>= 1;
	}
	return ans;
}

int_t ans = 1;

void top_sort() {
	std::queue<int> t;
	t.push(1);
	while (!t.empty()) {
		int p = t.front(); t.pop();
		for (size_t i = 0; i < m[p].size(); i++) {
			int to = m[p][i];
			if (to == y) 
				dp[to] = (ans*fast_pow(origin[y], mod - 2)) % mod;
			else
				dp[to] = (dp[to] + (dp[p] * fast_pow(origin[to], mod - 2)) % mod) % mod;
			in[to]--;
			if (in[to] == 0) t.push(to);
		}
	}
}

void Initalize() {
	scanf("%d %d %d %d", &N, &M, &x, &y);
	for (int i = 1; i <= M; i++) {
		int u, v;
		scanf("%d %d", &v, &u);
		m[v].push_back(u);
		in[u]++;
		origin[u]++;
	}
	origin[y]++;
	for (int i = 1; i <= N; i++) {
		if (in[i] != 0) ans = (ans*origin[i]) % mod;
	}
}

int main() {


	Initalize();

	top_sort();
	//ans = (ans * 2) % mod;
	if (y == 1 || y == x) {
		printf("%lld", (ans) % mod);
		return 0;
	}
	printf("%lld\n", (ans - dp[x] + mod) % mod);


}