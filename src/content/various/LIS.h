/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Time: $O(N \log N)$
 * Status: Tested on kattis:longincsubseq, stress-tested
 */
#pragma once

template<class I> VI lis(const vector<I>& S) {
	if (S.empty()) return {};
	VI prev(SZ(S));
	typedef pair<I, int> p;
	vector<p> res;
	REP(i,0,SZ(S)) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(ALL(res), p{S[i], 0});
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = it == res.begin() ? 0 : (it-1)->second;
	}
	int L = SZ(res), cur = res.back().second;
	VI ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
