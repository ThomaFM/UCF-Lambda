#include "../utilities/template.h"

#include "../../content/data-structures/Xorbasis.h"

mt19937 rng;

struct XORBasisChatGPT {
    static const int MAXLOG = 64; // for 64-bit integers
    std::vector<long long> basis;
    
    XORBasisChatGPT() : basis(MAXLOG, 0) {}
    
    bool insert(long long x) {
        for (int i = MAXLOG - 1; i >= 0; i--) {
            if (!(x & (1LL << i))) continue;
            
            if (!basis[i]) {
                basis[i] = x;
                return true;
            }
            
            x ^= basis[i];
        }
        return false;
    }
    
    bool canForm(long long x) {
        for (int i = MAXLOG - 1; i >= 0; i--) {
            if (!(x & (1LL << i))) continue;
            
            if (!basis[i]) return false;
            x ^= basis[i];
        }
        return x == 0;
    }
    
};

int main() {
	int numOnes = 0, numZeros = 0;
	ll inBasis[1000];
	ll inBasisLen = 0;
	for (int iter = 0; iter < 1e4; ++iter) {
		inBasisLen = 0;
		XORBasis<64> basis;
		XORBasisChatGPT basisChatGPT;
		for (int q = 0; q < 500; ++q) {
			ll v = uniform_int_distribution<ll>(LLONG_MIN, LLONG_MAX)(rng);
			if (rng() % 8 != 0) {
				basis.add(v);
				basisChatGPT.insert(v);
				inBasis[inBasisLen++] = v;
			}
			else {
				(basis.check(v) ? numOnes : numZeros)++;
				if (basis.check(v) != basisChatGPT.canForm(v)) {
					cout << "Disagreement on " << v << "\n";
					cout << "Hackpack says " << basis.check(v) << "; ChatGPT says "
						<< basisChatGPT.canForm(v) << "\n";
					cout << "Basis contents:\n";
					for (ll i = 0; i < inBasisLen; ++i) cout << inBasis[i] << " ";
					cout << endl;
					assert(0);
				}
			}
		}
	}

	assert(numOnes >= 0.1 * (numOnes + numZeros));
	assert(numZeros >= 0.1 * (numOnes + numZeros));

	return 0;
}
