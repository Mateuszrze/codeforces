// zmienne sa od 1 do n, negacja to + n
// rob() zwraca 0 jak nie ma rozwiazania oraz 1 gdy jest rozwiazanie
// po uruchomieniu rob() w wektorze val beda wartosci -1 i 1 oznaczajace wartosci logiczne zmiennych
// ludzie[i] to wierzcholki znajdujace sie w i-tej spojnej skladowej
// skl[i] to numer skladowej w ktorej jest wierzcholek numer i
// cofnij() cofa ostatnio dodana klauzule
// mozna puszczac ile razy sie chce (tzn. puscic, potem dodac/usunac pare kawedzi i potem znowu puscic)
// init(int N) inicjalizuje, 1, 2, ... n to zmienne, n + 1, n + 2, ... 2n to ich negacje
struct dwasat
{
  int n;
  vector<vector<int> > wek, odw, ludzie;
  vector<int> para, vis, val;
  vector<int> V, skl;
  vector<int> st;
  int num = 0;
  VPII ost;

  void init(int N)
  {
    n = N;
    wek.resize(2 * n + 4);
    ludzie.resize(2 * n + 4);
    odw.resize(2 * n + 4);
    para.resize(2 * n + 4);
    vis.resize(2 * n + 4, 0);
    val.resize(2 * n + 4, 0);
    skl.resize(2 * n + 4, 0);
    st.resize(2 * n + 4, 0);
    for(int i = 1;i <= n;i++)
    {
      para[i] = i + n;
      para[i + n] = i;
    }
  }

  void cofnij()
  {
    wek[ost.back().fi].pop_back();
    wek[ost.back().se].pop_back();
    odw[para[ost.back().fi]].pop_back();
    odw[para[ost.back().se]].pop_back();
    ost.pop_back();
  }

  void dodaj(int a, int b) // dodajesz a lub b
  {
    wek[para[a]].pb(b);
    wek[para[b]].pb(a);
    odw[b].pb(para[a]);
    odw[a].pb(para[b]);
    ost.pb({para[a], para[b]});
  }

  void dfs(int x)
  {
    vis[x] = 1;
    for(auto s : wek[x])
      if(vis[s] == 0)
        dfs(s);
    V.pb(x);
  }

  void rek(int x)
  {
    vis[x] = 1;
    skl[x] = num;
    ludzie[num].pb(x);
    for(auto s : odw[x])
      if(vis[s] == 0)
        rek(s);
  }

  bool rob()
  {
    num = 0;
    V.clear();
    for(int i = 0;i <= 2 * n + 3;i++)
    {
      ludzie[i].clear();
      vis[i] = st[i] = skl[i] = val[i] = 0;
    }
    for(int i = 1;i <= 2 * n;i++)
      if(vis[i] == 0)
        dfs(i);
    reverse(all(V));
    for(int i = 0; i <= 2 * n + 3;i++)
      vis[i] = 0;
    for(auto s : V)
      if(vis[s] == 0)
      {
        num++;
        rek(s);
      }
    for(int i = 1;i <= n;i++)
      if(skl[i] == skl[i + n])
        return 0;
    for(int i = 1;i <= 2 * n;i++)
      for(auto s : wek[i])
        if(skl[i] != skl[s])
          st[skl[s]]++;
    queue<int> q;
    for(int i = 1;i <= num;i++)
      if(st[i] == 0)
        q.push(i);

    while(SZ(q))
    {
      int a = q.front();
      q.pop();
      int cnt = -1;
      for(auto s : ludzie[a])
        if(val[s] != 0)
          cnt = val[s];
      for(auto s : ludzie[a])
      {
        val[s] = cnt;
        val[para[s]] = cnt * (-1);
      }
      for(auto s : ludzie[a])
        for(auto v : wek[s])
          if(skl[s] != skl[v])
          {
            st[skl[v]]--;
            if(st[skl[v]] == 0)
              q.push(skl[v]);
          }
    }
    return 1;
  }
};
