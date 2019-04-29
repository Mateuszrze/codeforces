//testowane na https://codeforces.com/contest/914/problem/F

/*
 * Autor programu: Marek Cygan
 * data:           17.03.2005
 * Program ilustrujacy liczenie tablicy PREF.
 * Wartoscia PREF[i] jest dlugosc najdluzszego
 * prefiksu calego slowa, ktory wystepuje w slowie
 * rozpoczynajac od i-tej litery
 */

struct PREF
{
  vector<int> PREF; // tutaj znajduje sie wynik
  int n; //dlugosc slowa
  string X; //slowo, dla ktorego bedziemy obliczac wartosci tablicy PREF
  //funkcja ta zwraca dlugosc najdluzszego
  //prefiksu slowa X, zaczynajacego sie na
  //pozycji j, zakladajac ze przed pozycja k
  //prefiks jest zgodny
  int pref(int j,int k)
  {
    k=max(k,j);
    int i=k-j;
    while (k<=n && X[i]==X[k-1]) { i++;  k++; }
    return k-j;
  }

  //procedura obliczaja kolejne wartosci tablicy PREF
  //w czasie liniowym
  void run(string s)
  {
    X = s;
    n = SZ(X);
    int i=1;
    PREF.resize(n + 3, 0);
    PREF[1]=-1;
    for (int j=2; j<=n; ++j)
    { int l=j-i+1;
      if (l<=PREF[i] && j+PREF[l]<i+PREF[i])
        PREF[j]=PREF[l];
      else
       { PREF[j]=pref(j,i+PREF[i]);
         i=j;
       }
    }
  }
};
