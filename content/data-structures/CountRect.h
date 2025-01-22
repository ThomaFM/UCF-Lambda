/**
 * Author: Adapted from Luke Videckis
 * Description: cnt[i][j] = number of times an i-by-j
 * sub rectangle appears such that all i*j cells \textbf{ARE 1}.
 * cnt[i][0],cnt[0][j] are garbage
 * Time: O(NM)
 * Status: tested
 */
vector<vi> count_rectangles(
	const vector<vector<bool>>&grid) {
    int n = sz(grid), m = sz(grid[0]);
    vector<vi> cnt(n + 1, vi(m + 1, 0));
    vi h(m);
    for( const auto &row : grid) {
        transform(all(h), begin(row), begin(h), 
        [](int a, bool g) { return g * (a + 1); });
        vi le ( mono_st(h,less())), r(mono_range(le));
        rep(j,0,m) {
            int cnt_l = j - le[j] - 1, cnt_r = r[j] - j - 1;
            cnt[h[j]][cnt_l + cnt_r + 1]++;
            cnt[h[j]][cnt_l]--;
            cnt[h[j]][cnt_r]--;
        }
    }
    rep(i,1,n+1) rep(k,0,2) for (int j = m; j > 1; j--)
        cnt[i][j - 1] += cnt[i][j];
    for (int i = n ; i > 1; i--)
        rep(j, 1, m + 1) cnt[i - 1][j] += cnt[i][j];
    return cnt;
}