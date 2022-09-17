/**
 * Author: Simon Lindholm
 * Date: 2021-01-09
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Time: O(V^3)
 * Status: Stress-tested together with GomoryHu
 */
#pragma once

pair<int, VI> globalMinCut(vector<VI> mat) {
	pair<int, VI> best = {INT_MAX, {}};
	int n = SZ(mat);
	vector<VI> co(n);
	REP(i,0,n) co[i] = {i};
	REP(ph,1,n) {
		VI w = mat[0];
		size_t s = 0, t = 0;
		REP(it,0,n-ph) { // O(V^2) -> O(E log V) with prio. queue
			w[t] = INT_MIN;
			s = t, t = max_element(ALL(w)) - w.begin();
			REP(i,0,n) w[i] += mat[t][i];
		}
		best = min(best, {w[t] - mat[t][t], co[t]});
		co[s].insert(co[s].end(), ALL(co[t]));
		REP(i,0,n) mat[s][i] += mat[t][i];
		REP(i,0,n) mat[i][s] = mat[s][i];
		mat[0][t] = INT_MIN;
	}
	return best;
}
