/**
 * Author: quasisphere
 * Source: https://codeforces.com/blog/entry/20861
 * Date: Unknown
 * Description: Each path in the automaton is a substring (if it ends in a terminal node, it is a suffix) And no. of occurences = no. of ways to reach a terminal node. Or keep reverse edges of suffix links(all prefixes for that substring), then no. of ways to reach a root.
 * Time: $O(len)$ map accesses, map can be at most of size alphabet, can also use unordered\_map
 * Status: untested
 */
#pragma once

struct SuffixAutomaton {
  vector<map<char, int>> edges;
  VI link, length; // length[i]: longest string in i-th class
  int last;        // index of equivalence class of whole string
  SuffixAutomaton(string s) : edges{}, link{-1}, length{0}, last(0) {
    edges.emplace_back();
    REP(i, 0, SZ(s)) {
      edges.emplace_back();
      length.push_back(i + 1);
      link.push_back(0);
      int r = SZ(edges) - 1, p = last;
      while (p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
        edges[p][s[i]] = r, p = link[p];
      }
      if (p != -1) {
        const int q = edges[p][s[i]];
        if (length[p] + 1 == length[q]) link[r] = q;
        else {
          edges.push_back(edges[q]);
          length.push_back(length[p] + 1);
          link.push_back(link[q]);
          const int qq = SZ(edges) - 1;
          link[q] = link[r] = qq;
          for (; p >= 0 && edges[p][s[i]] == q; p = link[p])
            edges[p][s[i]] = qq;
        }
      }
      last = r;
    }
    VI terminals;
    for (int p = last; p > 0; p = link[p])
      terminals.push_back(p);
  }
};
