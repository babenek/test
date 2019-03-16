//
// Created by user on 16.03.19.
//

#include <chrono>
#include <random>
#include <iostream>


const char *test(const int a, const int b, long long v[])
{
	static const char *pass = "PASS";
	static const char *fail = "FAIL";
	for (int n = a; n < b; ++n)
	{
		if (v[n] < v[n + 1])
			return fail;
	}
	return pass;
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
			if (v[m] > bubble)
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

void quick_sort(const int a, const int b, long long v[])
{
	for (int n = a; n <= b; ++n)
	{
		std::cout << v[n] << " ";
	}

}


int main()
{
	const int lim = 1 << 16;
	long long bubble[lim];
	long long quick[lim];
	long long change[lim];
	long long oth[lim];

	std::mt19937_64 generator;
	{
		const auto start = std::chrono::system_clock::now();
		for (int n = 0; n < lim; ++n)
		{
			oth[n] = change[n] = quick[n] = bubble[n] = generator();
		}
		const auto duration = std::chrono::system_clock::now() - start;;
		std::cout << test(0, lim - 1, bubble) << " filled:"
				  << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
	}
	{
		const auto start = std::chrono::system_clock::now();
		bubble_sort(0, lim - 1, bubble);
		const auto duration = std::chrono::system_clock::now() - start;;
		std::cout << test(0, lim - 1, bubble) << " bubble:"
				  << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
	}

	{
		const auto start = std::chrono::system_clock::now();
		quick_sort(0, lim - 1, quick);
		const auto duration = std::chrono::system_clock::now() - start;;
		std::cout << test(0, lim - 1, quick) << " quick:"
				  << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
	}

	return 0;
}