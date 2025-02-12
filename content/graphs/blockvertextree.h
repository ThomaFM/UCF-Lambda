/**
 * Author: Luke Videckis
 * Description: articulation points and block-vertex tree
 * self edges not allowed
 * adj[u] += {v, i};
 * adj[v] += {u, i};
 * iscut[v] = 1 iff cut node
 * bccid[edge id] = id, 0<=id<numbccs
 * returns {numbccs, bccid, iscut}
 * Assumes the root node points to itself.
 */
auto cuts(const auto& adj, int m) {
	int n = ssize(adj), num_bccs = 0, q = 0, s = 0;
	vector<int> bcc_id(m, -1), is_cut(n), tin(n), st(m);
	auto dfs = [&](auto&& self, int v, int p) -> int {
	  int low = tin[v] = ++q;
	  for (auto [u, e] : adj[v]) {
		assert(v != u);
		if (e == p) continue;
		if (tin[u] < tin[v]) st[s++] = e;
		int lu = -1;
		low = min(low, tin[u] ?: (lu = self(self, u, e)));
		if (lu >= tin[v]) {
		  is_cut[v] = p >= 0 || tin[v] + 1 < tin[u];
		  while (bcc_id[e] < 0) bcc_id[st[--s]] = num_bccs;
		  num_bccs++;
		}
	  }
	  return low;
	};
	for (int i = 0; i < n; i++)
	  if (!tin[i]) dfs(dfs, i, -1);
	return tuple{num_bccs, bcc_id, is_cut};
  }
  //!   
  //! vector<vector<pii>> adj(n);
  //! auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
  //! auto bvt = block_vertex_tree(adj,
  //!   num_bccs, bcc_id);
  //!   
  //! vector<basic_string<array<int, 2>>> adj(n);
  //! auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
  //! auto bvt = block_vertex_tree(adj, num_bccs, bcc_id);
  //!
  //! //to loop over each unique bcc containing a node u:
  //! for (int bccid : bvt[v]) {
  //!     bccid -= n;
  //! }
  //! //to loop over each unique node inside a bcc:
  //! for (int v : bvt[bccid + n]) {}
  //! [0, n) are original nodes
  //! [n, n + num_bccs) are BCC nodes
  //! @time O(n + m)
  //! @time O(n)
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