#pragma once
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

class input {
public:
	static void Open() {
		freopen("C:/OI/Template/Template/T.in", "r", stdin);
	}
	static void Close() {
		fclose(stdin);
	}
};

class result {
public:
	static void Open() {
		freopen("C:/OI/Template/Template/T.out", "r", stdin);
	}
	static void Close() {
		fclose(stdin);
	}
};

class output {
public:
	static void Open() {
		freopen("C:/OI/Template/Template/T.ans", "w", stdout);
	}
	static void Close() {
		fclose(stdout);
	}
};

class reader {
public:
	static int getInt() {
		return (int)getInt64();
	}
	static long long getInt64() {
		long long x = 0;
		long long f = 1;
		char ch = getchar();
		while (ch<'0' || ch>'9') {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (ch >= '0'&&ch <= '9') {
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x*f;
	}
};