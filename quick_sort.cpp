//
// Created by user on 16.03.19.
//

#include <chrono>
#include <random>
#include <iostream>

#define NDEBUG

#include <cassert>

#define CALCULATE_RECURSION (1)
#if CALCULATE_RECURSION
static size_t rec = 0;
static size_t maxrec = 0;
#endif


template<typename T>
const T *quick_search(const T *a, const T *b, const T X)
{
#if CALCULATE_RECURSION
	rec++;
	if (rec > maxrec)
		maxrec = rec;
#endif
	const T *x = (a + ((b - a) >> 1));
	T Y = *x;
	if (X < Y)
	{
		if (a == x)
		{
			return nullptr;
		}
		else
		{
			return quick_search(a, x - 1, X);
		}
	}
	else if (Y < X)
	{
		if (b == x)
		{
			return nullptr;
		}

		else
		{
			return quick_search(x + 1, b, X);
		}
	}
	else// (X == Y)
	{
		return x;
	}
}

//-----------------------------------------------



template<typename T>
const T *brute_search(const T *a, const T *b, const T X)
{
	for (const T *x = a; x <= b; ++x)
	{
		if (X == *x)
			return x;
	}
	return nullptr;
}


//---------------------------------------------


template<typename T>
void print(const T *a, const T *b)
{
	for (const T *n = a; n != b; ++n)
	{
		std::cout << n << ": " << *n << std::endl;
	}
	std::cout << b << ": " << *b << std::endl;
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
long long int sum(const T *a, const T *b)
{
	long long int S = *b;
	for (const T *n = a; n != b; ++n)
	{
		S += *n;
	}
	return S;
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
	//std::cout << "swap: " << a << " <-> " << b << std::endl;
	const T t = *a;
	*a = *b;
	*b = t;
}

template<typename T>
void sort(T *a, T *b)
{
	if (*b < *a)
		swap(a, b);
}

template<typename T>
void sort(T *a, T *b, T *c)
{
	T A = *a;
	T B = *b;
	T C = *c;

	char abc = 0;
	abc |= ((A < B) ? 001 : 0) | ((B < A) ? 010 : 0);
	abc |= ((B < C) ? 002 : 0) | ((C < B) ? 020 : 0);
	abc |= ((A < C) ? 004 : 0) | ((C < A) ? 040 : 0);


	switch (abc)
	{
		case 000:
			// A:1 B:1 C:1
			// A:2 B:2 C:2
			// A:3 B:3 C:3
		case 005:
			// A:1 B:2 C:2
			// A:1 B:3 C:3
			// A:2 B:3 C:3
		case 006:
			// A:1 B:1 C:2
			// A:1 B:1 C:3
			// A:2 B:2 C:3
		case 007:
			// A:1 B:2 C:3
			break;

		case 012:
			// A:3 B:2 C:3
			// A:2 B:1 C:2
			// A:3 B:1 C:3
		case 016:
			// A:2 B:1 C:3
			*a = B;
			*b = A;
			break;


		case 021:
			// A:1 B:2 C:1
			// A:1 B:3 C:1
			// A:2 B:3 C:2
		case 025:
			// A:1 B:3 C:2
			*b = C;
			*c = B;
			break;


		case 050:
			// A:2 B:1 C:1
			// A:3 B:1 C:1
			// A:3 B:2 C:2
		case 060:
			// A:2 B:2 C:1
			// A:3 B:3 C:1
			// A:3 B:3 C:2
		case 070:
			// A:3 B:2 C:1
			*a = C;
			*c = A;
			break;


		case 052:
			// A:3 B:1 C:2
			*a = B;
			*b = C;
			*c = A;
			break;

		case 061:
			// A:2 B:3 C:1
			*a = C;
			*b = A;
			*c = B;
			break;

		default:
		{
			std::cerr << "wrong case:" << std::oct << static_cast<short>(abc) //
					  << " A:" << A << " B:" << B << " C:" << C << std::endl;
		}
			break;
	}
}


//------------------------------------------------------------------------------

template<typename T>
void qsort3(T *aa, T *bb)
{

#if CALCULATE_RECURSION
	rec++;
	if (rec > maxrec)
		maxrec = rec;
#endif
	if (aa >= bb)
	{
#if CALCULATE_RECURSION
		rec--;
#endif
		return;
	}
	if ((aa + 1) == bb)
	{
		//std::cout << "duo sort: " << aa << " , " << bb << std::endl;
		sort(aa, bb);
#if CALCULATE_RECURSION
		rec--;
#endif
		return;
	}
	if ((aa + 2) == bb)
	{
		// std::cout << "triple sort: " << aa << " , " << bb << std::endl;

		sort(aa, aa + 1, bb);
#if CALCULATE_RECURSION
		rec--;
#endif
		return;
	}
	// todo case of 3 elements
	T *a = aa;
	T *b = bb;

	T *x = (a + ((b - a) >> 1));

	sort(a, x, b);

	T A = *a;
	T B = *b;
	const T X = *x;
	//std::cout << "quick sort: " << aa << " , " << bb << " : " << X << std::endl;

	T *_a = x;
	T *b_ = x;
	while (true)
	{
		while (a < _a)
		{
			while (A < X)
			{
				++a;
				A = *a;
			}
			while (A == X)
			{
				--_a;
				if (_a < a)
				{
					_a = a;
					break;
				}
				//swap(a, _a);
				A = *_a;
				*_a = X;
				*a = A;
			}
			if (X < A)
				break;
		}


		while (b_ < b)
		{
			while (X < B)
			{
				--b;
				B = *b;
			}
			while (B == X)
			{
				++b_;
				if (b < b_)
				{
					b_ = b;
					break;
				}
				//swap(b, b_);
				B = *b_;
				*b_ = X;
				*b = B;
			}
			if (B < X)
				break;
		}

		if (a < _a and b_ < b)
		{
			assert(*_a == X);
			assert(*b_ == X);
			assert(X < A);
			assert(B < X);
			assert(*a == A);
			assert(*b == B);
			*b = A;
			*a = B;
			++a;
			--b;
			A = *a;
			B = *b;
		}
		else if (a == _a and b_ < b)
		{
			assert(*a == X);
			assert(*_a == X);
			assert(*b == B);
			assert(*b_ == X);
			assert(B < X);
			++b_;
			if (b_ < b)
			{
				*a = B;
				++a;
				++_a;
				B = *b_;
				*b = B;
				*b_ = X;
			}
			else
			{
				*a = B;
				*b = X;
				break;
			}
		}
		else if (a < _a and b_ == b)
		{
			assert(*a == A);
			assert(X < A);

			assert(*b == X);
			assert(*b_ == X);
			--_a;
			if (a < _a)
			{
				*b = A;
				--b;
				--b_;
				A = *_a;
				*a = A;
				*_a = X;
			}
			else
			{
				*b = A;
				*a = X;
				break;
			}
		}
		else
		{
			assert(b == b_);
			assert(a == _a);
			break;
		}
	}


	assert(b == b_);
	assert(a == _a);

	if (aa < a)
		qsort3(aa, a);
	if (b < bb)
		qsort3(b, bb);
#if CALCULATE_RECURSION
	rec--;
#endif
}

//------------------------------------------------------------------------------

template<typename T>
void qsort2(T *a, T *b)
{
#if CALCULATE_RECURSION
	rec++;
	if (rec > maxrec)
		maxrec = rec;
#endif
	if (not(a < b))
	{
#if CALCULATE_RECURSION
		rec--;
#endif
		return;
	}
	if ((a + 1) == b)
	{
		if (*b < *a)
			swap(a, b);
#if CALCULATE_RECURSION
		rec--;
#endif
		return;
	}

	T *A = a;
	T *B = b;
	const T *c = a + ((b - a) >> 1);
	T P = *c;

	do
	{
		while (*a < P)
			++a;

		while (P < *b)
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
		qsort2(A, b);
	if (a < B)
		qsort2(a, B);
#if CALCULATE_RECURSION
	rec--;
#endif
}

//------------------------------------------------------------------------------

int main_qsort()
{

	const unsigned lim = 1500000000;
	typedef int T;
	/*
	const unsigned lim = 600000000;
	typedef long long int T;
	brutesearch
	AVG=1362.21
	SIGM=3.54484
quick
	const unsigned lim = 1500000000;
	typedef int T;
 AVG=0
 SIGM=0
 MAXREC=31
	*/
	/*

	10000000

	unsigned

	qs3
	AVG=2397.97
	SIGM=72.0195

	qs2
	AVG=1825.08
	SIGM=14.4573


	char
	qs3
	AVG=665.82
	SIGM=21.6039

	qs2
	AVG=1196.53
	SIGM=10.4244

	short
	qs2
	AVG=1502.58
	SIGM=10.5482
	qs3
	AVG=1485.86
	SIGM=23.222

	1000000
	long long int
	qs3
	AVG=201.7
	SIGM=2.52784
	qs2
	AVG=164.03
	SIGM=2.44726

	-O
	qs3
	AVG=108.32
	SIGM=10.4727
	qs2
	AVG=74.94
	SIGM=2.17633
	*/
	T *V = new T[lim];//
	//const T W[lim] = {9, 8, 7, 6};
	T *a = V;
	T *b = V + lim;
	// test password 'ndU6t2fe6^2'

	std::mt19937_64 generator(time(nullptr));
	assert(0);
	double S = 0;
	const unsigned stat_size = 100;
	long long stat[stat_size];

	do
	{
		for (int n = 0; n < lim; ++n)
		{
			auto X = generator();
			V[n] = X;
		}

		const T H = hash(a, b);
		const auto sm = sum(a, b);
		//std::cout << H << std::endl;
		if (test(V, b))
		{
			//std::cout << "already sorted?!?!?!" << std::endl;
			continue;
		}

		std::cout << "test:" << " hash:" << H << " sum:" << sm << std::endl;

		qsort2(a, b);

		if (not verify(a, b, H) or sm != sum(a, b))
		{
			std::cout << "FAIL array" << std::endl;
			//print(a, b);
			return 1;
		}
		if (not test(a, b))
		{
			std::cout << "FAIL sort" << std::endl;
			//print(a, b);
			return 1;
		}

	}
	while (false);

#if CALCULATE_RECURSION
	maxrec = rec;
#endif

	for (unsigned s = 0; s < stat_size; ++s)
	{

#if CALCULATE_RECURSION
		rec = 0;
#endif

		const T X = *(b-3);

		const auto start = std::chrono::system_clock::now();
		const T *x = quick_search(a, b, X);
		const auto duration = std::chrono::system_clock::now() - start;

		if (nullptr == x or *x != X)
		{
			std::cout << X << " not found" << std::endl;
			return 1;
		}

		stat[s] = std::chrono::duration_cast<std::chrono::milliseconds>(
			duration).count();

		std::cout << "PASS:" << stat[s] << " msec" << std::endl;
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
#if CALCULATE_RECURSION
	std::cout << " MAXREC=" << maxrec << std::endl;
#endif
	delete[]V;
	return 0;
}
