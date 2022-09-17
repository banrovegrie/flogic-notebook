/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "LCA.h"

typedef vector<pair<int, int>> vpi;
vpi compressTree(LCA& lca, const VI& subset) {
	static VI rev; rev.resize(SZ(lca.time));
	VI li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(ALL(li), cmp);
	int m = SZ(li)-1;
	REP(i,0,m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.lca(a, b));
	}
	sort(ALL(li), cmp);
	li.erase(unique(ALL(li)), li.end());
	REP(i,0,SZ(li)) rev[li[i]] = i;
	vpi ret = {PII(0, li[0])};
	REP(i,0,SZ(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.lca(a, b)], b);
	}
	return ret;
}
