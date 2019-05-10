//
// Created by user on 12.03.19.
//

#include <iostream>

unsigned hash(char *string)
{
	if (nullptr == string)
		return static_cast<unsigned >(-1);

	unsigned result = 0;

	while (true)
	{
		const char s = *string;
		if ('\0' == s)
			break;
		result <<= 5;
		result ^= s;
		string++;
	};

	return 0x1FFFF &( result % 65537);
}


int main()
{
	unsigned hash_table[65537] = {0,};
	char s[5] = {0,};
	for (char k = '0'; k < '3'; ++k)
	{
		s[0] = k;
		for (char n = 'A'; n <= 'Z'; ++n)
		{
			s[1] = n;
			for (char m = 'A'; m <= 'Z'; ++m)
			{
				s[2] = m;
				for (char l = 'A'; l <= 'Z'; ++l)
				{

					s[3] = l;
					hash_table[hash(s)]++;
					std::cout << s << ":" << hash(s) << std::endl;
				}
			}
		}
	}


	unsigned filled = 0;
	for (unsigned n = 0; n < 65537; ++n)
	{
		std::cout << n << ":" << hash_table[n] << std::endl;
		if (hash_table[n])
			filled++;
	}
	std::cout << filled / 65537.0 << std::endl;


	return 0;

}


