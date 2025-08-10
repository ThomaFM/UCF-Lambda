/**
 * Author: Thomas Meeks
 * Date: August 9th 2025
 * Source: https://codeforces.com/blog/entry/91632 + Seba's Implementation
 * Description: Count \# primes <= N, can be modified to return sum of primes
 * by setting f(p) = n, ps(n) = nth tri number. 
 * Status: Tested on https://judge.yosupo.jp/problem/counting_primes 
 * + some bruteforce
 * Time: $O(n^{3/4})$
 */

ll countprimes(ll n) { //n>0
	vector<ll> divs,dp; ll sq = sqrtl(n);
	for (ll l = 1, r; l <= n && (r = n / (n / l)); l = r + 1) 
		divs.push_back(r);
	auto idx = [&](ll x) -> int {
	return x <= sq ? x - 1 : (sz(divs) - n / x); };
	rep(i,0,sz(divs)) dp.push_back(divs[i]-1);
	for(ll p = 2; p*p <= n; ++p) // ^ ps(divs[i])-1
		if(dp[p-1]!=dp[p-2])
		for(int i = sz(divs)-1; divs[i]>=p*p && i>=0; i--)
			dp[i] -= (dp[idx(divs[i]/p)]-dp[p-2]);// *f(p);
	return dp.back();
}