/**
 * Author: Brian
 * Date: 10/15/2025
 * Source: CP-Algorithms/Codeforces blog
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

typedef struct Node {
	Node *l = 0, *r = 0;
	int val, y, c;
	Node(int val) : val(val), y(rand()) { pull(); }
	void pull(); void push();
} *np;
int cnt(np n) { return n ? n->c : 0; }
void Node::pull() { c = cnt(l) + cnt(r) + 1; }
void Node::push() {}
np nl, nr;
pair<np, np> split(np x, int i, np &l = nl, np &r = nr) {
	if (!x) return {l = r = 0, 0};
	x->push(); // VVV "cnt(x->l)" => "x->val" for lower_bound
	if (i <= cnt(x->l)) split(x->l, i, l, x->l), r = x;
	else split(x->r, i - cnt(x->l) - 1, x->r, r), l = x;
	x->pull(); // ^^^ and "i - cnt(x->l) - 1" => "i"
	return {l, r};
}
auto merge(np l, np r, np &x = nl) {
	if (!l || !r) return x = l ?: r;
	l->push(), r->push();
	if (l->y < r->y) merge(l, r->l, r->l), x = r;
	else merge(l->r, r, l->r), x = l;
	x->pull();
	return x;
}
template<class F> void each(np n, F f) {
	if (n) { n->push(); each(n->l, f); f(n->val); each(n->r, f); }
}
