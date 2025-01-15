//Tested on https://judge.yosupo.jp/problem/segment_add_get_min
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "lichao.h"
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,q; cin >> n >> q;
    node nd = node(-1e9,1e9);
    for(int i = 0; i < n; i++){
        ll l,r,a,b; cin >> l >> r >> a >> b;
        func line = func(a,b);
        nd.rangeUpdate(l,r-1,line);
    }

    for(int i = 0; i < q; i++){
        int qtype; cin >> qtype;
        if(!qtype){
            ll l,r,a,b; cin >> l >> r >> a >> b;
            func line = func(a,b);
            nd.rangeUpdate(l,r-1,line);
        }else{
            int x; cin >> x;
            ll y = nd.query(x);
            if(y >= 8e18) cout << "INFINITY\n";
            else cout << nd.query(x) << "\n";
        }
    }

    cout.flush();

    return 0;
}