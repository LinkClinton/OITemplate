/*
brute
*/
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define MAX 80000
#define INF 99999999

#ifndef _DEBUG
#define nullptr NULL
#endif // !_DEBUG


struct Edge {
	int id;
	int u, v;
	int c;
	bool In;
	Edge() { id = 0; u = 0; v = 0; c = 0; In = false; }
	Edge(int _u, int _v, int _c, int _id) { u = _u; v = _v; c = _c; id = _id; In = false; }

	int other(int x) { if (x == u) return v; return u; }

	static bool cmp(const Edge a, const Edge b) {
		return a.c < b.c;
	}
};

Edge edge[MAX];
Edge* hash_edge[MAX];
int hash_id[MAX];

int N, M, Q;

long long ans = 0;

static bool cmp(Edge* a, Edge* b) {
	return a->c < b->c;
}

class LinkCutTree {
private:
	//check
	struct Node {
		Node* left;
		Node* parent;
		Node* right;
		bool reverse;
		int value;
		Edge* edge;
		int max_value;
		Node* max_node;

		Node() {
			left = nullptr; right = nullptr;
			reverse = false;
			value = 0;  edge = nullptr;
			max_value = -INF; max_node = nullptr;
		}
	};

	Node node_pool[MAX]; //check

						 //check
	bool IsRoot(Node* node) {
		if (node->parent == nullptr) return true;
		if (node->parent->left != node && node->parent->right != node) return true;
		return false;
	}

	//check
	Node* NewNode(int value) {
		Node* node = new Node();
		node->value = value;
		return node;
	}

	//check
	int value(Node* node) {
		if (node) return node->value;
		return 0;
	}

	//check
	int max_value(Node* node) {
		if (node) return node->max_value;
		return -INF;
	}

	template<typename T>
	T max(T x, T y) { if (x > y) return x; return y; }

	//check
	void update(Node* node) {
		if (node == nullptr) return;
		node->max_value = node->value;
		node->max_node = node;
		if (node->max_value < max_value(node->left))
			node->max_value = node->left->max_value,
			node->max_node = node->left->max_node;
		if (node->max_value < max_value(node->right))
			node->max_value = node->right->max_value,
			node->max_node = node->right->max_node;
	}

	//check
	void downdate(Node* node) {
		if (node == nullptr) return;
		if (node->reverse) {
			std::swap(node->left, node->right);
			if (node->left)
				node->left->reverse ^= true;
			if (node->right)
				node->right->reverse ^= true;
			node->reverse = false;
		}
	}

	//check
	Node* get_parent(Node* node) {
		downdate(node->parent);
		downdate(node);
		return node->parent;
	}

	//check
	void update_rotate(Node* node, Node* parent) {
		if (parent->parent) {
			if (parent->parent->left == parent)
				parent->parent->left = node;
			if (parent->parent->right == parent)
				parent->parent->right = node;
		}

		node->parent = parent->parent;
		parent->parent = node;

		update(parent);
		update(node);
	}

	//check
	void left_rotate(Node* node) {
		Node* parent = get_parent(node);

		parent->right = node->left;
		if (node->left) node->left->parent = parent;
		node->left = parent;

		update_rotate(node, parent);
	}

	//check
	void right_rotate(Node* node) {
		Node* parent = get_parent(node);

		parent->left = node->right;
		if (node->right) node->right->parent = parent;
		node->right = parent;

		update_rotate(node, parent);
	}

	std::vector<Node*> down_pool;

