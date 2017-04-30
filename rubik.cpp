#include <cstdio>
#include <random>
#include <cmath>
#include <string>
#include <stdexcept>
#include <cassert>


#define PACKAGES 128
//------------------------------------------------------------------------------
int sum(const char r[6][8])
{
	int sum=0;
	for (unsigned n=0;n<6;++n)
		for (unsigned m=0;m<8;++m)
			sum+=r[n][m];
	return sum;
}

//------------------------------------------------------------------------------

unsigned short hashing(const unsigned r[4])
{
	const unsigned hash=r[0]^r[1]^r[2]^r[3];
	return (hash^(hash>>16));
}
//------------------------------------------------------------------------------

unsigned short hashing(const char r[6][8])
{
	unsigned hash=0;
	unsigned sum=0;
	for (unsigned n=0;n<6;++n)
	{
		for (unsigned m=0;m<8;++m)
		{
			hash ^= (r[n][m])<<(n+m);
			if(r[n][m] == n) 
				sum++;
		}
	}
	return ((0x03&sum) | (hash<<2));
}

//------------------------------------------------------------------------------

bool turn(const int q, char r[6][8])
{
	char t[6][8];	
	
	for (unsigned n=0;n<6;++n)
	{
		if(q==n) 
			continue; 
		for (unsigned m=0;m<8;++m)
			t[n][m] = r[n][m];
	}
	
	for(int n=0;n<8;++n)
	{
		t[q][n]=r[q][(n+6)%8];
	}
	
	switch(q)
	{
	case 0:
		t[1][0]=r[4][0];
		t[1][1]=r[4][1];
		t[1][2]=r[4][2];

		t[2][0]=r[1][0];
		t[2][1]=r[1][1];
		t[2][2]=r[1][2];

		t[3][0]=r[2][0];
		t[3][1]=r[2][1];
		t[3][2]=r[2][2];

		t[4][0]=r[3][0];
		t[4][1]=r[3][1];
		t[4][2]=r[3][2];
	break;
	
	case 1:
		t[0][0]=r[2][2];
		t[0][1]=r[2][3];
		t[0][2]=r[2][4];

		t[2][2]=r[5][2];
		t[2][3]=r[5][3];
		t[2][4]=r[5][4];

		t[4][0]=r[0][2];
		t[4][6]=r[0][0];
		t[4][7]=r[0][1];

		t[5][2]=r[4][6];
		t[5][3]=r[4][7];
		t[5][4]=r[4][0];
	break;
	
	case 2:
		t[0][2]=r[3][2];
		t[0][3]=r[3][3];
		t[0][4]=r[3][4];

		t[1][0]=r[0][4];
		t[1][6]=r[0][2];
		t[1][7]=r[0][3];

		t[3][2]=r[5][0];
		t[3][3]=r[5][1];
		t[3][4]=r[5][2];

		t[5][0]=r[1][6];
		t[5][1]=r[1][7];
		t[5][2]=r[1][0];
	break;
	
	case 3:
		t[0][4]=r[4][2];
		t[0][5]=r[4][3];
		t[0][6]=r[4][4];

		t[2][0]=r[0][6];
		t[2][6]=r[0][5];
		t[2][7]=r[0][4];

		t[4][2]=r[5][6];
		t[4][3]=r[5][7];
		t[4][4]=r[5][0];

		t[5][0]=r[2][0];
		t[5][6]=r[2][6];
		t[5][7]=r[2][7];
	break;
	
	case 4:
		t[0][0]=r[1][4];
		t[0][6]=r[1][3];
		t[0][7]=r[1][2];

		t[1][2]=r[5][4];
		t[1][3]=r[5][5];
		t[1][4]=r[5][6];

		t[3][0]=r[0][0];
		t[3][6]=r[0][6];
		t[3][7]=r[0][7];

		t[5][4]=r[3][6];
		t[5][5]=r[3][7];
		t[5][6]=r[3][0];
	break;
	
	case 5:
		t[1][4]=r[2][4];
		t[1][5]=r[2][5];
		t[1][6]=r[2][6];

		t[2][4]=r[3][4];
		t[2][5]=r[3][5];
		t[2][6]=r[3][6];

		t[3][4]=r[4][4];
		t[3][5]=r[4][5];
		t[3][6]=r[4][6];

		t[4][4]=r[1][4];
		t[4][5]=r[1][5];
		t[4][6]=r[1][6];
	break;
	}
	
	hashing(t);
	
	for (unsigned n=0;n<6;++n)
		for (unsigned m=0;m<8;++m)
			r[n][m] = t[n][m];
	
	return true;
}

//------------------------------------------------------------------------------

