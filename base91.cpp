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
namespace base91
{
static const unsigned base=91;
static const unsigned char_bits=8;
static const unsigned digit_bits=13;
static const unsigned digit_size=0x2000;
static const unsigned digit_mask=0x1FFF;


#define ABC91 '!','~','}','|','{','z','y','x','w','v','u','t','s','r','q','p'\
,'o','n','m','l','k','j','i','h','g','f','e','d','c','b','a','`','_','^',']'\
,'#','[','Z','Y','X','W','V','U','T','S','R','Q','P','O','N','M','L','K','J'\
,'I','H','G','F','E','D','C','B','A','@','?','>','=','<',';',':','9','8','7'\
,'6','5','4','3','2','1','0','$','.','-',',','+','*',')','(','\'','&','%'


#define DUP90(a) a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a\
,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a\
,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a

char lo[digit_size]={DUP90(ABC91), '!','~'};

#define DUP91(a) DUP90(a),a

char hi[digit_size]=
{DUP91('!'),DUP91('~'),DUP91('}'),DUP91('|'),DUP91('{'),DUP91('z'),DUP91('y')
,DUP91('x'),DUP91('w'),DUP91('v'),DUP91('u'),DUP91('t'),DUP91('s'),DUP91('r')
,DUP91('q'),DUP91('p'),DUP91('o'),DUP91('n'),DUP91('m'),DUP91('l'),DUP91('k')
,DUP91('j'),DUP91('i'),DUP91('h'),DUP91('g'),DUP91('f'),DUP91('e'),DUP91('d')
,DUP91('c'),DUP91('b'),DUP91('a'),DUP91('`'),DUP91('_'),DUP91('^'),DUP91(']')
,DUP91('#'),DUP91('['),DUP91('Z'),DUP91('Y'),DUP91('X'),DUP91('W'),DUP91('V')
,DUP91('U'),DUP91('T'),DUP91('S'),DUP91('R'),DUP91('Q'),DUP91('P'),DUP91('O')
,DUP91('N'),DUP91('M'),DUP91('L'),DUP91('K'),DUP91('J'),DUP91('I'),DUP91('H')
,DUP91('G'),DUP91('F'),DUP91('E'),DUP91('D'),DUP91('C'),DUP91('B'),DUP91('A')
,DUP91('@'),DUP91('?'),DUP91('>'),DUP91('='),DUP91('<'),DUP91(';'),DUP91(':')
,DUP91('9'),DUP91('8'),DUP91('7'),DUP91('6'),DUP91('5'),DUP91('4'),DUP91('3')
,DUP91('2'),DUP91('1'),DUP91('0'),DUP91('$'),DUP91('.'),DUP91('-'),DUP91(',')
,DUP91('+'),DUP91('*'),DUP91(')'),DUP91('('),DUP91('\''),DUP91('&'),'%','%'};

char decoder[256]=
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1

,0x5F,0x5E,0x5D,0x5C,0x5B,0x5A,0x59,0x58,0x57,0x56,0x55,0x54,0x53,0x52,0x51,0x50
,0x4F,0x4E,0x4D,0x4C,0x4B,0x4A,0x49,0x48,0x47,0x46,0x45,0x44,0x43,0x42,0x41,0x40
,0x3F,0x3E,0x3D,0x3C,0x3B,0x3A,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30
,0x2F,0x2E,0x2D,0x2C,0x2B,0x2A,0x29,0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20
,0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,0x10
,0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,-1

,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
}

char hilo[base][base]=

//------------------------------------------------------------------------------
inline char getDigit(const unsigned n)
{
	const char m=0x7F^n;
	switch(m)
	{
		case '"':
			return '!';
		break;
		case '/':
			return '#';
		break;
		case '\\':
			return '$';
		break;
		default:
			return m;
		break;
	}
}
//------------------------------------------------------------------------------
inline char getByte(const unsigned n)
{
	switch(n)
	{
		case '!':
			return 0x7f^'"';
		break;
		case '#':
			return 0x7f^'/';
		break;
		case '$':
			return 0x7f^'\\';
		break;
		default:
			return 0x7f^n;
		break;
	}
}

//char hi[digit_size]={'~',};
//char lo[digit_size]={'~',};

//unsigned short hilo[base][base]={0,};


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
			TRACE("push "<<static_cast<short>(0xFF & acc));
			out.push_back(0xFF & acc);
			acc>>=char_bits;
			bitacc-=char_bits;
			TRACE("remain "<<bitacc<<" "<<acc);
		}
	}
	
	if(-1!=lower)
	{
		TRACE(lower);
		acc|=hilo[0][lower]<<bitacc;
		TRACE(acc);
		bitacc+=7;
		TRACE("remain "<<bitacc);
	}
	
	while(char_bits<=bitacc)
	{
		TRACE("push "<<static_cast<short>(0xFF & acc));
		out.push_back(0xFF & acc);
		acc>>=char_bits;
		bitacc-=char_bits;
	}
	
	return;
}
}//namespace base91
//------------------------------------------------------------------------------
int main()
{
	for(unsigned n=0, hi=0,lo=0;n<base91::digit_size;++n)
	{
		base91::lo[n]=getDigit(lo);
		base91::hi[n]=getDigit(hi);
		base91::hilo[hi][lo]=n;
		if(base91::base==(++lo))
		{
			hi++;
			lo=0;
		}
	}
	
	srand(time(nullptr));
for(int i=0;i<1000000;++i)
{
	std::vector<unsigned char> in;//{0,143,10,15};
	const unsigned size=rand()%15;
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
			return EXIT_FAILURE;
		}
		else
		{
		TRACE(n<<" : "<<static_cast<short>(in[n])<<" == "<< static_cast<short>(test[n]));
		}
	}
}	

	return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------

