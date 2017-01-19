
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

#define MAX 210000

typedef long long int_t;

namespace NTT {

	const int_t P = 1004535809;
	const int_t g = 3;

	int_t pow[MAX];
	
	int_t fast_pow(int_t x, int_t n) {
		if (n == 0) return 1;
		int_t c = 1;
		while (n) {
			if (n & 1)c = (c*x) % P;
			x = (x*x) % P;
			n >>= 1;
		}
		return c;
	}

	int_t Pow(int_t n) {
		return fast_pow(g, n);
	}

	void Initalize(int n) {
		pow[0] = 1;
		for (int i = 1; i <= n; i++)
			pow[i] = pow[i - 1] * g;
	}

	std::vector<int> index;
	std::vector<int> index_temp;

	void GetIndex(size_t l, size_t r) {
		if (l == r) return;
		index_temp.clear();

		size_t mid = (l + r) >> 1;

		for (size_t i = l; i <= mid; i++)
			index_temp.push_back(index[l + (((i - l) * 2) ^ 1)]);
		for (size_t i = l; i <= mid; i++)
			index[i] = index[l + (i - l) * 2];
		for (size_t i = mid + 1; i <= r; i++)
			index[i] = index_temp[i - mid - 1];

		GetIndex(l, mid); GetIndex(mid + 1, r);
	}

	void GetIndex(size_t size) {
		index.clear();
		index.resize(size);

		for (size_t i = 0; i < size; i++)
			index[i] = i;

		GetIndex(0, size - 1);
	}

	void AsIndex(std::vector<int_t> &result) {
		GetIndex(result.size());
		std::vector<int_t> temp = result;

		for (size_t i = 0; i < result.size(); i++)
			result[i] = temp[index[i]];
	}

	void DFT(std::vector<int_t> &result, size_t n, int_t flag) {
		AsIndex(result);
		for (size_t i = 1; i < n; i <<= 1) {
			size_t length = i << 1;
			int_t Wn = (Pow((P - 1) / length)) % P;
			for (size_t j = 0; j < n; j += length) {
				int_t W = 1;
				for (size_t k = 0; k < i; k++) {
					int_t x = result[j + k];
					int_t y = (result[j + k + i] * W) % P;
					result[j + k] = (x + y) % P;
					result[j + k + i] = (x - y + P) % P;
					W = (W*Wn) % P;
				}
			}
		}
		if (flag == -1) {
			for (size_t i = 1; i < n / 2; i++)
				std::swap(result[i], result[n - i]);
			int_t inv = fast_pow(n, P - 2);
			for (size_t i = 0; i < result.size(); i++)
				result[i] = (result[i] * inv) % P;
		}
	}

}

char c1[MAX];
char c2[MAX];

size_t len1;
size_t len2;
size_t len;
size_t n;

std::vector<int_t> A1;
std::vector<int_t> A2;


int main() {
	scanf("%s", c1);
	scanf("%s", c2);

	len1 = strlen(c1);
	len2 = strlen(c2);

	len = len1 + len2;

	for (n = 1; n < len; n <<= 1);

	A1.resize(n);
	A2.resize(n);

	for (size_t i = 0; i < len1; i++)
		A1[i] = c1[i] - '0';
	for (size_t i = 0; i < len2; i++)
		A2[i] = c2[i] - '0';

	NTT::Initalize(n);

	NTT::DFT(A1, n, 1);
	NTT::DFT(A2, n, 1);
	for (size_t i = 0; i < n; i++)
		A1[i] = (A1[i] * A2[i]) % NTT::P;
	NTT::DFT(A1, n, -1);

	for (size_t i = 0; i < A1.size() / 2; i++)
		std::swap(A1[i], A1[A1.size() - 1 - i]);

	bool first = true;

	int len = 0;

	for (size_t i = 0; i < A1.size() - 1; i++) {
		if (A1[i] != 0) first = false;
		if (first) continue;
		c1[len++] = A1[i] % 10 + '0';
		A1[i + 1] += A1[i] / 10;
	}

	int_t value = A1[A1.size() - 1];

	while (value > 0) {
		c1[len++] = value % 10 + '0';
		value = value / 10;
	}
	
	for (int i = len - 1; i >= 0; i--) {
		printf("%c", c1[i]);
	}
	printf("\n");


}