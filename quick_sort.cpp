//
// Created by user on 16.03.19.
//

#include <chrono>
#include <random>
#include <iostream>
#include <cassert>

static size_t rec = 0;
static size_t maxrec = 0;


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

	std::cout << "swap: " << a << " <-> " << b << std::endl;
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

#define RECURSION_CALC

template<typename T>
void qsort(T *aa, T *bb)
{

	std::cout << "sort: " << aa << " , " << bb << std::endl;
#ifdef RECURSION_CALC
	rec++;
#endif
	if (aa >= bb)
	{
#ifdef RECURSION_CALC
		if (rec > maxrec)
			maxrec = rec;
		rec--;
#endif
		return;
	}
	if ((aa + 1) == bb)
	{
		sort(aa, bb);
#ifdef RECURSION_CALC
		if (rec > maxrec)
			maxrec = rec;
		rec--;
#endif
		return;
	}
	if ((aa + 2) == bb)
	{
		sort(aa, aa + 1, bb);
#ifdef RECURSION_CALC
		if (rec > maxrec)
			maxrec = rec;
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
	T X = *x;
	T B = *b;

	T *_a = x - 1;
	T *b_ = x + 1;
	do
	{
		while (a < _a and A < X)
		{
			++a;
			A = *a;
			while (A == X and a < _a)
			{
				swap(a, _a);
				--_a;
				A = *a;
			}
		}
		while (b_ < b and X < B)
		{
			--b;
			B = *b;
			while (B == X and b_ < b)
			{
				swap(b, b_);
				++b_;
				B = *b;
			}
		}

		if (a < _a and b_ < b)
		{
			//			if (X < A and B < X)
			{
				swap(a, b);
				++a;
				A = *a;
				--b;
				B = *b;
			}
		}
		else if (a <= _a and b_ == b)
		{
			swap(_a, b_);
			swap(a, b);
			++a;
			A = *a;
			--b;
			b_ = b;
			//B = *b;
		}
		else if (a == _a and b_ <= b)
		{
			swap(b_, _a);
			swap(b, a);
			--b;
			B = *b;
			++a;
			_a = a;
		}
		else
		{
			break;
		}

	}
	while (a < _a or b_ < b);

	if (aa < a)
		qsort(aa, a);
	if (b < bb)
		qsort(b, bb);
#ifdef RECURSIONCALC
	if (rec > maxrec)
		maxrec = rec;
	rec--;
#endif
}

//------------------------------------------------------------------------------

int main()
{
//	for (int a = 1; a <= 3; ++a)
//		for (int b = 1; b <= 3; ++b)
//			for (int c = 1; c <= 3; ++c)
//			{
//				int abc[3];
//				abc[0] = a;
//				abc[1] = b;
//				abc[2] = c;
//				sort(&abc[0], &abc[1], &abc[2]);
//				if (not test(&abc[0], &abc[2]))
//				{
//					//std::cout << "FAIL sort" << std::endl;
//					//print(&abc[0], &abc[2]);
//					//return 1;
//				}
//			}
//	return 0;

	const unsigned lim = 4;

	typedef unsigned short T;
	T *V = new T[lim];//
	const T W[lim] = {2, 7, 3, 5};
	T *a = V;
	T *b = V + lim - 1;

	std::mt19937_64 generator(time(nullptr));


	double S = 0;
	const unsigned stat_size = 100;
	long long stat[stat_size];
	for (unsigned s = 0; s < stat_size; ++s)
	{
		for (int n = 0; n < lim; ++n)
		{
			V[n] =  generator()%10;
		}
		const T H = hash(V, b);

		//std::cout << H << std::endl;
		//print(0, lim - 1, V);
		if (test(V, b))
		{
			//std::cout << "sorted?!?!?!" << std::endl;
			continue;
		}


		std::cout << "-------------------" << std::endl;
		print(a, b);
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
			std::cout << "FAIL sort:" << maxrec << std::endl;
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
	std::cout << " MAXREC=" << maxrec << std::endl;

	delete[]V;
	return 0;
}