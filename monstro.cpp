
//#define _GLIBCXX_USE_CXX11_ABI 1
#include <limits>
#include <cstdint>
#include <cinttypes>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>


int test(const int c,int n);

int main(int ac,char **ap)
{
	const std::vector<std::string> ops
	{
		"n++;",
		"n--;",
		"n+=c;",
		"n-=c;",
		"n<<=(c&3);",
		"n>>=(c&3);",
		"n^=c;",
		"n%=c;",
		"n*=c;",
		"n/=c;",
		"n|=c;",
		"n&=c;"
	};

	const std::vector<int> idx{0,1,2,3,4,5,6,7,8};//,9,10,11};

	{
		int f=0;
		std::vector<int> i=idx;
		do
		{
			std::printf("int f_%08x(const int c, int n){",f);

			for (auto &n : i)
			{
				std::printf("%s",ops[n].c_str());
			}
			std::printf("return n;};\n");
			++f;
		}
		while (std::next_permutation(i.begin(),i.end()));
	}
	
	{
		int f=0;
		std::vector<int> i=idx;
		
		std::printf("#include <cstdlib>\n#include <ctime>\n#include <cstdio>\n");

		std::printf("int main(){"
			"std::srand(std::time(nullptr));"
			"const int c=std::rand();"
			"int n=std::rand();"
			"\n"
			);
		
		do
		{
			std::printf("n=f_%08x(c,n);\n",f);
			++f;
		}
		while (std::next_permutation(i.begin(),i.end()));
		
		std::printf("std::printf(\"%%d\",n);\nreturn 0;}"
			);
	}
	
	
	//    std::srand(std::time(nullptr)); 
	//    int n=std::rand();
	//    std::printf("\n%d\n",r);
	//    return test(r);
	return 0;
}
