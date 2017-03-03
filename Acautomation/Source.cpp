#include<iostream> 
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>

#define MAX 610000

using namespace std;

struct Question {
	int l, r;
	int id;
	Question(int l_, int r_, int id_) {
		l = l_;
		r = r_;
		id = id_;
	}
};

int n, q;

int ans[MAX];

class ChairTree {
private:
	struct Node {
		Node* left;
		Node* right;
		int size;
	};
	Node* root;

	Node* NewNode() {
		Node* node = new Node();
		return node;
	}
	int size(Node* node) { if (node) return node->size; return 0; }
	void update(Node* node) {
		if (!node) return;
		node->size = size(node->left) + size(node->right);
	}
	void Insert(Node* &node, int l, int r, int value) {
		if (!node) node = NewNode();
		if (l == r) {
			node->size = 1;
			return;
		}
		int mid = (l + r) >> 1;
		if (value <= mid)
			Insert(node->left, l, mid, value);
		else Insert(node->right, mid + 1, r, value);
		update(node);
	}
	void Merge(Node* &last, Node* &node, int l, int r) {
		if (!last) return;
		if (!node) { node = last; return; };
		if (l == r) {
			node->size = 1;
			return;
		}
		int mid = (l + r) >> 1;
		if (last->left)
			Merge(last->left, node->left, l, mid);
		if (last->right)
			Merge(last->right, node->right, mid + 1, r);
		update(node);
	}
	int Query(Node* node, int l, int r, int quel, int quer) {
		if (!node) return 0;
		if (quel <= l && r <= quer)
			return node->size;
		int mid = (l + r) >> 1;
		int ans = 0;
		if (quer <= mid) return Query(node->left, l, mid, quel, quer);
		else if (quel > mid) return Query(node->right, mid + 1, r, quel, quer);
		else {
			ans += Query(node->left, l, mid, quel, mid);
			ans += Query(node->right, mid + 1, r, mid + 1, quer);
		}
		return ans;
	}
	int l, r;
public:
	void Initalize(int L, int R) {
		l = L; r = R;
	}
	void Insert(int value) {
		Insert(root, l, r, value);
	}
	void Merge(ChairTree* last) {
		Merge(last->root, root, l, r);
	}
	int  Query(int quel, int quer) {
		return Query(root, l, r, quel, quer);
	}
};

class AcautoMation {
private:
	struct Node {
		Node* next[2];
		Node* fail;
		ChairTree Ct;
		std::vector<Node*> son;
		std::vector<Question> que;
	};

	Node* root;
	Node pool[MAX];
	int cnt;

	Node* NewNode() {
		cnt++;
		Node* node = &pool[cnt];
		node->Ct.Initalize(1, n);
		return node;
	}
public:
	AcautoMation() { cnt = 0; root = NewNode(); }
	void Insert(char* c, int l, int r, int id) {
		int len = strlen(c);
		Node* node = root;
		for (int i = 0; i<len; i++) {
			int id = c[i] - 'a';
			if (!node->next[id]) node->next[id] = NewNode();
			node = node->next[id];
		}
		node->que.push_back(Question(l, r, id));
	}
	void GetFail() {
		std::queue<Node*> t;
		t.push(root);
		while (!t.empty()) {
			Node* node = t.front();
			t.pop();
			for (int i = 0; i < 2; i++) {
				if (!node->next[i]) continue;
				if (node == root) {
					node->next[i]->fail = root;
					t.push(node->next[i]);
				}
				else {
					Node* tmp = node;
					while (tmp != root && !tmp->fail->next[i])
						tmp = tmp->fail;
					if (tmp == root)
						node->next[i]->fail = root;
					else node->next[i]->fail = tmp->fail->next[i];
					t.push(node->next[i]);
				}
			}
		}
	}
	void Run(const char* c, int len, int id) {
		Node* node = root;
		for (int i = 0; i<len; i++) {
			int val = c[i] - 'a';
			while (node && !node->next[val])
				node = node->fail;
			if (!node) node = root;
			node = node->next[val];
			Node* fail = node;
			if (fail) {
				fail->Ct.Insert(id);
			}
		}
	}
	void dfs(Node* x) {
		for (size_t i = 0; i<x->son.size(); i++) {
			dfs(x->son[i]);
			x->Ct.Merge(&x->son[i]->Ct);
		}
		for (size_t i = 0; i<x->que.size(); i++) {
			ans[x->que[i].id] = x->Ct.Query(x->que[i].l,
				x->que[i].r);
		}
	}
	void getAns() {
		for (int i = cnt; i >= 1; i--) {
			if (!pool[i].fail) continue;
			pool[i].fail->son.push_back(&pool[i]);
		}
		dfs(root);
	}
};

AcautoMation A;


char c[MAX];
std::string str[MAX];

void Initalize() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%s", c);
		str[i] = c;
	}
	for (int i = 1; i <= q; i++) {
		int l, r;
		scanf("%d %d %s", &l, &r, c);
		A.Insert(c, l, r, i);
	}
	A.GetFail();
}

int main() {
	Initalize();
	for (int i = 1; i <= n; i++) {
		A.Run(str[i].c_str(), str[i].length(), i);
	}
	A.getAns();
	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
