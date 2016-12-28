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

