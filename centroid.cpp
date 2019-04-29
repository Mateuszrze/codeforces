// testowane na https://codeforces.com/contest/715/problem/C

VPII wek[maxn];
int r[maxn];
int syn[maxn];
VI tmp;
bool zaz[maxn];

void dfs(int x, int f = -1)
{
  tmp.pb(x);
  r[x] = 1;
  syn[x] = 0;
  for(auto s : wek[x])
    if(s.fi != f && zaz[s.fi] == 0)
    {
      dfs(s.fi, x);
      r[x] += r[s.fi];
      syn[x] = max(syn[x], r[s.fi]);
    }
}

int centro(int x)
{
  tmp.clear();
  dfs(x);
  for(auto s : tmp)
    if(syn[s] * 2 <= r[x] && (r[x] - r[s]) * 2 <= r[x])
      return s;
  assert(0);
}

// tutaj liczymy wynik z tego co dodalismy
void licz(int x, int f = -1)
{
  for(auto s : wek[x])
    if(s.fi != f && zaz[s.fi] == 0)
    {
      licz(s.fi, x);
    }
}

// tutaj dodajemy sciezki do mozliwych do policzenia pozniej
void dodaj(int x, int f = -1)
{
  for(auto s : wek[x])
    if(s.fi != f && zaz[s.fi] == 0)
    {
      dodaj(s.fi, x);
    }
}

void rozbij(int x)
{
  x = centro(x);
  zaz[x] = 1;
  // wypada doliczyc x
// DOLICZ X 
  for(auto s : wek[x])
    if(zaz[s.fi] == 0)
    {
      licz(s.fi);
      dodaj(s.fi);
    }
  reverse(all(wek[x]));
  for(auto s : wek[x])
    if(zaz[s.fi] == 0)
    {
      licz(s.fi);
      dodaj(s.fi);
    }
  for(auto s : wek[x])
    if(zaz[s.fi] == 0)
      rozbij(s.fi);
}
