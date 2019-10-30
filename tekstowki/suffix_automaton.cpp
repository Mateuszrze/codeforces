// testowane na
// https://www.spoj.com/problems/STRMATCH/
// https://open.kattis.com/problems/stringmultimatching
// https://www.spoj.com/problems/SUBLEX/
// https://pl.spoj.com/problems/KMP/
// https://www.codechef.com/problems/SUBQUERY
// http://solve.edu.pl/tasks/view/83

struct SAM
{
  struct state // mozna usunac wszystko oprocz link, len oraz next
  {
    bool terminal = 0; // whether a node is terminal
    int ter_sum = -1; // number of terminal nodes we have path to
    LL paths = -1LL; // number of paths starting at this node
    int first_pos = 0; // position of first occurence in the word (position of the last letter)
    int len; // dlugosc najdluzszgo slowa w wierzcholku
    int link; // suflinka
    map<char, int> next;
    VI rev_link; // sons in link tree
  };

  vector<state> st;
  int sz, last;

  void init()
  {
    st.clear();
    st.pb(state());
    st[0].len = 0;
    st[0].link = -1;
    st[0].first_pos = -1;
    sz = 1;
    last = 0;
  }

  int len(int a)
  {
    if(a == -1) return -1;
    return st[a].len;
  }

  void run(string s)
  {
    init();
    for(auto v : s)
      sa_extend(v);
    int cur = last;
    while(cur != 0)
    {
      st[cur].terminal = 1;
      cur = st[cur].link;
    }
    // mozna wykomentowac, jezeli jest za wolne (ale to i tak dziala w O(n))
    for(int i = 0;i < SZ(st);i++)
    {
      if(st[i].link >= 0)
        st[st[i].link].rev_link.pb(i);
      Ter_sum(i);
      Paths(i);
    }
  }

  SAM(){}
  SAM(string s)
  {
    run(s);
  }

  void sa_extend(char c)
  {
    st.pb(state());
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = st[last].first_pos + 1;
    int p = last;
    while(p != -1 && !st[p].next.count(c))
    {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if(p == -1)
    {
        st[cur].link = 0;
        last = cur;
        return;
    }
    int q = st[p].next[c];
    if(st[p].len + 1 == st[q].len)
        st[cur].link = q;
    else
    {
        int clone = sz++;
        st.pb(state());
        st[clone].len = st[p].len + 1;
        st[clone].first_pos = st[q].first_pos;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        while (p != -1 && st[p].next[c] == q)
        {
            st[p].next[c] = clone;
            p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
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
  // returns the position of a string in automaton
  int position(string s)
  {
    int cur = 0;
    for(auto v : s)
      if(!st[cur].next.count(v))
        return -1;
      else
        cur = st[cur].next[v];
    return cur;
  }

  int first_occ(string s)
  {
    int cur = position(s);
    if(cur == -1) return -1;
    return st[cur].first_pos - SZ(s) + 1;
  }

  // returns number of occurences of s in string
  int occ(string s)
  {
    int cur = position(s);
    if(cur == -1) return 0;
    return Ter_sum(cur);
  }
  // returns vector with positions where s starts to occur (1-indexed), complexity O(answer)
  VI pos_occ(string s)
  {
    int cur = position(s);
    if(cur == -1) return {};
    VI V;
    queue<int> q;
    q.push(cur);
    while(SZ(q))
    {
      int a = q.front();
      q.pop();
      V.pb(st[a].first_pos - SZ(s) + 1);
      for(auto v : st[a].rev_link)
        q.push(v);
    }
    erase_duplicates(V);
    return V;
  }

  // returns number of distinct substrings in string (without empty)
  LL distinct()
  {
    return Paths(0) - 1;
  }

};
