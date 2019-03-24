/**
 * Author: Djok
 * Date: 2020-01-01
 * License: CC0
 * Source: My head
 * Description: None
 * Usage: ask Djok
 * Status: tested I guess
 */

bool isPrime(int x) {
  if(x < 2) return 0;
  if(x == 2) return 1;
  if(x % 2 == 0) return 0;
  for(int i = 3; i * i <= x; i += 2)
    if(x % i == 0) return 0;
  return 1;
}

int mul(int a, int b) {
  return (long long)a * b % MOD;
}

int add(int a, int b) {
  a += b;
  if(a >= MOD) return a - MOD;
  return a;
}

int getPw(int a, int b) {
  int ans = 1;
  for(; b > 0; b /= 2) {
    if(b & 1) ans = mul(ans, a);
    a = mul(a, a);
  }
  return ans;
}

long long modInv(long long a, long long m) {
  if(a == 1) return 1;
  return (1 - modInv(m % a, a) * m) / a + m;
}

long long CRT(vector<long long> &r, vector<long long> &p) {
  long long ans = r[0] % p[0], prod = p[0];
  for(int i = 1; i < r.size(); ++i) {
    long long coef = ((r[i] - (ans % p[i]) + p[i]) % p[i]) * modInv(prod % p[i], p[i]) % p[i];
    ans += coef * prod;
    prod *= p[i];
  }
  return ans;
}

long long getPhi(long long n) {
  long long ans = n - 1;
  for(int i = 2; i * i <= n; ++i) {
    if(n % i) continue;
    while(n % i == 0) n /= i;
    ans -= ans / i;
  }
  if(n > 1) ans -= ans / n;
  return ans;
}

// fact is a vector with prime divisors of N - 1 (N here is modulo) and N is prime
// the idea is that if N is prime, then N-1 is phi(N), which means the cycle has length N - 1
// now, lets try to see if X is a generator
// we know that if x ^ phi(N) == 1 then x ^ 2*phi(N) is also == 1, and here we get the idea
// if for some divisor of phi(N), x ^ div == 1, then obviously X is not a generator
// because the cycle is not of length N
// good luck to understand this after one year :)
bool isGenerator(int x, int n) {
  if(cmmdc(x, n) != 1) return 0;

  for(auto it : fact)
    if(Pow(x, (n - 1) / it, n) == 1) 
      return 0;
  return 1;
}

// Lucas Theorem
// calc COMB(N, R) if N and R is VERY VERY BIG and MOD is PRIME
r -= 2; n += m - 2;
while(r > 0 || n > 0) {
  ans = (1LL * ans * comb(n % MOD, r % MOD)) % MOD;
  n /= MOD; r /= MOD;
}

// GAUSS FOR F2 space
// SZ is the size of basis
void gauss(int mask) {
  for(int i = 0; i < n; ++i) {
    if(!(mask & (1 << i))) continue;
    if(!basis[i]) {
      basis[i] = mask;
      ++sz;
      break;
    }
    mask ^= basis[i];
  }
}

// if A is a permutation of B, then A == B mod 9

bool isSquare(int x) {
  int a = sqrt(x) + 0.5;
  return a * a == x;
}

int getDiscreteLog(int a, int b, int m) {
  if(b == 1) return 0;
  int n = sqrt(m) + 1;
  int an = 1;
  for(int i = 0; i < n; ++i) an = (an * a) % m;
  unordered_map<int, int> vals;
  for(int i = 1, cur = an; i <= n; ++i) {
    if(!vals.count(cur)) vals[cur] = i;
    cur = (cur * an) % m;
  }
  for(int i = 0, cur = b; i <= n; ++i) {
    if(vals.count(cur)) {
      int ans = vals[cur] * n - i;
      return ans;
    }
    cur = (cur * a) % m;
  }
  return -1;
}