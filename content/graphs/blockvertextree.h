/**
 * Author: Luke Videckis
 * Time: $O(n+m)$
 */
#pragma once

auto block_vertex_tree(const auto& adj, int num_bccs,
	const vector<int>& bcc_id) {
	int n = ssize(adj);
	vector<basic_string<int>> bvt(n + num_bccs);
	vector<bool> vis(num_bccs);
	for (int i = 0; i < n; i++) {
		for (auto [_, e_id] : adj[i]) {
			int bccid = bcc_id[e_id];
			if (!vis[bccid]) {
				vis[bccid] = 1;
				bvt[i] += bccid + n;
				bvt[bccid + n] += i;
			}
		}
		for (int bccid : bvt[i]) vis[bccid - n] = 0;
	}
	return bvt;
}

vector<basic_string<array<int, 2>>> adj(n);
auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
auto bvt = block_vertex_tree(adj, num_bccs, bcc_id);

//to loop over each unique bcc containing a node u:
for (int bccid : bvt[v]) {
	bccid -= n;
}
//to loop over each unique node inside a bcc:
for (int v : bvt[bccid + n]) {}
// [0, n) are original nodes
// [n, n + num_bccs) are BCC nodes
