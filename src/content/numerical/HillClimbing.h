/**
 * Author: Simon Lindholm
 * Date: 2015-02-04
 * License: CC0
 * Source: Johan Sannemo
 * Description: Poor man's optimization for unimodal functions.
 * Status: used with great success
 */
#pragma once

typedef array<double, 2> P;

template<class F> pair<double, P> hillClimb(P start, F f) {
	pair<double, P> cur(f(start), start);
	for (double jmp = 1e9; jmp > 1e-20; jmp /= 2) {
		REP(j,0,100) REP(dx,-1,2) REP(dy,-1,2) {
			P p = cur.second;
			p[0] += dx*jmp;
			p[1] += dy*jmp;
			cur = min(cur, make_pair(f(p), p));
		}
	}
	return cur;
}
