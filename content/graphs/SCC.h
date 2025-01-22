/**
 * Author: Luke Videckis
 * Description: Finds strogly connected components
 * in a directed graph.
 * Usage: auto [num_sccs, scc_id] = sccs(adj);
          scc_id[v] = id, 0<=id<num_sccs
          for each edge u -> v: scc_id[u] >= scc_id[v]
 * Time: O(E + V)
 * Status: Tested
 */

auto sccs(const vector<vi>& adj) {
  int n = sz(adj), num_sccs = 0, q = 0, s = 0;
  vi scc_id(n, -1), tin(n), st(n);
  auto dfs = [&](auto&& self, int v) -> int {
    int low = tin[v] = ++q; st[s++] = v;
    for (int u : adj[v]) if (scc_id[u] < 0)
        low = min(low, tin[u] ?: self(self, u));
    if (tin[v] == low) {
      while (scc_id[v] < 0) scc_id[st[--s]] = num_sccs;
      num_sccs++; 
    } 
    return low;
  };
  rep(i,0,n) if (!tin[i]) dfs(dfs, i);
  return pair{num_sccs, scc_id};
}