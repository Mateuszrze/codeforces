
// testowane na https://www.spoj.com/problems/SUBLEX/
// https://pl.spoj.com/problems/KMP/
// http://solve.edu.pl/tasks/view/83
// pos_occ nie jestem pewien zlozonosci mozliwe ze zadziala w O(dlugosc slowa)


struct Suffix_Automaton
{
  struct state
  {
    bool terminal = 0; // whether a node is terminal
    int ter_sum = -1; // number of terminal nodes we have path to
    LL paths = -1LL; // number of paths starting at this node
    int len, link;
    map<char, int> next;
  };

  vector<state> st;
  int sz, last;

  void init()
  {
    st.pb(state());
    st[0].len = 0;
    st[0].link = -1;
    sz = 1;
    last = 0;
  }

  Suffix_Automaton()
  {
    init();
  }

  void sa_extend(char c)
  {
    while(last + 2 >= SZ(st))
      st.pb(state());
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
  }
  // number of different paths reachable from cur
  LL Paths(int cur)
  {
    if(st[cur].paths == -1LL)
    {
      st[cur].paths = 1LL;
      for(auto s : st[cur].next)
        st[cur].paths += Paths(s.se);
    }
    return st[cur].paths;
  }
  // number of reachable terminal nodes from cur
  int Ter_sum(int cur)
  {
    if(st[cur].ter_sum == -1LL)
    {
      st[cur].ter_sum = st[cur].terminal;
      for(auto s : st[cur].next)
        st[cur].ter_sum += Ter_sum(s.se);
    }
    return st[cur].ter_sum;
  }
  //returns kth lexicographical substrings of string
  string kth(LL k)
  {
    k++;
    int cur = 0;
    string res;
    while(1)
    {
      k--;
      if(k == 0)
        return res;
      for(auto s : st[cur].next)
      {
        if(Paths(s.se) >= k)
        {
          res.pb(s.fi);
          cur = s.se;
          break;
        }
        else
          k -= Paths(s.se);
      }
    }
  }

  void run(string s)
  {
    clear();
    st.resize(SZ(s) * 2 + 1);
    for(auto v : s)
      sa_extend(v);
    int cur = last;
    while(cur != 0)
    {
      st[cur].terminal = 1;
      cur = st[cur].link;
    }
  }
  // returns number of occurences of s in string
  int occ(string s)
  {
    int cur = 0;
    for(auto v : s)
      if(!st[cur].next.count(v))
        return 0;
      else
        cur = st[cur].next[v];
    return Ter_sum(cur);
  }
  // returns vector with positions where s starts to occur (1-indexed)
  VI pos_occ(string s)
  {
    int cur = 0;
    for(auto v : s)
      if(!st[cur].next.count(v))
        return {};
      else
        cur = st[cur].next[v];
    VI V;
    queue<PII> q;
    q.push({cur, SZ(s)});
    while(SZ(q))
    {
      PII a = q.front();
      q.pop();
      if(st[a.fi].terminal)
        V.pb(st[last].len - a.se);
      for(auto v : st[a.fi].next)
        if(Ter_sum(v.se) > 0)
          q.push({v.se, a.se + 1});
    }
    reverse(all(V));
    assert(SZ(V) == occ(s));
    return V;
  }

  // returns number of distinct substrings in string (without empty)
  LL distinct()
  {
    return Paths(0) - 1;
  }

  void clear()
  {
    st.clear();
    init();
  }

};
