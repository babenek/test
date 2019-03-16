//
// Created by user on 16.03.19.
//

#include <chrono>
#include <random>
#include <iostream>


template<typename T>
void print(const T *a, const T *b)
{
	for (const T *n = a; n != b; ++n)
	{
		std::cout << n << ":" << *n << std::endl;
	}
	std::cout << b << ":" << *b << std::endl;
}

template<typename T>
T hash(const T *a, const T *b)
{
	T H = *b;
	for (const T *n = a; n != b; ++n)
	{
		H ^= *n;
	}
	return H;
}

template<typename T>
bool verify(const T *a, const T *b, const T h)
{
	return (h == hash(a, b));
}


template<typename T>
bool test(const T *a, const T *b)
{
	for (const T *n = a; n != b; ++n)
	{
		if (*n > *(n + 1))
			return false;
	}
	return true;
}

template<typename T>
void swap(T *a, T *b)
{
	const T t = *a;
	*a = *b;
	*b = t;
}


template<typename T>
void qsort(T *a, T *b)
{
	if (a >= b)
	{
		return;
	}
	if ((a + 1) == b)
	{
		if (*a > *b)
			swap(a, b);
		return;
	}

	T *A = a;
	T *B = b;
	const T *c = a + ((b - a) >> 1);
	T P = *c;

	//const T S = A / 3 + B / 3 + P / 3; todo: may be used precalc statistic...

	do
	{
		while (*a < P)
			++a;

		while (*b > P)
			--b;

		if (a < b)
		{
			swap(a, b);
			++a;
			--b;
		}
	}
	while (a < b);


	if (A < b)
		qsort(A, b);
	if (a < B)
		qsort(a, B);
}

int main()
{

	const unsigned lim = 1 << 22;

	typedef unsigned short T;
	T *V = new T[lim];//= {5, 7, 3};
	T *a = V;
	T *b = V + lim - 1;

	std::mt19937_64 generator(time(0));


	double S = 0;
	const unsigned stat_size = 100;
	long long stat[stat_size];
	for (unsigned s = 0; s < stat_size; ++s)
	{

		for (int n = 0; n < lim; ++n)
		{
			V[n] = generator();
		}
		const T H = hash(V, b);

		//std::cout << H << std::endl;
		//print(0, lim - 1, V);
		if (test(V, b))
		{
			//std::cout << "sorted?!?!?!" << std::endl;
			continue;
		}


		const auto start = std::chrono::system_clock::now();
		qsort(a, b);
		const auto duration = std::chrono::system_clock::now() - start;
		if (not verify(a, b, H))
		{
			std::cout << "FAIL array" << std::endl;
			return 1;
		}
		if (not test(a, b))
		{
			std::cout << "FAIL sort" << std::endl;
			print(a, b);
			return 1;
		}
		stat[s] = std::chrono::duration_cast<std::chrono::milliseconds>(
			duration).count();
		S += stat[s];
	}

	S /= (1.0 * stat_size);
	std::cout << " AVG=" << S << std::endl;


	double Z = 0;
	for (unsigned s = 0; s < stat_size; ++s)
	{
		const double t = (stat[s] - S);
		Z += (t * t);
	}
	std::cout << " SIGM=" << sqrt(Z / (1.0 * stat_size)) << std::endl;

	delete[]V;
	return 0;
}