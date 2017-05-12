#include <cstdio>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cassert>


//------------------------------------------------------------------------------
namespace base91
{
static const unsigned base=91;
static const unsigned char_bits=8;
static const unsigned digit_bits=13;
static const unsigned digit_size=0x2000;
static const unsigned digit_mask=0x1FFF;

void encode(const std::vector<unsigned char> & in,std::string & out)
{
	out.clear();
	out.reserve(digit_bits*in.size()/char_bits+2);
	unsigned acc=0;
	int bitacc=0;

	for (auto & n:in)
	{
		acc <<= char_bits;
		acc |= n;
		bitacc+=char_bits;
		while(digit_bits>=bitacc)
		{
			const unsigned cod = digit_mask & acc;
			out.push_back(lo[cod]);
			out.push_back(hi[cod]);
			acc>>=digit_bits;
			bitacc-=digit_bits;
		}
	}

	while(0 < bitacc)
	{
		const unsigned cod = digit_mask & acc;
		out.push_back(lo[cod]);
		out.push_back(hi[cod]);
		acc>>=digit_bits;
		bitacc-=digit_bits;
	}
	
	
	return;
}
void decode(const std::string & in,std::vector<unsigned char> & out)
{
	return;
}
}
//------------------------------------------------------------------------------

int main()
{
	std::vector<unsigned char> in{0,0,0,0,0,0,0,0,0};
	std::string out;
	base91::encode(in,out);
	std::cout<<out<<std::endl;
	
	return 0;
}

//------------------------------------------------------------------------------

