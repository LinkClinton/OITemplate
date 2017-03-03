#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

#define MAX 210000

int N;

class SegTree {
private:
	struct Node {
		Node* left;
		Node* right;
		int value;
	};

	Node* root;

	Node* NewNode() {
		Node* node = new Node();
		return node;
	}

	Node* bulid(int l, int r) {
		if (l == r) {
			Node* node = NewNode();
			node->value = (l + r) >> 1;
			return node;
		}
		Node* node = NewNode();
		int mid = (l + r) >> 1;
		node->left = bulid(l, mid);
		node->right = bulid(mid + 1, r);
		return node;
	}
	Node* Modify(Node* Last, int x, int value, int l, int r) {
		if (l == r) {
			Node* node = NewNode();
			node->value = value;
			return node;
		}
		Node* node = NewNode();
		int mid = (l + r) >> 1;
		if (x <= mid) node->left = Modify(Last->left, x, value, l, mid),
			node->right = Last->right;
		else node->right = Modify(Last->right, x, value, mid + 1, r),
			node->left = Last->left;
		return node;
	}
	Node* Query(Node* node, int x, int l, int r) {
		if (l == r) return node;
		int mid = (l + r) >> 1;
		if (x <= mid) return Query(node->left, x, l, mid);
		else return Query(node->right, x, mid + 1, r);
	}
public:
	void Bulid() {
		root = bulid(1, N);
	}
	void CopyFrom(SegTree tree) {
		root = tree.root;
	}
	void Modify(SegTree tree, int x, int value) {
		root = Modify(tree.root, x, value, 1, N);
	}
	int  QueryFather(int x) {
		return Query(root, x, 1, N)->value;
	}
};

class UnionSet {
private:
	SegTree arr[MAX];
	int find(int x, int version) {
		int f = arr[version].QueryFather(x);
		if (f == x) return x;
		return find(f, version);
	}
	int nowversion;
	int siz[MAX];

public:
	void reset(int size) {
		arr[0].Bulid();
		for (int i = 1; i <= N; i++)
			siz[i] = 1;
		nowversion = 0;
	}
	void GoBack(int version) {
		int lastversion = nowversion;
		arr[++nowversion] = arr[version];
	}
	void Union(int x, int y) {
		int fx = find(x, nowversion);
		int fy = find(y, nowversion);
		int sizx = siz[fx];
		int sizy = siz[fy];
		if (sizx > sizy) std::swap(fx, fy);
		int lastversion = nowversion;
		arr[++nowversion].Modify(arr[lastversion], fx, fy);
		siz[fy]++;
	}
	int IsConnect(int x, int y) {
		int fx = find(x, nowversion);
		int fy = find(y, nowversion);
		int lastversion = nowversion;
		arr[++nowversion] = arr[lastversion];
		if (fx == fy) return 1;
		return 0;
	}
};

UnionSet set;

int lastans = 0;

int M;

int main() {
	scanf("%d %d", &N, &M);
	set.reset(N);
	for (int i = 1; i <= M; i++) {
		int kind;
		scanf("%d", &kind);
		if (kind == 1) {
			int a, b;
			scanf("%d %d", &a, &b);
			//a ^= lastans; b ^= lastans;
			set.Union(a, b);
		}
		else if (kind == 2) {
			int version;
			scanf("%d", &version);
			//version ^= lastans;
			set.GoBack(version);
		}
		else {
			int a, b;
			scanf("%d %d", &a, &b);
			//a ^= lastans; b ^= lastans;
			lastans = set.IsConnect(a, b);
			printf("%d\n", lastans);
		}
	}
}