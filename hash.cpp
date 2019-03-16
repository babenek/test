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

	return result%21111;
}


int main_hash()
{
	unsigned hash_table[21112]={0,};
	char s[4]={0,};
	for (char n = 'A'; n <= 'Z'; ++n)
	{
		s[0]=n;
		for (char m = 'A'; m <= 'Z'; ++m)
		{
			s[1] = m;
			for (char l = 'A'; l <= 'Z'; ++l)
			{

				s[2] = l;
				hash_table[hash(s)]++;
				//			std::cout << n<<m << ":" << hash(s) << std::endl;
			}
		}
	}

	unsigned filled=0;
	for (unsigned n = 0;n<21112;++n)
	{
		std::cout << n<<":"<<hash_table[n] << std::endl;
		if(hash_table[n])
			filled++;
	}
	std::cout << filled/21112.0 << std::endl;


	return hash(0);

}