bool check(const char r[6][8])
{
	bool res=true;
	for (unsigned n=0;n<6 && res;++n)
		for (unsigned m=0;m<8 && res;++m)
			res = (n == r[n][m]);
	return res;
}

//------------------------------------------------------------------------------

void init(char r[6][8])
{
	for (unsigned n=0;n<6;++n)
		for (unsigned m=0;m<8;++m)
			r[n][m] = n;
	return;
}

//------------------------------------------------------------------------------

void print(const char r[6][8])
{
	printf("\n");
	for (unsigned n=0;n<6;++n)
	{
		for (unsigned m=0;m<8;++m) 
			printf("%d",r[n][m]);
		if (5!=n) 
			printf(" : ");
	}
	return;
}

//------------------------------------------------------------------------------

void pack(const char r[6][8], unsigned p[4])
{
	unsigned t[6]={0,};
	for (unsigned n=0;n<6;++n)
	{
		for (unsigned m=0;m<8;++m)
		{
			static const unsigned po[8]={1, 6, 6*6, 6*6*6, 6*6*6*6, 6*6*6*6*6, 6*6*6*6*6*6, 6*6*6*6*6*6*6};

			t[n]+=r[n][m]*po[m];	
		}
		//assert(t[n]<1679616);
	}
	p[0]=t[0] | (t[1]<<21);
	p[1]=(t[1]>>11) | (t[2]<<11);
	p[2]=t[3] | (t[4]<<21);
	p[3]=(t[4]>>11) | (t[5]<<11);
}

//------------------------------------------------------------------------------

void solve(char r[6][8])
{

	return;
}

//------------------------------------------------------------------------------

void place(const unsigned p[4], const unsigned short m, unsigned *packs)
{
	for(unsigned n=0;n<4;++n)
		*(packs+4*m+n)=p[n];
}
//------------------------------------------------------------------------------

bool found(const unsigned p[4], const unsigned short s, const unsigned *packs)
{
	bool res;
	for(unsigned m=0;m<s;++m)
	{
		res=true;
		for(unsigned n=0;n<4 && res;++n)
			res &= (p[n] == *(packs+4*m+n));
		if (res)
			break;
	}		
	return res;
}
//------------------------------------------------------------------------------

bool exists(const unsigned p[4], unsigned short hashes[65536],unsigned *packs[65536])
{
	const unsigned hash=hashing(p);
	if(hashes[hash]==0)
	{
		hashes[hash]=1;
		place(p,0,packs[hash]);
		printf(" first added %4x",hash);		
	}
	else
	{
		if(found(p,hashes[hash],packs[hash]))
		{
			printf(" duplicate %4x",hash);
			return true;
		}
		else
		{
			if(hashes[hash]<PACKAGES)
			{
				place(p,hashes[hash],packs[hash]);		
				hashes[hash]++;
				printf(" added %4x N=%d",hash,hashes[hash]);
			}
			else 
				throw std::domain_error("limit packs");
		}
	}
	return false;
}

//------------------------------------------------------------------------------

int main()
{
	std::srand(time(0));

	//printf ("\n%d, %d, %d\n",power(1,0),power(6,8),power(2,31));
	
	
	char s[6][8];
	unsigned short hashes[65536]={0,};
	unsigned *packs[65536];	
	for(unsigned n=0;n<65536;++n)
		packs[n]=new unsigned[4*PACKAGES];
	
	init(s);
	//print(s);
	//const unsigned short initialHash=hashing(s);
	//hashes[initialHash]++;
	//printf("   %d",initialHash);
	
	for(int l=0;l<5555555;++l)
	{
		turn(std::rand()%6,s);
		//turn(0,s);
		//print(s);
		//assert(120==sum(s));
		//const unsigned short hash=hashing(s);
		//hashes[hash]++;
		//printf("   %d   %d",hashes[hash],hash);
		
		unsigned p[4]={0,0,0,0};
		pack(s,p);
		printf("\n%9d : %8x, %8x, %8x, %8x",l,p[0],p[1],p[2],p[3]);
		
		if(exists(p,hashes,packs))
		{
			printf("\n");
		}
		
		if(check(s))
		{
			printf("\n   solved!");
			break;
		}
			
	}
	printf("\n");
	
/*	
	unsigned long long S=0;
	for (unsigned n=0;n<65536;++n)
		S+=hashes[n];
	const double V=S/65536.0;	
	double sm=0;
	for (unsigned n=0;n<65536;++n)
		sm+=(V-hashes[n])*(V-hashes[n]);
	const double v=sqrt(static_cast<double>(sm/65536.0));
	printf("\naverage=%f, div=%f",V,v);
*/	
	printf("\n");
	
	
	for(unsigned n=0;n<65536;++n)
		delete [] packs[n];
	return 0;
}

//------------------------------------------------------------------------------

