#pragma once

#include<cstdio>
#define DEBUG
class input {
public:
	static void Open() {
		freopen("C:/OI/Template/Template/T.in", "r", stdin);
	}
	static void Close() {
		fclose(stdin);
	}
};

class output {
public:
	static void Open() {
		freopen("C:/OI/Template/Template/T.out", "w", stdout);
	}
	static void Close() {
		fclose(stdout);
	}
};


