/**
 * Author: Max Bennedich
 * Date: 2004-02-08
 * Description: Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n).
 * Can easily be extended to prime moduli; for prime powers, repeatedly
 * set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

int matInv(vector<vector<double>>& A) {
	int n = SZ(A); VI col(n);
	vector<vector<double>> tmp(n, vector<double>(n));
	REP(i,0,n) tmp[i][i] = 1, col[i] = i;

	REP(i,0,n) {
		int r = i, c = i;
		REP(j,i,n) REP(k,i,n)
			if (fabs(A[j][k]) > fabs(A[r][c]))
				r = j, c = k;
		if (fabs(A[r][c]) < 1e-12) return i;
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		REP(j,0,n)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		double v = A[i][i];
		REP(j,i+1,n) {
			double f = A[j][i] / v;
			A[j][i] = 0;
			REP(k,i+1,n) A[j][k] -= f*A[i][k];
			REP(k,0,n) tmp[j][k] -= f*tmp[i][k];
		}
		REP(j,i+1,n) A[i][j] /= v;
		REP(j,0,n) tmp[i][j] /= v;
		A[i][i] = 1;
	}

	/// forget A at this point, just eliminate tmp backward
	for (int i = n-1; i > 0; --i) REP(j,0,i) {
		double v = A[j][i];
		REP(k,0,n) tmp[j][k] -= v*tmp[i][k];
	}

	REP(i,0,n) REP(j,0,n) A[col[i]][col[j]] = tmp[i][j];
	return n;
}
