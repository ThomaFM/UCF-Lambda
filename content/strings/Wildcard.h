/**
 * Author: Luke Videckis
 * Description: string matching with wildcards, returns boolean
 * vector of size s-p+1 representing if a match occurs at this 
 * start position, wild cards are repsented by 0 and 
 * can be in s,p or both. 
 * Time: O((n+m) log (n+m))
 * Status: tested on yusopo
 */
vector<vl> make_powers(const vl& v) {
    int n = sz(v); 
    vector<vl> pws(3, vl(n)); pws[0] = v;
    rep(k,1,3) rep(i,0,n) //mod?
        pws[k][i] = pws[k-1][i]*v[i];
    return pws;
}

vector<bool> wildcard_pattern_matching(const vl& s,
    const vl& p) {
    int n = sz(s), m = sz(p);
    auto s_pws = make_powers(s), p_pws = make_powers(p);
    for (auto& p_pw : p_pws) reverse(all(p_pw));
    vector<vl> res(3);
    rep(pw_hay,0,3) //ntt
        res[pw_hay] = conv(s_pws[pw_hay], p_pws[2 - pw_hay]);
    vector<bool> mtch(n - m + 1);
    rep(i,0,sz(mtch)){
        int id = i + m - 1;
        auto num = res[0][id] - 2 * res[1][id] + res[2][id];
        mtch[i] = !num; //num == 0
    }
    return mtch;
}