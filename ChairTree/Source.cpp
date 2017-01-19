#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>

#define MAX 100010

#ifndef _DEBUG
#define nullptr NULL
#endif // !_DEBUG


typedef long long int_t;

class ChairTree {
private:
	struct Node {
		Node* left;
		Node* right;
		int_t value;
		int_t sum;
	};

	Node node[33];
	int cnt;

	Node* NewNode() {
		cnt++;
		return &node[cnt];
	}

	int_t value(Node* node) { if (node) return node->value; return 0; }
	int_t sum(Node* node) { if (node) return node->sum; return 0; }

	void update(Node* node) {
		if (!node) return;
		if (node->left == node->right) return;
		node->value = 0;
		node->sum = 0;
		node->value = value(node->left) + value(node->right);
		node->sum = sum(node->left) + sum(node->right);
	}
	void Insert(Node* node, int value, int l, int r) {
		if (l == r) {
			node->value = 1;
			node->sum = value;
			return;
		}
		int mid = (l + r) >> 1;
		if (value <= mid) {
			if (!node->left)node->left = NewNode();
			Insert(node->left, value, l, mid);
		}
		else {
			if (!node->right)node->right = NewNode();
			Insert(node->right, value, mid + 1, r);
		}
		update(node);
	}

	void Merge(Node* node, Node* last, int l, int r) {
		if (!last) return;
		int mid = (l + r) >> 1;
		if (l == r) {
			node->value += last->value;
			node->sum = node->value*(int_t)mid;
			return;
		}
		if (last->left) {
			if (!node->left) node->left = last->left;
			else
				Merge(node->left, last->left, l, mid);
		}
		if (last->right) {
			if (!node->right) node->right = last->right;
			else
				Merge(node->right, last->right, mid + 1, r);
		}
		update(node);
	}
	int Find(Node* node, int_t limit, int l, int r) {
		if (!node) return 0;
		if (l == r) {
			int ans = 0;
			for (int i = 1; i < node->value; i++) {
				limit -= l;
				if (limit < 0) break;
				ans++;
			}
			return ans;
		}
		int ans = 0;
		int mid = (l + r) >> 1;
		int_t left_sum = sum(node->left);
		if (limit >= left_sum) {
			ans += value(node->left);
			ans += Find(node->right, limit - left_sum, mid + 1, r);
		}
		else {
			ans += Find(node->left, limit, l, mid);
		}
		return ans;
	}

	Node* root;

	int left;
	int right;
public:
	void Create(int value, int l, int r) {
		root = NewNode();
		Insert(root, value, l, r);
		left = l;
		right = r;
	}
	void Merge(ChairTree* other) {
		Merge(root, other->root, left, right);
	}
	int  Find(int_t limit) {
		return Find(root, limit, left, right);
	}
};

ChairTree ct[MAX];

std::vector<int> son[MAX];

int N, M;

int lead[MAX];
int cost[MAX];

int_t Ans = 0;

#define MAXM 1000002001

void dfs(int x) {
	ct[x].Create(cost[x], 1, M + 10);
	for (size_t i = 0; i < son[x].size(); i++) {
		dfs(son[x][i]);
		ct[x].Merge(&ct[son[x][i]]);
	}
	if (x == 3) {
		bool end = true;
	}
	int_t ans = ct[x].Find(M);
	ans = (int_t)lead[x] * ans;
	if (ans > Ans) Ans = ans;
}

void Initalize() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		int p;
		scanf("%d %d %d", &p, &cost[i], &lead[i]);
		son[p].push_back(i);
	}
}

int main() {


	Initalize();

	dfs(1);

	printf("%lld\n", Ans);
}