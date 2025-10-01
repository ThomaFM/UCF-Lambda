/**
 * Author: Thomas Meeks
 * Date: 2019-10-31
 * License: CC0
 * Source: Luke Videckis
 * Description: Various helper queries for suffix array problems
 * inputs are 0based and ranges are given and returned as incex
 * Time: lenlcp: O(1), cmpsub: O(1), findstr: O(log(n))
 * Status: Tested
*/
#pragma once

struct SAQuery{
    SuffixArray sa; RMQ<int> lcp;
    string s; vector<int> sainv;
    SAQuery(SuffixArray sa,string s):sa(sa), lcp(sa.lcp), s(s){
        sainv.resize(sz(s)+1);
        rep(i,0,sz(sa.sa)) sainv[sa.sa[i]] = i;
    } //len_lcp: takes in two ind and returns lcp
    int len_lcp(int u, int v){
        if(u==v) return sz(s)-u;
        auto[l,r] = minmax(sainv[u],sainv[v]);
        return lcp.query(l+1,r+1);
    } //given [) substr of s: s1<s2->-1,s1==s2->0,s1>s2->1
    int cmp_sub(int l1, int r1, int l2, int r2){ //[)
        auto sgn = [](int x){ return (x>0)-(x<0); };
        int len1 = r1-l1+1, len2 = r2-l2+1;
        return len_lcp(l1,l2) < min(len1,len2)
            ? sgn(sainv[l1]-sainv[l2]): sgn(len1-len2);
    }//returns [) range of the SA, substr is given [)
    pair<int, int> find_str(int s_l, int s_r) { //[)
        auto cmp = [&](int i, bool flip) -> bool {
            return flip ^ (len_lcp(i, s_l) < s_r - s_l); };
        auto it = begin(sa.sa) + sainv[s_l];
		int l=lower_bound(begin(sa.sa),it,0,cmp)-begin(sa.sa);
        int r=lower_bound(it+1,end(sa.sa),1,cmp)-begin(sa.sa);
        return {l, r}; //[)
    }
};
