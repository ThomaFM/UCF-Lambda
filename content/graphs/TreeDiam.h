/**
 * Author: Sachin
 * Description: Short code for finding a diameter of a tree and returning the path 
 * Time: $O(|V|)$
 * Status: stress-tested
 */
auto diameter = [&](int u, int p, auto &&diameter) -> vi {
    vi best;
    for (int v : graph[u]){
        if (v == p) continue;
        vi cur = diameter(v, u, diameter);
        if (sz(cur) > sz(best)) swap(cur, best);
    }
    best.push_back(u);
    return best;
};
//vi diam = diameter(0, -1, diameter);
//diam = diameter(diam[0], -1, diameter);
//number of nodes on diam is diam.size()
