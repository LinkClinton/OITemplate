#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>

#define MAX 260000
#define LOG 18

struct Tc {
	int to, c;
};

class Tree {
private:
	int cnt;

	bool vis[MAX];

	void dfs(int x) {
		vis[x] = true;
		dfn[x] = ++cnt;
		start[x] = cnt;
		for (size_t i = 0; i < m[x].size(); i++) {
			int to = m[x][i].to;
			if (vis[to]) continue;
			parent[to][0] = x;
			value[to][0] = m[x][i].c;
			dep[to] = dep[x] + 1;
			dfs(to);
		}
		end[x] = cnt;
	}
public:
	int parent[MAX][LOG + 1];
	long long value[MAX][LOG + 1];
	int dfn[MAX];
	int start[MAX];
	int end[MAX];
	int dep[MAX];

	std::vector<Tc> m[MAX];

	int NodeCount;
	int EdgeCount;

	void Create() {
		dfs(1);
		for (int i = 1; i <= LOG; i++)
			for (int j = 1; j <= NodeCount; j++) {
				parent[j][i] = parent[parent[j][i - 1]][i - 1];
				value[j][i] = std::min(value[j][i - 1], value[parent[j][i - 1]][i - 1]);
			}
	}

#define INF 1999999999999

	long long Min_Value(int p, int son) {
		long long ans = INF;
		for (int i = LOG; i >= 0; i--) {
			if (parent[son][i] != 0 && dep[parent[son][i]] > dep[p])
				ans = std::min(ans, (long long)value[son][i]),
				son = parent[son][i];
		}

		ans = std::min(ans, (long long)value[son][0]);

		return ans;
	}

	int LCA(int u, int v) {
		//u>v
		if (dep[u] < dep[v]) std::swap(u, v);

		for (int i = LOG; i >= 0; i--)
			if (parent[u][i] != 0 && dep[parent[u][i]] >= dep[v])
				u = parent[u][i];

		if (u == v) return u;

		for (int i = LOG; i >= 0; i--)
			if (parent[u][i] != parent[v][i])
				u = parent[u][i], v = parent[v][i];

		return parent[u][0];
	}
};

class VirtualTree {
public:
	struct Node {
		int id; int dfn; long long value;
		long long ans;
		std::vector<int> son;
		Node(int _id = 0, int _dfn = 0) { id = _id; dfn = _dfn; value = 0; ans = 0; }
		operator int() { return id; }
	};
private:
	Tree* tree;

	static bool cmp(const Node &a, const Node &b) {
		return a.dfn < b.dfn;
	}

	bool vis[MAX];
	bool Is[MAX];

	void Connect(int parent, int son) {
		node[parent].son.push_back(son);
		node[son].value = tree->Min_Value(node[parent], node[son]);
	}

	void BuildVirtualTree() {
		std::stack<int> Stack;

		for (int i = 1; i <= len; i++) {
			if (Stack.empty()) { Stack.push(i); continue; }
			while (tree->start[node[Stack.top()]] > node[i].dfn
				|| tree->end[node[Stack.top()]] < node[i].dfn)
				Stack.pop();
			Connect(Stack.top(), i);
			Stack.push(i);
		}
	}

	void dp(int x) {
		node[x].ans = 0;
		if (node[x].son.size() == 0) node[x].ans = node[x].value;
		for (size_t i = 0; i < node[x].son.size(); i++) {
			dp(node[x].son[i]);
			node[x].ans += node[node[x].son[i]].ans;
		}
		node[x].ans = std::min(node[x].ans, (long long)node[x].value);
		if (Is[node[x]]) node[x].ans = node[x].value;
	}
public:
	int len;
	Node node[MAX];

	void CreateFromTree(Tree* _tree) {
		tree = _tree;

		std::sort(node + 1, node + len + 1, cmp);

		for (int i = 1; i <= len; i++)
			vis[node[i]] = true, Is[node[i]] = true;

		int size = len;

		for (int i = 1; i < size; i++) {
			int LCA = tree->LCA(node[i], node[i + 1]);
			if (vis[LCA]) continue;
			vis[LCA] = true;
			node[++len].id = LCA;
			node[len].dfn = tree->dfn[LCA];
			node[len].son.clear();
		}

		std::sort(node + 1, node + 1 + len, cmp);

		if (node[1] == 1) node[1].value = INF;
		else node[1].value = tree->value[node[1]][0];

		BuildVirtualTree();
	}

	long long Ans() {
		dp(1);
		if (node[1].id != 1) node[1].ans = std::min(node[1].ans, (long long)tree->Min_Value(1, node[1]));
		return node[1].ans;
	}

	void reset() {
		for (int i = 1; i <= len; i++)
			vis[node[i]] = false, Is[node[i]] = false;
		len = 0;
	}
};

Tree tree;

VirtualTree vtree;

int read() {
	int x = 0;
	int f = 1;
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

void Initalize() {
	tree.NodeCount = read();

	for (int i = 1; i < tree.NodeCount; i++) {
		int u = read();
		int v = read();
		int c = read();
		tree.m[u].push_back({ v,c });
		tree.m[v].push_back({ u,c });
	}

	tree.Create();
}

int T;
int main() {
	Initalize();
	T = read();
	for (int i = 1; i <= T; i++) {
		vtree.reset();

		int NodeCount = read();

		vtree.len = NodeCount;
		for (int i = 1; i <= NodeCount; i++) {
			int id = read();
			vtree.node[i].id = id;
			vtree.node[i].dfn = tree.dfn[id];
			vtree.node[i].son.clear();
		}
		vtree.CreateFromTree(&tree);

		printf("%lld\n", vtree.Ans());
	}
}