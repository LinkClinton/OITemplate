/*
1.区间赋值
2.区间翻转
3.区间取反
4.区间查询
*/

#ifndef _DEBUG
#define nullptr NULL
#endif // !_DEBUG


#include<algorithm>
#include<iostream>
#include<cstring>
#include<cassert>
#include<cstdio>
#include<vector>


#define Get(x,y) (x?x->y:0)
#define MAX 120000

class Splay {
private:
	struct Node {
		Node *left, *right;
		Node *parent;
		int sum;
		int size;
		int value;
		int left_max;
		int left_min;
		int right_min;
		int right_max;
		int cover;
		bool swap;
		bool invert;
	};

	Node *NewNode(Node *parent) {
		Node* node = new Node();
		node->parent = parent;
		node->size = 1;
		return node;
	}

	Node* root;
	Node* nil;

	void update(Node *node) {
		if (!node) return;
		downdate(node->left);
		downdate(node->right);
		node->sum = Get(node->left, sum) + Get(node->right, sum) + node->value;
		node->left_max = std::max(Get(node->left, left_max), std::max(Get(node->left, sum)
			+ node->value, Get(node->left, sum) + node->value + Get(node->right, left_max)));
		node->left_min = std::min(Get(node->left, left_min), std::min(Get(node->left, sum)
			+ node->value, Get(node->left, sum) + node->value + Get(node->right, left_min)));
		node->right_max = std::max(Get(node->right, right_max), std::max(Get(node->right, sum)
			+ node->value, Get(node->right, sum) + node->value + Get(node->left, right_max)));
		node->right_min = std::min(Get(node->right, right_min), std::min(Get(node->right, sum)
			+ node->value, Get(node->right, sum) + node->value + Get(node->left, right_min)));
		node->size = Get(node->left, size) + Get(node->right, size) + 1;
	}
	void downdate(Node *node) {
		if (!node) return;
		if (node->swap) {
			if (node->left)
				node->left->swap ^= true;
			if (node->right)
				node->right->swap ^= true;
			std::swap(node->left, node->right);
			std::swap(node->right_min, node->left_min);
			std::swap(node->right_max, node->left_max);
			node->swap = false;
		}
		if (node->cover != 0) {
			if (node->left)
				node->left->invert = false,
				node->left->cover = node->cover;
			if (node->right)
				node->right->invert = false,
				node->right->cover = node->cover;
			node->value = node->cover;
			node->sum = node->size*node->cover;
			if (node->cover == 1)
				node->left_max = node->sum,
				node->left_min = 0,
				node->right_max = node->sum,
				node->right_min = 0;
			if (node->cover == -1)
				node->left_max = 0,
				node->left_min = node->sum,
				node->right_max = 0,
				node->right_min = node->sum;
			node->cover = 0;
		}
		if (node->invert) {
			if (node->left)
				node->left->invert ^= true;
			if (node->right)
				node->right->invert ^= true;
			node->value = -node->value;
			node->sum = -node->sum;
			std::swap(node->left_max, node->left_min);
			std::swap(node->right_max, node->right_min);
			node->left_max = -node->left_max;
			node->left_min = -node->left_min;
			node->right_max = -node->right_max;
			node->right_min = -node->right_min;
			node->invert = false;
		}
	}

	void UpdateParent(Node *node, Node *parent) {
		if (parent->parent) {
			if (parent->parent->left == parent)
				parent->parent->left = node;
			else parent->parent->right = node;
		}

		node->parent = parent->parent;
		parent->parent = node;

		if (parent == root) root = node;

		update(parent);
		update(node);
	}

	void LeftRotate(Node *node) {
		Node *parent = node->parent;
		downdate(parent);
		downdate(node);

		parent->right = node->left;
		if (node->left)
			node->left->parent = parent;
		node->left = parent;

		UpdateParent(node, parent);
	}

	void RightRotate(Node *node) {
		Node *parent = node->parent;
		downdate(parent);
		downdate(node);

		parent->left = node->right;
		if (node->right)
			node->right->parent = parent;
		node->right = parent;

		UpdateParent(node, parent);
	}

	std::vector<Node*> pool;

