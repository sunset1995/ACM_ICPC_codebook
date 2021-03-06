#include <climits>
typedef unsigned long long int ull;

ull bases[20] = { 2ULL, 3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL };

ull fake_mul(ull n, ull m, ull x);
ull fast_pow(ull n, ull p, ull x);

bool is_prime(ull n)
{
	if (n < 2ULL) return false;

	for (int tt = 0; tt < 12; tt++) {
		ull a;
		a = bases[tt] % n;

		if (a == 0 || a == 1 || a == n - 1) {
			continue;
		}

		int t = 0;
		ull u = n - 1ULL;
		while ((u & 1ULL) == 0ULL) u >>= 1, t++;

		ull x = fast_pow(a, u, n);   // x = a ^ u % n;
		if (x == 1ULL || x == (n - 1)) continue;
		for (int i = 0; i < t - 1; i++)
		{
			if (ULLONG_MAX / x < x) {
				x = fake_mul(x, x, n);
			}
			else {
				x = x*x%n;
			}
			if (x == 1) return false;
			if (x == n - 1) break;
		}
		if (x == n - 1) continue;
		return false;
	}
	return true;
}

ull fake_mul(ull n, ull m, ull x)
{
	ull re = 0ULL;
	while (m != 0ULL) {
		if ((m & 1ULL) != 0ULL) {
			if (ULLONG_MAX - re < n) {
				ull temp = ULLONG_MAX%x;

				temp += (n - (ULLONG_MAX - re)) % x;
				re = temp%x;
			}
			else {
				re = (re + n) % x;
			}
		}

		if (ULLONG_MAX - n < n) {
			ull temp = ULLONG_MAX%x;

			temp += (n - (ULLONG_MAX - n)) % x;
			n = temp%x;
		}
		else {
			n = n + n%x;
		}

		m >>= 1;
	}
	return re;
}

ull fast_pow(ull n, ull p, ull x)
{
	ull re = 1ULL;

	while (p != 0ULL) {
		if ((p & 1ULL) != 0ULL) {
			if (ULLONG_MAX / re < n) {
				re = fake_mul(n, re, x);
			}
			else {
				re = (re*n) % x;
			}
		}

		if (ULLONG_MAX / n < n) {
			n = fake_mul(n, n, x);
		}
		else {
			n = (n*n) % x;
		}
		p >>= 1;
	}
	return re;
}

// Below is non-extreme version
ull fake_mul(ull n, ull m, ull x) {
	ull re = 0ULL;
	n %= x, m %= x;
	while( m ) {
		if( m&1ULL )
			re = (re+n) % x;
		n = (n+n) % x;
		m >>= 1;
	}
	return re;
}
ull fast_pow(ull n, ull p, ull x) {
	ull re = 1ULL;
	while( p ) {
		if( p&1ULL )
			re = fake_mul(re,n,x);
		n = fake_mul(n,n,x);
		p >>= 1;
	}
	return re;
}
bool is_prime(ull n) {
	static const int bNum = 12;
	static const ull bases[bNum] = {
		2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL
	};
	if( n<=2ULL ) return n==2ULL;
	if( !(n&1ULL) ) return false;

	ull u = n-1;
	while( !(u&1ULL) )
		u >>= 1;
	for(int i=0; i<bNum; i++) {
		if( bases[i]%n == 0 ) continue;
		ull t = u;
		ull a = fast_pow(bases[i], t, n);
		if( a==1 || a==n-1 ) continue;
		while( t!=n-1 && a!=1 && a!=n-1 ) {
			a = fake_mul(a,a,n);
			t <<= 1;
		}
		if( t==n-1 && a==1 ) continue;
		if( a!=n-1 ) return false;
	}
	return true;
}
