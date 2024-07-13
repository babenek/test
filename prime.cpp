
#include <iostream>
#include <string>
#include <stdint.h>

uint8_t *db;
/*
 * 0 - not prime
 * 1 - prime or not checked
 */

const uint64_t maxNumber = 0xFFFFFFFF;
//const uint64_t maxNumber = 1000; // 168 numbers up to 1000
//const uint64_t maxNumber = 7919; // 1000 numbers up to 7919
//const uint64_t maxNumber = 104729; // 10000 numbers up to 104729
//const uint64_t maxNumber = 1000000;

//const uint32_t bitCount = 2 << 28;
const uint32_t bitCount = (maxNumber >> 4) + ((maxNumber % 16) ? 1 : 0);

inline uint32_t index(const uint32_t n)
{
	return (n >> 4);
}
inline uint8_t mask(const uint32_t n)
{
	return (1 << ((0xF & n) >> 1));
}

inline bool check(const uint64_t n)
{
	return (mask(n) & db[index(n)]);
}

int main()
{
	unsigned c = 1;
	std::cout << "2" << "\n"; // the first prime number!

	db = new uint8_t[bitCount];
	for (uint32_t n = 0; n < bitCount; n++)
	{
		db[n] = 0xFF;
	}

	for (uint64_t n = 3; n <= maxNumber; n += 2)
	{
		if (check(n))
		{
			c++;
			//if (0 == (c % 1000000))
			std::cout << n  << "\n";
			// it is prime. do all mux

			uint64_t MMax = maxNumber / n;
			if (not (MMax & 0x1))
				MMax--;

			for (uint64_t m = MMax; m >= n; m -= 2)
			{
				if (check(m))
				{
					const uint64_t q = m * n;
					const uint32_t im = index(q);
					const uint8_t bm = mask(q);
					db[im] &= (0xFF ^ bm);
				}
			}
		}
	}

	//std::cout << std::endl << c << " done!" << std::endl;

	delete[] db;
}

