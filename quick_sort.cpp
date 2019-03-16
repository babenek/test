//
// Created by user on 16.03.19.
//

#include <chrono>
#include <random>
#include <iostream>


void print(const int a, const int b, long long v[])
{
//	for (int n = a; n <= b; ++n)
//	{
//		std::cout << n << ":" << v[n] << std::endl;
//	}
}


long long hash(const int a, const int b, long long v[])
{
	long long H = v[b];
	for (int n = a; n < b; ++n)
	{
		H ^= v[n];
	}
	return H;
}

const char *test(const int a, const int b, long long v[], const long long h)
{
	static const char *pass = "PASS";
	static const char *fail = "FAIL";

	if (h == hash(a, b, v))
	{
		for (int n = a; n < b; ++n)
		{
			if (v[n] > v[n + 1])
				return fail;
		}
		return pass;
	}

	return fail;
}

void swap(const int a, const int b, long long v[])
{
	const long long t = v[a];
	v[a] = v[b];
	v[b] = t;
}

void bubble_sort(const int a, const int b, long long v[])
{
	for (int n = a; n <= b; ++n)
	{
		int bubble_m = n;
		long long bubble = v[n];
		for (int m = n + 1; m <= b; ++m)
		{
			if (v[m] < bubble)
			{
				bubble = v[m];
				bubble_m = m;
			}
		}
		if (n != bubble_m)
		{
			swap(n, bubble_m, v);
		}
	}
}

void oth_sort(const int a, const int b, long long v[])
{
	bool f = true;
	while (f)
	{
		f = false;
		for (int n = a; n < b; ++n)
		{
			if (v[n] > v[n + 1])
			{
				swap(n, n + 1, v);
				f = true;
			}
		}
	}
}

void quick_sort(const int A, const int B, long long v[])
{
	if (A >= B)
		return;
	long long p = v[(A + (B - 1))>>1];

	int a = A;
	int b = B;
	do
	{
		while (v[a] < p)
			++a;

		while (v[b] > p)
			--b;

		if (v[a] > v[b])
		{
			swap(a, b, v);
			//			++a;
		}
	}
	while (a < b);

	quick_sort(A, a, v);

	quick_sort(a + 1, B, v);

}


int main()
{
	const int lim = 1 << 19;
	long long quick[lim];
//	long long bubble[lim];
//	long long change[lim];
//	long long oth[lim];

	long long H = 0;
	std::mt19937_64 generator(time(0));
	{
		const auto start = std::chrono::system_clock::now();
		for (int n = 0; n < lim; ++n)
		{
			//oth[n] = change[n] = bubble[n] =
			quick[n] = generator();
		}
		H = hash(0, lim - 1, quick);
		const auto duration = std::chrono::system_clock::now() - start;
		std::cout << test(0, lim - 1, quick, H) << " filled:"
				  << std::chrono::duration_cast<std::chrono::milliseconds>(
					  duration).count() << std::endl;
		std::cout << "hash:" << H << std::endl;
	}
	//	print(0, lim - 1, bubble);
	//	{
	//		const auto start = std::chrono::system_clock::now();
	//		bubble_sort(0, lim - 1, bubble);
	//		const auto duration = std::chrono::system_clock::now() - start;;
	//		std::cout << test(0, lim - 1, bubble, H) << " bubble:"
	//				  << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
	//	}
	//	{
	//		const auto start = std::chrono::system_clock::now();
	//		oth_sort(0, lim - 1, oth);
	//		const auto duration = std::chrono::system_clock::now() - start;;
	//		std::cout << test(0, lim - 1, oth, H) << " oth:"
	//				  << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
	//	}
	{
		const auto start = std::chrono::system_clock::now();
		quick_sort(0, lim - 1, quick);
		const auto duration = std::chrono::system_clock::now() - start;;
		std::cout << test(0, lim - 1, quick, H) << " quick:"
				  << std::chrono::duration_cast<std::chrono::milliseconds>(
					  duration).count() << std::endl;
	}
	print(0, lim - 1, quick);

	return 0;
}