/**
 * Author: Tyler Marks
 * Description: Gets all factors of a number $N$ given the prime factorization of the number.
 * as lists of primes and corresponding power
 * Time: ~ $O(\sqrt[3]{N})$
 * Status: Probably works now
*/

void getFactors(auto &primes, auto &pws, auto &divs, int i = 0, ll n = 1) {
	if(i == pws.size()) return void(divs.push_back(n));
	for(ll j = 0, pow = 1; j <= pws[i]; j++, pow *= primes[i])
		getFactors(primes, pws, divs, i+1, n * pow);
}
