bool isPrime[VMAX];
vector<int> primes;

void linearSieve(int n) {
	for(int i = 2; i <= n; ++i) isPrime[i] = true;
	for(int i = 2; i <= n; ++i) {
		if(isPrime[i]) primes.push_back(i);
		for(auto p : primes) {
			if(i * p > n) break;
			isPrime[p * i] = false;
			if(i % p == 0) break;
		}
	}
}
