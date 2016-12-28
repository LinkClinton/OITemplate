/*
a^k=b mod p

m=sqrt(p)

k=cm+q

a^q = b*a^cm*-1 mod p

枚举q

然后枚举c

如果有的话，那么就是答案了。

*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>

namespace BSGS {

	long long a, b, p;

	long long fast_pow(long long x, long long n) {
		long long c = 1;
		while (n) {
			if (n & 1) c = (c*x) % p;
			x = (x*x) % p;
			n >>= 1;
		}
		return c;
	}

	long long inv(long long x) {
		return fast_pow(x, p - 2);
	}

	std::map<long long, long long> hash;

	void Initalize(long long _a, long long _b, long long _p) {
		a = _a;
		b = _b;
		p = _p;
		hash.clear();
	}

	long long Main() {
		if (b == 1) return 0;
		long long m = (long long)ceil(sqrt(p));

		//a^0=1
		hash.insert(std::pair<long long, long long>(1, 0));

		long long aq = 1;
		for (long long i = 1; i <= m; i++) {
			aq = aq*a%p;
			hash.insert(std::pair<long long, long long>(aq%p, i));
		}

		long long ap = 1;
		for (long long i = 0; i <= m; i++) {
			std::map<long long, long long>::iterator it = hash.find((b*inv(ap)) % p);

			if (it != hash.end()) {
				return i*m + it->second;
			}ap = ap*aq%p;
		}
		return -1;
	}

}

long long a, b, p;

int main() {
	while (~scanf("%lld %lld %lld", &p, &a, &b)) {
		BSGS::Initalize(a, b, p);
		long long ans = BSGS::Main();
		if (ans == -1) printf("no solution\n");
		else printf("%lld\n", ans);
	}
}