/**
 * Author: Devansh Gautam
 * Date: Unknown 
 * License: CC0
 * Description: Supports point updates at position
 * Time: $O(n^{5/3})$ when block = $n^{2/3}$
 * Status: untested
 */
struct Query { int l, r, id, t; }
struct Update { int pos, pre, now; };
void MoWithUpdates(vector<Query> qs, vector<Update> upd) {
  int BLK; // set block size
  sort(qs.begin(), qs.end(), [&](Query a, Query b) {
    return {a.l/BLK, a.r/BLK, a.t} < {b.l/BLK, b.r/BLK, b.t};
  });
  for (auto q : qs) {
    while (t < q.t) ++t, apply(upd[t].pos, upd[t].now);
    while (t > q.t) apply(upd[t].pos, upd[t].pre), --t;
    while (l > q.l) add(--l);
    while (l < q.l) remove(l++);
    while (r < q.r) add(++r);
    while (r > q.r) remove(r--);
    ans[q.id] = get();
  }
}
