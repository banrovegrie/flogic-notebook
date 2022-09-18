/**
 * Author: Anurudh Peduri
 * Date: 2020-01-13
 * License: CC0
 * Description: Add lines $y = ax + b$ and query for min at given $x$
 * Time: $O(log n)$ per update/query.
 */
const dbl INF = 1e16;
struct HullDynamic {
#define CLREF const Line&
  struct Line {
    int a; ll b, val=0; dbl xLeft = -INF; bool type=0;
    Line(int a = 0, ll b = 0): a(a), b(b) {}
    ll eval(int x) const{ return a * 1ll * x + b; }
    bool operator< (CLREF l2) const {
      return l2.type ? (xLeft > l2.val) : (a < l2.a);
    }
  };
  using Iter = set<Line>::iterator;
  bool parallel(CLREF l1, CLREF l2) { return l1.a == l2.a; }
  dbl meetX(CLREF l1, CLREF l2) {
    return parallel(l1, l2) ? INF :
      (l2.b-l1.b) / (dbl(l1.a-l2.a));
  }
  set<Line> hull;
  bool hasPrev(Iter it) { return it != hull.begin(); }
  bool hasNext(Iter it) {
    return it != hull.end() && next(it) != hull.end(); 
  }
  bool bad(CLREF l1, CLREF l2, CLREF l3){
    return meetX(l1,l3) <= meetX(l1,l2);
  }
  bool bad(Iter it) {
    return hasPrev(it) && hasNext(it)
        && (bad(*next(it), *it, *prev(it)));
  }
  Iter upd_left_border(Iter it) {
    if(!hasNext(it)) return it;
    dbl val = meetX(*it, *next(it));
    Line buf(*it); it = hull.erase(it);
    buf.xLeft = val; return hull.insert(it, buf);
  }
  void insert_line(int a, ll b) {
    Line l3 = Line(a, b); auto it = hull.lower_bound(l3);
    if (it != hull.end() && parallel(*it , l3)) {
      if (it->b <= b) return;
      it = hull.erase(it);
    }
    it = hull.insert(it, l3);
    if (bad(it)) { hull.erase(it); return; }
    while (hasPrev(it) && bad(prev(it))) hull.erase(prev(it));
    while (hasNext(it) && bad(next(it))) hull.erase(next(it));
    it = upd_left_border(it);
    if (hasPrev(it)) upd_left_border(prev(it));
    if (hasNext(it)) upd_left_border(next(it));
  } 
  ll eval(int x) {
    Line q; q.val = x; q.type = 1;
    auto best = hull.lower_bound(q);
    return (best == hull.end()) ? INF : best->eval(x);
  }
};
