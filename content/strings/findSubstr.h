/**
 * Author: Luke Videckis
 * Date: 2025-10-02
 * Description: returns inc-exclusive range of occurences of needle string
 * inside suffix array, assumes global sa structure and global s (haystack)
 * Time: $O(|ndl|log(|s|))$
 * Status: Works but not stress-tested
 */
pair<int,int> find_str(const string &ndl){
	auto le = lower_bound(begin(sa.sa)+1,end(sa.sa), 0, 
	[&](int i, int) -> bool { return lexicographical_compare
		(begin(s) + i, end(s), all(ndl)); });
	auto ri = lower_bound(le, end(sa.sa), 0, 
	[&](int i, int) -> bool { return mismatch(begin(s) + i, 
		end(s), all(ndl)).second == end(ndl);});
	return {le-begin(sa.sa),ri-begin(sa.sa)}; //[)
}
