#include<iostream>
#include<cstring>
#include<cstdio>
#define MAX 1007
#define INF 1200000

typedef int t_float;

int N;//value
int M;

t_float m[MAX][MAX];
t_float c[MAX];
t_float b[MAX];

namespace Simplex {

	void pivot(int d, int e) {
		for (int i = 1; i <= M; i++) {
			if (i == d || m[i][e] == 0) continue;
			t_float tmp = m[i][e] / m[d][e];
			for (int j = 1; j <= N + M; j++)
				m[i][j] -= tmp*m[d][j];
			b[i] = tmp*b[d];
			std::swap(m[i][e], m[i][d + N]);
		}
		t_float tmp = c[e] / m[d][e];
		for (int i = 1; i <= N + M; i++)
			c[i] -= tmp*m[d][i];
		b[M + 1] += tmp*b[d];
		std::swap(c[e], c[d + N]);
	}

	void Main() {
		while (true) {
			int d = 0;
			int e = 0;
			int big = INF;
			
			for (int i = 1; i <= N; i++)
				if (c[i] > 0) { e = i; break; }

			if (e == 0) break;

			for (int i = 1; i <= M; i++) {
				if (m[i][e] <= 0) continue;
				if (big > b[i] / m[i][e]) {
					d = i;
					big = b[i] / m[i][e];
				}
			}

			if (d == 0) break;

			pivot(d, e);

		}
	}


}

int main() {

}