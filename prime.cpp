//
// Created by user on 10.05.19.
//

#include <iostream>

typedef unsigned long long ULL;

const ULL MAX_NUMBER = 1ull << 33;

const ULL MAX_DB = MAX_NUMBER>>7;// except 2  and  all odd  numbers

inline void
clean(ULL primes[])
{
	for (unsigned n = 0; n < MAX_DB; ++n)
		primes[n] = 0;
}

inline bool
prime(ULL number, ULL *primes)
{
	return (not(primes[number >> 7] & (1ull << (0x3F & (number >> 1)))));
}

inline void
set(ULL number, ULL primes[])
{
	primes[number >> 7] |= (1ull << (0x3F & (number >> 1)));
}

void
eratosfen(ULL primes[])
{
	clean(primes);

	for (ULL n = 3; n < MAX_NUMBER; n += 2)
	{
		if (not prime(n, primes))
			continue;
		const ULL d = n << 1;
		for (ULL m = n + d; m < (1ull << 32); m += d)
			set(m, primes);

	}
}

int
main()
{
	// 2^32 / 2^6 = 2^26
	ULL *primes = new ULL[MAX_DB];

	eratosfen(primes);
	ULL s = 1; // 2 - is the prime
	ULL mask = ~(s - 1);
	for (ULL n = 3; n < MAX_NUMBER; n += 2)
	{
		if (0 != (n & mask) and prime(n, primes))
		{
			for (ULL m = n - 2; m > 3; m -= 2)
			{
				if (prime(m, primes))
				{
					std::cout << std::showbase << std::hex << m << std::endl;
					break;
				}
			}
			s <<= 1;
			mask = ~(s - 1);
		}
	}

	delete[]primes;
	return 0;
}