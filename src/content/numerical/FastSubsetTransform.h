/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(VI& a, bool inv) {
	for (int n = SZ(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) REP(j,i,i+step) {
			int &u = a[j], &v = a[j + step]; tie(u, v) =
				inv ? PII(v - u, u) : PII(v, u + v); // AND
				// inv ? PII(v, u - v) : PII(u + v, u); // OR /// include-line
				// PII(u + v, u - v);                   // XOR /// include-line
		}
	}
	// if (inv) for (int& x : a) x /= SZ(a); // XOR only /// include-line
}
VI conv(VI a, VI b) {
	FST(a, 0); FST(b, 0);
	REP(i,0,SZ(a)) a[i] *= b[i];
	FST(a, 1); return a;
}
