#include<iostream>
#include<cstring>
#include<cstdio>

#define MAX 120000

int n, d;

int d_axis[MAX][10];

int Abs(int x) {
	if (x < 0) return -x;
	return x;
}

int max(int x, int y) {
	if (x > y) return x;
	return y;
}

int get_dis(int x, int y) {
	int ans = 0;
	for (int i = 1; i <= d; i++) {
		ans += Abs(d_axis[x][i] - d_axis[y][i]);
	}
	return ans;
}

int ans = 0;

void Initalize() {
	std::cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= d; j++) {
			std::cin >> d_axis[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans = max(ans, get_dis(i, j));
		}
	}

	std::cout << ans << std::endl;

}

int main() {
	Initalize();
}