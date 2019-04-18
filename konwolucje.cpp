
const LL inv2 = (mod + 1) / 2LL;
// testowane na zadaniu https://codeforces.com/contest/914/problem/G
// f = 1 jak chcemy wyliczyc wartosci w punktach
// f = -1 jak chcemy cofnac wyliczanie w punktach
// mozna uzywac fwt_* (co, co2, gdzie bedzie wynik, dlugosc) dziala, gdy co lub co2
// co i co2 zostaje odwrocone (w postaci wartosci w punktach) - jest tak zeby bylo szybciej
// funkcje fwt_* nie dziaja gdy dostana te sama tablie (pierwsze przejscie zrobi sie dwa razy)

inline void FWT_or(int *a, int n, int f) {
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += (len << 1)) {
            for(int j = 0; j < len; j++) {
                a[i + len + j] = ((a[i + len + j] + f * a[i + j]) % mod + mod) % mod;
            }
        }
    }
    return;
}

inline void FWT_and(int *a, int n, int f) {
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += (len << 1)) {
            for(int j = 0; j < len; j++) {
                a[i + j] = ((a[i + j] + f * a[i + len + j]) % mod + mod) % mod;
            }
        }
    }
    return;
}

inline void FWT_xor(int *a, int n, int f) {
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += (len << 1)) {
            for(int j = 0; j < len; j++) {
                int t = a[i + len + j];
                a[i + len + j] = (a[i + j] - t + mod) % mod;
                a[i + j] = (a[i + j] + t) % mod;
                if(f == -1) {
                    a[i + len + j] = 1ll * a[i + len + j] * inv2 % mod;
                    a[i + j] = 1ll * a[i + j] * inv2 % mod;
                }
            }
        }
    }
    return;
}

void fwt_xor(int *a, int *b, int * c, int n)
{
  FWT_xor(a, n, 1);
  FWT_xor(b, n, 1);
  for(int i = 0; i < n;i++)
    c[i] = a[i] * (LL) b[i] % mod;
  FWT_xor(c, n, -1);
}

void fwt_and(int *a, int *b, int * c, int n)
{
  FWT_and(a, n, 1);
  FWT_and(b, n, 1);
  for(int i = 0; i < n;i++)
    c[i] = a[i] * (LL) b[i] % mod;
  FWT_and(c, n, -1);
}

void fwt_or(int *a, int *b, int * c, int n)
{
  FWT_or(a, n, 1);
  FWT_or(b, n, 1);
  for(int i = 0; i < n;i++)
    c[i] = a[i] * (LL) b[i] % mod;
  FWT_or(c, n, -1);
}
