/**
 * Author: tesla\_protocol
 * Date: Unknown
 * License: CC0
 * Description: Dirichlet - $H(n) = \sum_{x y = n} a_x b_y, 1 \le n \le N$
 * Status: unknown
 */

#pragma once

VI mobius(int N) {
  VI mu(N + 1, 1);
  vector<bool> ispr(N + 1, 1);
  for (int i = 2; i <= N; ++i) {
    if (!ispr[i]) continue;
    for (int j = i; j <= N; j += i) {
      ispr[j] = 0;
      mu[j] *= -1;
    }
    if (i * 1ll * i > N) continue;
    for (int j = i * i, ii = i * i; j <= N; j += ii)
      mu[j] = 0;
  }
  return mu;
}
VI DirichletConvolution(const VI &a, const VI &b, int N) {
  VI h(N + 1, 0);
  REP(i, 1, N + 1)
    for (int j = i; j <= N; j += i) h[j] += a[i] * b[j / i];
  return h;
}