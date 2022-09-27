/**
 * Author: Amul Agrawal
 * Description: Representing each number in 2D vector space,
 * finding basis of that vector space. total elements = $2^{sz}$. 
 * ways to represent $x$ is $2^{n-sz}$, unique basis combination for every subset.
 * Time: O(N*log(A[i]))
 */
#pragma once
int basis[d], sz; // basis[i] keeps the mask of the vector whose f value is i
void insertVector(int mask) {
	for (int i = 0; i < d; i++) {
		if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)
		if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
			basis[i] = mask; ++sz; return;
		}
		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}