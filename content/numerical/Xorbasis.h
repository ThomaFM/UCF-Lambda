/**
 * Author: Thomas Meeks
 * Date: 2004-02-08
 * License: CC0
 * Description: Makes a basis of binary vectors
 * Time: check/add -> O((B^2)/32) 
 */
template<int B>
struct XORBasis {
	bitset<B> basis[B];
	int npivot = 0, nfree = 0;
	bool check(bitset<B> v) {
		for(int i = B-1; i >= 0; i--)
			if (v[i]) v ^= basis[i];
		return v.none();
	}
	bool add(bitset<B> v) {
		for(int i = B-1; i >= 0; i--)
			if (v[i]) {
				if (basis[i].none()) return basis[i] = v, ++npivot;
				v ^= basis[i];
			}
        return !++nfree;
	}
};
