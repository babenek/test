//
// Created by user on 12.03.19.
//

#include <iostream>

#define PRIME 65536

unsigned hash(char *string)
{
	if (nullptr == string)
		return static_cast<unsigned >(-1);

	unsigned result = 0;
	unsigned mask = static_cast<unsigned >(-1);

	char s;
	while ((s = *string))
	{
		result <<= 5;
		result ^= s;
		mask <<= 2;
		mask ^= s;
		++string;
	}
	//	return 0xFFFF & (result ^ (result >> 16));
	//return 0xFFFF & ((((result) % 3) << 15) | ((result) % 7) << 12 | (((result) % 31) << 7) | (((result) % 127) << 0));
	result%=65521;

	return (result);
}

int prime();

int main()
{
	//	prime();
	//	return 0;
	unsigned max = 0;
	unsigned probes = 0;
	unsigned hash_table[PRIME] = {0,};
	char s[33] = "BAzhfdn+ denj shdj, cdd dsiud.))";
	for (char k = 'a'; k <= 'z'; ++k)
	{
		s[28] = k;
		for (char n = 'A'; n <= 'Z'; ++n)
		{
			s[29] = n;
			for (char m = 'a'; m <= 'z'; ++m)
			{
				s[30] = m;
				for (char l = '5'; l <= '7'; ++l)
				{
					probes++;
					s[31] = l;
					const auto h = hash(s);
					hash_table[h]++;
					if (max < hash_table[h])
						max = hash_table[h];
					//std::cout << s << ":" << hash(s) << std::endl;
				}
			}
		}
	}
	unsigned filled = 0;
	for (unsigned n = 0; n < PRIME; ++n)
	{
		std::cout << n << ":" << hash_table[n] << std::endl;
		if (hash_table[n])
			filled++;
	}

	std::cout << "probes:" << probes << std::endl;
	std::cout << "max:" << max << std::endl;

	std::cout << filled / static_cast<double>(PRIME) << std::endl;


	return 0;

}


