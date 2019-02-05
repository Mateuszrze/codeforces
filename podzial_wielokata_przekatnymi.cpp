// zlozonosc O(n logn) // log z seta
// przyjmuje n - liczba wierzcholkow wielokata foremnego 
// add_edge dodaje przekatna wielokata
// PROGRAM ZAKLADA ZE PRZEKATNE SIE NIE PRZECINAJA  ( nie moga sie przecinac - wtedy nie istnieje podzial)
// funkcja rob() zwraca wektor pól kazde z pol jest opisane przez wszystkie wierzcholki danego pola (wielokata)
// kazdy wielakat skladowy ma wierzcholki podane w kolejnosci rosnacej

struct podzial
{
  int n;
  vector<set<int> > out;
  set<PII> kraw;

  podzial(int N)
  {
    n = N;
    out.resize(n + 2);
  }

  vector<vector<int> > rob()
  {
    for(int i = 1;i < n;i++)
      add(i, i + 1);
    add(n, 1);
    vector< vector<int> > pola;
    while(SZ(kraw))
    {
      PII cnt = (*kraw.begin());
      VI cur;
      cur.pb(cnt.fi);
      usun(cnt);
      while(cnt.fi < cnt.se)
      {
        cnt = gdzie(cnt);
        cur.pb(cnt.fi);
        usun(cnt);
      }
      pola.pb(cur);
    }
    return pola;
  }

  void add(int x, int y)
  {
    out[x].insert(y);
    kraw.insert({x, y});
  }

  void usun(PII cnt)
  {
    kraw.erase(cnt);
    out[cnt.fi].erase(cnt.se);
  }

  PII gdzie(PII cnt)
  {
    auto it = out[cnt.se].lower_bound(cnt.fi);
    if(it != out[cnt.se].begin())
    {
      it--;
      return {cnt.se, *it};
    }
    it = out[cnt.se].end();
    it--;
    return {cnt.se, *it};
  }
};
