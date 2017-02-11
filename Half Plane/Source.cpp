#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>

struct Vec2 {
	double x, y;
	Vec2(int _x = 0, int _y = 0) { x = _x; y = _y; }
};

struct Line {
	int a, b, c;
	Line() { a = 0; b = 0; c = 0; }
	Line(Vec2 start, Vec2 end) { getLine(start, end); }
	void getLine(Vec2 start, Vec2 end) {
		a = end.y - start.y;
		b = start.x - end.x;
		c = -(a*start.x + b*start.y);
	}
	int getValue(Vec2 vec) {
		return a*vec.x + b*vec.y + c;
	}
	Vec2 getVec(Vec2 start, Vec2 end) {
		Vec2 result;
		double u = std::abs(a*start.x + b*start.y + c);
		double v = std::abs(a*end.x + b*end.y + c);

		result.x = (start.x*v + end.x*u) / (u + v);
		result.y = (start.y*v + end.y*v) / (u + v);

		return result;
	}
};

Line line;

std::vector<Vec2> read;
std::vector<Vec2> ans;

bool no_ans = false;

void getCutAns(Line line) {
	std::vector<Vec2> temp;

	for (size_t i = 1; i < ans.size() - 1; i++) {
		if (line.getValue(ans[i]) >= 0) {
			temp.push_back(ans[i]);
		}
		else {
			if (line.getValue(ans[i - 1]) > 0) {
				temp.push_back(line.getVec(ans[i - 1], ans[i]));
			}
			if (line.getValue(ans[i + 1]) > 0) {
				temp.push_back(line.getVec(ans[i], ans[i + 1]));
			}
		}
	}

	ans.clear();
	if (temp.empty()) { no_ans = true; return; }
	temp.push_back(temp[0]);
	ans.push_back(temp[temp.size() - 2]);
	for (size_t i = 0; i < temp.size(); i++)
		ans.push_back(temp[i]);
}

int n;

void Initalize() {
	read.clear();
	ans.clear();

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		read.push_back(Vec2(x, y));
	}
	read.push_back(read[0]);

	ans.push_back(read[read.size() - 2]);
	for (size_t i = 0; i < read.size(); i++) ans.push_back(read[i]);
}

int main() {
	int t;
	scanf("%d", &t);

	for (int i = 1; i <= t; i++) {
		Initalize();
		no_ans = false;
		for (size_t i = 0; i < read.size() - 1; i++) {
			getCutAns(Line(read[i], read[i + 1]));
			if (no_ans) break;
		}
		if (no_ans) printf("NO\n");
		else printf("YES\n");
	}
	bool end = true;
}