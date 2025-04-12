/**
 * Source: cp-algo
 * Description: A string is called simple (or a Lyndon word), if it is strictly smaller 
 * than any of its own nontrivial suffixes. Examples of simple strings are:  $a$, $b$, $ab$, $aab$ , $abb$ , $ababb$ , $abcd$ .
 * It can be shown that a string is simple, if and only if it is strictly smaller than all its nontrivial cyclic shifts.
 * Next, let there be a given string  $s$ . The Lyndon factorization of the string $s$  is a factorization 
 * $s = w_1 w_2 \dots w_k$ , where all strings
 * $w_i$  are simple, and they are in non-increasing order 
 * $w_1 \ge w_2 \ge \dots \ge w_k$ .
 * It can be shown, that for any string such a factorization exists and that it is unique.
 * 
 * Time: O(N)
 * Status: Stress-tested
 */
vector<string> duval(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}