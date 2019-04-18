const int mod = 1e9 + 7;
const LL inv2 = (mod + 1) / 2LL;
// f = 0 jak chcemy wyliczyc pierwiastki
// f = -1 jak chcemy cofnac wyliczanie pierwiastkow

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
