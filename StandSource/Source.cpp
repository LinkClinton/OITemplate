#include<iostream>
#include<cstring>
#include<complex>
#include<cstdio>
#include<vector>

typedef std::complex<double> T;

namespace FFT {

	std::vector<int> Index;
	std::vector<int> Index_Temp;

	void GetIndex(size_t l, size_t r) {
		if (l == r) return;
		Index_Temp.clear();

		size_t mid = (l + r) >> 1;
		for (size_t i = l; i <= mid; i++)
			Index_Temp.push_back(Index[l + (((i - l) * 2) ^ 1)]);
		for (size_t i = l; i <= mid; i++)
			Index[i] = Index[l + (i - l) * 2];
		for (size_t i = mid + 1; i <= r; i++)
			Index[i] = Index_Temp[i - mid - 1];

		GetIndex(l, mid); GetIndex(mid + 1, r);
	}

	void AsIndex(std::vector<T> &result) {
		Index.clear();
		Index.resize(result.size());

		for (size_t i = 0; i < Index.size(); i++)
			Index[i] = i;

		GetIndex(0, Index.size() - 1);

		std::vector<T> temp = result;
		for (size_t i = 0; i < result.size(); i++)
			result[i] = temp[Index[i]];
	}

	const double PI = acos(-1);

	void DFT(std::vector<T>& result, int flag) {
		AsIndex(result);
		for (size_t i = 1; i < result.size(); i << 1) {
			size_t length = i << 1;
			T Wn = T(cos(2.0*PI / length), sin(2.0*PI / length*flag));
			for (size_t j = 0; j < result.size(); j += length) {
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
		if (flag == -1) for (size_t i = 0; i < result.size(); i++) result[i] /= result.size();
	}
}

int main() {
}
	
