#include <cstdio>
#include <random>

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

int hashing(const char r[6][8])
{
	int hash=0;
	int sum=0;
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

unsigned power(const unsigned a,const unsigned p)
{
	unsigned res=1;
	for (unsigned n=0;n<p;++n)
		res*=a;
	return res;
}

//------------------------------------------------------------------------------

void pack(const char r[6][8], unsigned short a[6], unsigned int b[6])
{
	for (unsigned n=0;n<6;++n)
	{
		unsigned val=0; 
		for (unsigned m=0;m<8;++m)
			val+=r[n][m]*power(6,m);
		a[]
	}
}

//------------------------------------------------------------------------------

void solve(char r[6][8])
{

	return;
}

//------------------------------------------------------------------------------

int main()
{
	std::srand(time(0));

	//printf ("\n%d, %d, %d\n",power(1,0),power(6,8),power(2,31));
	
	
	char s[6][8];
	
	int hashes[65536]={0,};

	init(s);
	print(s);
	const unsigned short initialHash=hashing(s);
	hashes[initialHash]++;
	printf("   %d",initialHash);
	
	for(int n=0;n<1000000;++n)
	{
		turn(std::rand()%6,s);
		//print(s);
		if(120!=sum(s)) exit(EXIT_FAILURE);
		const unsigned short hash=hashing(s);
		hashes[hash]++;
		//printf("   %d   %d",hashes[hash],hash);
	}
	printf("\n");
	for (unsigned n=0;n<65536;++n)
	{
		printf("%d:%d",n,hashes[n]);
		if (hashes[n]>0)
			printf("\n");
		else
	 		printf(" ");
	}
	printf("\n");
	return 0;
}

//------------------------------------------------------------------------------
