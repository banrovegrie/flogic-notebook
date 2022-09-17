template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) a.d[i][j] += d[i][k]*m.d[k][j];
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N) ret[i] += d[i][j] * vec[j];
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};