	void DownSplay(Node *node, Node *to) {
		pool.clear();
		while (node != to) {
			pool.push_back(node);
			node = node->parent;
		}
		if (to != nil)
			pool.push_back(to);
		for (int i = pool.size() - 1; i >= 0; i--)
			downdate(pool[i]);

	}

	void splay(Node *node, Node *to) {
		DownSplay(node, to);

		while (node->parent != to) {
			if (node->parent->parent == to) {
				if (node->parent->left == node)
					RightRotate(node);
				else LeftRotate(node);
			}
			else {
				if (node->parent->parent->left == node->parent) {
					if (node->parent->left == node)
						RightRotate(node->parent),
						RightRotate(node);
					else
						LeftRotate(node),
						RightRotate(node);
				}
				else {
					if (node->parent->right == node)
						LeftRotate(node->parent),
						LeftRotate(node);
					else
						RightRotate(node),
						LeftRotate(node);
				}
			}
		}
	}

	Node *GetKth(Node* node, int kth) {
		downdate(node);
		int lsize = Get(node->left, size);
		if (kth > lsize + 1) return GetKth(node->right, kth - lsize - 1);
		else if (kth == lsize + 1) return node;
		else return GetKth(node->left, kth);
	}

	Node *Bulid(Node *parent, int l, int r, int arr[]) {
		if (l > r) return nullptr;
		if (l == r) {
			Node* node = NewNode(parent);
			node->value = arr[(l + r) >> 1];
			node->sum = node->value;
			node->left_max = std::max(0, node->value);
			node->left_min = std::min(0, node->value);
			node->right_max = std::max(0, node->value);
			node->right_min = std::min(0, node->value);
			return node;
		}
		int mid = (l + r) >> 1;
		Node* node = NewNode(parent);
		node->left = Bulid(node, l, mid - 1, arr);
		node->right = Bulid(node, mid + 1, r, arr);
		node->value = arr[mid];
		update(node);
		return node;
	}
public:
	Splay() {
		nil = new Node();
		root = nullptr;
	}
	void Bulid(int l, int r, int arr[]) {
		root = Bulid(nil, l, r, arr);
	}
	void GetSeq(int l, int r) {
		Node* L = GetKth(root, l);
		Node* R = GetKth(root, r + 2);
		splay(L, nil);
		splay(R, root);
	}
	void Replace(int l, int r, int value) {
		GetSeq(l, r);
		downdate(root->right->left);
		root->right->left->cover = value;
		splay(root->right->left, nil);
	}
	void Swap(int l, int r) {
		GetSeq(l, r);
		downdate(root->right->left);
		root->right->left->swap ^= true;
		splay(root->right->left, nil);
	}
	void Invert(int l, int r) {
		GetSeq(l, r);
		downdate(root->right->left);
		root->right->left->invert ^= true;
		splay(root->right->left, nil);
	}
	int  Query(int l, int r) {
		GetSeq(l, r); downdate(root->right->left);
		Node *node = root->right->left;
		return (std::abs(node->left_min) + 1) / 2 + (std::abs(node->right_max) + 1) / 2;
	}
};

Splay splay;

int N, M;
int arr[MAX];

char c[MAX];
char ct[100];
char v[100];

void Initalize() {
	scanf("%d %d", &N, &M);
	scanf("%s", c);
	for (int i = 1; i <= N; i++) {
		if (c[i - 1] == '(') arr[i + 1] = 1;
		else arr[i + 1] = -1;
	}
	arr[1] = -9999;
	arr[N + 2] = 9999;
	splay.Bulid(1, N + 2, arr);
}

int main() {
	Initalize();
	for (int i = 1; i <= M; i++) {
		scanf("%s", ct);
		switch (ct[0])
		{
		case 'R': {
			int l, r, val;
			scanf("%d %d %s", &l, &r, v);
			if (v[0] == '(') val = 1; else val = -1;
			splay.Replace(l, r, val);
			break;
		}
		case 'S': {
			int l, r;
			scanf("%d %d", &l, &r);
			splay.Swap(l, r);
			break;
		}
		case 'I': {
			int l, r;
			scanf("%d %d", &l, &r);
			splay.Invert(l, r);
			break;
		}
		case 'Q': {
			int l, r;
			scanf("%d %d", &l, &r);
			printf("%d\n", splay.Query(l, r));
			break;
		}
		default:
			break;
		}
	}
}