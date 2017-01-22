#include"StandSource.hpp"

#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>

#define MAX 12000

int v[MAX];
int N, M;

char c[MAX];
char ct[MAX];
char vc[MAX];

void Initalize() {
	std::ios::sync_with_stdio(false);
	std::cin >> N >> M;
	std::cin >> c;
	for (int i = 0; i < N; i++) {
		if (c[i] == '(') v[i + 1] = 1;
		else v[i + 1] = -1;
	}
}

void Replace(int l, int r, int value) {
	for (int i = l; i <= r; i++)
		v[i] = value;
}

void Invert(int l, int r) {
	for (int i = l; i <= r; i++)
		v[i] = -v[i];
}

void Swap(int l, int r) {
	int mid = (l + r) >> 1;
	for (int i = l; i <= mid; i++)
		std::swap(v[i], v[r - i + l]);
}

int  Query(int l, int r) {
	int left_min = 0;
	int right_max = 0;
	int sum = 0;
	for (int i = l; i <= r; i++) {
		sum += v[i];
		left_min = std::min(left_min, sum);
	}
	sum = 0;
	for (int i = r; i >= l; i--) {
		sum += v[i];
		right_max = std::max(right_max, sum);
	}
	return (std::abs(left_min) + 1) / 2 + (std::abs(right_max) + 1) / 2;
}

int main() {
	Initalize();
	for (int i = 1; i <= M; i++) {
		std::cin >> ct;
		switch (ct[0])
		{
		case 'R': {
			int l, r, val;
			std::cin >> l >> r >> vc;
			if (vc[0] == '(') val = 1; else val = -1;
			Replace(l, r, val);
			break;
		}
		case 'S': {
			int l, r;
			std::cin >> l >> r;
			Swap(l, r);
			break;
		}
		case 'I': {
			int l, r;
			std::cin >> l >> r;
			Invert(l, r);
			break;
		}
		case 'Q': {
			int l, r;
			std::cin >> l >> r;
			std::cout << Query(l, r) << std::endl;
			break;
		}
		default:
			break;
		}
	}
}

