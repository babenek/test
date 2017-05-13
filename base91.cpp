#include <cstdio>
#include <random>
#include <cmath>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <iostream>

#define TRACE(a) std::cout<<a<<std::endl;
//------------------------------------------------------------------------------
namespace base91
{
static const unsigned base=91;
static const unsigned char_bits=8;
static const unsigned digit_bits=13;
static const unsigned digit_size=0x2000;
static const unsigned digit_mask=0x1FFF;

char hi[digit_size]={'~',};
char lo[digit_size]={'~',};

unsigned short hilo[base][base]={0,};

//------------------------------------------------------------------------------

void encode(const std::vector<unsigned char> & in,std::string & out)
{
	out.clear();
	out.reserve(digit_bits*in.size()/char_bits+2);
	unsigned acc=0;
	unsigned bitacc=0;

	for (auto & n:in)
	{
		acc |= n<<bitacc;
		bitacc+=char_bits;
TRACE("added "<<static_cast<short>(n)<<" : "<<acc<<" , "<<bitacc);
		while(digit_bits<=bitacc)
		{
			const unsigned cod = digit_mask & acc;
			out.push_back(lo[cod]);
			out.push_back(hi[cod]);
			acc>>=digit_bits;
			bitacc-=digit_bits;
TRACE("pushed "<<lo[cod]<<" : "<<hi[cod]<<" : "<<cod<<" , "<<acc<<" , "<<bitacc);
		}
	}

	if(0 != bitacc)
	{
		const unsigned cod = digit_mask & acc;
		out.push_back(lo[cod]);
		if(7<=bitacc)
		{
			out.push_back(hi[cod]);
			TRACE("push_ "<<lo[cod]<<" : "<<hi[cod]<<" : "<<cod<<" , "<<acc<<" , "<<bitacc);
		}
	}
	
	return;
}

//------------------------------------------------------------------------------

void decode(const std::string & in,std::vector<unsigned char> & out)
{
	out.clear();
	out.reserve(char_bits*in.size()/digit_bits);
	TRACE("\ndecode\n");
	
	unsigned acc=0;
	int bitacc=0;
	short lower=-1;
	
	for (auto & n:in)
	{
		if(-1==lower)
		{
			lower=n-'!';
			continue;
		}
		acc|=hilo[n-'!'][lower]<<bitacc;
		bitacc+=digit_bits;
		lower=-1;
		
		while(char_bits<=bitacc)
		{
			out.push_back(0xFF & acc);
			acc>>=char_bits;
			bitacc-=char_bits;
		}
	}
	
	if(-1!=lower)
	{
		acc<<=digit_bits;
		acc|=hilo[0][lower];
		bitacc+=7;
	}
	
	while(char_bits<=bitacc)
	{
		out.push_back(0xFF & acc);
		acc>>=char_bits;
		bitacc-=char_bits;
	}
	
	return;
}
}

//------------------------------------------------------------------------------

int main()
{
	for(unsigned n=0, hi=0,lo=0;n<base91::digit_size;++n)
	{
		base91::lo[n]='!'+lo;
		base91::hi[n]='!'+hi;
		base91::hilo[hi][lo]=n;
		if(base91::base==(++lo))
		{
			hi++;
			lo=0;
		}
	}
	
	srand(time(nullptr));
	std::vector<unsigned char> in;//{0,143,10,15};
	const unsigned size=10;//rand()%15;
	for (unsigned n=0;n<size;++n)
		in.push_back(rand()%256);
	std::string out;
	base91::encode(in,out);
	std::cout<<out<<std::endl;
	
	std::vector<unsigned char> test;
	base91::decode(out,test);

	if(in.size() != test.size())
	{
		TRACE(in.size() <<"!="<< test.size());	
		return EXIT_FAILURE;
	}
	
	for (unsigned n=0;n<size;++n)
	{
		if(in[n]!=test[n])
		{
			TRACE(n<<" ! "<<static_cast<short>(in[n])<<" != "<< static_cast<short>(test[n]));
		}
		else
		{
		TRACE(n<<" : "<<static_cast<short>(in[n])<<" == "<< static_cast<short>(test[n]));
		}
	}
	

	return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------

