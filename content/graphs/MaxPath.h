/**
 * Author: Thomas Meeks
 * Source: folklore/sachin
 * Description: Given edges (Weight,U,V) answers max on path queries of 
 * the induced MST.
 * Time: $O(Nlog(N))$
 */
struct maxPath{
    vector<int> p,s,wt; ll tot = 0;
    maxPath(vector<tuple<int,int,int>> ed, int n): 
        p(n), s(n,1),wt(n,INT_MAX){
        sort(all(ed)); iota(all(p),0); 
        for(auto[w,u,v]: ed){
            while(u!=p[u]) u=p[u]; 
            while(v!=p[v]) v=p[v];
            if(u==v) continue; tot+=w;
            if(s[u]>s[v]) swap(u,v);
            p[u] = v; s[v]+=s[u]; wt[u] = w;
        }
    }
    int query(int u, int v){
        while(p[u]!=v && p[v]!=u){
            if(wt[u]<wt[v]) u=p[u]; 
            else v=p[v]; 
        } 
        return p[u]==v ? wt[u]:wt[v];
    }
};
