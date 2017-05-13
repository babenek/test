#include <cstdio>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <iostream>

#define TRACE(a) std::cout<<__LINE__<<"# "<<a<<std::endl;
//------------------------------------------------------------------------------
inline char getDigit(const unsigned n)
{
	switch(n)
	{
		case 0:
			return '!';
		break;
		case 35:
			return '#';
		break;
		case 80:
			return '$';
		break;
		default:
			return 0x7F^n;
		break;
	}
}

//------------------------------------------------------------------------------
int main()
{
	for(unsigned n=0;n<91;++n)
	{
		std::cout<<",DUP91('"<<getDigit(n)<<"')";
	}
	return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------

