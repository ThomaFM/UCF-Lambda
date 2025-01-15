// * Author: Thomas Meeks
// * Source: Tyler Marks
// * Description: min Li-chao tree allows for range add of arbitary functions
// * such that any two functions only occur atmost once.
// * Usage: inc-inc, implicit, works with negative indices, O(log(n)) query
// * flip signs in update and modify query to change to max.
struct func {
    ll A,B;
    func(ll A, ll B): A(A), B(B) {}
    ll operator()(ll x) { return (A*x + B); }
};
const func idem = {0,(ll)8e18}; //idempotent, change for max
struct node {
    int lo, md, hi;
    func f = idem;
    node *left = nullptr, *right = nullptr;
    node(int lo, int hi): lo(lo), hi(hi), md(lo+(hi-lo)/2) {}
    void check(){
        if(left) return;
        left = new node(lo,md);
        right = new node(md+1,hi);
    }
    void update(func e) { //flip signs for max
        if(e(md) < f(md)) swap(e, f);
        if(lo == hi) return; 
        if(e(lo) > f(lo) && e(hi) > f(hi)) return;
        check();
        if(e(lo) < f(lo)) left->update(e);
        else right->update(e);
    } 
    void rangeUpdate(int L, int R, func e) { //[]
        if(R < lo || hi < L) return;
        if(L <= lo && hi <= R) return update(e);
        check();
        left->rangeUpdate(L, R, e);
        right->rangeUpdate(L, R,e);
    }
    ll query(int x) { //change to max if needed
        if(lo == hi) return f(x); check();
        if(x <= md) return min(f(x), left->query(x));
        return min(f(x), right->query(x));
    }
};