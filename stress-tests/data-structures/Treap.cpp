#include "../utilities/template.h"

#include "../../content/data-structures/Treap.h"

void split2(Node *x, Node *&l, Node *&r, int i) {
	if (!x) { l = r = 0; return; }
	x->push();
	if (i <= x->val) split2(x->l, l, x->l, i), r = x;
	else split2(x->r, x->r, r, i), l = x;
	x->pull();
}
auto split2(Node *x, int i) { pair<Node *, Node *> r;
	split2(x, r.first, r.second, i); return r; }

int ra() {
	static unsigned x;
	x *= 4176481;
	x += 193861934;
	return x >> 1;
}

Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}

int main() {
	srand(3);
	rep(it,0,1000) {
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) {
			nodes.emplace_back(i*2+2);
			exp.emplace_back(i*2+2);
		}
		Node* n = 0;
		rep(i,0,10)
			n = merge(n, &nodes[i]);

		int v = rand() % 25;
		int left = cnt(split2(n, v).first);
		int rleft = (int)(lower_bound(all(exp), v) - exp.begin());
		assert(left == rleft);
	}

	rep(it,0,10000) {
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) nodes.emplace_back(i);
		rep(i,0,10) exp.emplace_back(i);
		Node* n = 0;
		rep(i,0,10)
			n = merge(n, &nodes[i]);

		int i = ra() % 11, j = ra() % 11;
		if (i > j) swap(i, j);
		int k = ra() % 11;
		if (i < k && k < j) continue;

		move(n, i, j, k);
		// cerr << i << ' ' << j << ' ' << k << endl;

		int nk = (k >= j ? k - (j - i) : k);
		vi iv(exp.begin() + i, exp.begin() + j);
		exp.erase(exp.begin() + i, exp.begin() + j);
		exp.insert(exp.begin() + nk, all(iv));

		int ind = 0;
		each(n, [&](int x) {
			// cerr << x << ' ';
			assert(x == exp[ind++]);
		});
		// cerr << endl;
	}
	cout<<"Tests passed!"<<endl;
}