	//check
	void splay(Node* node) {
		Node* tmp_node = node;

		down_pool.clear();

		while (!IsRoot(tmp_node)) {
			down_pool.push_back(tmp_node);
			tmp_node = tmp_node->parent;
		}
		down_pool.push_back(tmp_node);

		for (int i = down_pool.size() - 1; i >= 0; i--)
			downdate(down_pool[i]);

		while (!IsRoot(node)) {
			if (node->parent->left == node)
				right_rotate(node);
			else left_rotate(node);
		}
	}

public:
	Node* operator[](int index) {
		return &node_pool[index];
	}
	void Access(Node* node) {
		downdate(node);
		splay(node);
		node->right = nullptr;
		update(node);

		while (node->parent) {
			splay(node->parent);
			downdate(node->parent);
			node->parent->right = node;
			update(node->parent);
			splay(node);
		}
	}
	void MakeRoot(Node* node) {
		Access(node);
		splay(node);
		node->reverse ^= true;
	}
	void Link(Node* u, Node* v) {
		MakeRoot(u);
		u->parent = v;
	}
	void Cut(Node* u, Node* v) {
		MakeRoot(u);
		Access(v);
		v->left = nullptr;
		u->parent = nullptr;
	}
	void LinkEdge(Node* e) {
		Node* u = &node_pool[e->edge->u];
		Node* v = &node_pool[e->edge->v];

		e->edge->In = true;

		Link(u, e);
		Link(e, v);
	}
	void CutEdge(Node* e) {
		Node* u = &node_pool[e->edge->u];
		Node* v = &node_pool[e->edge->v];

		e->edge->In = false;

		Cut(u, e);
		Cut(e, v);
	}
	void Fix(Node* new_edge) {
		Node* u = &node_pool[new_edge->edge->u];
		Node* v = &node_pool[new_edge->edge->v];

		MakeRoot(u);
		Access(v);

		Node* target = v->left->max_node;

		if (new_edge->value >= target->value) return;

		ans = ans - target->edge->c + new_edge->edge->c;

		CutEdge(target);

		LinkEdge(new_edge);
	}
	void Modify(Node* node, int value) {
		MakeRoot(node);
		node->value = value;
		update(node);
	}
	bool IsConnect(Node* u, Node* v) {
		if (u == v) return true;
		MakeRoot(u);
		Access(v);
		while (v->left)
			v = v->left;
		if (v == u) return true;
		return false;
	}
};
LinkCutTree lct;



void Initalzie() {
	scanf("%d %d %d", &N, &M, &Q);
	for (int i = 1; i <= M; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		edge[i] = Edge(u, v, c, i);
	}
	for (int i = 1; i <= N; i++) {
		lct[i]->edge = nullptr;
		lct[i]->value = -INF;
	}
	for (int i = 1; i <= M; i++) {
		lct[i + N]->edge = &edge[i];
		lct[i + N]->value = edge[i].c;
		hash_edge[i] = &edge[i];
	}
	std::sort(hash_edge + 1, hash_edge + 1 + M, cmp);
	for (int i = 1; i <= M; i++) {
		hash_id[hash_edge[i]->id] = i;
		if (!lct.IsConnect(lct[hash_edge[i]->u], lct[hash_edge[i]->v])) {
			lct.LinkEdge(lct[hash_edge[i]->id + N]);
			ans += hash_edge[i]->c;
			hash_edge[i]->In = true;
		}
	}
}


void Fix(int hashid) {
	while (hashid != 1 && hash_edge[hashid - 1]->c > hash_edge[hashid]->c) {
		std::swap(hash_edge[hashid - 1], hash_edge[hashid]);
		std::swap(hash_id[hash_edge[hashid]->id], hash_id[hash_edge[hashid - 1]->id]);
		hashid--;
	}
	while (hashid != M && hash_edge[hashid + 1]->c < hash_edge[hashid]->c) {
		std::swap(hash_edge[hashid + 1], hash_edge[hashid]);
		std::swap(hash_id[hash_edge[hashid]->id], hash_id[hash_edge[hashid + 1]->id]);
		hashid++;
	}
}

int main() {
	Initalzie();
	for (int i = 1; i <= Q; i++) {
		int edge_id;
		int new_value;
		scanf("%d %d", &edge_id, &new_value);
		if (edge[edge_id].u == edge[edge_id].v) {
			printf("%lld\n", ans);
			continue;
		}
		if (edge[edge_id].In == false) {
			if (edge[edge_id].c <= new_value) {
				edge[edge_id].c = new_value;
				lct.Modify(lct[edge_id + N], new_value);
			}
			else {
				edge[edge_id].c = new_value;
				lct.Modify(lct[edge_id + N], new_value);
				lct.Fix(lct[edge_id + N]);
			}
		}
		else {
			if (edge[edge_id].c >= new_value) {
				ans = ans - edge[edge_id].c + new_value;
				edge[edge_id].c = new_value;
				lct.Modify(lct[edge_id + N], new_value);
			}
			else {
				lct.CutEdge(lct[edge_id + N]);
				bool failed = false;
				for (int j = hash_id[edge_id] + 1; j <= M; j++) {
					if (hash_edge[j]->c >= new_value) { failed = true; break; }
					if (!lct.IsConnect(lct[hash_edge[j]->u], lct[hash_edge[j]->v])) {
						lct.LinkEdge(lct[hash_edge[j]->id + N]);
						ans = ans - edge[edge_id].c + hash_edge[j]->c;
						break;
					}
				}
				if (failed) {
					lct.LinkEdge(lct[edge_id + N]);
					ans = ans - edge[edge_id].c + new_value;
				}
				edge[edge_id].c = new_value;
				lct.Modify(lct[edge_id + N], new_value);
			}
		}

		//fix
		Fix(hash_id[edge_id]);

		printf("%lld\n", ans);
	}
}