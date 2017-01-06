#include"StandSource.hpp"


#define MAX 120000
#define INF 50000

int f[MAX];

int main() {
	output::Open();
	for (int i = 1; i <= INF; i++) {
		for (int j = 1; j <= i; j++)
			f[i] += i / j;
		std::cout << f[i] << std::endl;
	}

	
	

}