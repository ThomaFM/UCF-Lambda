/**
 * Author: Lukr Videckis
 * Description: when cmp = less():
 *              a[le[i]] < a[i] >= a[ri[i]]
 * Time: O(N).
 * Usage: vi le = mono_st(a, less()), 
 *           ri = mono_range(le);
 * less_equal(), greater(), greater_equal()
 * Status: tested
 */
template<class T, typename F>
vi mono_st(const vector<T> & a, F cmp) {
	vi le(sz(a));
	rep(i,0,sz(a)){ 
    for (le[i] = i -1; le[i] >= 0 && !cmp(a[le[i]],a[i]);) 
        le[i] = le[le[i]]; }
	return le;
}

vi mono_range(const vi &le) {
	vi ri(sz(le), sz(le));
	rep (i, 0, sz(le)) 
    for (int j = i - 1; j != le[i]; j = le[j])
		ri[j] = i;
	return ri;
}