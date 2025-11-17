/**
 * Author: Luke Videckis
 * Time: $O(n + m)$
 * Memory: $O(n)$
 */
#pragma once

auto bridge_tree(const auto& adj, int num_ccs,
	const vector<int>& br_id, const vector<int>& is_br) {
	vector<basic_string<int>> tree(num_ccs);
	for (int i = 0; i < ssize(adj); i++)
		for (auto [u, e_id] : adj[i])
			if (is_br[e_id]) tree[br_id[i]] += br_id[u];
	return tree;
}

vector<basic_string<array<int, 2>>> adj(n);
auto [num_ccs, br_id, is_br] = bridges(adj, m);
auto bt = bridge_tree(adj, num_ccs, br_id, is_br);
