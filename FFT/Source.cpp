#include<iostream>
#include<cstring>
#include<complex>
#include<vector>
#include<cmath>

typedef std::complex<double> T;

double const PI = acos(-1);

namespace FFT {
	static std::vector<int> index;
	static std::vector<int> index_temp;

	static void GetIndex(size_t l, size_t r) {
		if (l == r) return;

		index_temp.clear();

		size_t mid = (l + r) >> 1;
		for (size_t i = l; i <= mid; i++)
			index_temp.push_back(index[l + ((i - l) * 2) ^ 1]);
		for (size_t i = l; i <= mid; i++)
			index[i] = index[l + (i - l) * 2];
		for (size_t i = mid + 1; i <= r; i++)
			index[i] = index_temp[i - mid - 1];

		GetIndex(l, mid); GetIndex(mid + 1, r);
	}

	static void GetIndex(size_t n) {
		index.clear();
		index.resize(n);
		for (size_t i = 0; i < n; i++)
			index[i] = i;
		GetIndex(0, n - 1);
	}

	template<typename T>
	static void AsIndex(std::vector<T> &result, size_t n) {
		GetIndex(n);
		std::vector<T> temp = result;
		for (size_t i = 0; i < result.size(); i++)
			result[i] = temp[index[i]];
	}

	//2^x==n and x is int
	template<typename T>
	static void Iterator_DFT(std::vector<T> &result, size_t n, int flag) {
		AsIndex(result, n);
		for (size_t i = 1; i < n; i <<= 1) {
			size_t length = i << 1;
			T Wn = T(cos(2.0*PI / length), sin(2.0*PI / length*flag));
			for (size_t j = 0; j < n; j += length) {
				T W = T(1, 0);
				for (size_t k = 0; k < i; k++) {
					T x = result[j + k];
					T y = W*result[j + k + i];
					result[j + k] = x + y;
					result[j + k + i] = x - y;
					W = W*Wn;
				}
			}
		}
	}

	template<typename T>
	static void DFT(std::vector<T> &result, int n, int flag) {
		if (n == 1) return;

		T Wn = T(cos(2.0*PI / n), sin(2.0*PI / n*flag));
		T W = T(1, 0);

		std::vector<T> result_left;
		std::vector<T> result_right;

		size_t half_n = (size_t)n >> 1;

		for (size_t i = 0; i < half_n; i++) {
			result_left.push_back(result[i * 2]);
			result_right.push_back(result[(i * 2) ^ 1]);
		}

		FFT::DFT(result_left, half_n, flag);
		FFT::DFT(result_right, half_n, flag);

		for (size_t i = 0; i < half_n; i++) {
			T temp = W*result_right[i];
			result[i] = result_left[i] + temp;
			result[i + half_n] = result_left[i] - temp;
			W = W*Wn;
		}
	}
}

int n, m;
int N, M;

std::vector<T> A1;
std::vector<T> A2;

int main() {
	scanf("%d %d", &n, &m);
	N = n; M = m;

	m += n;
	for (n = 1; n <= m; n <<= 1);

	A1.resize(n);
	A2.resize(n);

	for (int i = 0; i <= N; i++) {
		int value;
		scanf("%d", &value);
		A1[i] = value;
	}
	for (int i = 0; i <= M; i++) {
		int value;
		scanf("%d", &value);
		A2[i] = value;
	}

	FFT::Iterator_DFT(A1, n, 1);
	FFT::Iterator_DFT(A2, n, 1);
	for (int i = 0; i < n; i++)
		A1[i] = A1[i] * A2[i];
	FFT::Iterator_DFT(A1, n, -1);

	for (int i = 0; i <= M + N; i++)
		printf("%d ", (int)(A1[i].real() / n + 0.5));
}
