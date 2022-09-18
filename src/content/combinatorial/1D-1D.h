/**
 * Author: Arjun P
 * Date: 2019-12-19
 * License: CC0
 * Description: Applicable if $dp_i = min_{j>i}(dp_j + cost(i,j)$ s.t. $opt_i \le opt_j$ when $i \le j$ (which holds if quadrangle) 
 * Time: $O(n \log n)$
 */
#define until first
#define opt second
ll dp[100000];
ll cost(int i, int j) {
  return dp[j] /* + cost to jump from i to j*/;
}
void solve(int n) {
  dp[n] = 0;
  vector<PII> v;
  v.EB(n - 1, n);
  for (int i = n - 1, ipos = 0; i >= 1; i--) {
    while (ipos+1 < SZ(v) && i <= v[ipos+1].until) ipos++;
    dp[i] = cost(i, v[ipos].opt);
    while (v.back().until < i
      && cost(v.back().until, i)
         <= cost(v.back().until, v.back().opt))
      { v.pop_back(); }
    int l = 1, r = min(i - 1, v.back().until);
    while (l <= r) {
      int mid = (l + r)/2;
      if (cost(mid, i) <= cost(mid, v.back().opt)) {
        l = mid + 1;
      } else { r = mid - 1; }
    }
    if (l - 1 >= 1) v.EB(l - 1, i);
  }
}
