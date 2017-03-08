#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

#define N 26

class Suffix {
	struct Node {
		Node* next[N];
		Node* pre;
		int step;
	};

	Node* NewNode(int step) {
		Node* node = new Node();
		node->step = step;
		return node;
	}

	Node* root;
	Node* last;

public:
	Suffix() {
		root = NewNode(0);
		last = root;
	}
	void Insert(char c) {
		Node* p = last;
		Node* np = NewNode(p->step + 1);

		while (p && !p->next[c - 'a'])
			p->next[c - 'a'] = np,
			p = p->pre;

		if (!p)
			np->pre = root;
		else {
			Node* q = p->next[c - 'a'];
			if (p->step + 1 == q->step)
				np->pre = q;
			else {
				Node* nq = NewNode(p->step + 1);
				memcpy(nq->next, q->next, sizeof(q->next));
				nq->pre = q->pre;
				q->pre = nq;
				np->pre = nq;
				while (p && p->next[c - 'a'] == q)
					p->next[c - 'a'] = nq,
					p = p->pre;
			}
		}
		last = np;
	}

};

int main() {

}