#include<iostream>
#include<cstring>
#include<cstdio>

#define MAX 40

struct Equation {
	int m[MAX];
	int equal;
};


int N, M;

Equation equations[MAX];

namespace Gauss {

	int x_num;
	int equation_num;

	Equation* equations;

	Equation t_equations[MAX];

	void Initalize(Equation* _equations, int xnum, int equationnum) {
		equations = _equations;
		x_num = xnum;
		equation_num = equationnum;
	}

	void SwapEquation(int x, int y) {
		for (int i = 1; i <= x_num; i++)
			std::swap(equations[x].m[i], equations[y].m[i]);

		std::swap(equations[x].equal, equations[y].equal);
	}

	void GetMainEquation(int x_pos) {
		int target = x_pos;

		for (int i = x_pos + 1; i <= equation_num; i++) {
			if (equations[i].m[x_pos] != 0) {
				target = i;
				break;
			}
		}

		SwapEquation(x_pos, target);
	}

	int ans = MAX;

	void BackAns() {
		memcpy(t_equations, ::equations, sizeof(::equations));

		int Ans = 0;

		for (int i = equation_num - 1; i >= 1; i--) {
			for (int j = i + 1; j <= x_num; j++) {
				t_equations[i].equal ^= t_equations[j].equal*t_equations[i].m[j];
			}
			Ans += t_equations[i].equal;
		}
		Ans += t_equations[equation_num].equal;
		if (ans > Ans) ans = Ans;
	}

	void dfs(int t) {
		if (t == equation_num + 1) {
			BackAns();
			return;
		}
		if (equations[t].m[t] != 1) {
			equations[t].m[t] = 1;
			equations[t].equal = 1;
			dfs(t + 1);
			equations[t].equal = 0;
			dfs(t + 1);
		}
		else dfs(t + 1);
	}

	void GetAnsThink() {
		dfs(1);
	}

	void Main() {
		for (int i = 1; i <= equation_num; i++) {
			GetMainEquation(i);

			for (int j = i + 1; j <= equation_num; j++) {
				if (equations[j].m[i] == 0) continue;
				for (int k = 1; k <= x_num; k++)
					equations[j].m[k] ^= equations[i].m[k];
				equations[j].equal ^= equations[i].equal;
			}
		}
	}
}



int main() {


}