/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Usage:
 * 	vector<P> p = ...;
 * 	p = polygonCut(p, P(0,0), P(1,0));
 * Status: tested but not extensively
 */
#pragma once

#include "Point.h"
#include "lineIntersection.h"

typedef Point<double> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
	if (SZ(poly) <= 2) return {};
	vector<P> res;
	REP(i,0,SZ(poly)) {
		P cur = poly[i], prev = i ? poly[i-1] : poly.back();
		if (zero(s.cross(e, cur))) {
			res.push_back(cur);
			continue;
		}
		bool side = s.cross(e, cur) < 0;
		if (side != (s.cross(e, prev) < 0))
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side)
			res.push_back(cur);
	}
	return res;
}
