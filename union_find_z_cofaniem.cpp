// testowane na jednym zadaniu https://codeforces.com/contest/891/problem/C
// find w O(log n)
// union w O(log n)
// zlozonosc dzieki robieniu mniejszy do wiekszego (nie ma kompresji sciezek)

int F[maxn];
int roz[maxn];
vector<pair<int, int > > wektor;

int fin(int x)
{
  if(F[x] != x)
    return fin(F[x]);
  return F[x];
}

void uni(int a, int b)
{
  a = fin(a);
  b = fin(b);
  if(roz[a] > roz[b])
    swap(a, b);
  if(a != b)
  {
    wektor.pb({a, b});
    roz[b] += roz[a];
    F[a] = b;
  }
  else
    wektor.pb({-1, -1});
}

//cofa ostatnio wykonanego uniona
void cofnij()
{
  auto xd = wektor.back();
  wektor.pop_back();
  if(xd.fi == -1)
    return;
  F[xd.fi] = xd.fi;
  roz[xd.se] -= roz[xd.fi];
}
// tego nie trzeba, ale trzeba pamietac, ze trzeba jakos zainicjalizowac union finda
void init(int n)
{ 
  for(int i = 0;i <= n;i++)
  {
    F[i] = i;
    roz[i] = 1;
  }
  wektor.clear();
}
